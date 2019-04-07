#include "../include/db_arr.h"

/*
Чтение записи number из массива *base в структуру *note
Возвращает 1 в случае успеха. 0 - неудача.
*/
uint8_t read_db_arr(rn_t number, record_t * note, record_db_a * base) {

	if (number > amount_db_arr(base)){ return 0; }

	strcpy(note->surname, base->db[number].surname);
	note->height = base->db[number].height;
	note->weight = base->db[number].weight;

	return 1;
	
}



/*
Запись note в массив *base. Номер ячейки помещается в *number.
Возвращает 1 в случае успеха. 0 - неудача.
*/
uint8_t write_db_arr(record_t note, record_db_a * base, rn_t * number) {
	// У нас нет памяти 
	if (base->pointer == base->size - DB_THRESHOLD) {
		record_t * new_block;
		// Увеличим память выделеную под массив.
		// И изменим ссылку на базу. Т.к указатель может измениться.
		new_block = realloc( base->db, (base->size + DB_START_SIZE) * sizeof(record_t) );
		
		if(new_block == NULL){ // Память не выделена
			return 0;
		} 
		base->db = new_block;
		// Увеличим счетчик размера массива.
		base->size = base->size + DB_START_SIZE;
	}


	strcpy(base->db[base->pointer].surname, note.surname);
	base->db[base->pointer].height = note.height;
	base->db[base->pointer].weight = note.weight;
	base->pointer++;

	if (number != NULL) {
		*number = (rn_t)base->pointer - 1;
	}

	return 1;
}

/*
Возвращает количество элементов в массиве записей *base.
*/
rn_t amount_db_arr(record_db_a *base) {
	return base->pointer;
}



/*
Вставляет запись note в базу *base относительно number в соответствии со specifier.
*/
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
		// Указателя свободной ячейки вперед
		base->pointer++;

		strcpy(base->db[number].surname, note.surname);
		base->db[number].height = note.height;
		base->db[number].weight = note.weight;


		

		return 1;
	}

	// После выбраного элемента
	if (specifier == AFTER) {
		if (number == base->pointer) {
			return write_db_arr(note, base, NULL);
		}
		// Вставка после элемента, это то же самое что вставка перед элемент+1.
		// Вызовем рекурсивно.
		return insert_db_arr(note, base, (number + 1), BEFORE);

	}
	
	// На место выбраного элемента
	if ( (specifier == INSTEAD) || (specifier == ONE) ) {
		if (number < base->pointer) {
			strcpy(base->db[number].surname, note.surname);
			base->db[number].height = note.height;
			base->db[number].weight = note.weight;
			return 1;
		}
	}

	return 0;
}

/*
Удаление записи с номером number из бызы *base в соответствии со specifier.
*/
uint8_t delite_db_arr(record_db_a * base, rn_t number, insert_t specifier) {
	// Удалить только выбраный элемент.
	if (specifier == ONE) {
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

	// Удаление записей из базы до якорной.
	if (specifier == BEFORE) {
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
	
	// Удаление записей из базы после якорной. 
	if (specifier == AFTER) {
		if (number < base->pointer) {
			base->pointer = number;
			return 1;
		}
		
	}
	return 0;
}



/*
Сортировка базы *base по колонке column.
*/
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
	uint8_t flag;
	
	do {
		flag = 0;
		
		for (rn_t i = 0; i < (base->pointer - 1) ; i++) {
			if( (column == HEIGHT && base->db[i].height > base->db[i + 1].height) ||
				(column == WEIGHT && base->db[i].weight > base->db[i + 1].weight) ||
				(column == SURNAME && strcmp(base->db[i].surname, base->db[i + 1].surname) > 0) ){
				
				record_t A;
				A = base->db[i];
				base->db[i] = base->db[i+1];
				base->db[i+1] = A;
				flag = 1;
				
			}
		} 


	} while (flag);

	return 1;

}
