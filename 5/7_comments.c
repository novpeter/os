#include "Extensions.h"
#include <math.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1000
#endif

// Define method's
void copyFiles(char **files, char *departure, char *destination, int am_files);
int dirFiles(char *dir, char ***files);
void copyDir(char **arr, int am_files, char *destination, char *departure);
int copyFile(char *dep, char *dest);
char *createPath(char *prefix, char *suffix);
int file_comparator_lex(const void *first, const void *second);


int file_comparator_lex(const void *a, const void *b)
{
    const char *first = *(const char **)a;
    const char *second = *(const char **)b;
    const int len = strlen(first) > strlen(second) ? strlen(second) : strlen(first);
    for (int i = 0; i < len; i++)
        if (first[i] - second[i])
            return first[i] - second[i];
    return strlen(first) - strlen(second);
}

/*Сортировка по размеру*/
/*Arr - массив названий файлов*/
/*Size - размер этого массива arr*/
void bubble_sort(char **arr, int size, char *dir)
{
    int flag = 1;
    struct stat st_1;
    struct stat st_2;

    while (flag)
    {
        flag = 0;
        for (int i = 1; i < size; i++)
        {
            // Берем инфу о файле по его пути
            stat(createPath(dir, arr[i - 1]), &st_1);
            stat(createPath(dir, arr[i]), &st_2);
            if (st_1.st_size - st_2.st_size > 0)
            {
                char *temp = arr[i - 1];
                arr[i - 1] = arr[i];
                arr[i] = temp;
                flag = 1;
            }
        }
    }
}

/*Создать путь до файлы*/
/*Префикс - путь до директории*/
/*Суффикс - Навзвание файла*/
char *createPath(char *prefix, char *suffix)
{
    const int str_len = strlen(prefix) + strlen(suffix);
    char *buffer = malloc(sizeof(char) * str_len + 2);
    
    //мемори копи (куда/откуда/сколько)
    // скопировать в буффер префикс
    memcpy(
        buffer,
        prefix,
        sizeof(char) * strlen(prefix));
    buffer[strlen(prefix)] = '/';
    memcpy(
        &buffer[strlen(prefix)+1],
        suffix,
        sizeof(char) * strlen(suffix));
    buffer[str_len+1] = '\0'; //нулевой байт в конце - путь законченный 
    puts(buffer);
    return buffer;
}

/*Копирует файл*/
/*Передаем пути*/
int copyFile(char *from, char *to)
{
    FILE *file_read_from = m_fopen(from, "r");
    FILE *file_write_to = m_fopen(to, "w");
    struct stat stats;
    stat(from, &stats);

    // буффер для копирования. 1 байт в чаре
    char *buffer = malloc(BUFFER_SIZE * sizeof(char));
    
    int size = 1;
    while (size)
    {
        m_gets(buffer, BUFFER_SIZE, file_read_from);
        size = strlen(buffer);
        m_fputs(buffer, file_write_to);
    }
    
    m_fclose(file_read_from);
    m_fclose(file_write_to);
    chmod(to, stats.st_mode); // копернули права
    free(buffer); //освоодили буффер
    
    return EXIT_SUCCESS;
}

int dirFiles(char *dir, char ***files)
{
    DIR *from = m_opendir(dir);
    struct dirent *file; 
    int size = 0;
    *files = (char **)malloc(sizeof(char) * BUFFER_SIZE);
    // Skip . and ..
    m_readdir(from);
    m_readdir(from);
    // Copy cycle
    while ((file = m_readdir(from)) != NULL)
        (*files)[size++] = (*file).d_name;

    return size; // возвращаем количество записанных названий файлов
}

void copyDir(char **arr, int am_files, char *destination, char *departure)
{
    struct stat st;
    for (int i = 0; i < am_files; i++)
    {
        char *to = createPath(destination, arr[i]);
        char *from = createPath(departure, arr[i]);
        stat(from, &st);
        if (S_ISDIR(st.st_mode))
        {
            char **files;
            int n_size = dirFiles(from, &files);
            mkdir(to, st.st_mode);
            copyDir(files, n_size, to, from);
        }
        else
        {
            copyFile(from, to);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
        m_puts("Wrong amount of arguments\n");

    char **files; // массив строк - имен файлов
    int size = dirFiles(argv[1], &files); // сколько имен файлов
    atoi(argv[2]) ? qsort(files, size, sizeof(char *), file_comparator_lex) : bubble_sort(files, size, argv[1]);
    copyDir(files, size, argv[3], argv[1]);

    return EXIT_SUCCESS;
}

// Отсортировать в заданном каталоге (аргумент 1 командной строки)
// и во всех его подкаталогах файлы по следующим критериям
// (аргумент 2 командной строки, задаётся в виде целого числа):
// 1 – по размеру файла, 2 – по имени файла.
// Записать файлы в порядке сортировки в новый каталог (аргумент 3 командной строки).
// После записи каждого файла выводить на консоль полный путь каталога, имя файла, размер файла.
