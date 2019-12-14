#include <stdio.h>

int main(int argc, char** argv) 
{
	FILE *fp;

	fp=fopen(argv[1], "w");
	int ch = getchar();
	while (ch != 1) 
	{
		fputc(ch, fp);
		ch = getchar();
	}
	fclose(fp);

	return 0;
}

//Написать программу ввода символов с клавиатуры и записи их в файл (в качестве аргумента при запуске программы вводится имя файла). Для чтения или записи файла использовать только функции посимвольного ввода-вывода getc(), putc(), fgetc(), fputc(). Предусмотреть выход после нажатия комбинации клавиш (например: ctrl-F). Предусмотреть контроль ошибок открытия/закрытия/чтения файла