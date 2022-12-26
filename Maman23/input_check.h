/*
 * Input check header file:
 * Declaring and including all the methods needed to check the user input.
 */

#ifndef INPUT_CHECK_H
#define INPUT_CHECK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Check count param method:
 * Input:
 * 1. number of params, the number of arguments the user entered.
 * Output:
 * 1. returns 0 - if the number of arguments is valid and equals to 3.
 * 2. return -1 - if the number is higher or lower.
 */
int check_count_param(int number_of_params);

/*
 * Check file open method:
 * Input:
 * 1. Pointer to a file type.
 * Output:
 * 1. return 0 - if the file opened up successfully.
 * 2. return -1 - if the file didnt open up.
 */

int check_file_open(FILE *file);

/*
 * is file empty method:
 * Input:
 * 1. Pointer to a file type.
 * Output:
 * 1. return 0 - if file is empty.
 * 2. return -1 - if file as some content.
 */
int is_file_empty(FILE *file);

#endif
