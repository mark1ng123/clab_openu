#include "first_parse.h"
#include "check_input_files.h"

/* Globals */
char *valid_opcode[] = {"mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec","jmp", "bne", "red", "prn",
                              "jsr", "rts", "stop"};
char *data_instruction[] = {".data", ".string"};
char *entry_extern_instruction[] = {".extern", ".entry"};
char *valid_register_names[] = {"r0","r1", "r2", "r3", "r4", "r5", "r6","r7"};

/* Error structs */
struct Error *errors_head = NULL;
struct Error *errors_tail = NULL;
struct Error *error = NULL;

/* Did error occur flag: */
int is_error = 0;
int is_symbol_error = 0;

/*TODO:
 * 1.   .ent, .ext
 * 2.   Calculate binary address values...
 * 3.   Left Exception: invalid chars in operation codes
 */

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
    int word_counter = 0;
    int IC =0, DC = 0;
    int is_qoute = 0;
    int op_code;
    int number_of_parameters;
    int data_instruction_code;
    int word_is_register = 0;
    int line_counter = 1;


    /* Errors: */
    char* error_def = NULL;
    /* Symbol declarations */
    char *potential_symbol_name;
    int decimal_adress = BASE_DECIMAL_ADD;

    /* Linked list intialization */
    struct Symbol *head = NULL;
    struct Symbol *tail = NULL;
    struct Symbol *symbol = NULL;

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
        printf("potential_symbol: %s\n ", potential_symbol_name);

        /*~~~~~~~~~~~~~~~ do we  count the line?, probably no ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        if(is_skip_line(potential_symbol_name) == 0){
            continue; /* do we */
        }

        /* Expression for finding a symbol: */
        else if(check_is_line_starting_with_symbol(potential_symbol_name) == 0){
            if(check_valid_symbol_name(potential_symbol_name, line_counter) == 0){
                /* Allocating memory for symbol struct */
                symbol = malloc(sizeof(struct Symbol));
                if(symbol == NULL){
                    printf("Unable to allocate memory for symbol\n");
                    return -1;
                }
                printf("decimal adress: %d for symbol: %s\n", decimal_adress, potential_symbol_name);

                /* Assigning the symbol his decimal address: */
                symbol->decimal_adress = decimal_adress;

                /* Reading everything that comes after the symbol: */
                rest_of_the_line = malloc(MAX_LINE_LENGTH - strlen(potential_symbol_name));
                if(rest_of_the_line == NULL){
                    printf("Unable to allocate memory for symbol\n");
                    return -1;
                }
                /* Everything after the colon */
                rest_of_the_line = strchr(reading_line, ':');
                rest_of_the_line++;
                printf("symbol name: %s , rest:%s\n", potential_symbol_name, rest_of_the_line);

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
                                printf("operation: %s\n", word_parse);
                                word_counter++;
                                word_parse = strtok(NULL, "\n");
                                printf("word_parse: %s\n", word_parse);
                                if(is_valid_operand_assignment(word_parse, line_counter, op_code) == 0){
                                    printf("OK");
                                    word_parse = strtok(word_parse, "\n, ");
                                    while(word_parse!=NULL){
                                    if(check_if_word_is_register(word_parse) != -1){
                                        word_is_register++;
                                    }
                                    else {
                                        word_counter++;
                                    }
                                    printf("\n word_parse is: %s \n" , word_parse);
                                    word_parse = strtok(NULL, "\n, ");
                                }
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
                                printf("operation: %s\n", word_parse);
                                word_counter ++;
                                word_parse = strtok(NULL, "(, ");
                                while(word_parse!=NULL){
                                    if(check_if_word_is_register(word_parse) != -1){
                                        word_is_register++;
                                    }
                                    else {
                                        word_counter++;
                                    }
                                    word_parse = strtok(NULL, ",) \n");
                                }
                                number_of_parameters = word_counter + word_is_register;
                                if(number_of_parameters != 2){
                                    error_def = "Invalid number of params";
                                    register_new_error(line_counter, error_def);
                                }else{
                                    if(word_is_register == 2){
                                        decimal_adress += word_counter;
                                        decimal_adress ++;
                                    }
                                    else{
                                        decimal_adress += word_counter;
                                        decimal_adress += word_is_register;
                                    }
                                }
                                word_is_register = 0;
                                word_counter = 0;
                                break;
                            /*jmp, bne, jsr*/
                            case 9:
                            case 10:
                            case 13:
                                printf("operation: %s\n", word_parse);
                                word_counter ++;
                                word_parse = strtok(NULL, "(, ");
                                while(word_parse!=NULL){
                                    if(check_if_word_is_register(word_parse) != -1){
                                        word_is_register++;
                                    }
                                    else {
                                        word_counter++;
                                    }
                                    word_parse = strtok(NULL, ",) \n");
                                }
                                number_of_parameters = word_counter + word_is_register;
                                if(number_of_parameters != 2 && number_of_parameters != 4){
                                    error_def = "Invalid number of params";
                                    register_new_error(line_counter, error_def);
                                }else{
                                    if(word_is_register == 2){
                                        decimal_adress += word_counter;
                                        decimal_adress ++;
                                    }
                                    else{
                                        decimal_adress += word_counter;
                                        decimal_adress += word_is_register;
                                    }
                                }
                                word_is_register = 0;
                                word_counter = 0;
                                break;
                            /* rts, stop */
                            case 14:
                            case 15:
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
                                printf("data_instraction: %s\n", word_parse);
                                word_parse = strtok(NULL, "\n");
                                printf("current_word: %s\n", word_parse);
                                if(is_valid_data_instruct(word_parse, line_counter) == 0){
                                word_parse = strtok(word_parse, ", \n");
                                    while(word_parse != NULL){
                                        printf("Word: %s\n", word_parse);
                                        printf("ascii: %d\n", (string_to_number_conv(word_parse)));
                                        word_parse = strtok(NULL, ", \n");
                                        word_counter ++;
                                    }
                                }
                                decimal_adress += word_counter;
                                word_counter = 0;
                                break;
                            /* .string */
                            case 1:
                                printf("data_instraction: %s\n", word_parse);
                                word_parse = strtok(NULL, "\n");
                                printf("current_word: %s\n", word_parse);

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
                                            printf("%d\n",calc_ascii_in_string(char_string));
                                            word_counter++;
                                        }
                                    }
                                    printf("%d\n",'\0');
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
                        printf("ext_or_ent: %s\n", word_parse);
                    }
                    else{
                        error_def = "Invalid syntax";
                        register_new_error(line_counter, error_def);
                        break;
                    }
                    word_parse = strtok(NULL, " \n");
                    word_counter++;
                }
                /* adding the symbol name */
                if(head != NULL){
                    insert_new_symbol(line_counter, potential_symbol_name, head, symbol, tail);
                }
                else{
                    symbol->name = potential_symbol_name;
                    symbol->line = line_counter;
                    symbol->next = NULL;
                    /* Linked list setters */
                    if (head == NULL) {
                        head = symbol;
                        tail = symbol;
                    } else {
                        tail->next = symbol;
                        tail = symbol;
                    }
                }
                word_counter = 0;
            }
        }/* Not starting with symbol, same methodology, just working on incrementing the decimal address on lines
        without symbols */
        else{
            printf("line:%s \n", reading_line);
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
                            printf("operation: %s\n", word_parse);
                            word_counter++;
                            word_parse = strtok(NULL, ", ");
                            while(word_parse!=NULL){
                                if(check_if_word_is_register(word_parse) != -1){
                                    word_is_register++;
                                }
                                else {
                                    word_counter++;
                                }
                                word_parse = strtok(NULL, ",\n ");
                            }
                            number_of_parameters = word_counter + word_is_register;
                            if(number_of_parameters != 3){
                                error_def = "Invalid number of params";
                                register_new_error(line_counter, error_def);
                            }else{
                                if(word_is_register == 2){
                                    decimal_adress += word_counter;
                                    decimal_adress ++;
                                }
                                else{
                                    decimal_adress += word_counter;
                                    decimal_adress += word_is_register;
                                }
                            }
                            word_is_register = 0;
                            word_counter = 0;
                            break;
                            /* not, clr, inc, dec, red, prn */
                        case 4:
                        case 5:
                        case 7:
                        case 8:
                        case 11:
                        case 12:
                            printf("operation: %s\n", word_parse);
                            word_counter ++;
                            word_parse = strtok(NULL, "(, ");
                            while(word_parse!=NULL){
                                if(check_if_word_is_register(word_parse) != -1){
                                    word_is_register++;
                                }
                                else {
                                    word_counter++;
                                }
                                word_parse = strtok(NULL, ",) \n");
                            }
                            number_of_parameters = word_counter + word_is_register;
                            if(number_of_parameters != 2){
                                error_def = "Invalid number of params";
                                register_new_error(line_counter, error_def);
                            }else{
                                if(word_is_register == 2){
                                    decimal_adress += word_counter;
                                    decimal_adress ++;
                                }
                                else{
                                    decimal_adress += word_counter;
                                    decimal_adress += word_is_register;
                                }
                            }
                            word_is_register = 0;
                            word_counter = 0;
                            break;
                            /*jmp, bne, jsr*/
                        case 9:
                        case 10:
                        case 13:
                            printf("operation: %s\n", word_parse);
                            word_counter ++;
                            word_parse = strtok(NULL, "(, ");
                            while(word_parse!=NULL){
                                if(check_if_word_is_register(word_parse) != -1){
                                    word_is_register++;
                                }
                                else {
                                    word_counter++;
                                }
                                word_parse = strtok(NULL, ",) \n");
                            }
                            number_of_parameters = word_counter + word_is_register;
                            if(number_of_parameters != 2 && number_of_parameters != 4){
                                error_def = "Invalid number of params";
                                register_new_error(line_counter, error_def);
                            }else{
                                if(word_is_register == 2){
                                    decimal_adress += word_counter;
                                    decimal_adress ++;
                                }
                                else{
                                    decimal_adress += word_counter;
                                    decimal_adress += word_is_register;
                                }
                            }
                            word_is_register = 0;
                            word_counter = 0;
                            break;
                            /* rts, stop */
                        case 14:
                        case 15:
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
                            printf("data_instraction: %s\n", word_parse);
                                word_parse = strtok(NULL, "\n");
                                printf("current_word: %s\n", word_parse);
                                if(is_valid_data_instruct(word_parse, line_counter) == 0){
                                word_parse = strtok(word_parse, ", \n");
                                    while(word_parse != NULL){
                                        printf("Word: %s\n", word_parse);
                                        printf("ascii: %d\n", (string_to_number_conv(word_parse)));
                                        word_parse = strtok(NULL, ", \n");
                                        word_counter ++;
                                    }
                                }
                                decimal_adress += word_counter;
                                word_counter = 0;
                                break;
                        /* .string */
                        case 1:
                            printf("data_instraction: %s\n", word_parse);
                            word_parse = strtok(NULL, "\n");
                            printf("current_word: %s\n", word_parse);

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
                                        printf("%d\n",calc_ascii_in_string(char_string));
                                        word_counter++;
                                    }
                                }
                                printf("%d\n",'\0');
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
                    printf("ext_or_ent: %s\n", word_parse);
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
        printf("decimal adress : %d\n", decimal_adress);
        rest_of_the_line = NULL;
        word_parse = NULL;
        line_counter++;
    }
    /* Free all the memory: */
    free(potential_symbol_name);
    free(symbol);
    free(word_parse);
    free(rest_of_the_line);
    free(reading_line);
    test_print_error();
    free(error);
    printf("IC: %d, DC: %d\n", IC, DC);
    fclose(am_file);
    return is_error;
}

