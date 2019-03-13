#ifndef DB_H
#define DB_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>


#define SORT "BUBBLE" // BUBBLE - сортировка пузырьком

#define DB_START_SIZE 10 // Начальный размер базы
#define DB_THRESHOLD 2 // Минимально возможное количество свободных ячеек.
#define NAME_SIZE 40


typedef uint16_t rn_t; // тип номера записи в базе

typedef uint32_t h_type; // Тип поля height
typedef float w_type;	// Тип поля weight

// Формат записи.
typedef struct {
	char surname[NAME_SIZE];
	h_type height;
	w_type weight;
} record_t;

// База данных с хранением в виде массива.
typedef struct {
	record_t * db;
	size_t size; // Текущий размер 
	rn_t pointer; // Номер свободной ячейки
} record_db_a;

typedef enum {
	BEFORE,
	AFTER,
	ONE,
	INSTEAD
} insert_t;


typedef enum {
	SURNAME,
	HEIGHT, 
	WEIGHT
} sort_t;


void create_db(record_db_a ** base);

uint8_t write_db(record_t note, rn_t * number, record_db_a * base);
uint8_t read_db(rn_t number, record_t * note, record_db_a * base);
rn_t amount_db(record_db_a * base);
uint8_t insert_db(record_t note, rn_t number, insert_t specifier, record_db_a * base);
uint8_t delite_db(rn_t number, insert_t specifier, record_db_a * base);
uint8_t sort_db(sort_t column, record_db_a * base);


#endif