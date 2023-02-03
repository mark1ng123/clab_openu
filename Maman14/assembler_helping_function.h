#ifndef ASSEMBLER_HELPING_FUNCTION_H
#define ASSEMBLER_HELPING_FUNCTION_H

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


/*
 * The Error structure,
 * Every time an error will occur, it will have a line number, a text definition of the error
 * and next pointer to another Error.
 */
struct Error{
    int line_number;
    char* error_defenition;
    struct Error *next;
};

/*
 * The Symbol structure,
 * Every time a Symbol will be saved, it will have a name saved, the address in the file
 * and next pointer to another Symbol.
 */
struct Symbol{
    char *name;
    int decimal_adress;
    struct Symbol *next;
};

/*
 * check_is_line_starting_with_symbol method:
 * Input:
 * 1. symbol -> the starting word in the line is a symbol.
 * Output:
 * 1. returns 0 -> if word is symbol.
 * 2. return -1 -> if word is not symbol.
 */
int check_is_line_starting_with_symbol(char *symbol);

/*
 * check_if_word_is_op method:
 * Input:
 * 1. optional_op -> the word in the line is a operation name.
 * Output:
 * 1. returns 0 -> if word is operation name.
 * 2. return -1 -> if word is not operation name.
 */
int check_if_word_is_op(char *optional_op);

/*
 * check_if_word_is_data_instruction method:
 * Input:
 * 1. optional_instruction -> the word in the line is a instruction name.
 * Output:
 * 1. returns 0 -> if word is instruction name.
 * 2. return -1 -> if word is not instruction name.
 */
int check_if_word_is_data_instruction(char *optional_instruction);

/*
 * check_if_word_is_data_register method:
 * Input:
 * 1. optional_instruction -> the word in the line is a register name.
 * Output:
 * 1. returns 0 -> if word is register name.
 * 2. return -1 -> if word is not register name.
 */
int check_if_word_is_register(char *optional_register);

/*
 * check_if_word_is_data_instruction method:
 * Input:
 * 1. optional_instruction -> the word in the line is a instruction name.
 * Output:
 * 1. returns 0 -> if word is instruction name.
 * 2. return -1 -> if word is not instruction name.
 */
int check_if_word_entry_extern_instruction(char *optional_instruction);

/*
 * is_skip_line method:
 * Input:
 * 1. potential_symbol_name -> the starting word in the line is a Semicolon.
 * Output:
 * 1. returns 0 -> if word is Semicolon.
 * 2. return -1 -> if word is not Semicolon.
 */
int is_skip_line(char *potential_symbol_name);

/*
 * string_to_number_conv method:
 * Input:
 * 1. string -> convert string to his ascii representation.
 * Output:
 * 1. returns integer -> ascii representation of the string.
 */
int string_to_number_conv(char *string);

/*
 * calc_ascii_in_string method:
 * Input:
 * 1. char_string -> convert char to his ascii representation.
 * Output:
 * 1. returns integer -> ascii representation of the char.
 */
int calc_ascii_in_string (char char_string);

/*
 * check_valid_symbol_name method:
 * Input:
 * 1. symbol -> check if the starting symbol in the line has a valid name.
 * 2. line -> save the file line in register_new_error if the symbol is not valid symbol name
 * Output:
 * 1. returns 0 -> if word is valid symbol name.
 * 2. return -1 -> if word is not valid symbol name, print error.
 */
int check_valid_symbol_name(char *symbol, int line);

/*
 * is_valid_string method:
 * Input:
 * 1. string -> check ".string instruction" variable validation .
 * 2. line -> save the file line in register_new_error if the variable is not valid variable in .string
 * Output:
 * 1. returns 0 -> if .string variable is valid.
 * 2. return -1 -> if .string variable not is valid.
 */
int is_valid_string (char * string, int line);

/*
 * is_valid_data_instruct method:
 * Input:
 * 1. string -> check ".data instruction" variable validation .
 * 2. line -> save the file line in register_new_error if the variable is not valid variable in .data
 * Output:
 * 1. returns 0 -> if .data variable is valid.
 * 2. return -1 -> if .data variable not is valid, print error.
 */
int is_valid_data_instruct(char * string, int line);

/*
 * is_valid_operand_assignment method:
 * Input:
 * 1. operand_phrase -> the given variable of the operation code
 * 2. line_counter -> save the file line in register_new_error if the variable is not valid variable in .data
 * 3. op_code -> the given operation code name from the line
 * Output:
 * 1. returns 0 -> if operation code variable/s is valid.
 * 2. return -1 -> if operation code variable/s not is valid, print error.
 */
int is_valid_operand_assignment(char *operand_phrase, int line_counter, int op_code);

/*
 * is_valid_operand_assignment method:
 * Input:
 * 1. line_number -> file line were the error was found
 * 2. error_definition -> the given error from function in use
 */
void register_new_error(int line_number, char* error_definition);

/*
 * test_print_error method:
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

/*
 * check_if_word_is_op method:
 * Input:
 * 1. head -> head of symbols in linked list.
 * 2. potential_symbol_name -> new symbol that is not inserted the linked list.
 * Output:
 * 1. returns it -> points back to head if no re-occured symbol name appeared .
 * 2. return null -> if symbol name appeared in list.
 */
struct Symbol *re_occuring_symbol_name(struct Symbol *head, char *potential_symbol_name);

/*
 * check_if_word_is_op method:
 * Input:
 * 1. line -> save error location.
 * 2. symbol_name -> symbol name.
 * 3. head -> head of the list.
 * 4. symbol -> current symbol.
 * 5. tail -> last of the list.
 */
void insert_new_symbol(int line, char *symbol_name);

int allocate_memory_for_symbol();

void append_decimal_adress_to_symbol(int decimal_adress);

void insert_symbol(char* symbol_name);

int return_if_symbol_head_null();

void print_symbols();

void free_symbols();
#endif
