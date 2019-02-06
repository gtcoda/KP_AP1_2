#include <stdlib.h>
#include <stdint.h>
#include "../include/record.h"

char welcome[] = ""
"KP_AP1_2 \n"
"Commands: \n"
"add		Добавить запись. \n"
"read		Прочитать и файл в базу. \n"
"write		Записать базу в файл. \n"
"view		Просмотр базы. \n"
"exit		Выход. \n"
"\n";


void main(void) {
	system("chcp 1251"); // переходим в консоли на русский язык
	char command[40];
	printf(welcome);

	while (1) {
		printf("Command : ");
		mfgets(command, sizeof(command), stdin);
		if (!strcmp(command, "add")) {
			add_record();
		}
		else if (!strcmp(command, "read")) {
			read_file();
		}
		else if (!strcmp(command, "write")) {
			write_file();
		}
		else if (!strcmp(command, "view")) {
			view_record();
		}
		else if (!strcmp(command, "exit")) {
			break;
		}
		else {
			printf("command %s not found! \n", command);
		}
	}

}