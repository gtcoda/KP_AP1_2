#include "../include/db.h"
#include "../include/db_arr.h"
#include "../include/db_list.h"



void create_db(db_union * base) {
	if (DB == "ARRAY") {
		base->array = malloc(sizeof(record_db_a));
		// �������� ��������� ��������� ����.
		base->array->size = 0;
		base->array->pointer = 0;
	}
	else if (DB == "LIST") {
		record_db_l * list;
		list = malloc(sizeof(record_db_l));
		// ������� ������.
		list->first = NULL;
		list->last = NULL;
		base->list = list;
	}
}






/* ######################################  ������ �� ����  ############################################ */
/*
�������� ������ number �� ����.
*/
uint8_t read_db(rn_t number, record_t * note, db_union * base) {
	if (DB == "ARRAY") {
		return read_db_arr(number, note, base->array);
	}
	else if (DB == "LIST") {
		return read_db_list(number, note, base->list);
	}

	return 0;
}



/* ######################################  ���������� ������� � ����  ############################################ */
/*
���������� ���������� ������� � ����
*/
rn_t amount_db(db_union * base) {
	if (DB == "ARRAY") {
		return	amount_db_arr(base->array);
	}
	else if (DB == "LIST") {
		return amount_db_list(base->list);
	}

	return 0;
}





/* ######################################  ������ � ����  ############################################ */

/*
�������� ������ note � ����.
number - ��������� �� ���������� ���� rn_t, ���� ���������� ����� ������. ��� NULL - ���� �� ������������
*/
uint8_t write_db(record_t note, rn_t * number, db_union * base) {
	if (DB == "ARRAY") {
		if (write_db_arr(note, base->array, number)) {
			return 1;
		}
		else {
			return 0;
		}
	}

	else if (DB == "LIST") {
		write_db_list_sort(note, base->list, number,HEIGHT);
		return 1;
	}
	else {
		printf(ERROR_DB);
		return 0;
	}

}




/* ######################################  ������ ������  ############################################ */
/*
�������� ������ � ������� number
*/
uint8_t replace_db(record_t note, rn_t number, db_union * base) {
	if (DB == "ARRAY") {
		if (replace_db_arr(note, base->array, number)) {
			return 1;
		}
		else {
			return 0;
		}
	}

	else if (DB == "LIST") {
		if (replace_db_list(note, base->list, number)) {
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
}





/* ######################################  ������� � ����  ############################################ */

/*
������� ������ note � ������� number � ������������ �� ��������������.
0 - ����� ��������� number
1 - ����� �������� number
*/
uint8_t insert_db(record_t note, rn_t number, insert_t specifier, db_union * base) {
	if (DB == "ARRAY") {
		if (insert_db_arr(note, base->array, number, specifier)) {
			return 1;
		}
		else {
			return 0;
		}
	}

	else if (DB == "LIST") {
		if (insert_db_list(note, base->list, number, specifier)) {
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






/* ######################################  �������� ���������  ############################################ */
uint8_t delite_db(rn_t number, insert_t specifier, db_union * base) {
	if (DB == "ARRAY") {
		if (delite_db_arr(base->array, number, specifier)) {
			return 1;
		}
		else {
			return 0;
		}
	}

	else if (DB == "LIST") {
		if (delite_db_list(base->list, number, specifier)) {
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




/* ######################################  ����������  ############################################ */

uint8_t sort_db(sort_t column, db_union * base) {
	if (DB == "ARRAY") {
		if (sort_db_arr(base->array, column)) {
			return 1;
		}
		else {
			return 0;
		}
	}

	else if (DB == "LIST") {
		if (sort_db_list(base->list, column)) {
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








