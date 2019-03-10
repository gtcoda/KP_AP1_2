#ifndef DB_H
#define DB_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>


#define SORT "BUBBLE" // BUBBLE - ���������� ���������

#define DB_START_SIZE 10 // ��������� ������ ����
#define NAME_SIZE 40

typedef uint16_t rn_t; // ��� ������ ������ � ����

// ������ ������.
typedef struct {
	char surname[NAME_SIZE];
	uint32_t height;
	float weight;
} record_t;

// ���� ������ � ��������� � ���� �������.
typedef struct {
	record_t * db;
	size_t size; // ������� ������ 
	rn_t pointer; // ����� ��������� ������
} record_db_a;

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


void create_db(record_db_a ** base);

uint8_t write_db(record_t note, rn_t * number, record_db_a * base);
uint8_t read_db(rn_t number, record_t * note, record_db_a * base);
rn_t amount_db(record_db_a * base);
uint8_t replace_db(record_t note, rn_t number, record_db_a * base);
uint8_t insert_db(record_t note, rn_t number, insert_t specifier, record_db_a * base);
uint8_t delite_db(rn_t number, insert_t specifier, record_db_a * base);
uint8_t sort_db(sort_t column, record_db_a * base);


#endif