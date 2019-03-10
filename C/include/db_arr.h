#ifndef DB_ARR_H
#define DB_ARR_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include "db.h"








uint8_t read_db_arr(rn_t number, record_t * note, record_db_a * base);

uint8_t write_db_arr(record_t note, record_db_a * base, rn_t * number);

rn_t amount_db_arr(record_db_a *base);

uint8_t replace_db_arr(record_t note, record_db_a * base, rn_t number);

uint8_t insert_db_arr(record_t note, record_db_a * base, rn_t number, insert_t specifier);

uint8_t delite_db_arr(record_db_a * base, rn_t number, insert_t specirier);

uint8_t sort_db_arr(record_db_a * base, sort_t column);
uint8_t sort_bubble_db_arr(record_db_a * base, sort_t column);




#endif