int check_is_line_starting_with_symbol(char *symbol){
    if(symbol[strlen(symbol)-1] == ':'){
        return 0;
    }
    return -1;
}

int check_valid_symbol_name(char *symbol, int line){
    char *error_def;
    int char_idx = 1;

    /*  Checking if first index of the symbol name is a letter  */
    if(isalpha(symbol[0]) == 0){
        error_def = "First letter of symbol is not an alphabetic letter";
        register_new_error(line,error_def);
        return -1;
    }

    for (; char_idx < strlen(symbol)-1; char_idx++) {
        if (isdigit(symbol[char_idx]) == 0 && isalpha(symbol[char_idx]) == 0) {
            error_def = "Invalid char in symbol name";
            register_new_error(line,error_def);
            return -1;
        }
    }
    is_error = 0;
    return 0;
}

int check_if_word_is_op(char *optional_op){
    int op_index = 0;
    for(; op_index < NUMBER_OF_OPERATIONS; op_index++){
        if(strcmp(optional_op, valid_opcode[op_index]) == 0){
            return op_index;
        }
    }
    return -1;
}

int check_if_word_is_data_instruction(char *optional_op){
    int op_index = 0;
    for(; op_index < NUMBER_OF_DATA_INST; op_index++){
        if(strcmp(optional_op, data_instruction[op_index]) == 0){
            return op_index;
        }
    }
    return -1;
}

