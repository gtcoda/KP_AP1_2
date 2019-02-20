#ifndef DB_LIST_H
#define DB_LIST_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include "db.h"


uint8_t read_db_list(rn_t number, record_t * note, record_db_l *list);

uint8_t write_db_list(record_t note, record_db_l * list, rn_t * number);
uint8_t write_db_list_sort(record_t note, record_db_l * list, rn_t * number, sort_t column);


rn_t amount_db_list(record_db_l * list);

uint8_t replace_db_list(record_t note, record_db_l * list, rn_t number);

uint8_t insert_db_list(record_t note, record_db_l * list, rn_t number, insert_t specifier);

uint8_t delite_db_list(record_db_l * list, rn_t number, insert_t specirier);

uint8_t sort_db_list(record_db_l * list, sort_t column);

#endif