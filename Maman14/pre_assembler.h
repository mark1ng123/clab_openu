/*
 * Pre-assembler header file:
 * The pre-assembler stage is the macro spreading stage,
 * The program will iterate over each line in the input assembly code file and look for macro declarations
 * The program will then save the macro and write it into the outfile in any place a macro was called,
 * The output of this stage will be a file ending with .am ext after all the macros as been spread,
 * and no macro declarations in the code, .am file will be a pure assembly code file.
 */

#ifndef PRE_ASSEMBLER_H
#define PRE_ASSEMBLER_H
#define FILE_DELIMITER "."
#define MAX_LINE_LENGTH 80

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * The Macro structure,
 * Every time a macro will be saved, it will have a name, a text/code written between the opening flag
 * and the closing flag and the next macro in line.
 */
typedef struct Macro{
    char *name;
    char *code;
    struct Macro *next;
}Macro;

/*
 * The pre-assemble method,
 * is the main method of this stage, it will receive one file from the user inputs and the file name,
 * then the method will iterate over the file and spread all the macros giving us the output of a new .am file
 * containing only assembly code.
 * Input:
 * 1. as_input_file -> One of the user inputted files.
 * 2. file_name -> the name of the as_input_file.
 * Output:
 * return 0 -> if the method was able to create .am file.
 * return -1 -> if something went wrong in the process.
 */
int pre_assemble(FILE *as_input_file, char* file_name);

#endif
