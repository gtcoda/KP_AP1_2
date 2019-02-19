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

static uint8_t delite_db_arr(record_db_a * base, rn_t number, insert_t specirier);
static uint8_t delite_db_list(record_db_l * list, rn_t number, insert_t specirier);

static uint8_t sort_db_arr(record_db_a * base, sort_t column);
static uint8_t sort_bubble_db_arr(record_db_a * base, sort_t column);
static uint8_t sort_db_list(record_db_l * list, sort_t column);


static void swap_arr(record_t * cell_1, record_t * cell_2);
static record_t_l * record_of_list(record_db_l * list, rn_t number);

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
		write_db_list(note, &list, number);
		return 1;
	}
	else {
		printf(ERROR_DB);
		return 0;
	}

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


uint8_t insert_db_arr(record_t note, record_db_a * base, rn_t number, insert_t specifier) {
	// Перед выбраным элементом
	if (specifier == BEFORE) {
		// Сдвинем базу на одну позицию.
		for (rn_t i = base->pointer; i > number; i--) {
			//base->db[i] = base->db[i - 1];
			strcpy(base->db[i].surname, base->db[i - 1].surname);
			base->db[i].height = base->db[i - 1].height;
			base->db[i].weight = base->db[i - 1].weight;
		}

		strcpy(base->db[number].surname, note.surname);
		base->db[number].height = note.height;
		base->db[number].weight = note.weight;


		// Указателя свободной ячейки вперед
		base->pointer++;

		return 1;
	}

	// После выбраного элемента
	if (specifier == AFTER) {
		if (number == base->pointer) {
			return write_db_arr(note, base, NULL);
		}
		// Вставка после элемента, это то же самое что вставка перд элемент+1.
		// Вызовем рекурсивно.
		return insert_db_arr(note, base, (number + 1), BEFORE);

	}

	return 0;
}


