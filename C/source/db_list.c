#include "../include/db_list.h"


static record_t_l * record_of_list(record_db_l * list, rn_t number);


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


uint8_t write_db_list_sort(record_t note, record_db_l * list, rn_t * number, sort_t column) {
	// ������� ������ ��� �������� ������ 
	record_t_l * record = malloc(sizeof(note));
	// ������� ������ ��� ������.
	record->data = malloc(sizeof(record_t));

	if (record == NULL) {
		return 0;
	}
		
	
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
		// ���� ���� �������� ������ �������, ������ ��� ����� �����. �������
		
		record->next = list->first;
		record->prev = record;

		list->first->prev = record;

		// ���� ����� ������
		list->first = record;

		return 1;
	}
	
	// ���� ����� ��� ������ ��������
	do {
		// ��������� �� ���� "HEIGHT"
		if (column == HEIGHT &&
			record->data->height < target->data->height) {
			// ������ ����� ������� target


			// ������������� ����� ��� ������.
			record->next = target;
			record->prev = target->prev;

			// ������ ����� ����� ������� �������.
			target->prev->next = record;
			target->prev = record;
			return 1;

		}

		// ��������� �� ���� "WEIGHT"
		if (column == WEIGHT &&
			record->data->weight < target->data->weight) {
			return 1;
		}

		// ��������� �� ���� "SURNAME"
		if (column == SURNAME &&
			strcmp(record->data->surname, target->data->surname) < 0) {
			return 1;
		}

		target = target->next;

	} while (list->last != target);

	// ������ �� ����� � ������, ������� � ���������


	if ((column == HEIGHT &&
		record->data->height > target->data->height) ||
		(column == WEIGHT &&
		record->data->weight > target->data->weight) ||
		(column == SURNAME &&
		strcmp(record->data->surname, target->data->surname) > 0))
	{
		// ���� ���� �������� ������ ����������, ������� ���.

			// ��� ���������� ���� ��� ���������
		record->prev = list->last;

		// ������ ���������� ���� � �����
		list->last->next = record;

		// ���� ���������� ���������
		list->last = record;

		// ���������� ����� ���, ��������� �� ����
		record->next = record;
	

		return 1;
	}
	
	// ������ ����� ����� ���������.
	// ������������� ����� ��� ������.
	record->next = target;
	record->prev = target->prev;

	// ������ ����� ����� ������� �������.
	target->prev->next = record;
	target->prev = record;
	return 1;




		


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

uint8_t delite_db_list(record_db_l * list, rn_t number, insert_t specirier) {

	record_t_l * target = record_of_list(list, number);
	if (target == NULL) {
		return 0;
	}

	// ������� ���� �������
	if (specirier == ONE) {
		// ������ ������� �� ������.
		target->prev->next = target->next;
		target->next->prev = target->prev;
		// ��������� ������
		// ����������� ������� ������ ��� ������. ����� ��������� �����.
		free(target->data);
		free(target);

		return 1;
	}

	if (specirier == AFTER) {
		// �������� ����� ���������� ������� ������
		record_t_l * last_free = list->last;
		
		// ������� ������
		list->last = target->prev;
		// �������� ��������� �������
		target->prev->next = target->prev;

		
		// ����������� ������.
		// ������� �� ���������� ��������, �� ������ ����� ������
		do {
			target = last_free;
			last_free = last_free->prev;
			// ����������� ������� ������ ��� ������. ����� ��������� �����.
			free(target->data);
			free(target);

		} while (last_free != list->last);

		return 1;
	}

	if (specirier == BEFORE) {
		// �������� ����� ���������� ������� ������
		record_t_l * first_free = list->first;

		// ������� ������
		list->first = target->next;
		// �������� ������ �������
		target->next->prev = target->next;


		// ����������� ������.
		// ������� �� ������� �������� �� ������ ������ ������.
		do {
			target = first_free;
			first_free = first_free->next;
			// ����������� ������� ������ ��� ������. ����� ��������� �����.
			free(target->data);
			free(target);

		} while (first_free != list->first);

		return 1;
	}

	return 0;
}


uint8_t sort_db_list(record_db_l * list, sort_t column) {
	record_db_l sort_list; // �������������� ������
	while (amount_db_list(list) != 0) {

	}


	return 0;
}

/* ######################################  ��������������� �������  ############################################ */
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