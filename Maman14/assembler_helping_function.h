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
#define BINARY_OP_CODE 4
#define REGISTER_SORTING 2
#define OPERANDS_OFFSET 6
#define BINARY_TWOS 12
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
 * check_if_word_entry_extern_instruction method:
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
 * re_occuring_symbol_name method:
 * Input:
 * 1. head -> head of symbols in linked list.
 * 2. potential_symbol_name -> new symbol that is not inserted the linked list.
 * Output:
 * 1. returns it -> points back to head if no re-occured symbol name appeared .
 * 2. return null -> if symbol name appeared in list.
 */
struct Symbol *re_occuring_symbol_name(struct Symbol *head, char *potential_symbol_name);

/*
 * insert_new_symbol method:
 * Checks if there is no reoccurrences before using the insert_symbol method, if there are it will register an error.
 * Input:
 * 1. line -> save error location.
 * 2. symbol_name -> symbol name.
 * 3. head -> head of the list.
 * 4. symbol -> current symbol.
 * 5. tail -> last of the list.
 */
void insert_new_symbol(int line, char *symbol_name);

/*
 * allocate_memory_for_symbol method:
 * Has no input, all she does is to allocate new memory for
 * potential symbol to enter, return -1 if we weren't able to allocate memory and 0 if memory was allocated.
 */
int allocate_memory_for_symbol();

/*
 * append_decimal_adress_to_symbol method:
 * Setter method, sets decimal adress into symbol struct.
 * Input:
 * 1. decimal_adress -> the adress in which the potential symbol is located.
 */
void append_decimal_adress_to_symbol(int decimal_adress);

/*
 * insert_symbol method:
 * The method does all the link list algorithm to insert the symbol in the right place, moves the head/tail
 * as much as needed to give the new symbol memory to be attached to.
 * Input:
 * 1. symbol_name -> the name of the new symbol.
 */
void insert_symbol(char* symbol_name);

/*
 * return_if_symbol_head_null method:
 * Does exactly what the name says,
 * if the head of the symbol linked list is null it return 0
 * otherwise returns 1.
 */
int return_if_symbol_head_null();

/*
 * print_symbols method:
 * printing all symbols from head to tail.
 */
void print_symbols();

/*
 * free_symbols method:
 * free the memory of the symbol list from head to tail.
 */
void free_symbols();

void binary_encoding(int op_code, int decimal_adress, char *operand_phrase, int number_of_registers, int line);

int allocate_memory_for_binary_code();

void print_binary_list();

void free_binary_list();

void insert_new_binary();

int int_to_ascii(int number);

char* int_to_binary(int number);

char* compliment_two_binary(char* binary_number, int number);

#endif
