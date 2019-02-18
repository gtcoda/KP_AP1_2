#include "../include/db.h"

record_db_a base;
record_db_l list = {NULL,NULL};


static uint8_t read_db_arr(rn_t number, record_t * note, record_db_a * base);
static uint8_t read_db_list(rn_t number, record_t * note, record_db_l *list);

static uint8_t write_db_arr(record_t note, record_db_a * base, rn_t * number);
static uint8_t write_db_list(record_t note, record_db_l * list, rn_t * number);

static rn_t amount_db_arr(record_db_a *base);
static rn_t amount_db_list(record_db_l * list);

static uint8_t replace_db_arr(record_t note, record_db_a * base, rn_t number);
static uint8_t replace_db_list(record_t note, record_db_l * list, rn_t number);

static uint8_t insert_db_arr(record_t note, record_db_a * base, rn_t number, insert_t specifier);
static uint8_t insert_db_list(record_t note, record_db_l * list, rn_t number, insert_t specifier);

static record_t_l * record_of_list(record_db_l * list, rn_t number);

/* ########################################### */
/*
�������� ������ number �� ����.
*/
uint8_t read_db(rn_t number, record_t * note) {
	if (DB == "ARRAY") {
		return read_db_arr(number, note, &base);
	}
	else if (DB == "LIST") {
		return read_db_list(number, note, &list);
	}

	return 0;
}

/*
������ ������ number �� ������� *base � ��������� *note
���������� 1 � ������ ������. 0 - �������.
*/
uint8_t read_db_arr(rn_t number, record_t * note, record_db_a * base) {
	strcpy(note->surname, base->db[number].surname);
	note->height = base->db[number].height;
	note->weight = base->db[number].weight;

	return 1;
}

/*
������ ������ number �� ������ *list � ��������� *note
���������� 1 � ������ ������. 0 - �������.
*/
uint8_t read_db_list(rn_t number, record_t * note, record_db_l *list) {
	record_t_l * follow = list->first;
	rn_t count = 0;

	if (follow != NULL) {
		do {
			// ��� ���� ������
			if (count == number) {

				strcpy(note->surname, follow->data->surname);
				note->height = follow->data->height;
				note->weight = follow->data->weight;
				return 1;
			}
			count++;
			follow = follow->next;
		} while (follow != list->last);

		// �������� �������� ������ � ������
		if (count == number) {
			strcpy(note->surname, follow->data->surname);
			note->height = follow->data->height;
			note->weight = follow->data->weight;
			return 1;
		}
	}

	return 0;
	
}

/* ########################################### */
/*
���������� ���������� ������� � ����
*/
rn_t amount_db() {
	if (DB == "ARRAY") {
		return	amount_db_arr(&base);
	}
	else if (DB == "LIST") {
		return amount_db_list(&list);
	}

	return 0;
}


/*
���������� ���������� ��������� � ������� ������� *base
*/
rn_t amount_db_arr(record_db_a *base) {
	return base->pointer;
}

/*
���������� ���������� ��������� � ������ *list
*/
rn_t amount_db_list(record_db_l * list){
	rn_t count = 0;
	record_t_l * follow = list->first;

	if (follow != NULL) {
		count = 1; // ������� ��������� �� 0, ���������� ���������� � 1
		if (list->first == list->last) { // � ��� ����� 1 �������
			return count; 
		}
		else {
			// ������� �� ������ � ��������� ���������� ���������
			do {
				count++;
				follow = follow->next;
			} while (follow != list->last);			
		
		}
	}
	return count;
}


/* ########################################### */

/*
�������� ������ note � ����.
number - ��������� �� ���������� ���� rn_t, ���� ���������� ����� ������. ��� NULL - ���� �� ������������
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
		return 1;
	}
	else {
		printf(ERROR_DB);
		return 0;
	}
	return 0;
}

/*
������ ������ note � ������ *base. ����� ������ ���������� � *number.
���������� 1 � ������ ������. 0 - �������.
*/
uint8_t write_db_arr(record_t note, record_db_a * base, rn_t * number) {
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
	// ������� ������ ��� �������� ������ 
	record_t_l * record = malloc(sizeof(note));
	// ������� ������ ��� ������.
	record->data = malloc(sizeof(record_t));

	if (record != NULL) {
		strcpy(record->data->surname, note.surname);
		record->data->height = note.height;
		record->data->weight = note.weight;

		// ���� ��� ���� ������
		if (list->first == NULL) {
			list->first = record;
			list->last = record;
			// ��������� ������
			record->next = record;
			record->prev = record;
		}
		else {
			// ��� ���������� ���� ��� ���������
			record->prev = list->last;

			// ������ ���������� ���� � �����
			list->last->next = record;

			// ���� ���������� ���������
			list->last = record;

			// ���������� ����� ���, ��������� �� ����
			record->next = record;

	
		}
		return 1;
	}
	
	return 0;
	
}



