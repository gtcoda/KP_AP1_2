#ifndef MENU_H
#define MENU_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <windows.h>

#define VELCOM "	��������� �������� �������. \n\r	KP_AP1_2 \n\r "

#define COUNT_LINE_VELCOM 2 // ���������� ����� ���������� ������������.
#define COLUMN_LINE_LEVCOM 0 // ��������� ������� ����� � ������������.

#define COUNT_LINE_DB_ACTIVE 3 // ���������� ����� ���������� ������ �������� ����.
#define COLUMN_LINE_DB_ACTIVE 0 // ��������� ������� ����� � ������ �������� ����. 

#define COUNT_LINE_MENU 12 // ���������� ����� ������� ��������.
#define COLUMN_LINE_MENU 1 // ��������� ������� ����� ����.

#define DB_ACTIVE_WORK (COUNT_LINE_VELCOM) // ������� ���������� ������ �������� ����
#define MEMU_WORK (COUNT_LINE_VELCOM + COUNT_LINE_DB_ACTIVE) // ������� ������ ������ ����
#define LINE_WORK (COUNT_LINE_MENU + COUNT_LINE_VELCOM + COUNT_LINE_DB_ACTIVE) // ������� ��������� ������ ��� ����.

#define INDENT 1 // ������ ��������


#define MENU_CREATE_DB 	"���������� ������."
#define MENU_ADD 		"�������� ������."
#define MENU_REPLACE 	"�������� ������."
#define MENU_READ 		"��������� ���� � ����."
#define MENU_WRITE		"�������� ���� � ����."
#define MENU_INSERT 	"������� ������."
#define MENU_DELITE 	"������� ������."
#define MENU_VIEW 		"�������� ����."
#define MENU_AMOUNT 	"�������� ���������� ��������� � ����."
#define MENU_SORT 		"����������."
#define MENU_DIAP 		"�������� ��������� � ���������."
#define MENU_EXIT 		"�����."

#define MENU_SURNAME 	"SURNAME"
#define MENU_HEIGHT 	"HEIGHT"
#define MENU_WEIGHT 	"WEIGHT"

#define DB_DAFAULT_NAME "default"

#define MESSAGE_NO_BASE "��� ����. �������!"
#define MESSAGE_NO_RECORDS "��� �� ����� ������!"
#define MESSAGE_NO_DELITE "���� �����. ������� ������.\n"

int menu(int x, int y, char* items[], int cnt);
void clear(int X, int Y);
void clear_line(int x, int cnt);


#endif
