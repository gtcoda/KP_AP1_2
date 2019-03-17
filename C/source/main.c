#include <stdlib.h>
#include <stdint.h>
#include <locale.h>
#include "../include/menu.h"
#include "../include/record.h"


void main(void) {	

	// переходим в консоли на русский язык
	setlocale(LC_ALL, "Rus");
	
	char velcome[] = "KP_AP1_2 \n"
		"\n";

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


		i = menu( (COUNT_LINE_VELCOM + 1), 1, items, sizeof(items)/sizeof(items[0]));

		clear(	sizeof(items) / sizeof(items[0]) + COUNT_LINE_VELCOM , 0);
		
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