#include "../include/record.h"

char *filename = RECORD_FILES;
void record_parsing(char * string);
void entry_record(record_t * note);
char * trim(char *s);


void record_parsing(char * string) {
	char surname[NAME_SIZE];
	char height[NAME_SIZE];
	char weight[NAME_SIZE];
	
	char *m = strtok(string, SEPARATOR);

	for (uint8_t i = 0; m != NULL; i++) {
		switch (i) {
		case 0: strcpy(surname, m); break;
		case 1: strcpy(height, m); break;
		case 2: strcpy(weight, m); break;
		}
		m = strtok(NULL, ":");
	}

	record_t record;

	strcpy(record.surname, trim(surname) );
	record.height = (uint16_t)strtol(height, NULL, 10);
	record.weight = strtof(weight, NULL);

	write_db(record, NULL);

}



void write_file() {
	char filename[100];
	rn_t count = 0;
	printf("Input filename: ");
	mfgets(filename, 100, stdin);
	
	FILE *fp;
	record_t rec;
	fp = fopen(filename, "w");

	if (fp != NULL) {

		for (count = 0; count < amount_db(); count++) {

			if (read_db(count, &rec)) {
				char buf[100];
				sprintf(buf, "%s %s %u %s %.2f \n", rec.surname, SEPARATOR, rec.height, SEPARATOR, rec.weight);
				fputs(buf, fp);
			}
			else {
				break;
			}
		}
		fclose(fp);
		printf("Write %u records!\n", count);
	}
	else {
		printf(" NO open file!\n");
	}
	
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
	record_t record;
	entry_record(&record);
	
	if ( write_db(record, NULL) ) {
		printf("Writing!\n");
	}
	else {
		printf("Write error!\n");
	}
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

	if (amount_db() == 0) {// Нет ни одной записи
		printf("There is no record!\n");
	}
	else {
		rn_t count = amount_db();
		printf(VIEW_HEAD);
		for (uint8_t i = 0; i <= count-1; i++) {
			record_t rec;
			read_db(i, &rec);

			printf("%-2u |%-10s| %-10u| %-10.2f", i, rec.surname, rec.height, rec.weight);
			printf("\n\r");
		}
	}
}

/*
Изменение записи
*/
void replace(void) {
	rn_t number = 0;
	record_t record;
	char str[STR_SIZE];
	printf("Number of fix record: ");
	mfgets(str, sizeof(str), stdin);
	number = (rn_t)strtol(str, NULL, 10);

	entry_record(&record);

	replace_db(record, number);
}

/*
Ввод записи
*/
void entry_record(record_t * note) {
	char height[NAME_SIZE];
	char weight[NAME_SIZE];

	printf("************* Enter Record **********\n");
	printf("Enter surname: ");
	mfgets(note->surname, sizeof(note->surname), stdin);

	printf("Enter height: ");
	mfgets(height, sizeof(height), stdin);
	note->height = (uint16_t)strtol(height, NULL, 10);

	printf("Enter weight: ");
	mfgets(weight, sizeof(weight), stdin);
	note->weight = strtof(weight, NULL);
}

void amount(void) {
	printf("Amount %u record.\n", amount_db() );
}

/*
Удаляеи пробелы в начале и конце строки
Внимаение! Изменяет и передаваемую строку и возвращает на неё указатель.
*/
char * trim(char *s) {
	size_t i = 0, j;
	
	// Удаляем пробелы и tab с начала строки
	while ((s[i] == ' ') || (s[i] == '\t')) {
		i++;
	}
	if (i > 0) {
		for (j = 0; j < strlen(s); j++) {
			s[j] = s[j + i];
		}
		s[j] = '\0';
	}

	// удаляем пробелы и табы с конца строки:
	i = strlen(s) - 1;
	while ((s[i] == ' ') || (s[i] == '\t')) {
		i--;
	}
	if (i < (strlen(s) - 1)) {
		s[i + 1] = '\0';
	}

	return s;
}