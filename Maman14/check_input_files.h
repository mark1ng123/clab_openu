/*
 * Check input files header file:
 * Main job is to check if the user input is valid and if the assembler is able to run.
 * Checking if the file extension is right, if there is any files given, if the files given are opening.
 */

#ifndef CHECK_INPUT_FILES_H
#define CHECK_INPUT_FILES_H
#include <stdio.h>
#include <string.h>


/*
 * number of files given method:
 * Input:
 * 1. number_of_files -> the number of files the user inputted through the terminal.
 * Output:
 * 1. returns 0 -> if there were given more than 0 files.
 * 2. return -1 -> if the user didn't input any file.
 */
int number_of_files_given(int number_of_files);

/*
 * is file valid method:
 * Input:
 * 1. *file -> One of the files the user wants to run through the assembler process.
 * Output:
 * 1. return 0 -> if the file was able to open.
 * 2. return -1 -> if the file is not opening.
 */
int is_file_valid(FILE *file);

/*
 * is file ending valid method:
 * Input:
 * 1. *file -> One of the files the user wants to run through the assembler process.
 * Output:
 * 1. return 0 -> if the file has the right .as file ext.
 * 2. return -1 -> if the file has any other file ext.
 */
int is_file_ending_valid(char* file_name);

#endif