/*
�������� ������ � ������� number
*/
uint8_t replace_db(record_t note, rn_t number) {
	if (DB == "ARRAY") {
		if (replace_db_arr(note, &base, number)) {
			return 1;
		}
		else {
			return 0;
		}
	}

	else if (DB == "LIST") {
		if (replace_db_list(note, &list, number)) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		printf(ERROR_DB);
		return 0;
	}
	return 0;
}

uint8_t replace_db_arr(record_t note, record_db_a * base, rn_t number) {
	if (number < DB_SIZE) {
		strcpy(base->db[number].surname, note.surname);
		base->db[number].height = note.height;
		base->db[number].weight = note.weight;
		return 1;
	}
	return 0;
}


/*
�������� ������� � number � ���� list �� note.
*/
uint8_t replace_db_list(record_t note, record_db_l * list, rn_t number) {
	record_t_l * rec = record_of_list(list, number);

	if (rec != NULL) {
		strcpy(rec->data->surname, note.surname);
		rec->data->height = note.height;
		rec->data->weight = note.weight;
		return 1;
	}

	return 0;

}


uint8_t insert_db(record_t note, rn_t number, insert_t specifier ) {
	if (DB == "ARRAY") {
		if (insert_db_arr(note, &base, number, specifier)) {
			return 1;
		}
		else {
			return 0;
		}
	}

	else if (DB == "LIST") {
		if (insert_db_list(note, &list, number, specifier)) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		printf(ERROR_DB);
		return 0;
	}
	return 0;
}

uint8_t insert_db_arr(record_t note, record_db_a * base, rn_t number, insert_t specifier) {
	// ����� �������� ���������
	if (specifier == BEFORE) {
		// ������� ���� �� ���� �������.
		for (uint8_t i = base->pointer; i > number; i--) {
			//base->db[i] = base->db[i - 1];
			strcpy(base->db[i].surname, base->db[i - 1].surname);
			base->db[i].height = base->db[i - 1].height;
			base->db[i].weight = base->db[i - 1].weight;
		}

		strcpy(base->db[number].surname, note.surname);
		base->db[number].height = note.height;
		base->db[number].weight = note.weight;


		// ��������� ��������� ������ ������
		base->pointer++;

		return 1;
	}

	// ����� ��������� ��������
	if (specifier == AFTER) {
		if (number == base->pointer) {
			return write_db_arr(note, base, NULL);
		}
		// ������� ����� ��������, ��� �� �� ����� ��� ������� ���� �������+1.
		// ������� ����������.
		return insert_db_arr(note, base, (number + 1), BEFORE);

	}

	return 0;
}


uint8_t insert_db_list(record_t note, record_db_l * list, rn_t number, insert_t specifier) {
	// ����� �������� ���������
	if (specifier == BEFORE) { 
		
		record_t_l * target = record_of_list(list, number);
		if (target == NULL) {
			return 0;
		}

		// ������� ������ ��� �������� ������ 
		record_t_l * record = malloc(sizeof(note));
		// ������� ������ ��� ������.
		record->data = malloc(sizeof(record_t));

		if (record != NULL) {
			strcpy(record->data->surname, note.surname);
			record->data->height = note.height;
			record->data->weight = note.weight;
		}

		// ������ ���������

		if (target == list->first) { // ������� ����� ������
			record->next = target;
			record->prev = record;

			list->first = record;

			target->prev = record;
		}
		else { // ������� �������

			// ��������� ������ ��� ������������ ��������. 
			record->next = target; 
			record->prev = target->prev;

			// ������� ������ ����� ����� �����������.
			target->prev->next = record;

			// ������� ������ �� ������� ����.
			target->prev = record;


		}

		return 1;

	}

	// ������� ����� ���������
	if (specifier == AFTER) {
		if (number == ( amount_db_list(list) - 1) ) {// ������ ����� ����������. ������� ���������� ��������.
			write_db_list(note, list, NULL);
			return 1;
		}
		// ������� ����� ��������, ��� �� �� ����� ��� ������� ���� �������+1.
		// ������� ����������.
		return insert_db_list(note, list, (number+1), BEFORE);
	}

	return 0;
}
/*
������� ������� �� ������
*/
record_t_l * record_of_list(record_db_l * list, rn_t number) {
	rn_t count = 0;
	record_t_l * follow = list->first;

	if (follow != NULL) {

		do {
			if (count == number) {
				return follow;
			}
			follow = follow->next;
			count++;
		} while (follow != list->last);

	}
	return NULL;
}