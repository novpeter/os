#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>

void print_dir(DIR *dir)
{
    if (!dir){
        printf("Wrong directory\n");
    }
    
    struct dirent *internal_dir;
    
    while ( (internal_dir = readdir(dir) ) != NULL ) {
        printf("%s\n",internal_dir->d_name);
    }
    
    closedir(dir);
    printf("\n");
}

int main( int argc, char* argv[], char** env )
{
	if (argc!=2){
		printf("Please, pass dir as first argument\n");
		return 1;
	}
    
    DIR *current_dir = opendir(getenv("PWD"));
    DIR *other_dir = opendir(argv[1]);
    
    print_dir(current_dir);
    print_dir(other_dir);
    
	return 0;
}

//Написать программу вывода на экран содержимого текущего и заданного первым параметром вызова программы каталогов. Предусмотреть контроль ошибок открытия/закрытия/чтения каталога.
