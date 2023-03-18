/*
 * Pre-assembler program:
 * Implementing everything that was explained in the header file.
 */

#include "pre_assembler.h"


int pre_assemble(FILE *as_input_file, char* file_name) {
    char *only_file_name = strtok(file_name, FILE_DELIMITER); /* taking the file name to declare the output file name*/
    /* Basic declarations for reading and writing from the input file */
    char line[MAX_LINE_LENGTH], temp_macro_name[MAX_LINE_LENGTH];
    char *reading_line;
    char *macro_name, *macro_code;
    int is_read_mcr = 0, is_read_end_mcr = 0;
    int found_macro, mcr_counter = 0;
    /* Basic declarations and initialization for saving the macros */
    struct Macro *head = NULL;
    struct Macro *tail = NULL;
    struct Macro *it = NULL;
    struct Macro *temp = NULL;
    struct Macro *macro = NULL;

    /* Output file declarations */
    FILE *am_output_file;
    printf("Creating a assembly code without macros called: %s\n", only_file_name);
    am_output_file = fopen(strcat(only_file_name, ".am"), "w");

    /* Allocating memory as the size of the max line length */
    reading_line = malloc(MAX_LINE_LENGTH);
    if(reading_line == NULL){
        printf("Had a problem allocating memory for the reading loop \n");
        return -1;
    }
    /* Reading Loop */
    while (fgets(reading_line, MAX_LINE_LENGTH, as_input_file) != NULL) {
        /* First expression checking for macro opening: */
        if ((strstr(reading_line, "mcr") !=NULL) && (strstr(reading_line, "endmcr") == NULL)) {
            sscanf(reading_line, " mcr %s" ,temp_macro_name);
            macro_name = malloc(strlen(temp_macro_name) + 1); /* Allocate memory for the macro name */
            if (macro_name == NULL) {
                printf("Had a problem allocating memory for the macro name\n");
                return -1;
            }
            strcpy(macro_name, temp_macro_name);
            is_read_mcr++; /* flagging that we found a macro and every line read afterwards belongs to the macro */
            macro_code = NULL;
            continue;
        }
            /* Second expression if we found a macro ending */
        else if (strstr(reading_line, "endmcr") != NULL && is_read_mcr != 0) {
            is_read_end_mcr ++;
            macro = malloc(sizeof(struct Macro)); /* Allocating memory for the Macro structure */
            if (macro == NULL) {
                printf("Had a problem allocating memory for macro\n");
                return -1;
            }
            /* Setters: */
            macro->name = macro_name;
            macro->code = macro_code;
            macro->next = NULL;
            /* Reset: */
            macro_name = NULL;
            macro_code = NULL;

            /* Linked list setters: */
            if (head == NULL) {
                head = macro;
                tail = macro;
            } else {
                tail->next = macro;
                tail = macro;
                tail->next = NULL;
            }
            is_read_mcr = 0;
        }
            /* Third expression if we opened a macro with the opening mcr flag write everything into the macro */
        else if(is_read_mcr != 0){
            if (macro_code == NULL) {
                macro_code = malloc(strlen(reading_line) + 1);
                if (macro_code == NULL) {
                    printf("Had a problem allocating memory for macro code\n");
                    return -1;
                }
                strcpy(macro_code, reading_line);
            } else {
                macro_code = realloc(macro_code, strlen(macro_code) + strlen(reading_line) + 1);
                if (macro_code == NULL) {
                    printf("Had a problem reallocating memory for macro code\n");
                    return -1;
                }
                strcat(macro_code, reading_line);
            }
        }
    }
    /* Finished using the reading_line pointer, so we can free it */
    free(reading_line);
    /* rewinding the file to the second writing loop */
    rewind(as_input_file);

    /* Writing loop */
    while (fgets(line, sizeof(line), as_input_file) != NULL) {
        found_macro = 0; /* macro flag */
        it = head; /* start point in the linked list: */
        /* Iterating over the Linked list */
        while (it != NULL) {
            if(strstr(line, "mcr") != NULL && strstr(line, "endmcr") == NULL){ /* Ignoring macros */
                mcr_counter++;
            }else if(strstr(line, "endmcr") != NULL){ /* Stop ignoring */
                mcr_counter = 0;
            }
            if (strstr(line, it->name) != NULL && mcr_counter==0) {
                if(it->code == NULL){
                    found_macro = 1;
                    it = it->next;
                    continue;
                }
                /* write the code instead of the macro name */
                fputs(it->code, am_output_file);
                found_macro = 1;
                break;
            }
            it = it->next;
        }
        if(mcr_counter > 0){
            continue;
        }
            /* Simple line write it */
        else if (!(found_macro) && strstr(line,"mcr") == NULL) {
            fputs(line, am_output_file);
            mcr_counter=0;
        }
    }

    /* file closing */
    fclose(as_input_file);
    fclose(am_output_file);


    /* Memory free */
    it = head;
    while(it!=NULL){
        temp = it;
        it = it->next;
        free(temp->name);
        free(temp->code);
        free(temp);
    }
    return 0;
}
