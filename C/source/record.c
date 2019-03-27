#include "../include/record.h"



char *filename = RECORD_FILES;
void db_manager_add(char * name);
void record_parsing(char * string);
void entry_record(record_t * note);
char * trim(char *s);
rn_t view_record_choice(void);

void view_record_diap_height(void);
void view_record_diap_weight(void);


struct {
	db db_list[MAX_DB];
	uint8_t count_db;
}manager_db;

record_db_a * active_db = NULL;

// Управление базами данных
void db_manager(void) {

		char * items[MAX_DB+1];
		uint8_t i;
		char *baseinsert = { "Добавить базу. \n" };
		
		clear (0, COUNT_LINE_VELCOM);

		printf("Базы: \n");

		for (i = 0; i < manager_db.count_db; i++) {
			items[i] = malloc(NAME_SIZE);
			strcpy(items[i], manager_db.db_list[i].name_db);
		}
		
		items[i] = malloc(NAME_SIZE);
		strcpy(items[i], baseinsert);
		uint8_t bases = 0;
		bases = menu( 3, DB_ACTIVE_WORK+1, items, manager_db.count_db+1);

		// Требуют создать новую  базу
		if (bases == i) {
			char db_name[NAME_SIZE];
			printf("======================================================== \n");
			// Получим имя базы.
			printf("Введите имя базы[%s]: ", DB_DAFAULT_NAME);
			mfgets(db_name, NAME_SIZE, stdin);

			if (strcmp (db_name, "") == 0 ) {
				db_manager_add(DB_DAFAULT_NAME);
			}
			else {
				db_manager_add(db_name);
			}

		}
		else {
			active_db = manager_db.db_list[bases].pointer_db;
		}
		
		// Почистим память!
		for (uint8_t m = 0; m <= i; m++) {
			free(items[m]);
		}

	clear (0, COUNT_LINE_VELCOM);
}


/*


*/
void db_manager_add(char * name) {
	
	strcpy((char *)&manager_db.db_list[ manager_db.count_db ].name_db, name);
	// Создадим новую базу.
	create_db(&manager_db.db_list[ manager_db.count_db ].pointer_db);

	// Сразу сделаем ее активной.
	active_db = manager_db.db_list[ manager_db.count_db ].pointer_db;

	manager_db.count_db++;
}


/*
Название активной базы. Переменная db_name не меньше NAME_SIZE;
*/ 
void db_manager_active_name(char * db_name) {
	
	for (uint8_t i = 0; i < manager_db.count_db; i++) {
		if (active_db == manager_db.db_list[i].pointer_db) {
			strcpy(db_name, manager_db.db_list[i].name_db);
			return;
		}
	}
	
	strcpy(db_name, "none");
	return;
}

void record_parsing(char * string) {
	char surname[NAME_SIZE];
	char height[NAME_SIZE];
	char weight[NAME_SIZE];
	
	char *m = strtok(string, SEPARATOR);

	for (uint8_t i = 0; m != NULL; i++) {
		switch (i) {
		case 0: strcpy_s(surname, NAME_SIZE, m); break;
		case 1: strcpy_s(height, NAME_SIZE, m); break;
		case 2: strcpy_s(weight, NAME_SIZE, m); break;
		}
		m = strtok(NULL, ":");
	}

	record_t record;

	strcpy(record.surname, trim(surname) );
	record.height = (uint16_t)strtol(height, NULL, 10);
	record.weight = strtof(weight, NULL);

	write_db(record, NULL, active_db);

}



