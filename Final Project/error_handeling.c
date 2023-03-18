#include "error_handeling.h"
#include "structures.h"

/* initialization for saving the Errors */
struct Error *errors_head = NULL;
struct Error *errors_tail = NULL;
struct Error *error = NULL;


void register_new_error(int line_number, char* error_definition){
    error = malloc(sizeof(struct Error));
    error->line_number = line_number;
    error->error_defenition = malloc(sizeof(char)*MAX_LINE_LENGTH);
    strcpy(error->error_defenition, error_definition);
    /*flag*/
    is_error = 1;
    if (errors_head == NULL) {
        errors_head = error;
        errors_tail = error;
        errors_head->next = NULL;
    } else {
        errors_tail->next = error;
        errors_tail = error;
        errors_tail->next = NULL;
    }
}

void print_and_free_error(){
    while(errors_head != NULL){
        printf("Error: %s in line: %d\n", errors_head->error_defenition, errors_head->line_number);
        free_error();
        errors_head = errors_head->next;
    }
}

void free_error(){
    free(errors_head->error_defenition);
    free(errors_head);
}

int return_is_error(){
    return is_error;
}