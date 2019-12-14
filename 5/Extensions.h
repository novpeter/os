#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>

void printError(int err)
{
    char *err_description = strerror(err);
    fprintf(stderr, "Error message : %s\n", err_description);
    free(err_description);
}
 
/*Вывести строку в файл*/ 
void ex_fputs(char *arr, FILE *file)
{
    errno = 0;
    for (int i = 0; arr[i] != '\0' && arr[i] != EOF; i++)
    {
        fputc(arr[i], file);
        if (errno)
            printError(errno);
        if (errno == EAGAIN)
            i--;
    }
}

/*Вывести строку*/
void ex_puts(char *arr)
{
    errno = 0;
    ex_fputs(arr, stdout);
}

/*Получить строку из файла*/
char *ex_gets(char *buffer, int amount, FILE *file)
{
    errno = 0;
    for (int i = 0; i < amount; i++)
    {
        buffer[i] = getc(file);
        if (errno)
            printError(errno);
        if (buffer[i] == EOF)
        {
            buffer[i] = '\0';
            break;
        }
    }
    return buffer;
}

/*Открыть файл*/
FILE *ex_fopen(char *path, char *mode)
{
    errno = 0;
    FILE *file = fopen(path, mode);
    if (errno)
        printError(errno);
    return file;
}

/*Закрываем файл*/
int ex_fclose(FILE *file)
{
    errno = 0;
    fclose(file);
    if (errno)
    {
        printError(errno);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/*Закрыть директорию*/
int ex_closedir(DIR *dirptr)
{
    errno = 0;
    int temp = closedir(dirptr);
    if (errno)
        printError(errno);
    return temp;
}

/*Открыть директорию*/
DIR *ex_opendir(const char *dirname)
{
    errno = 0;
    DIR *directory = opendir(dirname);
    if (errno)
        printError(errno);
    return directory;
}

/*Возращает структурки файлов*/
struct dirent *ex_readdir(DIR *dirptr)
{
    errno = 0;
    struct dirent *d = readdir(dirptr);
    if (errno)
        printError(errno);
    return d;
}