void write_file(void) {
	// Проверим наличие базы. 
	if (active_db == NULL) { db_manager(); }

	rn_t count = 0;

	char file_name[FILE_NAME_SIZE];
	printf("Введите имя файла[%s]: ", DEFAULT_WRITE_FILE);
	mfgets(file_name, FILE_NAME_SIZE, stdin);

	if (strcmp(file_name, "") == 0) {
		strcpy(file_name, DEFAULT_WRITE_FILE);
	}
	
	FILE *fp;
	record_t rec;
	fp = fopen(file_name, "w");

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



void read_file(void) {
	// Проверим наличие базы. 
	if (active_db == NULL) { db_manager(); }

	rn_t count = 0;
	FILE *fp;
	char file_name[FILE_NAME_SIZE];
	printf("Введите имя файла[%s]: ", DEFAULT_READ_FILE);
	mfgets(file_name, FILE_NAME_SIZE, stdin);

	if (strcmp (file_name, "") == 0 ) {
		printf("Read default file: %s \n", DEFAULT_READ_FILE);
		fp = fopen(DEFAULT_READ_FILE, "r");

		if (fp == NULL) {
			printf("Default file is not fount! \n");
			return;
		}

	}
	else {
		fp = fopen(file_name, "r");
		if (fp == NULL) {
			printf("File %s is not fount! \n", file_name);
			return;
		}
	}



	char buffer[STR_SIZE];
	while (fgets(buffer, STR_SIZE, fp) != NULL) {
		record_parsing(buffer);
		count++;
	}

	printf("Add %u record!\n", count);

	

	fclose(fp);
}

void add_record(void) {
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



void view_record(void) {
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

			printf(VIEW_BODY, i, rec.surname, rec.height, rec.weight);
		}
	}
}

/*
Изменение записи
*/
void replace(void) {
	// Проверим наличие базы. 
	if (active_db == NULL) { db_manager(); }
	// Проверим есть ли в базе записи.
	if (amount_db(active_db) == 0) {
		add_record();
		return;
	}

	rn_t number = 0;

	number = view_record_choice();

	record_t record;
	entry_record(&record);
	replace_db(record, number, active_db);
	
	// Выведем измененную базу.
	clear(0, LINE_WORK);
	view_record();
}

/*
Добавление записи
*/
void insert(void) {
	// Проверим наличие базы. 
	if (active_db == NULL) { db_manager(); }

	// Проверим есть ли в базе записи.
	if (amount_db(active_db) == 0) {
		add_record();
		return;
	}
	rn_t number = 0;
	insert_t specifier;
	record_t record;


	number = view_record_choice();
	
	printf("Select position: \n");
		
	char * items[2] = {	"0 - BEFORE.",
						"1 - AFTER."
	};
	
	specifier = menu(1, LINE_WORK + 1, items, sizeof(items) / sizeof(items[0]));
	clear(1, LINE_WORK);


	entry_record(&record);

	insert_db(record, number, specifier, active_db);

	// Выведем измененную базу.
	clear(0, LINE_WORK);
	view_record();
}


void delite(void) {
	// Проверим наличие базы. 
	if (active_db == NULL) { db_manager(); }

	if (amount_db(active_db) == 0) {
		printf(MESSAGE_NO_DELITE);
		return;
	}

	rn_t number = 0;
	insert_t specifier;


	number = view_record_choice();

	printf("Input specifir: \n");
	char * items[] = {	"0 - BEFORE.",
						"1 - AFTER.",
						"2 - ONE."
	};
	
	specifier = menu(1, LINE_WORK + 1, items, sizeof(items) / sizeof(items[0]));
	clear(1, LINE_WORK);
	
	delite_db(number, specifier, active_db);
	// Выведем измененную базу.
	clear(0, LINE_WORK);
	view_record();
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
	printf("Column for sort: \n");

	char * items[] = {	MENU_SURNAME,
						MENU_HEIGHT,
						MENU_WEIGHT
	};
	
	column = menu(1, LINE_WORK + 1, items, sizeof(items) / sizeof(items[0]));
	clear(0, LINE_WORK);


	if (sort_db(column, active_db)) {
		printf("Сортируем по полю [%s] по возрастанию. \n", items[column]);
		view_record(active_db);
	}
	else {
		printf("Sort falled! \n");
	}
}


/*
Выводит на экран базу данных в диапазоне с вичисление минимума максимума и среднего. 
*/
void view_record_diap(void){
	sort_t column;

	printf("Выберите поле:\n");
	char * items[] = {	MENU_HEIGHT,
						MENU_WEIGHT
	};
	
	column = menu(0, LINE_WORK + 1, items, sizeof(items) / sizeof(items[0]));
	clear(0, LINE_WORK);
	
	if (items[column] == MENU_HEIGHT) {
		view_record_diap_height();
	}
	else if (items[column] == MENU_WEIGHT) {
		view_record_diap_weight();
	}
}

