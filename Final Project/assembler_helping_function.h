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
#define SYMBOL_TO_BINARY_OP_CODE 20
#define EXTERN_OP_CODE 21
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "structures.h"

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

/*
 * binary_encoding method:
 * Will receive a line and convert the line to binary according to the instructions given in the project.
 * Input:
 * 1.op_code -> the operation code used in the line.
 * 2.decimal_adress -> the decimal adress of the line given.
 * 3.operand_phrase -> the operands phrase coming after the op code used.
 * 4.number_of_registers -> the number of registers given in the operand phrase.
 * 5.line-> debuging reasons needs to be removed later <<<<<<<<<<<<<
 */
void binary_encoding(int op_code, int decimal_adress, char *operand_phrase, int number_of_registers, int line);

/*
 * allocate_memory_for_binary_code method:
 * Does excatly what it says, allocates memory for a new line of binary code.
 * Output:
 * 1. return -1 if it wasnt able to allocate memory.
 * 2. return 0 if allocation worked.
 */
int allocate_memory_for_binary_code();

/*
 * print_binary_list method:
 * prints the binary list we saved.
 */
void print_binary_list();

/*
 * free_binary_list method:
 * frees the memory of the binary list.
 */
void free_binary_list();

/*
 * insert_new_binary method:
 * inserts a new binary line of code to the binary list we have.
 */
void insert_new_binary();

/*
 * int_to_ascii method:
 * receives an interger and converts the integer to ascii.
 * Input:
 * 1.number-> the number we want to convert to ascii.
 * Output:
 * 1.the number in ascii code.
 */
int int_to_ascii(int number);

/*
 * int_to_binary method:
 * receives an integer and converts it to 1's compliment binary.
 * Input:
 * 1. number -> the number we want to convert to binary.
 * 2. op_code -> the operation code used to prvoke binary encoding.
 * Output:
 * returns a string of X bits representing a binary number, X changes due to the op code given to the function.
 */
char* int_to_binary(int number, int op_code);

/*
 * compliment_two_binary method:
 * receives a char pointer which points to a compliment 1's binary number and an integer which represented in binary.
 * and converts it to 2's compliment binary.
 * Input:
 * 1. binary_number -> the char pointer that points to the 1's binary number.
 * 2. number -> the number we represented in binary.
 * Output:
 * returns a string of X bits representing a 2's compliment binary number, X changes due to the op code given to the function.
 */
char* compliment_two_binary(char* binary_number, int number);

/*
 * Both of the methods below does the same as binary encoding with different rules.
 */
void binary_encoding_for_data(int decimal_adress, char *operand_phrase, int line);

void binary_encoding_for_string(int decimal_adress, char *operand_phrase, int line);

/*
 * potential_symbol_to_binary:
 * inserts a new binary line of code to the missing line from first_parse.
 * method uses:
 * potential_symbol_to_binary, check_if_in_symbol_table, write_symbol_binary
 */
void potential_symbol_to_binary(char* potential_symbol_name, int line_counter);

/*
 * check_if_potential_symbol_name:
 * receives a string pointer to a potential symbol name.
 * Input:
 * 1. potential_symbol -> the string pointer.
 * Output:
 * 1. return -1 if its not a valid symbol name.
 * 2. return 0 if its a valid symbol name.
 */
int check_if_potential_symbol_name(char *potential_symbol);

/*
 * check_if_in_symbol_table:
 * receives a string pointer to a valid symbol name so
 * we can check if he is in our symbol_table.
 * Input:
 * 1. potential_symbol -> the string pointer.
 * Output:
 * 1. return int decimal number if its in symbol_table.
 * 2. return 0 if its not a in symbol_table.
 */
int check_if_in_symbol_table(char* potential_symbol_name);

/*
 * write_symbol_binary:
 * inserts decimal address to binary into the binary list
 */
void write_symbol_binary(char* decimal_address);

/*
 * clean_potential_symbol_to_binray:
 * delete the Colon from out our symbols
 */
void clean_potential_symbol_to_binray();

/*
 * create_object_file:
 * creating a file object from the given file name
 * Input:
 * 1. file_name -> the file name so we can create the designated file.
 * Output:
 * 1. return -1 if there was a problem printing to a file.
 * 2. return 0 if .ob file was created.
 */
int create_object_file(char* file_name);


/*
 * allocate_memory_for_entry:
 * allocating memory for entry op_code
 * Output:
 * 1. return -1 Unable allocate memory.
 * 2. return 0 memory allocation succeeded.
 */
int allocate_memory_for_entry();

/*
 * allocate_memory_for_extern:
 * allocating memory for extern op_code
 * Output:
 * 1. return -1 Unable allocate memory.
 * 2. return 0 memory allocation succeeded.
 */
int allocate_memory_for_extern();

/*
 * check_entry_in_extern:
 * searching in extren table if there is the same symbol name as entry.
 * Input:
 * 1. potential_symbol -> the string pointer. 
 * Output:
 * 1. return 1 entry symbol is in extern table.
 * 2. return 0 entry symbol isnt in extern table.
 */
int check_entry_in_extern(char *potential_symbol_name);

