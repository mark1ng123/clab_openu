/*
 * second_parse header:
 * Responsible for handling the second parsing of the assembler code after the intial binary list.
 * It will iterate over all the rows in the file, parse them differently, and extract the necessary details that are missing
 * in the binary list to be complete for the code to binary conversation.
 */
#ifndef SECOND_PARSE_H
#define SECOND_PARSE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * second_parse method:
 * input: file_name -> the name of the file which need to be parsed for the second time.
 * output:
 * 1. is_error -> returns 0 if it was done correctly and finished parsing, otherwise 1 if error occurred.
 */
int second_parse(char* file_name);


#endif
