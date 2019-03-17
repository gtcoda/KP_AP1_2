#ifndef MENU_H
#define MENU_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <windows.h>

#define VELCOM "KP_AP1_2 \n\n";

#define COUNT_LINE_VELCOM 2 // Количество строк занимаемое приветствием.
#define COUNT_LINE_MENU 12 // Количество строк занятых менюшкой.

#define LINE_WORK (COUNT_LINE_MENU + COUNT_LINE_VELCOM) // Позиция начальной строки под меню.

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


int menu(int x, int y, const char* items[], int cnt);
void clear(int X, int Y);
#endif
