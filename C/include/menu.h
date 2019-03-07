#ifndef MENU_H
#define MENU_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <windows.h>

#define VELCOM "KP_AP1_2 \n\n"

#define COUNT_LINE_VELCOM 2 // ���������� ����� ���������� ������������.
#define COLUMN_LINE_LEVCOM 0 // ��������� ������� ����� � ������������.

#define COUNT_LINE_DB_ACTIVE 3 // ���������� ����� ���������� ������ �������� ����.
#define COLUMN_LINE_DB_ACTIVE 0 // ��������� ������� ����� � ������ �������� ����. 

#define COUNT_LINE_MENU 13 // ���������� ����� ������� ��������.
#define COLUMN_LINE_MENU 1 // ��������� ������� ����� ����.

#define DB_ACTIVE_WORK (COUNT_LINE_VELCOM) // ������� ���������� ������ �������� ����
#define MEMU_WORK (COUNT_LINE_VELCOM + COUNT_LINE_DB_ACTIVE) // ������� ������ ������ ����
#define LINE_WORK (COUNT_LINE_MENU + COUNT_LINE_VELCOM + COUNT_LINE_DB_ACTIVE) // ������� ��������� ������ ��� ����.

#define MENU_CREATE_DB "���������� ������.\n"
#define MENU_ADD "�������� ������.\n"
#define MENU_REPLACE "�������� ������.\n"
#define MENU_READ "��������� ���� � ����.\n"
#define MENU_WRITE	"�������� ���� � ����.\n"
#define MENU_INSERT "������� ������.\n"
#define MENU_DELITE "������� ������.\n"
#define MENU_VIEW "�������� ����.\n"
#define MENU_AMOUNT "�������� ���������� ��������� � ����.\n"
#define MENU_SORT "����������.\n"
#define MENU_DIAP "�������� ��������� � ���������.\n"
#define MENU_EXIT "�����.\n"

#define MENU_SURNAME "SURNAME"
#define MENU_HEIGHT "HEIGHT"
#define MENU_WEIGHT "WEIGHT"


int menu(int x, int y, char* items[], int cnt);
void clear(int X, int Y);
void clear_line(int x, int cnt);
#endif
