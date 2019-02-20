#include "../include/db_arr.h"


static void swap_arr(record_t * cell_1, record_t * cell_2);

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
Возвращает количество элементов в массиве записей *base
*/
rn_t amount_db_arr(record_db_a *base) {
	return base->pointer;
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

uint8_t replace_db_arr(record_t note, record_db_a * base, rn_t number) {
	if (number < DB_SIZE) {
		strcpy(base->db[number].surname, note.surname);
		base->db[number].height = note.height;
		base->db[number].weight = note.weight;
		return 1;
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