/*
 * check_extern_in_entry:
 * searching in entry table if there is the same symbol name as extren.
 * Input:
 * 1. potential_symbol -> the string pointer. 
 * Output:
 * 1. return 1 entry symbol is in entry table.
 * 2. return 0 entry symbol isnt in entry table.
 */
int check_extern_in_entry(char *potential_symbol_name);

/*
 * insert_new_entry:
 * cheking if entry symbol name already in the table if not insert
 * Input:
 * 1. line -> the number of the line. 
 * 2. symbol_name -> the string pointer. 
 */
void insert_new_entry(int line ,char *symbol_name);

/*
 * insert_entry:
 * allocating and inserting the entry symbol.
 * Input: 
 * 1. symbol_name -> the string pointer. 
 */
void insert_entry(char* symbol_name);

/*
 * insert_new_extern:
 * cheking if extern symbol name already in the table if not insert
 * Input:
 * 1. line -> the number of the line. 
 * 2. symbol_name -> the string pointer. 
 */
void insert_new_extern(int line ,char *symbol_name);

/*
 * insert_extern:
 * allocating and inserting the extern symbol.
 * Input: 
 * 1. symbol_name -> the string pointer. 
 */
void insert_extern(char* symbol_name);

/*
 * re_occuring_entry_name:
 * cheking if symbol entry name was already in the entry table
 * Input:
 * 1. potential_symbol -> the string pointer. 
 * Output:
 * 1. return 1 new entry symbol already in the entry table.
 * 2. return 0 new entry symbol isnt in entry table.
 */
int re_occuring_entry_name(char *potential_symbol_name);

/*
 * re_occuring_extren_name:
 * cheking if symbol entry name was already in the extern table
 * Input:
 * 1. potential_symbol -> the string pointer. 
 * Output:
 * 1. return 1 new extern symbol already in the table.
 * 2. return 0 new extern symbol isnt in externtable.
 */
int re_occuring_extern_name(char *potential_symbol_name);


/*
 * check_if_in_entry_table:
 * searching in entry table if there is the same symbol name as extren.
 * Input:
 * 1. potential_symbol -> the string pointer. 
 * Output:
 * 1. return 1 entry symbol is in entry table.
 * 2. return 0 entry symbol isnt in entry table.
 */
int check_if_in_entry_table(char* potential_symbol_name);

/*
 * check_if_in_extern_table:
 * searching in entry table if there is the same symbol name as extren.
 * Input:
 * 1. potential_symbol -> the string pointer. 
 * Output:
 * 1. return 1 entry symbol is in entry table.
 * 2. return 0 entry symbol isnt in entry table.
 */
int check_if_in_extern_table(char* potential_symbol_name);

/*
 * check_if_extern_using_a_symbol_from_current_file:
 * searching if extren symbol name is in symbol table
 * Output:
 * 1. return -1 extern using symbol name that in symbol table.
 * 2. return 0 entry symbol isnt in entry table.
 */
int check_if_extern_using_a_symbol_from_current_file();

/*
 * initArray:
 * allocating memory for struct DecimalAdressArray
 * Input:
 * 1. a -> struct of extern symbol name adresses. 
 * 2. initialSize -> size of the array.
 */
void initArray(struct DecimalAdressArray *a, size_t initialSize);

/*
 * insertArray:
 * inserting and re-allocating memory for struct DecimalAdressArray
 * Input:
 * 1. a -> struct of extern symbol name adresses. 
 * 2. element -> new adress to add.
 */
void insertArray(struct DecimalAdressArray *a, int element);

/*
 * freeArray:
 * free memory for struct DecimalAdressArray
 * Input:
 * 1. a -> struct of extern symbol name adresses.  
 */
void freeArray(struct DecimalAdressArray *a);

/*
 * create_entry_file:
 * checking if there is not an empty entry table and creating a file and printing the table .
 * Input:
 * 1. file_name -> given file name to create entry file for him. 
 * Output:
 * 1. return -1 there was a problem allocating memory for entry file.
 * 2. return 0 entry file was created.
 */
int create_entry_file(char* file_name);

/*
 * create_extern_file:
 * checking if there is not an empty extern table and creating a file and printing the table .
 * Input:
 * 1. file_name -> given file name to create extern file for him. 
 * Output:
 * 1. return -1 there was a problem allocating memory for extern file.
 * 2. return 0 entry file was created.
 */
int create_extern_file(char* file_name);

/*
 * free_extern_list:
 * free memory for extern symbol table.
 */
void free_extern_list();

/*
 * free_entry_list:
 * free memory for extern symbol table.
 */
void free_entry_list();

/*
 * check_if_extern_list_is_empty method:
 * will check if the extern list is empty for the extern file creation,
 * if list is empty return 1 and a file does not need to be created,
 * otherwise return 0 and create extern file.
 */
int check_if_extern_list_is_empty();


/*
 * check_if_entry_list_is_empty method:
 * will check if the entry list is empty for the entry file creation,
 * if list is empty return 1 and a file does not need to be created,
 * otherwise return 0 and create extern file.
 */
int check_if_entry_list_is_empty();

#endif

