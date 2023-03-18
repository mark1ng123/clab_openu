/*
 * first_parse header:
 * Responsible for handling the first parsing of the assembler code after the macro spreading.
 * It will iterate over all the rows in the file, parse them, and extract the necessary details,
 * for the code to binary conversation.
 */
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

/* first parse method:
 * input: file_name -> file name that needs to be converted and hasnt been parsed yet.
 * output:
 * 1. is_error -> 0 if the parsing was done correctly and finished, 1 if error occurred during parse.
 */
int first_parse(char* file_name);

#endif



