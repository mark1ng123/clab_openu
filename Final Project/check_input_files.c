/*
 * Check input files program:
 * Implementing everything that has been written and explained in the header file.
 */

#include "check_input_files.h"
#define FILE_DELIMITER '.'
#define VALID_FILE_EXT ".as"


int number_of_files_given(int number_of_files){
    if(number_of_files == 0){
        return -1;
    }
    return 0;
}

int is_file_ending_valid(char *file_name){
    char *file_ext = strrchr(file_name, FILE_DELIMITER);
    if(strcmp(file_ext, VALID_FILE_EXT) !=0){
        return -1;
    }
    return 0;
}

int is_file_valid(FILE *file){
    if(file == NULL){
        return -1;
    }
    return 0;
}