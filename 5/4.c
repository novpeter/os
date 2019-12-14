#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

int main( int argc, char* argv[] )
{
    if (argc!=3){
        printf("Please, pass filename as first argument, grouping as second\n");
        return 1 ;
    }
    int letter;
    FILE * input_file;
    input_file = fopen(argv[1],"r");
    if (input_file == NULL){
        printf("File doesnt exist");
        return 1;
    }
    int i = 1;
    int N = atoi(argv[2]);
    while ((letter = getc(input_file)) != EOF) {
        putc(letter,stdout);
        if (letter == 10){
            i = i+1;
        }
        if (N == 0){
            i =-1;
        }
        if (i > N){
            while (getc(stdin) == EOF){;}
            i = 1;
        }
    }
    fclose(input_file);
    return 0;
}

//Написать программу вывода содержимого текстового файла на экран (в качестве аргумента при запуске программы передаётся имя файла, второй аргумент (N) устанавливает вывод по группам строк (по N строк) или сплошным текстом (N=0)). Для вывода очередной группы строк необходимо ожидать нажатия пользователем любой клавиши. Для чтения или записи файла использовать только функции посимвольного ввода-вывода getc(), putc(), fgetc(), fputc(). Предусмотреть контроль ошибок открытия/закрытия/чтения/записи файла
