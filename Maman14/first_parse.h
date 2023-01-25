/*
 *
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


struct Symbol{
    char *name;
    int decimal_adress;
    int line;
    struct Symbol *next;
};

struct Error{
    int line_number;
    char* error_defenition;
    struct Error *next;
};


int check_valid_symbol_name(char *symbol, int line);

int check_is_line_starting_with_symbol(char *symbol);

int first_parse(char* file_name);

int check_if_word_is_op(char *optional_op);

int check_if_word_is_data_instruction(char *optional_op);

int check_if_word_entry_extern_instruction(char *optional_op);

int check_if_word_is_register(char *optional_op);

int is_skip_line(char *potential_symbol_name);

int is_valid_data_instruct(char * string, int line);

int is_valid_string (char *s, int line);

int calc_ascii_in_string (char char_string);

struct Symbol *re_occuring_symbol_name(struct Symbol *head, char *potential_symbol_name);

void register_new_error(int line_number, char* error_definition);

void insert_new_symbol(int line, char *symbol_name, struct Symbol *head, struct Symbol *symbol,  struct Symbol *tail);

void test_print_error();

int string_to_number_conv(char *string);
#endif

