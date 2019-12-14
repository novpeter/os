#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    time_t t;
    struct tm *timeinfo;
    pid_t pid_1, pid_2;

    if (pid_1 = fork())
        pid_2 = fork();

    time(&t);
    timeinfo = localtime(&t);

    if (pid_2 == 0 || pid_1 == 0)
    {
        printf("%d %d [%d:%d:%d]\n",
            	getpid(),
            	getppid(),
            	timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    }
    else
    {
        printf(
            "%d [%d:%d:%d]\n",
            getpid(),
            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
        const char *command = "ps -x | grep ppc.o";

        system(command);
    }
    
    return EXIT_SUCCESS;
}

/*
Написать программу, создающую два дочерних процесса с использованием двух вызовов
fork(). Родительский и два дочерних процесса должны выводить на экран свой pid и pid
родительского процесса и текущее время в формате: часы : минуты : секунды :
миллисекунды. Используя вызов system(), выполнить команду ps -x в родительском
процессе. Найти свои процессы в списке запущенных процессов.
*/
