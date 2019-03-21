#include <stdlib.h>
#include <stdint.h>
#include <locale.h>
#include "../include/menu.h"
#include "../include/record.h"


void main(void) {	

	// переходим в консоли на русский язык
	setlocale(LC_ALL, "Rus");

	printf(VELCOM);

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
		// ##############################
		char db_name[NAME_SIZE];
		db_manager_active_name(db_name);
		

		clear_line(DB_ACTIVE_WORK, COUNT_LINE_DB_ACTIVE);

		printf("======================================================== \n");
		printf("Database active: %s \n", db_name);
		printf("======================================================== \n");
		// ##############################
		int i = 0;

		i = menu(COLUMN_LINE_MENU, MEMU_WORK, items, sizeof(items)/sizeof(items[0]));

		clear(COLUMN_LINE_MENU, sizeof(items) / sizeof(items[0]) + MEMU_WORK);
		
		printf("======================================================== \n");


		if (!strcmp(items[i], MENU_ADD)) {
			add_record();
			continue;
		}
		else if (!strcmp(items[i], MENU_REPLACE)) {
			replace();
			continue;
		}
		else if (!strcmp(items[i], MENU_CREATE_DB)) {
			db_manager();
			continue;
		}
		else if (!strcmp(items[i], MENU_READ)) {
			read_file();
			continue;
		}
		else if (!strcmp(items[i], MENU_WRITE)) {
			write_file();
			continue;
		}
		else if (!strcmp(items[i], MENU_INSERT)) {
			insert();
			continue;
		}
		else if (!strcmp(items[i], MENU_DELITE)) {
			delite();
			continue;
		}
		else if (!strcmp(items[i], MENU_VIEW)) {
			view_record();
			continue;
		}
		else if (!strcmp(items[i], MENU_AMOUNT)) {
			amount();
			continue;
		}
		else if (!strcmp(items[i], MENU_SORT)) {
			sort();
			continue;
		}
		else if (!strcmp(items[i], MENU_EXIT)) {
			break;
		}
		
		
	}

}