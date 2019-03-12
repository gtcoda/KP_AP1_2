/*
Модуль работы с записями
*/
#ifndef RECORD_H
#define RECORD_H

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "db.h"
#include "menu.h"


#define DB_DEFAULT_CREATE "CREATE DB " DB_DAFAULT_NAME

#define VIEW_HEAD "№  | Surname	| Height	| Weight \n\r"
#define VIEW_BODY "%-2u | %-10s	| %-10u	| %-10.2f \n\r"
#define SEPARATOR ":"

#define RECORD_FILES "text2.txt"
#define DEFAULT_READ_FILE "text_in.txt"
#define DEFAULT_WRITE_FILE "text_out.txt"


#define DB_SIZE 50
#define NAME_SIZE 40
#define STR_SIZE 100 // максимальная длинна вводимой строки
#define MAX_DB 5

#define FILE_NAME_SIZE NAME_SIZE

typedef struct {
	char name_db[NAME_SIZE];
	record_db_a * pointer_db;
}db;


void db_manager(void);
void db_manager_active_name(char * db_name);


void add_record(void);
void write_file(void);
void view_record();
void read_file(void);
void amount(void);
void replace(void);
void insert(void);
void delite(void);
void sort(void);
void view_record_diap(void);

char * mfgets(char * string, int num, FILE * filestream);

#endif 