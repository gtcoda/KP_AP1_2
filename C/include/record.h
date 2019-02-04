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



#define RECORD_FILES "text.txt"
#define DB_SIZE 10
#define NAME_SIZE 40

typedef struct {
	char name[NAME_SIZE];
	uint32_t square;
	uint16_t ports;
} record_t;

typedef struct {
	record_t db[DB_SIZE];
	uint8_t pointer; // Номер свободной ячейки
} record_db;




void add_record();
void db_to_file();
char * mfgets(char * string, int num, FILE * filestream);
void view_record();
void file_to_db();

#endif 