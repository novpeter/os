#include "Extensions.h"
#include <math.h>
#include <sys/types.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1000
#endif

// Define method's
int copyDir(char **arr, int am_files, char *destination, char *departure);
char *createPath(char *prefix, char *suffix);
void compareFiles(char *first_path, char *second_path);


char *createPath(char *prefix, char *suffix)
{
    const int str_len = strlen(prefix) + strlen(suffix);
    char *buffer = malloc(sizeof(char) * str_len + 2);
    
    memcpy(
        buffer,
        prefix,
        sizeof(char) * strlen(prefix));
    buffer[strlen(prefix)] = '/';
    memcpy(
        &buffer[strlen(prefix)+1],
        suffix,
        sizeof(char) * strlen(suffix));
    buffer[str_len+1] = '\0';
    return buffer;
}

int dirFiles(char *dir, char ***files)
{
    DIR *from = ex_opendir(dir);
    struct dirent *file; 
    struct stat st;
    int size = 0;
    *files = (char **)malloc(sizeof(char) * BUFFER_SIZE);
    
    // Skip . and ..
    ex_readdir(from);
    ex_readdir(from);

    while ((file = ex_readdir(from)) != NULL)
    {
        char* path = createPath(dir, (*file).d_name);
        stat(path, &st);

        if (S_ISDIR(st.st_mode))
        {
//            continue;
            char** inside_files;
            int inside_files_size = dirFiles(path, &inside_files);
            memcpy(&(*files)[size], inside_files, inside_files_size * sizeof(char));
            free(inside_files);
            size+=inside_files_size;
        }
        else
            (*files)[size++] = path;
    }

    return size;
}

void compareFiles(char *first_path, char *second_path)
{
    FILE *file1 = ex_fopen(first_path, "r");
    FILE *file2 = ex_fopen(second_path, "r");

    int symbol;

    while((symbol = fgetc(file1)) != EOF)
    {
        if(symbol != fgetc(file2))
        {
            printf("FALSE | Pid: %d | File 1: %s | File 2: %s\n", getpid(), first_path, second_path);
            return;
        }
    }
    printf(" TRUE | Pid: %d | File 1: %s | File 2: %s\n", getpid(), first_path, second_path);
    fclose(file1);
    fclose(file2);
}


int main(int argc, char *argv[])
{
    if (argc < 3) {
        ex_puts("Wrong amount of arguments\n");
        return EXIT_FAILURE;
    }

    char **dir1_file_paths;
    char **dir2_file_paths;

    int size1 = dirFiles(argv[1], &dir1_file_paths);
    int size2 = dirFiles(argv[2], &dir2_file_paths);

    int max_pids_count = atoi(argv[3]);

    int counter = 0;
    pid_t current_pid = getpid();

    for (int i = 0; i < size1; i++)
    {
        for (int j = 0; j < size2; j++)
        {
            if(current_pid) {
                if (counter < max_pids_count  || counter == size1 - i) {
                    counter++;
                    current_pid = fork();
                } else {
                    wait(WAIT_ANY);
                    counter--;
                }
            } else {
                
                compareFiles(dir1_file_paths[i], dir2_file_paths[j]);
                return EXIT_SUCCESS;
            }
        }
    }
        

    return EXIT_SUCCESS;
}

/*
Написать программу поиска одинаковых по их содержимому файлов в двух каталогов, например, Dir1 и Dir2. Пользователь задаёт имена Dir1 и Dir2. В результате работы программы файлы, имеющиеся в Dir1, сравниваются с файлами в Dir2 по их содержимому. Процедуры сравнения должны запускаться в отдельном процессе для каждой пары сравниваемых файлов. Каждый процесс выводит на экран свой pid, имя файла, общее число просмотренных байт и результаты сравнения. Число одновременно работающих процессов не должно превышать N (вводится пользователем).
*/
