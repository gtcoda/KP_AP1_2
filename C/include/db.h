#ifndef DB_H
#define DB_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>


#define DB "LIST" // LIST - св€зный список, ARRAY - массив
#define SORT "BUBBLE" // BUBBLE - сортировка пузырьком
#define SORT_FIELD "SURNAME" // SURNAME, HEIGHT, WEIGHT ѕоле сортировки

#define ERROR_DB "Not model DB!"

#define DB_SIZE 50
#define NAME_SIZE 40
typedef uint16_t rn_t; // тип номера записи в базе

typedef struct {
	char surname[NAME_SIZE];
	uint32_t height;
	float weight;
} record_t;

typedef struct {
	record_t db[DB_SIZE];
	rn_t pointer; // Ќомер свободной €чейки
} record_db_a;



typedef struct _record_t_l {
	record_t * data;
	struct _record_t_l * next;
	struct _record_t_l * prev;
}record_t_l;


typedef struct {
	record_t_l * first;
	record_t_l * last;
}record_db_l;


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

typedef uint16_t rn_t; // тип номера записи в базе


uint8_t write_db(record_t note, rn_t * number);
uint8_t read_db(rn_t number, record_t * note);
rn_t amount_db();
uint8_t replace_db(record_t note, rn_t number);
uint8_t insert_db(record_t note, rn_t number, insert_t specifier);
uint8_t delite_db(rn_t number, insert_t specifier);
uint8_t sort_db(sort_t column);


#endif