int check_if_word_is_register(char *optional_op){
    int op_index = 0;
    for(; op_index < NUMBER_OF_REGISTERS; op_index++){
        if(strcmp(optional_op, valid_register_names[op_index]) == 0){
            return op_index;
        }
    }
    return -1;
}

int check_if_word_entry_extern_instruction(char *optional_op){
    int op_index = 0;
    for(; op_index < NUMBER_OF_ENT_EXT; op_index++){
        if(strcmp(optional_op, entry_extern_instruction[op_index]) == 0){
            return op_index;
        }
    }
    return -1;
}

int is_skip_line(char *potential_symbol_name) {
    if (potential_symbol_name[0] == ';'){
        return 0;
    }
    return -1;
}


int string_to_number_conv(char *string){
    printf("str len: %lu\n", strlen(string));
    return '0' + atoi(string);
}


int is_valid_operand_assignment(char *operand_phrase, int line_counter, int op_code){
    char *temp_string;
    char *error_def;
    char current_char;
    char *full_operand;

    int is_comma;
    int is_open;
    int char_num = 0;
    /* Catching the minimum operands for each op code */
    if ((op_code >= 0 && op_code <= 13 && operand_phrase == NULL ) || (op_code > 13 && operand_phrase != NULL)){
        error_def = "Invalid syntax";
        register_new_error(line_counter, error_def);
        return -1;
    }

    temp_string = malloc(strlen(operand_phrase) + 1);
    full_operand = malloc(strlen(operand_phrase) + 1);
    strcpy(temp_string, operand_phrase);

    for (current_char = *temp_string; current_char != '\0'; current_char = *++temp_string) {
        printf("current_char %c\n", current_char);
        /* Not Valid chars */
        if(current_char != '-' && current_char != ',' && current_char != '+' && current_char != ')' && current_char != '('
        && (current_char > '9' || current_char <'0') && (isalpha(current_char) == 0)){
                error_def = "Invalid syntax";
                register_new_error(line_counter, error_def);
                return -1;
            }
        else if(((op_code >=0 && op_code <=3) || op_code == 6 ) && (current_char == '(' || current_char == ')')){
                error_def = "Invalid syntax";
                register_new_error(line_counter, error_def);
                return -1;
            }
        if(current_char == ','){
            if(*(temp_string+1) == '\0'){
                error_def = "Invalid syntax";
                register_new_error(line_counter, error_def);
                return -1;
            }
            is_comma++;
            char_num++;
            full_operand[char_num] = '\0';
            printf("full operand : %s\n", full_operand);
            char_num = 0;
        }else if(current_char == '('){
            if(*(temp_string+1) == '\0'){
                error_def = "Invalid syntax";
                register_new_error(line_counter, error_def);
                return -1;
            }
            is_open++;
        }else if(current_char == ')' && is_open == 1){
            is_open--;
            char_num = 0;
        }else{
            printf("char num %d, current char %c \n", char_num, current_char);
            full_operand[char_num] = current_char;
            char_num++;
        }
    }
    full_operand[char_num] = '\0';
    printf("full operand : %s\n", full_operand);
    return 0;
}

