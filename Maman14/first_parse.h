
#ifndef FIRST_PARSE_H
#define FIRST_PARSE_H
#define FILE_DELIMITER "."
#define MAX_LINE_LENGTH 80
#define MAX_SYMBOL_LENGTH 30
#define NUMBER_OF_OPERATIONS 16
#define NUMBER_OF_DATA_INST 2
#define NUMBER_OF_ENT_EXT 2
#define NUMBER_OF_REGISTERS 8
#define BASE_DECIMAL_ADD 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int first_parse(char* file_name);

#endif



