#include "../include/record.h"

char *filename = RECORD_FILES;
void record_parsing(char * string);


void record_parsing(char * string) {
	char surname[NAME_SIZE];
	char height[NAME_SIZE];
	char weight[NAME_SIZE];

	char *m = strtok(string, ":");

	for (uint8_t i = 0; m != NULL; i++) {

		switch (i) {
		case 0: strcpy(surname, m); break;
		case 1: strcpy(height, m); break;
		case 2: strcpy(weight, m); break;
		}
		m = strtok(NULL, ":");
	}

	record_t record;

	strcpy(record.surname, surname);
	record.height = (uint16_t)strtol(height, NULL, 10);
	record.weight = strtof(weight, NULL);

	write_db(record, NULL);

}



void write_file() {
	char filename[100];
	rn_t count;
	printf("Input filename: ");
	mfgets(filename, 100, stdin);
	
	count = write_db_file((char *)&filename);

	printf("Write %u records!\n", count);
}



void read_file() {
	rn_t count = 0;
	FILE *fp;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("File not found!");
		return;
	}

	char buffer[STR_SIZE];
	while (fgets(buffer, STR_SIZE, fp) != NULL) {
		record_parsing(buffer);
		count++;
	}

	printf("Add %u record!\n", count);

	

	fclose(fp);
}

void add_record() {
	char str[STR_SIZE];
	printf("Enter Record:");
	mfgets(str, sizeof(str), stdin);
	record_parsing(str);
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
	system("chcp 1251"); // переходим в консоли на русский язык
	printf(VIEW_HEAD);
	for (uint8_t i = 0; i < amount_db(); i++) {
		record_t rec;
		read_db(i, &rec);

		printf("%-2u |%-8s| %-8u| %-8.2f", i, rec.surname, rec.height, rec.weight);
		printf("\n\r");
	}
}


