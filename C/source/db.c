#include "../include/db.h"
#include "../include/db_arr.h"
#include "../include/db_list.h"

record_db_a base;
record_db_l list = {NULL,NULL};

/* ######################################  ������ �� ����  ############################################ */
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



/* ######################################  ���������� ������� � ����  ############################################ */
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





/* ######################################  ������ � ����  ############################################ */

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
		write_db_list_sort(note, &list, number,HEIGHT);
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
}





/* ######################################  ������� � ����  ############################################ */

/*
������� ������ note � ������� number � ������������ �� ��������������.
0 - ����� ��������� number
1 - ����� �������� number
*/
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






/* ######################################  �������� ���������  ############################################ */
uint8_t delite_db(rn_t number, insert_t specifier) {
	if (DB == "ARRAY") {
		if (delite_db_arr(&base, number, specifier)) {
			return 1;
		}
		else {
			return 0;
		}
	}

	else if (DB == "LIST") {
		if (delite_db_list(&list, number, specifier)) {
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

uint8_t sort_db(sort_t column) {
	if (DB == "ARRAY") {
		if (sort_db_arr(&base, column)) {
			return 1;
		}
		else {
			return 0;
		}
	}

	else if (DB == "LIST") {
		if (sort_db_list(&list, column)) {
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








