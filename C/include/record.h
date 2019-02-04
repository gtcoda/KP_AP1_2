/*
Модуль работы с записями
*/
#ifndef HEAP_H
#define HEAP_H

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>



#define RECORD_FILES "../text2.txt"
#define DB_SIZE 50
#define NAME_SIZE 40
#define DB "ARRAY" // LIST - связный список, ARRAY - массив


#define VIEW_HEAD "Surname | Height | Weight \n\r"
#define ERROR_DB "Not model DB!"

typedef struct {
	char surname[NAME_SIZE];
	uint32_t height;
	float weight;
} record_t;

typedef struct {
	record_t db[DB_SIZE];
	uint8_t pointer; // Номер свободной ячейки
} record_db;



typedef struct {
	char surname[NAME_SIZE];
	uint32_t height;
	float weight;
	struct record_t_s * nest;
	struct record_t_s * prev;
}record_t_s;


typedef struct {
	record_t_s * first;
	record_t_s * last;
}record_db_s;



typedef uint16_t rn_t; // тип номера записи в базе


void add_record();
void write_file();
char * mfgets(char * string, int num, FILE * filestream);
void view_record();
void read_file();

#endif 