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


static record_t_l * record_of_list(record_db_l * list, rn_t number);

/* ########################################### */
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

/*
Чтение записи number из массива *base в структуру *note
Возвращает 1 в случае успеха. 0 - неудача.
*/
uint8_t read_db_arr(rn_t number, record_t * note, record_db_a * base) {
	strcpy(note->surname, base->db[number].surname);
	note->height = base->db[number].height;
	note->weight = base->db[number].weight;

	return 1;
}

/*
Чтение записи number из списка *list в структуру *note
Возвращает 1 в случае успеха. 0 - неудача.
*/
uint8_t read_db_list(rn_t number, record_t * note, record_db_l *list) {
	record_t_l * follow = list->first;
	rn_t count = 0;

	if (follow != NULL) {
		do {
			// Эта наша запись
			if (count == number) {

				strcpy(note->surname, follow->data->surname);
				note->height = follow->data->height;
				note->weight = follow->data->weight;
				return 1;
			}
			count++;
			follow = follow->next;
		} while (follow != list->last);

		// Проверим последюю запись в списке
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


/*
Возвращает количество элементов в массиве записей *base
*/
rn_t amount_db_arr(record_db_a *base) {
	return base->pointer;
}

/*
Возвращает количество элементов в списке *list
*/
rn_t amount_db_list(record_db_l * list){
	rn_t count = 0;
	record_t_l * follow = list->first;

	if (follow != NULL) {
		count = 1; // Индексы считаются от 0, количество начинается с 1
		if (list->first == list->last) { // У нас всего 1 элемент
			return count; 
		}
		else {
			// Пройдем по списку и посчитаем количество элементов
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
		return 1;
	}
	else {
		printf(ERROR_DB);
		return 0;
	}
	return 0;
}

/*
Запись записи note в массив *base. Номер ячейки помещается в *number.
Возвращает 1 в случае успеха. 0 - неудача.
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
	// Выделим память для элемента списка 
	record_t_l * record = malloc(sizeof(note));
	// Выделим память для записи.
	record->data = malloc(sizeof(record_t));

	if (record != NULL) {
		strcpy(record->data->surname, note.surname);
		record->data->height = note.height;
		record->data->weight = note.weight;

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
Заменить элемент № number в базе list на note.
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

/*
Находим элемент по номеру
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