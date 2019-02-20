#include "../include/db.h"
#include "../include/db_arr.h"
#include "../include/db_list.h"

record_db_a base;
record_db_l list = {NULL,NULL};

/* ######################################  Чтение из базы  ############################################ */
/*
Получить запись number из базы.
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



/* ######################################  Количество записей в базе  ############################################ */
/*
Возвращает количество записей в базе
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





/* ######################################  Запись в базу  ############################################ */

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
		write_db_list_sort(note, &list, number,HEIGHT);
		return 1;
	}
	else {
		printf(ERROR_DB);
		return 0;
	}

}




/* ######################################  Замена записи  ############################################ */
/*
Заменить запись с номером number
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





/* ######################################  Вставка в базу  ############################################ */

/*
Вставка записи note в позицию number в соответствии со спецификатором.
0 - перед элементом number
1 - после элемента number
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






/* ######################################  Удаление элементов  ############################################ */
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




/* ######################################  Сортировка  ############################################ */

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








