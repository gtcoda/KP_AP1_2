#include "../include/db.h"

record_db base;
record_db_l list = {NULL,NULL};

uint8_t write_db_arr(record_t note, record_db * base, rn_t * number);
uint8_t write_db_list(record_t note, record_db_l * list, rn_t * number);
uint8_t read_db_arr(rn_t number, record_t * note, record_db * base);
rn_t write_db_file_arr(FILE *fp, record_db *base);
rn_t amount_db_arr(record_db *base);

/* ########################################### */

/*
Пишет базу в файл filename
*/
rn_t write_db_file(char * filename) {
	rn_t count = 0;
	FILE *fp;
	fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("File not write!");
		return 0;
	}


	if (DB == "ARRAY") {
		count = write_db_file_arr(fp, &base);
	}
	else if (DB == "LIST") {

	}
	else {
		printf(ERROR_DB);
	}

	fclose(fp);

	return count;
}

/*
Запись в файловый поток *fp, базы  *base.
Возвращает количество записаных записей или 0 при неудаче.
*/
rn_t write_db_file_arr(FILE *fp, record_db *base) {
	uint8_t i = 0;

	if (fp == NULL) {
		return 0;
	}

	for (i = 0; i < amount_db_arr(base); i++) {
		record_t rec;

		if (read_db_arr(i, &rec, base)) {
			char buf[100];
			sprintf(buf, "%s : %u : %.2f \n", rec.surname, rec.height, rec.weight);
			fputs(buf, fp);
		}
		else {
			break;
		}

	}

	return i;
}


/* ########################################### */
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
Чтение записи number из массива *base в структуру *note
Возвращает 1 в случае успеха. 0 - неудача.
*/
uint8_t read_db_arr(rn_t number, record_t * note, record_db * base) {
	strcpy(note->surname, base->db[number].surname);
	note->height = base->db[number].height;
	note->weight = base->db[number].weight;

	return 1;
}

/* ########################################### */
/*
Возвращает количество записей в базе
*/
rn_t amount_db() {
	if (DB == "ARRAY") {
		return	amount_db_arr(&base);
	}
	else if (DB == "LIST") {

	}

	return 0;
}


/*
Возвращает количество элементов в массиве записей *base
*/
rn_t amount_db_arr(record_db *base) {
	return base->pointer;
}



/* ########################################### */

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
		write_db_list(note, &list, number);
	}
	else {
		printf(ERROR_DB);
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

uint8_t write_db_list(record_t note, record_db_l * list, rn_t * number) {
	record_t_l * record = malloc(sizeof(note));
	if (record != NULL) {
		strcpy(record->surname, note.surname);
		record->height = note.height;
		record->weight = note.weight;

		// Если наш блок первый
		if (list->first == NULL) {
			list->first = record;
			list->last = record;
			// Связываем записи
			record->next = record;
			record->prev = record;
		}
		else {
			// Наш предыдущий блок был последним
			record->prev = list->last;

			// Свяжем предыдущий блок с нашим
			list->last->next = record;

			// Сами становимся последним
			list->last = record;

			// Следующего блока нет, указываем на себя
			record->next = record;

	
		}
		return 1;
	}
	
	return 0;
	
}

