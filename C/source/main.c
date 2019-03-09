#include <stdlib.h>
#include <stdint.h>
#include <windows.h>

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

void clear(int X, int Z) {
	COORD topLeft = { X, Z };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}






void gotoxy(int x, int y) {
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void textcolor(short f, short b) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), f | (b << 4));
}

char getch() {
	HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD rec;
	DWORD event;

	FlushConsoleInputBuffer(hstdin);
	while (ReadConsoleInputA(hstdin, &rec, 1, &event)) {
		if ((rec.EventType == KEY_EVENT)
			&& (rec.Event.KeyEvent.bKeyDown)) {
			return rec.Event.KeyEvent.wVirtualKeyCode;
		}
	}
	return EOF;
}

int menu(int x, int y, const char* items[], int cnt) {
	const short COLOR_FG = 7;
	const short COLOR_BG = 0;

	int i;
	char ch;

	textcolor(COLOR_FG, COLOR_BG);
	for (i = 0; i < cnt; ++i) {
		gotoxy(x, y + i);
		printf("%s", items[i]);
	}
	i = 0;
	gotoxy(x, y); textcolor(COLOR_BG, COLOR_FG);
	printf("%s", items[i]);

	while (((ch = getch()) != EOF) && (ch != VK_RETURN)) {
		gotoxy(x, y + i); textcolor(COLOR_FG, COLOR_BG);
		printf("%s", items[i]);
		switch (ch) {
		case VK_ESCAPE:
			return 0;
		case VK_UP:
			i = (i == 0) ? (cnt - 1) : (i - 1);
			break;
		case VK_DOWN:
			i = (i == cnt - 1) ? 0 : (i + 1);
			break;
		}
		gotoxy(x, y + i); textcolor(COLOR_BG, COLOR_FG);
		printf("%s", items[i]);
	}
	textcolor(COLOR_FG, COLOR_BG);

	return i + 1;
}












void main(void) {
	system("chcp 1251"); // переходим в консоли на русский язык
	char command[40];
	printf(welcome);

	const char* items[] = { "\n Добавить запись. ",
							"\n Заменить запись. ",
							"\n Прочитать и файл в базу. ",
							"\n Записать базу в файл. ",
							"\n Вставка записи. ",
							"\n Удалить записи. ",
							"\n Просмотр базы. ",
							"\n Просмотр количества элементов в базе. ",
							"\n Сортировка. ",
							"\n Выход. "
							
	};


	while (1) {
		int i = 0;

		i = menu(3, 3, items, 9);

		gotoxy(1, 14);
		printf("Return: %d\n\n", i);
		clear(1, 15);

		switch (i) {
		case 1: add_record(); break;
		case 2: replace(); break;
		case 3: read_file(); break;
		case 4: write_file(); break;
		case 5: insert(); break;
		case 6: delite(); break;
		case 7: view_record(); break;
		case 8: amount(); break;
		case 9: sort(); break;
		}

/*		printf("Command : ");
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
		*/
	}

}