int is_valid_data_instruct(char * string, int line){
    char *temp_string;
    char *error_def;
    int is_comma = 0;
    int digits = 0;
    int is_symbol = 0;
    char number;
    char number_symbol;
    char *full_number;
    char *prev_full_number;

    /* Catching null string */
    if(string == NULL){
        error_def = "Invalid syntax";
        register_new_error(line, error_def);
        return -1;
    }
    prev_full_number = malloc(strlen(string)+1);
    full_number = malloc(strlen(string)+1);
    temp_string = malloc(strlen(string)+1);
    strcpy(temp_string,string);

    for (number = *temp_string; number != '\0'; number = *++temp_string) {
        /* Catching invalid symbols */
        if(number != '-' && number != ',' && number != '+' && (number > '9' || number <'0')){
            error_def = "Invalid syntax";
            register_new_error(line, error_def);
            return -1;
        }
        if(number == '-' || number == '+'){
            is_symbol ++;
            if(is_symbol == 1){
                number_symbol = number;
                full_number[digits] = number_symbol;
                digits++;
            }else{
                error_def = "Invalid syntax";
                register_new_error(line, error_def);
                return -1;
            }

        }
        else if(number == ','){
            /* Catching comma with no numbers in the end */
            if(*(temp_string+1) == '\0'){
                error_def = "Invalid syntax";
                register_new_error(line, error_def);
                return -1;
            }
            is_comma++;
            if(is_comma == 1){
                if(full_number[0] == '\0' || strcmp(prev_full_number, full_number) == 0){
                    error_def = "Invalid syntax";
                    register_new_error(line, error_def);
                    return -1;
                }
                printf("full number: %s\n", full_number);
                digits = 0;
            }else if(is_comma == 2 && digits != 0 && is_symbol == 0){
                printf("full number: %s\n", full_number);
                digits = 0;
                is_comma = 0;
                strcpy(prev_full_number, full_number);
            }
            else{
                error_def = "Invalid syntax";
                register_new_error(line, error_def);
                return -1;
            }
            continue;
        }
        else{
                full_number[digits] = number;
                digits++;
                is_symbol = 0;
            }
        }
    printf("full number: %s\n", full_number);
    free(prev_full_number);
    free(full_number);
    return 0;
}