void view_record_diap_height(void) {
	rn_t begin, end, count = 0, min=0, max=0;
	uint32_t midle = 0;
	char str[NAME_SIZE];

	printf("Введите диапазон.\n");
	printf("Начало диапазона: ");
	mfgets(str, sizeof(str), stdin);
	begin = (uint16_t)strtol(str, NULL, 10);

	printf("Конец диапазона: ");
	mfgets(str, sizeof(str), stdin);
	end = (uint16_t)strtol(str, NULL, 10);



	for (rn_t i = 0; i < amount_db(active_db); i++) {
		record_t rec, rec_min_max;
		read_db(i, &rec, active_db);

		if (rec.height >= begin && rec.height <= end) {
			midle = midle + rec.height;
			count++;
			printf(VIEW_BODY, i, rec.surname, rec.height, rec.weight);
		}

		// Проверяем на минимум.
		read_db(min, &rec_min_max, active_db);
		if (rec.height < rec_min_max.height ) {
			min = i;
		}

		// Проверяем на максимум.
		read_db(max, &rec_min_max, active_db);
		if (rec.height > rec_min_max.height) {
			max = i;
		}

	}

	if (count != 0) {
		midle = midle / count;
	}
	
	record_t rec_min, rec_max;
	printf("Среднее по полю [HEIGHT]: %d \n", midle);

	printf("Минимальное по полю [HEIGHT]: \n");
	read_db(min, &rec_min, active_db);
	printf(VIEW_BODY, min, rec_min.surname, rec_min.height, rec_min.weight);

	printf("Максимальное по полю [HEIGHT]: \n");
	read_db(max, &rec_max, active_db);
	printf(VIEW_BODY, max, rec_max.surname, rec_max.height, rec_max.weight);
}

void view_record_diap_weight(void) {

	rn_t count = 0, min = 0, max = 0;
	float begin = 0, end = 0, midle = 0;
	char str[NAME_SIZE];

	printf("Введите диапазон.\n");
	printf("Начало диапазона: ");
	mfgets(str, sizeof(str), stdin);
	begin = strtof(str, NULL);

	printf("Конец диапазона: ");
	mfgets(str, sizeof(str), stdin);
	end = strtof(str, NULL);



	for (rn_t i = 0; i < amount_db(active_db); i++) {
		record_t rec, rec_min_max;
		read_db(i, &rec, active_db);

		if (rec.weight >= begin && rec.weight <= end) {
			midle = midle + rec.weight;
			count++;
			printf(VIEW_BODY, i, rec.surname, rec.height, rec.weight);
		}

		// Проверяем на минимум.
		read_db(min, &rec_min_max, active_db);
		if (rec.weight < rec_min_max.weight) {
			min = i;
		}

		// Проверяем на максимум.
		read_db(max, &rec_min_max, active_db);
		if (rec.weight > rec_min_max.weight) {
			max = i;
		}

	}

	if (count != 0) {
		midle = midle / count;
	}
	record_t rec_min, rec_max;
	printf("Среднее по полю [WEIGHT]: %.2f \n", midle);

	printf("Минимальное по полю [WEIGHT]: \n");
	read_db(min, &rec_min, active_db);
	printf(VIEW_BODY, min, rec_min.surname, rec_min.height, rec_min.weight);

	printf("Максимальное по полю [WEIGHT]: \n");
	read_db(max, &rec_max, active_db);
	printf(VIEW_BODY, max, rec_max.surname, rec_max.height, rec_max.weight);
}

/*
Выводит на экран базу данных с возможностью выбора элемента
*/
rn_t view_record_choice(void) {
	// Создадим список 
	char ** items;
	rn_t i = 0;
	items = (char **)malloc(sizeof(char *) * amount_db(active_db));

	for (i = 0; i < amount_db(active_db); i++) {
		char str[100];
		record_t rec;
		read_db(i, &rec, active_db);
		sprintf(str, "%-2u |%-10s| %-10u| %-10.2f \r", i, rec.surname, rec.height, rec.weight);
		items[i] = malloc(100);
		strcpy(items[i], str);
	}

	i = menu(1, LINE_WORK, items, amount_db(active_db));

	// Почистим память!
	for (uint8_t m = 0; m < amount_db(active_db); m++) {
		free(items[m]);
	}
	free(items);

	clear(1, LINE_WORK);

	return i;
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
	else {
		// Чистим входные буферы. Пользователь мог ввести больше NAME_SIZE. Считае все до символа "\n"
		do {} while (getchar() != '\n');
	}
	return res;
}