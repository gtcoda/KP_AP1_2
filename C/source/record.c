#include "../include/record.h"



static void db_manager_add(char * name);
static void record_parsing(char * string);
static void entry_record(record_t * note);
static void strncpy_s_m(char * dst, size_t len, char * src);
static char * trim(char *s);
static rn_t view_record_choice(void);

static void view_record_diap_height(void);
static void view_record_diap_weight(void);


struct {
	db db_list[MAX_DB];
	uint8_t count_db;
}manager_db;

record_db_a * active_db = NULL;

/*
 �������� � ����� ���� ������.
*/
void db_manager(void) {

		char * items[MAX_DB+1];
		uint8_t i;
		char *baseinsert = { "�������� ����. \n" };
		
		clear (0, COUNT_LINE_VELCOM);

		printf("����: \n");

		for (i = 0; i < manager_db.count_db; i++) {
			items[i] = malloc(NAME_SIZE);
			strcpy(items[i], manager_db.db_list[i].name_db);
		}
		
		items[i] = malloc(NAME_SIZE);
		strcpy(items[i], baseinsert);
		uint8_t bases = 0;
		bases = menu( 3, DB_ACTIVE_WORK+1, items, manager_db.count_db+1);

		// ������� ������� �����  ����
		if (bases == i) {
			char db_name[NAME_SIZE];
			printf("======================================================== \n");
			// ������� ��� ����.
			printf("������� ��� ����[%s]: ", DB_DAFAULT_NAME);
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
		
		// �������� ������!
		for (uint8_t m = 0; m <= i; m++) {
			free(items[m]);
		}

	clear (0, COUNT_LINE_VELCOM);
}


/*
�������� ����� ���� ������.
*/
void db_manager_add(char * name) {
	
	strcpy((char *)&manager_db.db_list[ manager_db.count_db ].name_db, name);
	// �������� ����� ����.
	create_db(&manager_db.db_list[ manager_db.count_db ].pointer_db);

	// ����� ������� �� ��������.
	active_db = manager_db.db_list[ manager_db.count_db ].pointer_db;

	manager_db.count_db++;
}


/*
�������� �������� ����. ���������� db_name �� ������ NAME_SIZE;
*/ 
void db_manager_active_name(char * db_name) {
	
	for (uint8_t i = 0; i < manager_db.count_db; i++) {
		if (active_db == manager_db.db_list[i].pointer_db) {
			strcpy(db_name, manager_db.db_list[i].name_db);
			return;
		}
	}
	
	strcpy(db_name, MESSAGE_NO_BASE);
	return;
}

/*
���������� �������������� ������ ������. � ���������� �� � ������������ � ����������.
*/
void record_parsing(char * string) {
	char surname[NAME_SIZE];
	char height[NAME_SIZE];
	char weight[NAME_SIZE];
	
	char *m = strtok(string, SEPARATOR);

	for (uint8_t i = 0; m != NULL; i++) {
		switch (i) {
		case 0: strncpy_s_m(surname, NAME_SIZE, m); break;
		case 1: strncpy_s_m(height, NAME_SIZE, m); break;
		case 2: strncpy_s_m(weight, NAME_SIZE, m); break;
		}
		m = strtok(NULL, ":");
	}

	record_t record;

	strcpy(record.surname, trim(surname) );
	record.height = (uint16_t)strtol(height, NULL, 10);
	record.weight = strtof(weight, NULL);

	write_db(record, NULL, active_db);

}


/*
�������� ���� � ����.
*/
void write_file(void) {
	// �������� ������� ����. 
	if (active_db == NULL) { db_manager(); }

	rn_t count = 0;

	char file_name[FILE_NAME_SIZE];
	printf("������� ��� �����[%s]: ", DEFAULT_WRITE_FILE);
	mfgets(file_name, FILE_NAME_SIZE, stdin);

	if (strcmp(file_name, "") == 0) {
		strcpy(file_name, DEFAULT_WRITE_FILE);
	}
	
	FILE *fp;
	record_t rec;
	fp = fopen(file_name, "w");

	if (fp != NULL) {

		for (rn_t len = amount_db(active_db); count < len; count++) {

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



/*
���������, ���������� � �������� ���������� ����� � ����. 
*/
void read_file(void) {
	// �������� ������� ����. 
	if (active_db == NULL) { db_manager(); }

	rn_t count = 0;
	FILE *fp;
	char file_name[FILE_NAME_SIZE];
	printf("������� ��� �����[%s]: ", DEFAULT_READ_FILE);
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


/*
���������� ����� ������ � �������� ����.
*/
void add_record(void) {
	// �������� ������� ����. 
	if (active_db == NULL) { db_manager(); }

	record_t record;
	entry_record(&record);
	
	if ( write_db(record, NULL, active_db) ) {
		printf("Writing!\n");
	}
	else {
		printf("Write error!\n");
	}
	view_record();
}


/*
������� ���������� ���� ������ � ���� �������.
*/
void view_record(void) {
	// �������� ������� ����. 
	if (active_db == NULL) { db_manager(); }


	if (amount_db(active_db) == 0) {// ��� �� ����� ������.
		printf("There is no record!\n");
	}
	else {
		rn_t count = amount_db(active_db);
		printf(VIEW_HEAD); // ������� ����� �������.
		for (uint8_t i = 0; i <= count-1; i++) {
			record_t rec;
			read_db(i, &rec, active_db);

			printf(VIEW_BODY, i, rec.surname, rec.height, rec.weight);
		}
	}
}

/*
��������� ������
*/
void replace(void) {
	// �������� ������� ����. 
	if (active_db == NULL) { db_manager(); return;}

	rn_t number = 0;
	char * items[3];
	char str[STR_SIZE];
	char str_input[STR_SIZE];
	record_t rec;

	number = view_record_choice();

	
	read_db(number, &rec, active_db);

	sprintf(str,"SURNAME: %s", rec.surname);
	items[0] = malloc(strlen(str) + 1);
	strcpy(items[0], str);
	
	
	sprintf(str,"HEIGHT: %d", rec.height);
	items[1] = malloc(strlen(str) + 1);
	strcpy(items[1], str);
	
	sprintf(str,"WEIGHT: %.2f", rec.weight);
	items[2] = malloc(strlen(str) + 1);
	strcpy(items[2], str);

	printf("������� ����: \n");
	
	rn_t i = menu(INDENT, LINE_WORK+1, items, 3);
	
	// �������� ������!
	for (uint8_t m = 0; m <= 2; m++) {
		free(items[m]);
	}
	
	switch(i){
		case 0:{
			clear_line(LINE_WORK+1, 1); // ������� ������ � ���������� ������
			printf(" SURNAME: ");
			mfgets(str_input, STR_SIZE, stdin);
			strcpy (rec.surname, str_input);
			break;
		}
		case 1:{
			clear_line(LINE_WORK+2, 1); // ������� ������ � ���������� ������
			printf(" HEIGHT: ");
			mfgets(str_input, STR_SIZE, stdin);
			rec.height = (uint16_t)strtol(str_input, NULL, 10);
			break;
		}
		case 2:{
			clear_line(LINE_WORK+3, 1); // ������� ������ � ���������� ������
			printf(" WEIGHT: ");
			mfgets(str_input, STR_SIZE, stdin);
			rec.weight = strtof(str_input, NULL);
			break;
		}
		
	}
	
	// ������� ���������� �������.
	insert_db(rec, number, INSTEAD ,active_db);
	
	// ������� ���������� ����.
	clear(0, LINE_WORK);
	view_record();
}

/*
������� ������
*/
void insert(void) {
	// �������� ������� ����. 
	if (active_db == NULL) { db_manager(); }

	// �������� ���� �� � ���� ������.
	if (amount_db(active_db) == 0) {
		add_record();
		return;
	}
	rn_t number = 0;
	insert_t specifier;
	record_t record;


	number = view_record_choice();
	
	printf("Select position: \n");
		
	char * items[] = {	"0 - ����� ��������.",
						"1 - ����� ���������.",
						"2 - ������ ���������."
	};
	
	specifier = menu(1, LINE_WORK + 1, items, sizeof(items) / sizeof(items[0]));
	clear(1, LINE_WORK);
	

	entry_record(&record);

	insert_db(record, number, specifier, active_db);

	// ������� ���������� ����.
	clear(0, LINE_WORK);
	view_record();
}

/*
�������� ������.
*/
void delite(void) {
	// �������� ������� ����. 
	if (active_db == NULL) { db_manager(); return;}

	if (amount_db(active_db) == 0) {
		printf(MESSAGE_NO_DELITE);
		return;
	}

	rn_t number = 0;
	insert_t specifier;


	number = view_record_choice();

	printf("Input specifir: \n");
	char * items[] = {	"0 - ��� �� ����������.",
						"1 - ��� ����� ����������.",
						"2 - ������ ���������."
	};
	
	specifier = menu(1, LINE_WORK + 1, items, sizeof(items) / sizeof(items[0]));
	clear(1, LINE_WORK);
	
	delite_db(number, specifier, active_db);
	// ������� ���������� ����.
	clear(0, LINE_WORK);
	view_record();
}

/*
���� ������
*/
void entry_record(record_t * note) {
	char height[NAME_SIZE];
	char weight[NAME_SIZE];

	printf("************* Enter Record **********\n");
	printf("Enter surname: ");
	mfgets(note->surname, sizeof(note->surname), stdin);

	printf("Enter height: ");
	mfgets(height, sizeof(height), stdin);
	note->height = (h_type)strtol(height, NULL, 10);

	printf("Enter weight: ");
	mfgets(weight, sizeof(weight), stdin);
	note->weight = (w_type)strtof(weight, NULL);
}

/*
���������� ���������� ��������� � ����.
*/
void amount(void) {
	// �������� ������� ����. 
	if (active_db == NULL) { db_manager(); }

	printf("Amount %u record.\n", amount_db (active_db) );
}


/*
����� ������� ���������� � ����������� �����������.
*/
void sort(void) {
	// �������� ������� ����. 
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
		printf("��������� �� ���� [%s] �� �����������. \n", items[column]);
		view_record();
	}
	else {
		printf("Sort falled! \n");
	}
}


/*
������� �� ����� ���� ������ � ��������� � ����������� �������� ��������� �� ���� � �������� �� ����. 
*/
void view_record_diap(void){
	sort_t column;
	if (amount_db(active_db) == 0) {
		printf(MESSAGE_NO_RECORDS);
		return;
	}

	printf("�������� ����:\n");
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
	h_type begin = 0, end = 0;
	rn_t count = 0, min, max; 
	uint32_t midle = 0;
	char str[NAME_SIZE];

	printf("������� ��������.\n");
	printf("������ ���������: ");
	mfgets(str, sizeof(str), stdin);
	begin = (h_type)strtol(str, NULL, 10);

	printf("����� ���������: ");
	mfgets(str, sizeof(str), stdin);
	end = (h_type)strtol(str, NULL, 10);




	for (rn_t i = 0, c = amount_db(active_db); i < c; i++) {
		record_t rec, rec_min_max;
		read_db(i, &rec, active_db);

		if (rec.height >= begin && rec.height <= end) {
			if(count == 0){
				min = max = i;
			}
			
			midle = midle + rec.height;
			count++;
			printf(VIEW_BODY, i, rec.surname, rec.height, rec.weight);
		

			// ��������� �� �������.
			read_db(min, &rec_min_max, active_db);
			if (rec.height < rec_min_max.height ) {
				min = i;
			}

			// ��������� �� ��������.
			read_db(max, &rec_min_max, active_db);
			if (rec.height > rec_min_max.height) {
				max = i;
			}
			
		}
	}

	if (count != 0) {
		midle = midle / count;
	
		record_t rec_min, rec_max;
		printf("������� �� ���� [HEIGHT]: %d \n", midle);

		printf("����������� �� ���� [HEIGHT]: \n");
		read_db(min, &rec_min, active_db);
		printf(VIEW_BODY, min, rec_min.surname, rec_min.height, rec_min.weight);

		printf("������������ �� ���� [HEIGHT]: \n");
		read_db(max, &rec_max, active_db);
		printf(VIEW_BODY, max, rec_max.surname, rec_max.height, rec_max.weight);
	}
	else{
		printf("��� ������� �������� � �������� [%u,%u] �� ���� [HEIGHT].", begin, end);
	}
}

void view_record_diap_weight(void) {

	rn_t min, max;
	rn_t count = 0;
	w_type begin = 0, end = 0, midle = 0;
	char str[NAME_SIZE];

	printf("������� ��������.\n");
	printf("������ ���������: ");
	mfgets(str, sizeof(str), stdin);
	begin = (w_type)strtof(str, NULL);

	printf("����� ���������: ");
	mfgets(str, sizeof(str), stdin);
	end = (w_type)strtof(str, NULL);



	for (rn_t i = 0, c = amount_db(active_db); i < c; i++) {
		record_t rec, rec_min_max;
		read_db(i, &rec, active_db);

		if (rec.weight >= begin && rec.weight <= end) {
			if(count == 0){
				min = max = i;
			}
			
			midle = midle + rec.weight;
			count++;
			printf(VIEW_BODY, i, rec.surname, rec.height, rec.weight);
		

			// ��������� �� �������.
			read_db(min, &rec_min_max, active_db);
			if (rec.weight < rec_min_max.weight) {
				min = i;
			}

			// ��������� �� ��������.
			read_db(max, &rec_min_max, active_db);
			if (rec.weight > rec_min_max.weight) {
				max = i;
			}
		}
	}

	if (count != 0) {
		midle = midle / count;
	
	record_t rec_min, rec_max;
	printf("������� �� ���� [WEIGHT]: %.2f \n", midle);

	printf("����������� �� ���� [WEIGHT]: \n");
	read_db(min, &rec_min, active_db);
	printf(VIEW_BODY, min, rec_min.surname, rec_min.height, rec_min.weight);

	printf("������������ �� ���� [WEIGHT]: \n");
	read_db(max, &rec_max, active_db);
	printf(VIEW_BODY, max, rec_max.surname, rec_max.height, rec_max.weight);
	}
	else{
		printf("��� ������� �������� � �������� [%f,%f] �� ���� [WEIGHT].", begin, end);
	}
}

/*
������� �� ����� ���� ������ � ������������ ������ ��������
*/
rn_t view_record_choice(void) {
	// �������� ������ 
	char ** items;
	rn_t i = 0;
	rn_t count = amount_db(active_db);
	items = (char **)malloc(sizeof(char *) * amount_db(active_db));

	for (i = 0; i < count; i++) {
		char str[100];
		record_t rec;
		read_db(i, &rec, active_db);
		sprintf(str, "%-2u |%-10s| %-10u| %-10.2f \r", i, rec.surname, rec.height, rec.weight);
		items[i] = malloc(100);
		strcpy(items[i], str);
	}

	i = menu(1, LINE_WORK, items, amount_db(active_db));

	// �������� ������!
	for (uint8_t m = 0; m < count; m++) {
		free(items[m]);
	}
	free(items);

	clear(1, LINE_WORK);

	return i;
}


/*
������� ������� � ������ � ����� ������
���������! �������� � ������������ ������ � ���������� �� �� ���������.
*/
char * trim(char *s) {
	size_t i = 0, j;
	size_t len = strlen(s);
	
	// ������� ������� � tab � ������ ������
	while ((s[i] == ' ') || (s[i] == '\t')) {
		i++;
	}
	if (i > 0) {
		for (j = 0; j < len; j++) {
			s[j] = s[j + i];
		}
		s[j] = '\0';
	}

	// ������� ������� � ���� � ����� ������:
	i = len - 1;
	while ((s[i] == ' ') || (s[i] == '\t')) {
		i--;
	}
	if (i < (len - 1)) {
		s[i + 1] = '\0';
	}

	return s;
}

/*
�������� ����-�������������� ������ � ����� ������������ �������.
������� ����������� ���������� ������ dst ����-������������.
*/
void strncpy_s_m(char * dst, size_t len, char * src){
	strncpy(dst, src, len);
	// ��� ������������� "\0" ���������� warning: cast from pointer to integer of different size
	// ������� �� ������� ��� warning. "\0" == 0
	dst[len - 1] = 0;
}



char * mfgets(char * string, int num, FILE * filestream) {
	char * res = fgets(string, NAME_SIZE, stdin);

	char * ptr = NULL;
	ptr = strchr(string, '\n');
	if (ptr != NULL) {
		*ptr = 0;
	}
	else {
		// ������ ������� ������. ������������ ��� ������ ������ NAME_SIZE. ������ ��� �� ������� "\n"
		do {} while (getchar() != '\n');
	}
	return res;
}