uint8_t insert_db_list(record_t note, record_db_l * list, rn_t number, insert_t specifier) {
	// Перед выбраным элементом
	if (specifier == BEFORE) { 
		
		record_t_l * target = record_of_list(list, number);
		if (target == NULL) {
			return 0;
		}

		// Выделим память для элемента списка 
		record_t_l * record = malloc(sizeof(note));
		// Выделим память для записи.
		record->data = malloc(sizeof(record_t));

		if (record != NULL) {
			strcpy(record->data->surname, note.surname);
			record->data->height = note.height;
			record->data->weight = note.weight;
		}

		// Меняем указатели

		if (target == list->first) { // Вставка перед первым
			record->next = target;
			record->prev = record;

			list->first = record;

			target->prev = record;
		}
		else { // Обычная вставка

			// Установим ссылки для вставляемого элемента. 
			record->next = target; 
			record->prev = target->prev;

			// Обновим ссылку блока перед вставляемым.
			target->prev->next = record;

			// Обновим ссылку на целевой блок.
			target->prev = record;


		}

		return 1;

	}

	// Вставка после выбраного
	if (specifier == AFTER) {
		if (number == ( amount_db_list(list) - 1) ) {// Встака после последнего. Обычное добавление элемента.
			write_db_list(note, list, NULL);
			return 1;
		}
		// Вставка после элемента, это то же самое что вставка перд элемент+1.
		// Вызовем рекурсивно.
		return insert_db_list(note, list, (number+1), BEFORE);
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


uint8_t delite_db_arr(record_db_a * base, rn_t number, insert_t specirier) {
	if (specirier == ONE) {
		if (number < base->pointer) {
			for (rn_t i = number; i < base->pointer; i++) {
				//base->db[i] = base->db[i + 1];
				strcpy(base->db[i].surname, base->db[i + 1].surname);
				base->db[i].height = base->db[i + 1].height;
				base->db[i].weight = base->db[i + 1].weight;
			}
			base->pointer--;
			return 1;
		}
	}

	if (specirier == BEFORE) {
		if (number < base->pointer) {

			for (uint8_t i = 0; i < ( base->pointer - number - 1) ; i++) {
				//base->db[i] = base->db[number + i + 1];
				strcpy(base->db[i].surname, base->db[number + i + 1].surname);
				base->db[i].height = base->db[number + i + 1].height;
				base->db[i].weight = base->db[number + i + 1].weight;
			}

			base->pointer = base->pointer - number - 1;
			return 1;
		}
	}
	
	if (specirier == AFTER) {
		if (number < base->pointer) {
			base->pointer = number;
			return 1;
		}
		
	}
	return 0;
}

uint8_t delite_db_list(record_db_l * list, rn_t number, insert_t specirier) {

	record_t_l * target = record_of_list(list, number);
	if (target == NULL) {
		return 0;
	}

	// Удалить один элемент
	if (specirier == ONE) {
		// Уберем элемент из списка.
		target->prev->next = target->next;
		target->next->prev = target->prev;
		// Освободим память
		// Обязательно сначала память для записи. Потом структуру связи.
		free(target->data);
		free(target);

		return 1;
	}

	if (specirier == AFTER) {
		// Сохраним адрес последнего лемента списка
		record_t_l * last_free = list->last;
		
		// Обрежем список
		list->last = target->prev;
		// Завернем последний элемент
		target->prev->next = target->prev;

		
		// Освобождаем память.
		// Пройдем от последнего элемента, до нового конца списка
		do {
			target = last_free;
			last_free = last_free->prev;
			// Обязательно сначала память для записи. Потом структуру связи.
			free(target->data);
			free(target);

		} while (last_free != list->last);

		return 1;
	}

	if (specirier == BEFORE) {
		// Сохраним адрес последнего лемента списка
		record_t_l * first_free = list->first;

		// Обрежем список
		list->first = target->next;
		// Завернем первый элемент
		target->next->prev = target->next;


		// Освобождаем память.
		// Пройдем от первого элемента до нового начала списка.
		do {
			target = first_free;
			first_free = first_free->next;
			// Обязательно сначала память для записи. Потом структуру связи.
			free(target->data);
			free(target);

		} while (first_free != list->first);

		return 1;
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



uint8_t sort_db_arr(record_db_a * base, sort_t column) {
	if (SORT == "BUBBLE") {
		return sort_bubble_db_arr(base, column);
	}
	return 0;

}


/*
Сортировка массива пузырьком
*/
uint8_t sort_bubble_db_arr(record_db_a * base, sort_t column) {
	uint8_t flag = 1;
	while (flag) {
		flag = 0;

		for (rn_t i = 0; i < base->pointer - 1; i++) {
			// Сортируем по полю "HEIGHT"
			if ( column == HEIGHT && 
				 base->db[i].height > base->db[i + 1].height ) {
				swap_arr(&base->db[i], &base->db[i + 1]);
				flag = 1;
			}

			// Сортируем по полю "WEIGHT"
			if ( column == WEIGHT && 
				 base->db[i].weight > base->db[i + 1].weight ) {
				swap_arr(&base->db[i], &base->db[i + 1]);
				flag = 1;
			}

			// Сортируем по полю "SURNAME"
			if ( column == SURNAME && 
				 strcmp(base->db[i].surname, base->db[i + 1].surname) > 0  ) {
				swap_arr(&base->db[i], &base->db[i + 1]);
				flag = 1;
			}


		}

		

	}

	return 1;

}



uint8_t sort_db_list(record_db_l * list, sort_t column) {


	return 0;
}
/* ######################################  Вспомогательные функции  ############################################ */
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

/*
Для сортировки пузырьком.
Меняет местами элементы массива element1 и element2.
*/
void swap_arr(record_t * element1, record_t * element2) {
	record_t A;
	A = *element1;
	*element1 = *element2;
	*element2 = A;
}

