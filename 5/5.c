#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main( int argc, char* argv[] )
{
    if (argc!=3){
        printf("Please, pass source filename as first argument, destination filename as second\n");
        return 1;
    }
    int letter;
    FILE * input_file;
    FILE * output_file;
    struct stat buf;
    input_file=fopen(argv[1],"r");
    if (input_file==NULL){
        printf("File %s doesnt exist\n",argv[1]);
        return 1;
    }
    output_file=fopen(argv[2],"w");
    if (output_file==NULL){
        printf("Destination file error");
        return 1;
    }
    while ((letter=getc(input_file)) != EOF ) {
        putc(letter,output_file);
    }
    stat(argv[1],&buf);
    fclose(input_file);
    fclose(output_file);
    printf("File copied\n");
    
    if (chmod(argv[2],buf.st_mode)==0){
        printf("Permissions copied\n");
    }
    else{
        printf("Failed to copy permissions\n");
    }

    return 0;
}

//Написать программу копирования одного файла в другой. В качестве параметров при вызове программы передаются имена первого и второго файлов. Для чтения или записи файла использовать только функции посимвольного ввода-вывода getc(), putc(), fgetc(), fputc(). Предусмотреть копирование прав доступа к файлу и контроль ошибок открытия/закрытия/чтения/записи файла.
