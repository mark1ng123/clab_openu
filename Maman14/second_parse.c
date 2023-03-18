#include "second_parse.h"
#include "check_input_files.h"
#include "assembler_helping_function.h"
#include "error_handeling.h"

int second_parse(char* file_name) {

    /* File declarations: */
    char *only_file_name = strtok(file_name, FILE_DELIMITER);
    FILE *am_file;

    /* Reading loop declarations */
    char *reading_line;
    char *word_parse;
    int line_counter = 0;

    /* Symbol declarations */
    char *potential_symbol_name;


    /*removing colon from symbols*/
    clean_potential_symbol_to_binray();
    /* Checking if extern is using a symbol in the current file */
    if(check_if_extern_using_a_symbol_from_current_file() == -1){
        is_error = return_is_error();
        return is_error;
    }

    /* Adding file extension .am to the file name */
    strcat(only_file_name, ".am");
    am_file = fopen(only_file_name,"r");


    /* Basic file checks */
    if(is_file_valid(am_file) == -1){
        printf("Had a problem opening one of the .am given files\n");
        return -1;
    }

    /* Allocating memory for main file reading pointer */
    reading_line = malloc(MAX_LINE_LENGTH);
    if(reading_line == NULL){
        printf("Had a problem allocating memory for the reading loop \n");
        return -1;
    }
    printf("opening second_parse am file: %s\n", only_file_name);

    /* Main reading loop, iterating over the file line by line */
    while (fgets(reading_line, MAX_LINE_LENGTH, am_file) != NULL) {
        line_counter++;
        potential_symbol_name = malloc(MAX_SYMBOL_LENGTH);
        if(potential_symbol_name == NULL){
            printf("Unable to allocate memory for symbol name\n");
            return -1;
        }/*removing starting symbol*/
        if(strstr(reading_line,".entry") != NULL || strstr(reading_line,".extern") != NULL){
            continue;
        }
        else if(strchr(reading_line,':')!= NULL){
            strtok(reading_line, ":");
            word_parse = strtok(NULL, "\n");
        }
        else{
            word_parse = strtok(reading_line, "");
        }
        word_parse = strtok(word_parse, "\n,( )");
        while(word_parse!=NULL){
            potential_symbol_to_binary(word_parse, line_counter);
            word_parse = strtok(NULL, "\n,( ) ");
        }
    }
    /* Free all the memory: */
    free(word_parse);
    free(reading_line);
    is_error = return_is_error();
    if(is_error == 1){
        print_binary_list();
        free_symbols();
        free_binary_list();
        free_entry_list();
        free_extern_list();
        fclose(am_file);
        return is_error;
    }
    fclose(am_file);
    print_binary_list();
    return is_error;
}
