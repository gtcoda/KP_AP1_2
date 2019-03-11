#include "../include/record.h"



char *filename = RECORD_FILES;
void db_manager_add(void);
void record_parsing(char * string);
void entry_record(record_t * note);
char * trim(char *s);



struct {
	db db_list[MAX_DB];
	uint8_t count_db;
}manager_db;

db_union * active_db = NULL;

// Управление базами данных
void db_manager(void) {
	// Нет ни одной базы. Создадим?
	if (manager_db.count_db == 0) {
		printf("Нет ни одной базы. Создадим! \n");
		db_manager_add();
	}
	else {
		char * items[MAX_DB+1];
		uint8_t i;
		const char *baseinsert = { "Добавить базу. \n" };
		
		clear(0, COUNT_LINE_VELCOM);

		printf("Базы: \n");

		for (i = 0; i < manager_db.count_db; i++) {
			items[i] = malloc(NAME_SIZE);
			strcpy(items[i], manager_db.db_list[i].name_db);
		}
		
		items[i] = malloc(NAME_SIZE);
		strcpy(items[i], baseinsert);
		uint8_t bases = 0;
		bases = menu(3, 3, items, manager_db.count_db+1);

		// Требуют создать новую  базу
		if (bases == i) {
			db_manager_add();
		}
		else {
			active_db = &manager_db.db_list[bases].pointer_db;
		}
		
		// Почистим память!
		for (uint8_t m = 0; m <= i; m++) {
			free(items[m]);
		}

	}

	clear(0, COUNT_LINE_VELCOM);
}



void db_manager_add(void) {
	char db_name[NAME_SIZE];
	printf("======================================================== \n");
	// Получим имя базы.
	printf("Введите имя базы: ");
	mfgets(db_name, NAME_SIZE, stdin);
	strcpy(&manager_db.db_list[ manager_db.count_db ].name_db, &db_name);
	// Создадим новую базу.
	create_db(&manager_db.db_list[ manager_db.count_db ].pointer_db);

	// Сразу сделаем ее активной.
	active_db = &manager_db.db_list[ manager_db.count_db ].pointer_db;

	manager_db.count_db++;
}

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

	write_db(record, NULL, active_db);

}



void write_file() {
	// Проверим наличие базы. 
	if (active_db == NULL) { db_manager(); }

	char filename[100];
	rn_t count = 0;
	printf("Input filename: ");
	mfgets(filename, 100, stdin);
	
	FILE *fp;
	record_t rec;
	fp = fopen(filename, "w");

	if (fp != NULL) {

		for (count = 0; count < amount_db(active_db); count++) {

			if (read_db(count, &rec, active_db)) {
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
	// Проверим наличие базы. 
	if (active_db == NULL) { db_manager(); }

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
	// Проверим наличие базы. 
	if (active_db == NULL) { db_manager(); }

	record_t record;
	entry_record(&record);
	
	if ( write_db(record, NULL, active_db) ) {
		printf("Writing!\n");
	}
	else {
		printf("Write error!\n");
	}
}



void view_record() {
	// Проверим наличие базы. 
	if (active_db == NULL) { db_manager(); }


	if (amount_db(active_db) == 0) {// Нет ни одной записи
		printf("There is no record!\n");
	}
	else {
		rn_t count = amount_db(active_db);
		printf(VIEW_HEAD);
		for (uint8_t i = 0; i <= count-1; i++) {
			record_t rec;
			read_db(i, &rec, active_db);

			printf("%-2u |%-10s| %-10u| %-10.2f", i, rec.surname, rec.height, rec.weight);
			printf("\n\r");
		}
	}
}

/*
Изменение записи
*/
void replace(void) {
	// Проверим наличие базы. 
	if (active_db == NULL) { db_manager(); }

	rn_t number = 0;
	record_t record;
	char str[STR_SIZE];
	printf("Number of fix record: ");
	mfgets(str, sizeof(str), stdin);
	number = (rn_t)strtol(str, NULL, 10);

	entry_record(&record);

	replace_db(record, number, active_db);
}

/*
Добавление записи
*/
void insert(void) {
	// Проверим наличие базы. 
	if (active_db == NULL) { db_manager(); }

	rn_t number = 0;
	insert_t specifier;
	record_t record;
	char str[STR_SIZE];
	printf("Number of insert record: ");
	mfgets(str, sizeof(str), stdin);
	number = (rn_t)strtol(str, NULL, 10);
	
	printf("Select position: \n");
	printf("0 - BEFORE; \n");
	printf("1 - AFTER; \n");
	mfgets(str, sizeof(str), stdin);
	specifier = (insert_t)strtol(str, NULL, 10);

	entry_record(&record);

	insert_db(record, number, specifier, active_db);
}


void delite(void) {
	// Проверим наличие базы. 
	if (active_db == NULL) { db_manager(); }

	rn_t number = 0;
	insert_t specifier;
	char str[STR_SIZE];

	printf("Number of delite record: ");
	mfgets(str, sizeof(str), stdin);
	number = (rn_t)strtol(str, NULL, 10);

	printf("Input specifir: \n");
	printf("0 - BEFORE; \n");
	printf("1 - AFTER; \n");
	printf("2 - ONE; \n");
	mfgets(str, sizeof(str), stdin);
	specifier = (insert_t)strtol(str, NULL, 10);
	delite_db(number, specifier, active_db);

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
	// Проверим наличие базы. 
	if (active_db == NULL) { db_manager(); }

	printf("Amount %u record.\n", amount_db (active_db) );
}


void sort(void) {
	// Проверим наличие базы. 
	if (active_db == NULL) { db_manager(); }

	sort_t column;
	char str[STR_SIZE];

	printf("Input specifir: \n");
	printf("0 - SURNAME; \n");
	printf("1 - HEIGHT; \n");
	printf("2 - WEIGHT; \n");
	mfgets(str, sizeof(str), stdin);
	column = (insert_t)strtol(str, NULL, 10);


	if (sort_db(column, active_db)) {
		printf("Sort end! \n");
		view_record(active_db);
	}
	else {
		printf("Sort falled! \n");
	}
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




char * mfgets(char * string, int num, FILE * filestream) {
	char * res = fgets(string, NAME_SIZE, stdin);
	char * ptr = NULL;
	ptr = strchr(string, '\n');
	if (ptr != NULL) {
		*ptr = 0;
	}
	return res;
}