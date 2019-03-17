#ifndef MENU_H
#define MENU_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <windows.h>

#define VELCOM "KP_AP1_2 \n\n";

#define COUNT_LINE_VELCOM 2 // ���������� ����� ���������� ������������.


#define MENU_CREATE_DB "\n ���������� ������. "
#define MENU_ADD "\n �������� ������. "
#define MENU_REPLACE "\n �������� ������. "
#define MENU_READ "\n ��������� ���� � ����. "
#define MENU_WRITE	"\n �������� ���� � ����. "
#define MENU_INSERT "\n ������� ������. "
#define MENU_DELITE "\n ������� ������. "
#define MENU_VIEW "\n �������� ����. "
#define MENU_AMOUNT "\n �������� ���������� ��������� � ����. "
#define MENU_SORT "\n ����������. "
#define MENU_EXIT "\n �����. "


int menu(int x, int y, const char* items[], int cnt);
void clear(int X, int Y);
#endif
