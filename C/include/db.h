#ifndef DB_H
#define DB_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>


#define DB "ARRAY" // LIST - связный список, ARRAY - массив
#define SORT "BUBBLE" // BUBBLE - сортировка пузырьком
#define SORT_FIELD "SURNAME" // SURNAME, HEIGHT, WEIGHT Поле сортировки

#define ERROR_DB "Not model DB!"

#define DB_START_SIZE 10 // начальный размер базы
#define NAME_SIZE 40

typedef uint16_t rn_t; // тип номера записи в базе

// Формат записи.
typedef struct {
	char surname[NAME_SIZE];
	uint32_t height;
	float weight;
} record_t;

// База данных с хранением в виде массива.
typedef struct {
	record_t db[DB_START_SIZE];
	size_t size; // Текущий размер 
	rn_t pointer; // Номер свободной ячейки
} record_db_a;

// Структура для хранения одной записи связного списка.
typedef struct _record_t_l {
	record_t * data;
	struct _record_t_l * next;
	struct _record_t_l * prev;
}record_t_l;

// База данных с хранением в виде связного списка.
typedef struct {
	record_t_l * first;
	record_t_l * last;
}record_db_l;

// Обьединение для доступа с разным базам.
typedef union {
	record_db_a * array;
	record_db_l * list;
} db_union;


typedef enum {
	BEFORE,
	AFTER,
	ONE
} insert_t;


typedef enum {
	SURNAME,
	HEIGHT, 
	WEIGHT
} sort_t;


void create_db(db_union * base);

uint8_t write_db(record_t note, rn_t * number, db_union * base);
uint8_t read_db(rn_t number, record_t * note, db_union * base);
rn_t amount_db(db_union * base);
uint8_t replace_db(record_t note, rn_t number, db_union * base);
uint8_t insert_db(record_t note, rn_t number, insert_t specifier, db_union * base);
uint8_t delite_db(rn_t number, insert_t specifier, db_union * base);
uint8_t sort_db(sort_t column, db_union * base);


#endif