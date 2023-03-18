#include "first_parse.h"
#include "check_input_files.h"
#include "assembler_helping_function.h"
#include "error_handeling.h"

int first_parse(char* file_name) {
    /* File declarations: */
    char *only_file_name = strtok(file_name, FILE_DELIMITER);
    FILE *am_file;

    /* Reading loop declarations */
    char *reading_line;
    char *rest_of_the_line;
    char *word_parse;
    char char_string;
    char *temp_string;
    char *operand_phrase;
    int word_counter = 0;
    int IC =0, DC = 0;
    int is_qoute = 0;
    int op_code;
    int data_instruction_code;
    int entry_or_extern;
    int word_is_register = 0;
    int line_counter = 1;


    /* Errors: */
    char* error_def = NULL;
    /* Symbol declarations */
    char *potential_symbol_name;
    int decimal_adress = BASE_DECIMAL_ADD;

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

    printf("opening am file: %s\n", only_file_name);
    /* Main reading loop, iterating over the file line by line */
    while (fgets(reading_line, MAX_LINE_LENGTH, am_file) != NULL) {
        /* Allocating memory for the symbol name pointer: */
        potential_symbol_name = malloc(MAX_SYMBOL_LENGTH);
        if(potential_symbol_name == NULL){
            printf("Unable to allocate memory for symbol name\n");
            return -1;
        }

        /* Reading in from the line*/
        sscanf(reading_line, " %s ", potential_symbol_name);

        if(is_skip_line(potential_symbol_name) == 0){
            continue; /* do we */
        }
        /* Expression for finding a symbol: */
        else if(check_is_line_starting_with_symbol(potential_symbol_name) == 0){
            if(check_valid_symbol_name(potential_symbol_name, line_counter) == 0){
                /* Allocating memory for symbol struct */
                if(allocate_memory_for_symbol()== 0){

                    /* Assigning the symbol his decimal address: */
                    append_decimal_adress_to_symbol(decimal_adress);

                    /* Reading everything that comes after the symbol: */
                    rest_of_the_line = malloc(MAX_LINE_LENGTH - strlen(potential_symbol_name));
                    if(rest_of_the_line == NULL){
                        printf("Unable to allocate memory for symbol\n");
                        return -1;
                    }
                    /* Everything after the colon */
                    rest_of_the_line = strchr(reading_line, ':');
                    rest_of_the_line++;

                    /* Parsing word by word and checking what are the next instructions given in our assembly program: */
                    word_parse = strtok(rest_of_the_line, " \n");
                    while(word_parse!=NULL){
                        /* Basic initialization for our operation codes/data instructions */
                        data_instruction_code = check_if_word_is_data_instruction(word_parse);
                        op_code = check_if_word_is_op(word_parse);
                        /* We found an operation code defined in the project */
                        if(op_code != -1){
                            /* Flow control on the index of the operation code and behavior declaration for our decimal
                             * address counter */
                            switch(op_code) { /* Documentation is written in the order of the cases: */
                                /* mov, cmp, add, sub, lea :*/
                                case 0:
                                case 1:
                                case 2:
                                case 3:
                                case 6:
                                    word_counter++;
                                    word_parse = strtok(NULL, "\n");
                                    operand_phrase = malloc(sizeof(word_parse));
                                    strcpy(operand_phrase, word_parse);
                                    if(is_valid_operand_assignment(word_parse, line_counter, op_code) == 0){
                                        word_parse = strtok(word_parse, "\n, ");
                                        while(word_parse!=NULL){
                                            if(check_if_word_is_register(word_parse) != -1){
                                                word_is_register++;
                                            }
                                            else {
                                                word_counter++;
                                            }
                                        word_parse = strtok(NULL, "\n, ");
                                    }
                                    if(word_is_register + word_counter != 3){
                                        error_def = "Invalid number of params";
                                        register_new_error(line_counter, error_def);
                                    }
                                    binary_encoding(op_code, decimal_adress, operand_phrase, word_is_register, line_counter);
                                    if(word_is_register == 2){
                                        decimal_adress += word_counter;
                                        decimal_adress ++;
                                    }
                                    else{
                                        decimal_adress += word_counter;
                                        decimal_adress += word_is_register;
                                    }
                                    word_is_register = 0;
                                    word_counter = 0;
                                }
                                break;
                                /* not, clr, inc, dec, red, prn */
                                case 4:
                                case 5:
                                case 7:
                                case 8:
                                case 11:
                                case 12:
                                    word_counter++;
                                    word_parse = strtok(NULL, "\n");
                                    operand_phrase = malloc(sizeof(word_parse));
                                    strcpy(operand_phrase, word_parse);
                                    if(is_valid_operand_assignment(word_parse, line_counter, op_code) == 0){
                                        word_parse = strtok(word_parse, "\n, ");
                                        if(check_if_word_is_register(word_parse) != -1){
                                            word_is_register++;
                                        }
                                        else {
                                            word_counter++;
                                        }
                                        strtok(NULL, "\n, ");
                                        if(word_is_register + word_counter != 2){
                                            error_def = "Invalid number of params";
                                            register_new_error(line_counter, error_def);
                                        }
                                        binary_encoding(op_code, decimal_adress, operand_phrase, word_is_register, line_counter);
                                        if(word_is_register == 2){
                                            decimal_adress += word_counter;
                                            decimal_adress ++;
                                        }
                                        else{
                                            decimal_adress += word_counter;
                                            decimal_adress += word_is_register;
                                        }
                                        word_is_register = 0;
                                        word_counter = 0;
                                    }
                                break;
                                /*jmp, bne, jsr*/
                                case 9:
                                case 10:
                                case 13:
                                    word_counter++;
                                    word_parse = strtok(NULL, "\n");
                                    operand_phrase = malloc(sizeof(word_parse));
                                    strcpy(operand_phrase, word_parse);
                                    if(is_valid_operand_assignment(word_parse, line_counter, op_code) == 0){
                                        word_parse = strtok(word_parse, "(, ");
                                        while(word_parse != NULL){
                                            if(word_counter == 1 && check_if_word_is_register(word_parse) != -1){
                                                error_def = "Invalid syntax";
                                                register_new_error(line_counter, error_def);
                                                word_counter++;
                                            }
                                            else if(check_if_word_is_register(word_parse) != -1){
                                                word_is_register++;
                                            }
                                            else {
                                                word_counter++;
                                            }
                                            word_parse = strtok(NULL, ",) \n");
                                        }
                                        if(word_is_register + word_counter != 4 && word_counter + word_is_register !=2){
                                            error_def = "Invalid number of params";
                                            register_new_error(line_counter, error_def);
                                        }
                                        binary_encoding(op_code, decimal_adress, operand_phrase, word_is_register, line_counter);
                                        if(word_is_register == 2){
                                            decimal_adress += word_counter;
                                            decimal_adress ++;
                                        }
                                        else{
                                            decimal_adress += word_counter;
                                            decimal_adress += word_is_register;
                                        }
                                        word_is_register = 0;
                                        word_counter = 0;
                                    }
                                    break;
                                /* rts, stop */
                                case 14:
                                case 15:
                                    binary_encoding(op_code, decimal_adress, operand_phrase, word_is_register, line_counter);
                                    decimal_adress ++;
                                    word_is_register = 0;
                                    word_counter = 0;
                                    break;
                            }
                            IC++;
                        }
                            /* If we didn't receive an op code we check if it is: .string or .data */
                        else if(check_if_word_is_data_instruction(word_parse)!=-1){
                            /* Flow control for .string and .data */
                            switch(data_instruction_code){
                                /* .data */
                                case 0:
                                    word_parse = strtok(NULL, "\n");
                                    operand_phrase = malloc(sizeof(word_parse));
                                    strcpy(operand_phrase, word_parse);
                                    if(is_valid_data_instruct(word_parse, line_counter) == 0){
                                        word_parse = strtok(word_parse, ", \n");
                                        while(word_parse != NULL){
                                            word_parse = strtok(NULL, ", \n");
                                            word_counter ++;
                                        }
                                    }
                                    binary_encoding_for_data(decimal_adress, operand_phrase, line_counter);
                                    decimal_adress += word_counter;
                                    word_counter = 0;
                                    break;
                                /* .string */
                                case 1:
                                    word_parse = strtok(NULL, "\n");
                                    operand_phrase = malloc(sizeof(word_parse));
                                    strcpy(operand_phrase, word_parse);
                                    if(is_valid_string(word_parse, line_counter) == 0){
                                        temp_string = malloc(strlen(word_parse)+1);
                                        strcpy(temp_string,word_parse);
                                        for (char_string = *temp_string; char_string != '\0'; char_string = *++temp_string) {
                                            if(char_string == '"') {
                                                is_qoute ++;
                                            }
                                            else if ((char_string == ' ') && (is_qoute == 0 || is_qoute == 2)){
                                                continue;
                                            }
                                            else {
                                                word_counter++;
                                            }
                                        }
                                        word_counter ++; /*need to add null pointer*/

                                    }
                                    binary_encoding_for_string(decimal_adress, operand_phrase, line_counter);
                                    decimal_adress += word_counter;
                                    word_counter = 0;
                                    is_qoute = 0;
                                    break;

                            }
                            DC++;
                        }else{
                            error_def = "Invalid syntax";
                            register_new_error(line_counter, error_def);
                            break;
                        }
                        word_parse = strtok(NULL, " \n");
                        word_counter++;
                    }
                    /* adding the symbol name */
                    if(return_if_symbol_head_null() != 1){
                        insert_new_symbol(line_counter, potential_symbol_name);
                    }
                    else{
                        insert_symbol(potential_symbol_name);
                    }
                    word_counter = 0;
                }
            }
        }/* Not starting with symbol, same methodology, just working on incrementing the decimal address on lines
        without symbols */
        else{
            word_parse = strtok(reading_line, " \n");
            while(word_parse!=NULL){
                data_instruction_code = check_if_word_is_data_instruction(word_parse);
                op_code = check_if_word_is_op(word_parse);
                if(op_code != -1){
                    /* Flow control on the index of the operation code and behavior declaration for our decimal
                     * address counter */
                    switch(op_code) { /* Documentation is written in the order of the cases: */
                        /* mov, cmp, add, sub, lea :*/
                            case 0:
                            case 1:
                            case 2:
                            case 3:
                            case 6:
                                word_counter++;
                                word_parse = strtok(NULL, "\n");
                                operand_phrase = malloc(sizeof(word_parse));
                                strcpy(operand_phrase, word_parse);
                                if(is_valid_operand_assignment(word_parse, line_counter, op_code) == 0){
                                    word_parse = strtok(word_parse, "\n, ");
                                    while(word_parse!=NULL){
                                    if(check_if_word_is_register(word_parse) != -1){
                                        word_is_register++;
                                    }
                                    else {
                                        word_counter++;
                                    }
                                    word_parse = strtok(NULL, "\n, ");
                                }
                                if(word_is_register + word_counter != 3){
                                    error_def = "Invalid number of params";
                                    register_new_error(line_counter, error_def);
                                }
                                binary_encoding(op_code, decimal_adress, operand_phrase, word_is_register, line_counter);
                                if(word_is_register == 2){
                                    decimal_adress += word_counter;
                                    decimal_adress ++;
                                }
                                else{
                                    decimal_adress += word_counter;
                                    decimal_adress += word_is_register;
                                }
                                word_is_register = 0;
                                word_counter = 0;
                            }
                            break;
                            /* not, clr, inc, dec, red, prn */
                            case 4:
                            case 5:
                            case 7:
                            case 8:
                            case 11:
                            case 12:
                                word_counter++;
                                word_parse = strtok(NULL, "\n");
                                operand_phrase = malloc(sizeof(word_parse));
                                strcpy(operand_phrase, word_parse);
                                if(is_valid_operand_assignment(word_parse, line_counter, op_code) == 0){
                                    word_parse = strtok(word_parse, "\n, ");
                                    if(check_if_word_is_register(word_parse) != -1){
                                        word_is_register++;
                                    }
                                    else {
                                        word_counter++;
                                    }
                                    strtok(NULL, "\n, ");
                                    if(word_is_register + word_counter != 2){
                                        error_def = "Invalid number of params";
                                        register_new_error(line_counter, error_def);
                                    }
                                    binary_encoding(op_code, decimal_adress, operand_phrase, word_is_register, line_counter);
                                    if(word_is_register == 2){
                                        decimal_adress += word_counter;
                                        decimal_adress ++;
                                    }
                                    else{
                                        decimal_adress += word_counter;
                                        decimal_adress += word_is_register;
                                    }
                                    word_is_register = 0;
                                    word_counter = 0;
                                }
                            break;
                            /*jmp, bne, jsr*/
                        case 9:
                        case 10:
                        case 13:
                            word_counter++;
                            word_parse = strtok(NULL, "\n");
                            operand_phrase = malloc(sizeof(word_parse));
                            strcpy(operand_phrase, word_parse);
                            if(is_valid_operand_assignment(word_parse, line_counter, op_code) == 0){
                                word_parse = strtok(word_parse, "(, ");
                                while(word_parse != NULL){
                                    if(word_counter == 1 && check_if_word_is_register(word_parse) != -1){
                                        error_def = "Invalid syntax";
                                        register_new_error(line_counter, error_def);
                                        word_counter++;
                                    }
                                    else if(check_if_word_is_register(word_parse) != -1){
                                        word_is_register++;
                                    }
                                    else {
                                        word_counter++;
                                    }
                                    word_parse = strtok(NULL, ",) \n");
                                }
                                if(word_is_register + word_counter != 4 && word_counter + word_is_register !=2){
                                    error_def = "Invalid number of params";
                                    register_new_error(line_counter, error_def);
                                }
                                binary_encoding(op_code, decimal_adress, operand_phrase, word_is_register, line_counter);
                                if(word_is_register == 2){
                                    decimal_adress += word_counter;
                                    decimal_adress ++;
                                }
                                else{
                                    decimal_adress += word_counter;
                                    decimal_adress += word_is_register;
                                }
                                word_is_register = 0;
                                word_counter = 0;
                            }
                            break;
                            /* rts, stop */
                        case 14:
                        case 15:
                            binary_encoding(op_code, decimal_adress, operand_phrase, word_is_register, line_counter);
                            decimal_adress ++;
                            word_is_register = 0;
                            word_counter = 0;
                            break;
                    }
                }
                else if(check_if_word_is_data_instruction(word_parse)!=-1){
                    switch(data_instruction_code){
                        /* .data */
                        case 0:
                            word_parse = strtok(NULL, "\n");
                            if(is_valid_data_instruct(word_parse, line_counter) == 0){
                                word_parse = strtok(word_parse, ", \n");
                                operand_phrase = malloc(sizeof(word_parse));
                                strcpy(operand_phrase, word_parse);
                                while(word_parse != NULL){
                                    word_parse = strtok(NULL, ", \n");
                                    word_counter ++;
                                }
                            };
                            binary_encoding_for_data(decimal_adress, operand_phrase, line_counter);
                            decimal_adress += word_counter;
                            word_counter = 0;
                            break;
                        /* .string */
                        case 1:
                            word_parse = strtok(NULL, "\n");

                            if(is_valid_string(word_parse, line_counter) == 0){
                                temp_string = malloc(strlen(word_parse)+1);
                                strcpy(temp_string,word_parse);
                                for (char_string = *temp_string; char_string != '\0'; char_string = *++temp_string) {
                                    if(char_string == '"') {
                                        is_qoute ++;
                                    }
                                    else if ((char_string == ' ') && (is_qoute == 0 || is_qoute == 2)){
                                        continue;
                                    }
                                    else {
                                        word_counter++;
                                    }
                                }
                                word_counter ++; /*need to add null pointer*/

                            }
                            decimal_adress += word_counter;
                            word_counter = 0;
                            is_qoute = 0;
                            break;

                        }
                    DC++;
                }
                else if(check_if_word_entry_extern_instruction(word_parse)!=-1){
                    entry_or_extern = check_if_word_entry_extern_instruction(word_parse);
                    switch(entry_or_extern){
                        /* extern */
                        case 0:
                            word_parse = strtok(NULL, "\n");
                            if(check_if_potential_symbol_name(word_parse) != -1){
                                if(allocate_memory_for_extern() == 0){
                                    insert_new_extern(line_counter, word_parse);
                                }
                            }else{
                                error_def = "Invalid syntax";
                                register_new_error(line_counter, error_def);
                            }
                            break;
                        /* entry */
                        case 1:
                            word_parse = strtok(NULL, "\n");
                            if(check_if_potential_symbol_name(word_parse) != -1){
                                if(allocate_memory_for_entry() == 0){
                                    insert_new_entry(line_counter, word_parse);
                                }
                            }else{
                                error_def = "Invalid syntax";
                                register_new_error(line_counter, error_def);
                            }
                            break;
                    }
                }
                else{
                    error_def = "Invalid syntax";
                    register_new_error(line_counter, error_def);
                    break;
                }
                /* cases 14 or 15 not forwarding */
                word_parse = NULL;
            }
            decimal_adress = decimal_adress + word_counter;
            word_is_register = 0;
            word_counter = 0;
        }
        rest_of_the_line = NULL;
        word_parse = NULL;
        line_counter++;
    }
    /* Free all the memory: */
    free(word_parse);
    free(rest_of_the_line);
    free(reading_line);
    is_error = return_is_error();
    if(is_error == 1){
        free_symbols();
        free_binary_list();
        free_entry_list();
        free_extern_list();
        fclose(am_file);
        return is_error;
    }
    print_symbols();
    print_binary_list();
    fclose(am_file);
    return is_error;
}


