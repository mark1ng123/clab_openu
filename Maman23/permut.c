/*
 * Permut program:
 * Main program, the program will receive arguments through the command line,
 * When the 1st argument is a data file, and the 2nd file is a string,
 * If all arguments are valid the program will print out all the permutation of the given string by the user.
 */

#include "input_check.h"
#include "algo.h"
#include <stdio.h>
#include <string.h>

#define MAX 512



int main(int argc, char **argv){
    FILE *file;
    char wanted_string[MAX];
    char current_word[MAX];

    /* Checking if the number of arguments received is on point. */
    if(check_count_param(argc) != 0){
        fprintf(stderr,"Error: You entered a bad number of arguments. \n");
        return -1;
    }

    file = fopen(argv[1], "r");
    strcpy(wanted_string, argv[2]);

    /* Checking if the file opened up successfully. */
    if(check_file_open(file) != 0){
        fprintf(stderr, "Error: Had a problem opening the given file. \n");
        return -1;
    }

    /* If we opened the file successfully, checking if the file is not empty. */
    if(is_file_empty(file) == 0){
        fprintf(stderr, "Error: File is empty.\n");
        fclose(file);
        return -1;
    }

    /* Reading all the file contents word by word. */
    while((fscanf(file, "%s", current_word)) != EOF){
            permute(wanted_string,current_word, 0, strlen(wanted_string)-1);
    }
    fclose(file);
    return 0;
}