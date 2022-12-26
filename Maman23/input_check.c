/*
 * input check program:
 * Will implement every method declared in input check header file.
 */
#include "input_check.h"


#define VALID_NUMBER_OF_PARAMS 3


int check_count_param(int number_of_params){
    if(number_of_params != VALID_NUMBER_OF_PARAMS){
        return -1;
    }
    return 0;
}

int check_file_open(FILE *file){
    if(file == NULL){
        return -1;
    }
    return 0;
}

int is_file_empty(FILE *file){
    unsigned long file_content_length;
    /*Seeking the end of the file*/
    fseek(file, 0, SEEK_END);
    file_content_length = (unsigned long)ftell(file);
    /* if it's bigger than 0 it has content.*/
    if(file_content_length > 0){
        rewind(file);
        return -1;
    }
    return 0;
}