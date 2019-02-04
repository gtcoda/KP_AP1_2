#include "../include/record.h"


record_db base;

char *filename = RECORD_FILES;




void record_parsing(char * string, record_db * base);


void record_parsing(char * string, record_db * base) {
	char name[NAME_SIZE];
	char square[NAME_SIZE];
	char ports[NAME_SIZE];

	char *m = strtok(string, ":");

	for (uint8_t i = 0; m != NULL; i++) {

		switch (i) {
		case 0: strcpy(name, m); break;
		case 1: strcpy(square, m); break;
		case 2: strcpy(ports, m); break;
		}
		m = strtok(NULL, ":");
	}


	strcpy(base->db[base->pointer].name, name);
	base->db[base->pointer].square = (uint16_t)strtol(square, NULL, 10);
	base->db[base->pointer].ports = (uint16_t)strtol(ports, NULL, 10);
	base->pointer++;

}

void db_to_file() {
	FILE *fp;
	fp = fopen(filename, "w");
	for (uint8_t i = 0; i < base.pointer; i++) {
		fputs(base.db[i].name, fp);
		fputs(":", fp);
		char buff[NAME_SIZE];

		itoa((int)base.db[i].square, (char *)buff, 10);
		fputs(buff, fp);
		fputs(":", fp);

		itoa((int)base.db[i].ports, buff, 10);
		fputs(buff, fp);

		fputs("\n\r", fp);

	}

	fclose(fp);

}



void file_to_db() {
	FILE *fp;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("File not found!");
		return;
	}
	char buffer[NAME_SIZE];
	while (fgets(buffer, NAME_SIZE, fp) != NULL) {
		record_parsing(buffer, &base);
	}

	fclose(fp);
}

void add_record() {
	char str[NAME_SIZE];
	printf("Enter Record:");
	mfgets(str, sizeof(str), stdin);
	record_parsing(str, &base);
}


char * mfgets(char * string, int num, FILE * filestream) {
	char * res = fgets(string, NAME_SIZE, stdin);
	char * ptr = NULL;
	ptr = strchr(string, '\n');
	if (ptr != NULL) {
		*ptr = 0;
	}
	return res;
}

void view_record() {
	printf("Name | Square | Ports \n\r");
	for (uint8_t i = 0; i < base.pointer - 1; i++) {
		printf("%-5s| %-7u| %-6u", base.db[i].name, base.db[i].square, base.db[i].ports);
		printf("\n\r");
	}
}