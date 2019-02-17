#ifndef DB_H
#define DB_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>


#define DB "LIST" // LIST - связный список, ARRAY - массив

#define ERROR_DB "Not model DB!"

#define DB_SIZE 50
#define NAME_SIZE 40

typedef struct {
	char surname[NAME_SIZE];
	uint32_t height;
	float weight;
} record_t;

typedef struct {
	record_t db[DB_SIZE];
	uint8_t pointer; // Номер свободной ячейки
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



typedef uint16_t rn_t; // тип номера записи в базе


uint8_t write_db(record_t note, rn_t * number);
uint8_t read_db(rn_t number, record_t * note);
rn_t amount_db();
uint8_t fix_db(record_t note, rn_t number);


#endif