int is_valid_string (char * string, int line) {
    char * temp_string;
    char *error_def;
    int is_first_quote = 0;
    int is_last_quote = 0;
    char char_string;

    /* Catching null string */
    if(string == NULL){
        error_def = "Invalid syntax";
        register_new_error(line, error_def);
        return -1;
    }

    temp_string = malloc(strlen(string)+1);
    strcpy(temp_string,string);


    for (char_string = *temp_string; char_string != '\0'; char_string = *++temp_string) {
        printf("this is char t: %c\n",char_string);
        if ((char_string == ' ') && (is_first_quote == 0)){
            continue;
        }
        else if (is_first_quote == 1 && is_last_quote == 1 && char_string!= ' '){
            error_def = "Invalid syntax";
            register_new_error(line, error_def);
            return -1;
        }
        else if (is_first_quote == 0 && is_last_quote == 0 && char_string!= '"'){
            error_def = "Invalid syntax";
            register_new_error(line, error_def);
            return -1;
        }
        else if(char_string == '"' && is_first_quote == 0){
            is_first_quote = 1;
        }
        else if (char_string == '"'){
            is_last_quote = 1;
        }
    }
    if(is_first_quote == 1 && is_last_quote == 1){
        return 0;
    }
    error_def = "Invalid syntax";
    register_new_error(line, error_def);
    return -1;
}

int calc_ascii_in_string (char char_string){
    return (int)char_string;
}


void register_new_error(int line_number, char* error_definition){
    error = malloc(sizeof(struct Error));
    error->line_number = line_number;
    error->error_defenition = malloc(sizeof(char)*MAX_LINE_LENGTH);
    strcpy(error->error_defenition, error_definition);
    is_error = 1;
    if (errors_head == NULL) {
        errors_head = error;
        errors_tail = error;
        errors_head->next = NULL;
    } else {
        errors_tail->next = error;
        errors_tail = error;
    }
}

struct Symbol *re_occuring_symbol_name(struct Symbol *head, char *potential_symbol_name){
    struct Symbol *it = NULL;
    it = head;
    while(head != NULL){
        if(strcmp(head->name, potential_symbol_name) == 0){
            return NULL;
        }
        head = head->next;
    }
    return it;
}

void insert_new_symbol(int line, char *symbol_name, struct Symbol *head, struct Symbol *symbol,  struct Symbol *tail){
    char *error_def;
    if(re_occuring_symbol_name(head, symbol_name) != NULL) {
        symbol->name = malloc(sizeof(symbol_name));
        strcpy(symbol->name, symbol_name);
        symbol->line = line;
        symbol->next = NULL;
        /* Linked list setters */
        while(tail->next != NULL){
            tail = tail->next;
        }
        tail->next = symbol;
    }else if(re_occuring_symbol_name(head, symbol_name) == NULL){
        error_def = "Reoccurring symbol name";
        register_new_error(line, error_def);
    }
}

void test_print_error(){
        while(errors_head != NULL){
        printf("Error: %s in line: %d\n", errors_head->error_defenition, errors_head->line_number);
        free(errors_head->error_defenition);
        errors_head = errors_head->next;
        }

}
