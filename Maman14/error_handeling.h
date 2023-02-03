#ifndef ERROR_HANDELING_H
#define ERROR_HANDELING_H

#define MAX_LINE_LENGTH 80
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "structures.h"
/* Declarations for flags */
int is_error;


/*
 * register_new_error method:
 * Input:
 * 1. line_number -> file line were the error was found
 * 2. error_definition -> the given error from function in use
 */
void register_new_error(int line_number, char* error_definition);

/*
 * print_and_free_error method:
 * check if error head is not null, if is not null print the error_definition
 */
void print_and_free_error();

/*
 * free_error method:
 * free the memory of the error pointer
 */
void free_error();

/*
 * return_is_error method:
 * Output:
 * 1. returns flag 0 -> error was not detected in another function.
 * 2. returns flag 1 -> error was detected in another function.
 */
int return_is_error();

/* Exporting */
extern int is_error;
extern struct Error *errors_head;
extern struct Error *error;
extern struct Error *errors_tail;
#endif
