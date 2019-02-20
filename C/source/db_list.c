#include "../include/db_list.h"


static record_t_l * record_of_list(record_db_l * list, rn_t number);


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


uint8_t write_db_list_sort(record_t note, record_db_l * list, rn_t * number, sort_t column) {
	// Выделим память для элемента списка 
	record_t_l * record = malloc(sizeof(note));
	// Выделим память для записи.
	record->data = malloc(sizeof(record_t));

	if (record == NULL) {
		return 0;
	}
		
	
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
		return 1;
	}
		
					
	record_t_l * target = list->first;

	if ( ( column == HEIGHT &&
		record->data->height < target->data->height ) ||
		( column == WEIGHT &&
		record->data->weight < target->data->weight ) ||
		( column == SURNAME &&
		strcmp(record->data->surname, target->data->surname) < 0) )
		{
		// Если наше значение меньше первого, значит оно самое малое. Обновим
		
		record->next = list->first;
		record->prev = record;

		list->first->prev = record;

		// Сами стали первым
		list->first = record;

		return 1;
	}
	
	// Ищем место для нашего элемента
	do {
		// Сортируем по полю "HEIGHT"
		if (column == HEIGHT &&
			record->data->height < target->data->height) {
			// Станем перед записью target


			// Устанавливаем связи для записи.
			record->next = target;
			record->prev = target->prev;

			// Меняем связи рядом стоящих записей.
			target->prev->next = record;
			target->prev = record;
			return 1;

		}

		// Сортируем по полю "WEIGHT"
		if (column == WEIGHT &&
			record->data->weight < target->data->weight) {
			return 1;
		}

		// Сортируем по полю "SURNAME"
		if (column == SURNAME &&
			strcmp(record->data->surname, target->data->surname) < 0) {
			return 1;
		}

		target = target->next;

	} while (list->last != target);

	// Запись не стала в список, сравним с последним


	if ((column == HEIGHT &&
		record->data->height > target->data->height) ||
		(column == WEIGHT &&
		record->data->weight > target->data->weight) ||
		(column == SURNAME &&
		strcmp(record->data->surname, target->data->surname) > 0))
	{
		// Если наше значение больше последнего, заменим его.

			// Наш предыдущий блок был последним
		record->prev = list->last;

		// Свяжем предыдущий блок с нашим
		list->last->next = record;

		// Сами становимся последним
		list->last = record;

		// Следующего блока нет, указываем на себя
		record->next = record;
	

		return 1;
	}
	
	// Займем место перед последним.
	// Устанавливаем связи для записи.
	record->next = target;
	record->prev = target->prev;

	// Меняем связи рядом стоящих записей.
	target->prev->next = record;
	target->prev = record;
	return 1;




		


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


uint8_t sort_db_list(record_db_l * list, sort_t column) {
	record_db_l sort_list; // Отсортированый список
	while (amount_db_list(list) != 0) {

	}


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