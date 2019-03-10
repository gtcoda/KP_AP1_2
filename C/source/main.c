#include <stdlib.h>
#include <stdint.h>
#include "../include/menu.h"
#include "../include/record.h"

char velcome[] = "KP_AP1_2 \n"
"\n";
#define COUNT_LINE_VELCOM 2 // Количество строк занимаемое шапкой.


#define MENU_CREATE_DB "\n Управление базами. "
#define MENU_ADD "\n Добавить запись. "
#define MENU_REPLACE "\n Заменить запись. "
#define MENU_READ "\n Прочитать файл в базу. "
#define MENU_WRITE	"\n Записать базу в файл. "
#define MENU_INSERT "\n Вставка записи. "
#define MENU_DELITE "\n Удалить записи. "
#define MENU_VIEW "\n Просмотр базы. "
#define MENU_AMOUNT "\n Просмотр количества элементов в базе. "
#define MENU_SORT "\n Сортировка. "
#define MENU_EXIT "\n Выход. "






void main(void) {

	int str = sizeof(record_t);
	int ar = sizeof(record_db_a);
	int li = sizeof(record_db_l);
	


	system("chcp 1251"); // переходим в консоли на русский язык
	char command[40];
	printf(velcome);

	const char* items[] = {
							MENU_CREATE_DB,
							MENU_ADD,
							MENU_REPLACE,
							MENU_READ,
							MENU_WRITE,
							MENU_INSERT,
							MENU_DELITE,
							MENU_VIEW,
							MENU_AMOUNT,
							MENU_SORT,
							MENU_EXIT
	};

	while (1) {
		int i = 0;

		i = menu(3, 1, items, sizeof(items)/sizeof(items[0]));

		// + число - количество строк в приветствии
		clear(0, sizeof(items) / sizeof(items[0])+2);
		
		printf("======================================================== \n");

		strcpy_s(&command, 40,items[i]);

		if (!strcmp(command, MENU_ADD)) {
			add_record();
		}
		else if (!strcmp(command, MENU_REPLACE)) {
			replace();
		}
		else if (!strcmp(command, MENU_CREATE_DB)) {
			db_manager();
		}
		else if (!strcmp(command, MENU_READ)) {
			read_file();
		}
		else if (!strcmp(command, MENU_WRITE)) {
			write_file();
		}
		else if (!strcmp(command, MENU_INSERT)) {
			insert();
		}
		else if (!strcmp(command, MENU_DELITE)) {
			delite();
		}
		else if (!strcmp(command, MENU_VIEW)) {
			view_record();
		}
		else if (!strcmp(command, MENU_AMOUNT)) {
			amount();
		}
		else if (!strcmp(command, MENU_SORT)) {
			sort();
		}
		else if (!strcmp(command, MENU_EXIT)) {
			break;
		}
		else {
			printf("command %s not found! \n", command);
		}
		
		clear(0, COUNT_LINE_VELCOM);

	}

}