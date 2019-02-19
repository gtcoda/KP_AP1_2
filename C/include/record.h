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

#define VIEW_HEAD "№  | Surname | Height | Weight \n\r"
#define SEPARATOR ":"

#define RECORD_FILES "../text2.txt"
#define DB_SIZE 50
#define NAME_SIZE 40
#define STR_SIZE 100 // максимальная длинна вводимой строки





void add_record();
void write_file();
char * mfgets(char * string, int num, FILE * filestream);
void view_record();
void read_file();
void amount(void);
void replace(void);
void insert(void);
void delite(void);
void sort(void);

#endif 