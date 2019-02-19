#include <stdlib.h>
#include <stdint.h>
#include "../include/record.h"

char welcome[] = ""
"KP_AP1_2 \n"
"Для вызова справки наберите help. \n"
"\n";

char help[] = ""
"Commands: \n"
"add		Добавить запись. \n"
"fix		Заменить запись. \n"
"insert		Вставка записи. \n"
"read		Прочитать и файл в базу. \n"
"write		Записать базу в файл. \n"
"view		Просмотр базы. \n"
"amount		Просмотр количества элементов в базе. \n"
"exit		Выход. \n"
"help		Вызов справки. \n"
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
		else if (!strcmp(command, "fix")) {
			replace();
		}
		else if (!strcmp(command, "read")) {
			read_file();
		}
		else if (!strcmp(command, "write")) {
			write_file();
		}
		else if (!strcmp(command, "insert")) {
			insert();
		}
		else if (!strcmp(command, "delite")) {
			delite();
		}
		else if (!strcmp(command, "view")) {
			view_record();
		}
		else if (!strcmp(command, "amount")) {
			amount();
		}
		else if (!strcmp(command, "sort")) {
			sort();
		}
		else if (!strcmp(command, "help")) {
			printf(help);
		}
		else if (!strcmp(command, "exit")) {
			break;
		}
		else {
			printf("command %s not found! \n", command);
		}
	}

}