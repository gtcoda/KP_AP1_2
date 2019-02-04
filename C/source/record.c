#include "../include/record.h"


record_db base;

record_db_s db;






char *filename = RECORD_FILES;




void record_parsing(char * string, record_db * base);

void record_parsing_add_arr(record_t record, record_db * base);



























void record_parsing(char * string, record_db * base) {
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

	record_parsing_add_arr(record, base);

}



void record_parsing_add_arr(record_t record, record_db * base) {
	strcpy(base->db[base->pointer].surname, record.surname);
	base->db[base->pointer].height = record.height;
	base->db[base->pointer].weight = record.weight;
	base->pointer++;
}


void write_file() {
	char filename[100];
	printf("Input filename: ");
	mfgets(filename, 100, stdin);

	FILE *fp;
	fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("File not write!");
		return;
	}
	for (uint8_t i = 0; i < base.pointer; i++) {
		fputs(base.db[i].surname, fp);
		fputs(":", fp);
		char buff[NAME_SIZE];

		itoa((int)base.db[i].height, (char *)buff, 10);
		fputs(buff, fp);
		fputs(":", fp);

		itoa((int)base.db[i].weight, buff, 10);
		fputs(buff, fp);

		fputs("\n", fp);

	}

	fclose(fp);

}



void read_file() {
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
	system("chcp 1251"); // переходим в консоли на русский язык
	printf(VIEW_HEAD);
	for (uint8_t i = 0; i < base.pointer; i++) {
		printf("%-8s| %-8u| %-8.2f", base.db[i].surname, base.db[i].height, base.db[i].weight);
		printf("\n\r");
	}
}



uint8_t write_db(record_t note, rn_t * number);
uint8_t read_db(rn_t number, record_t * note);
uint8_t write_db_arr(record_t note, record_db * base, rn_t * number);
uint8_t read_db_arr(rn_t number, record_t * note, record_db * base);

/*
Добавить запись note в базу.
number - указатель на переменную типа rn_t, куда поместится номер записи. Или NULL - если не используется
*/
uint8_t write_db(record_t note, rn_t * number) {
	if (DB == "ARRAY") {
		if (write_db_arr(note, &base, number)) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else if (DB == "LIST") {

	}
	else {
		printf(ERROR_DB);
	}
	return 0;
}


/*
Получить запись number из базы.
*/
uint8_t read_db(rn_t number, record_t * note) {
	if (DB == "ARRAY") {
		return read_db_arr(number, note, &base);
	}
	else if (DB == "LIST") {

	}
	
	return 0;
}

/*
Запись записи note в массив *base. Номер ячейки помещается в *number.
Возвращает 1 в случае успеха. 0 - неудача.
*/
uint8_t write_db_arr(record_t note, record_db * base, rn_t * number) {
	strcpy(base->db[base->pointer].surname, note.surname);
	base->db[base->pointer].height = note.height;
	base->db[base->pointer].weight = note.weight;
	base->pointer++;

	if (number != NULL) {
		*number = (rn_t)base->pointer - 1;
	}
	return 1;
}

/*
Чтение записи number из массива *base в структуру *note
Возвращает 1 в случае успеха. 0 - неудача.
*/
uint8_t read_db_arr(rn_t number, record_t * note, record_db * base) {
	strcpy (note->surname, base->db[number].surname);
	note->height = base->db[number].height;
	note->weight = base->db[number].weight;

	return 1;
}