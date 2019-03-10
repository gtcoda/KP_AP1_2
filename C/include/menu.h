#ifndef MENU_H
#define MENU_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <windows.h>



int menu(int x, int y, const char* items[], int cnt);
void clear(int X, int Y);
#endif
