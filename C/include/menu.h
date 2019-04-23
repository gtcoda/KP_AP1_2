#ifndef MENU_H
#define MENU_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <windows.h>

#define VELCOM "	Обработка массивов записей. \n\r	KP_AP1_2 \n\r "

#define COUNT_LINE_VELCOM 2 // Количество строк занимаемое приветствием.
#define COLUMN_LINE_LEVCOM 0 // Начальная колонка строк с приветствием.

#define COUNT_LINE_DB_ACTIVE 3 // Количество строк занимаемое именем активной базы.
#define COLUMN_LINE_DB_ACTIVE 0 // Начальная колонка строк с именем активной базы. 

#define COUNT_LINE_MENU 12 // Количество строк занятых менюшкой.
#define COLUMN_LINE_MENU 1 // Начальная колонка строк меню.

#define DB_ACTIVE_WORK (COUNT_LINE_VELCOM) // Позиция занимаемая именем активной базы
#define MEMU_WORK (COUNT_LINE_VELCOM + COUNT_LINE_DB_ACTIVE) // ПОЗИция строки начала меню
#define LINE_WORK (COUNT_LINE_MENU + COUNT_LINE_VELCOM + COUNT_LINE_DB_ACTIVE) // Позиция начальной строки под меню.

#define INDENT 1 // Отступ основной


#define MENU_CREATE_DB 	"Управление базами."
#define MENU_ADD 		"Добавить запись."
#define MENU_REPLACE 	"Изменить запись."
#define MENU_READ 		"Прочитать файл в базу."
#define MENU_WRITE		"Записать базу в файл."
#define MENU_INSERT 	"Вставка записи."
#define MENU_DELITE 	"Удалить записи."
#define MENU_VIEW 		"Просмотр базы."
#define MENU_AMOUNT 	"Просмотр количества элементов в базе."
#define MENU_SORT 		"Сортировка."
#define MENU_DIAP 		"Просмотр элементов в диапазоне."
#define MENU_EXIT 		"Выход."

#define MENU_SURNAME 	"SURNAME"
#define MENU_HEIGHT 	"HEIGHT"
#define MENU_WEIGHT 	"WEIGHT"

#define DB_DAFAULT_NAME "default"

#define MESSAGE_NO_BASE "Нет базы. Создать!"
#define MESSAGE_NO_RECORDS "Нет ни одной записи!"
#define MESSAGE_NO_DELITE "База пуста. Удалять нечего.\n"

int menu(int x, int y, char* items[], int cnt);
void clear(int X, int Y);
void clear_line(int x, int cnt);


#endif
