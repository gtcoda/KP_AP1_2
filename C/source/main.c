#include <stdlib.h>
#include <stdint.h>
#include "../include/record.h"

char welcome[] = ""
"KP_AP1_2 \n"
"��� ������ ������� �������� help. \n"
"\n";

char help[] = ""
"Commands: \n"
"add		�������� ������. \n"
"fix		�������� ������. \n"
"insert		������� ������. \n"
"read		��������� � ���� � ����. \n"
"write		�������� ���� � ����. \n"
"view		�������� ����. \n"
"amount		�������� ���������� ��������� � ����. \n"
"exit		�����. \n"
"help		����� �������. \n"
"\n";

void main(void) {
	system("chcp 1251"); // ��������� � ������� �� ������� ����
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