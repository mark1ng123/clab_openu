/*
 * Assembler Program file:
 * The program will take a code written in assembly and convert it to machine language code,
 * The program will receive through the command line the file or files the program the user wants to convert,
 * The program will work in a 3-step plan:
 * 1. Pre-assembler -> Main job is expanding macros (more doc written in the pre-assembler program files)
 * 2. First-parse -> Parsing the .am file which the pre-assembler outputs.
 * 3. Second-parse -> Parsing the .am file for the second time mainly for symbol binaries.
 * And when its finished we will receive a machine language code file ending with obj extension.
 */
#include <stdio.h>
#include "check_input_files.h"
#include "pre_assembler.h"
#include "first_parse.h"
#include "second_parse.h"
#include "assembler_helping_function.h"
#include "error_handeling.h"

/*
 * Main function:
 * Receiving the user input and navigating between the different steps the program needs to do.
 * Starting with the user input check -> pre-assembler -> ... -> machine lang code.
 */
int main(int argc, char **argv){
    int file_idx = 1;
    int given_files = argc-1;
    char *file_name;
    FILE *current_file;

    /* checking if any files were given to the assembler program */
    if(number_of_files_given(given_files) == -1){
        printf("You didnt enter any file for the assembler program\n");
        return -1;
    }

    /* main iteration, iterating over the files given and moving them through the assembler compiling process */
    for(;file_idx <= given_files; file_idx++){
        file_name = argv[file_idx];
        printf("%s\n", argv[file_idx]);

        /* checking for valid .as file extension */
        if(is_file_ending_valid(file_name) == -1){
            printf("%s is not ending with .as extension \n", file_name);
            return -1;
        }

        /* checking if a file can be opened */
        current_file = fopen(argv[file_idx], "r");
        if(is_file_valid(current_file) == -1){
            printf("Had a problem opening one of the given files\n");
            return -1;
        }


        /* step one: pre-assembler stage: */
        if(pre_assemble(current_file, file_name)==-1){
            return -1;
        }

        /*step two: first_parse stage: */

        if(first_parse(file_name) != 1){\
            /*step three: second_parse stage: */
            if(second_parse(file_name) != 1){
                /* If both stages finished correctly we create the output files */
                if(create_object_file(file_name) == -1){
                    return -1;
                }
                if(check_if_entry_list_is_empty() == 0){
                    if(create_entry_file(file_name) == -1){
                        return -1;
                    }
                }
                if(check_if_extern_list_is_empty() == 0){
                    if(create_extern_file(file_name) == -1){
                        return -1;
                    }
                }
                free_symbols();
                free_binary_list();
                free_entry_list();
                free_extern_list();
            }else{
                print_and_free_error();
            }
        }else{
            print_and_free_error();
        }
    }

    return 0;
}
