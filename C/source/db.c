#include "../include/db.h"
#include "../include/db_arr.h"




void create_db(record_db_a ** base) {
	record_db_a * array;
		array = malloc(sizeof(record_db_a));
		// �������� ��������� ��������� ����.
		array->db = malloc(sizeof(record_t) * DB_START_SIZE);
		array->size = DB_START_SIZE;
		array->pointer = 0;

		*base = array;
}



/* ######################################  ������ �� ����  ############################################ */
/*
�������� ������ number �� ����.
*/
uint8_t read_db(rn_t number, record_t * note, record_db_a * base) {
	return read_db_arr(number, note, base);
}



/* ######################################  ���������� ������� � ����  ############################################ */
/*
���������� ���������� ������� � ����
*/
rn_t amount_db(record_db_a * base) {
	return	amount_db_arr(base);

}





/* ######################################  ������ � ����  ############################################ */

/*
�������� ������ note � ����.
number - ��������� �� ���������� ���� rn_t, ���� ���������� ����� ������. ��� NULL - ���� �� ������������
*/
uint8_t write_db(record_t note, rn_t * number, record_db_a * base) {

	if (write_db_arr(note, base, number)) {
		return 1;
	}
	else {
		return 0;
	}
	

}




/* ######################################  ������ ������  ############################################ */
/*
�������� ������ � ������� number
*/
uint8_t replace_db(record_t note, rn_t number, record_db_a * base) {

	if (replace_db_arr(note, base, number)) {
		return 1;
	}
	else {
		return 0;
	}
	
}





/* ######################################  ������� � ����  ############################################ */

/*
������� ������ note � ������� number � ������������ �� ��������������.
0 - ����� ��������� number
1 - ����� �������� number
*/
uint8_t insert_db(record_t note, rn_t number, insert_t specifier, record_db_a * base) {
	if (insert_db_arr(note, base, number, specifier)) {
		return 1;
	}
	else {
		return 0;
	}
}






/* ######################################  �������� ���������  ############################################ */
uint8_t delite_db(rn_t number, insert_t specifier, record_db_a * base) {

	if (delite_db_arr(base, number, specifier)) {
		return 1;
	}
	else {
		return 0;
	}

}




/* ######################################  ����������  ############################################ */

uint8_t sort_db(sort_t column, record_db_a * base) {

	if (sort_db_arr(base, column)) {
		return 1;
	}
	else {
		return 0;
	}

}








