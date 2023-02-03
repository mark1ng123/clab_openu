#include "assembler_helping_function.h"

/* Globals */
char *valid_opcode[] = {"mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec","jmp", "bne", "red", "prn",
                              "jsr", "rts", "stop"};
char *data_instruction[] = {".data", ".string"};
char *entry_extern_instruction[] = {".extern", ".entry"};
char *valid_register_names[] = {"r0","r1", "r2", "r3", "r4", "r5", "r6","r7"};

/* Declarations for flags */
int is_error = 0;
int is_symbol_error = 0;

/* initialization for saving the Errors */
struct Error *errors_head = NULL;
struct Error *errors_tail = NULL;
struct Error *error = NULL;

/* intialization for saving the Symbols */
struct Symbol *symbol_head = NULL;
struct Symbol *symbol_tail = NULL;
struct Symbol *symbol = NULL;

/* Functions */
int check_is_line_starting_with_symbol(char *symbol){
    if(symbol[strlen(symbol)-1] == ':'){
        return 0;
    }
    return -1;
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

int check_if_word_is_data_instruction(char *optional_instruction){
    int op_index = 0;
    for(; op_index < NUMBER_OF_DATA_INST; op_index++){
        if(strcmp(optional_instruction, data_instruction[op_index]) == 0){
            return op_index;
        }
    }
    return -1;
}

int check_if_word_is_register(char *optional_register){
    int op_index = 0;
    for(; op_index < NUMBER_OF_REGISTERS; op_index++){
        if(strcmp(optional_register, valid_register_names[op_index]) == 0){
            return op_index;
        }
    }
    return -1;
}

int check_if_word_entry_extern_instruction(char *optional_instruction){
    int op_index = 0;
    for(; op_index < NUMBER_OF_ENT_EXT; op_index++){
        if(strcmp(optional_instruction, entry_extern_instruction[op_index]) == 0){
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
    return '0' + atoi(string);
}

int calc_ascii_in_string (char char_string){
    return (int)char_string;
}

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

int check_valid_symbol_name(char *symbol, int line){
    char *error_def;
    int char_idx = 1;

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
    return 0;
}

int is_valid_string (char * string, int line) {
    char *temp_string;
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
        /* move if encounter spaces in the beginning */
        if ((char_string == ' ') && (is_first_quote == 0)){
            continue;
        }
        /* after reading the string and closing the quote there is invalid char */
        else if (is_first_quote == 1 && is_last_quote == 1 && char_string!= ' '){
            error_def = "Invalid syntax";
            register_new_error(line, error_def);
            return -1;
        }
        /* if first char is not quote */
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

int is_valid_operand_assignment(char *operand_phrase, int line_counter, int op_code){

    char *temp_string;
    char *error_def;
    char current_char;
    char *full_operand;

    int char_num = 0;
    int temp_number_of_chars = 0;
    int char_idx = 0;

    /*Flags*/
    int is_comma = 0;
    int is_open = 0;
    int is_close = 0;
    int is_symbol = 0;
    int is_digit = 0;
    int is_char = 0;
    int is_space = 0;
    int is_imidiate = 0;


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
        /* Not Valid chars */
        if(current_char != '#' && current_char != ' ' && current_char != '-' && current_char != ',' && current_char != '+'
        && current_char != ')' && current_char != '(' && (isdigit(current_char) == 0) && (isalpha(current_char) == 0)){
                error_def = "Invalid syntax";
                register_new_error(line_counter, error_def);
                return -1;
            }
        /* Not Valid chars in op_code that are not 9,10,13 */
        else if((op_code!=9 && op_code!=10 && op_code !=13) && (current_char == '(' || current_char == ')')){
                error_def = "Invalid syntax";
                register_new_error(line_counter, error_def);
                return -1;
            }
        if(current_char == ','){
            /* comma isnt valid in this op_codes */
            if(op_code == 4 || op_code == 5 || op_code == 7 || op_code == 8 || op_code == 11 || op_code == 12){
                error_def = "Invalid syntax";
                register_new_error(line_counter, error_def);
                return -1;
            }
            /* there comma in the end of the file */
            if(*(temp_string+1) == '\0'){
                error_def = "Invalid syntax";
                register_new_error(line_counter, error_def);
                return -1;
            }
            is_comma++;
            /* commas are next to each other */
            if(is_comma > 1){
                error_def = "Invalid syntax";
                register_new_error(line_counter, error_def);
                return -1;
            /* number and then char */
            }else if(is_char > 0 && is_digit != 0){
                error_def = "Invalid syntax";
                register_new_error(line_counter, error_def);
                return -1;
            /* symbol with char */
            }else if(is_symbol == 1 && is_char > 0){
                error_def = "Invalid syntax";
                register_new_error(line_counter, error_def);
                return -1;
            /* hashtag with no number */
            }else if(is_imidiate != 0 && is_digit == 0){
                error_def = "Invalid syntax";
                register_new_error(line_counter, error_def);
                return -1;
             /* symbol with no number*/
            }else if(is_symbol == 1 && is_digit == 0){
                error_def = "Invalid syntax";
                register_new_error(line_counter, error_def);
                return -1;
            }
            /* Reset full operand string */
            for(; char_num < sizeof (full_operand); char_num++){
                full_operand[char_num] = '\0';
            }
            printf("full operand : %s\n", full_operand);
            char_num = 0;
            is_symbol = 0;
            is_char = 0;
            is_digit = 0;
            is_space = 0;
            is_imidiate = 0;
        }else if(current_char == '('){
            if(*(temp_string+1) == '\0'){
                error_def = "Invalid syntax";
                register_new_error(line_counter, error_def);
                return -1;
            }else if(char_num ==0){
                error_def = "Invalid syntax";
                register_new_error(line_counter, error_def);
                return -1;
            }
            else{
                is_open++;
            }
            printf("full operand : %s\n", full_operand);
            char_num = 0;
            is_char = 0;
        }else if(current_char == ')' && is_open == 1){
            is_close++;
            if(is_close !=0 && is_space!=0){
                error_def = "Invalid syntax";
                register_new_error(line_counter, error_def);
                return -1;
            }
            char_num = 0;
        }else if(current_char == ')' && is_open == 0){
            error_def = "Invalid syntax";
            register_new_error(line_counter, error_def);
            return -1;
        }else if(current_char == '+' || current_char == '-'){
            is_symbol++;
            if(is_symbol > 1 || is_char > 0 ){
                error_def = "Invalid syntax";
                register_new_error(line_counter, error_def);
                return -1;
            }else if(is_symbol == 1 && char_num != 0){
                error_def = "Invalid syntax";
                register_new_error(line_counter, error_def);
                return -1;
            }
            full_operand[char_num] = current_char;
            char_num++;
        }else if(current_char == '#'){
            is_imidiate++;
            if(char_num != 0){
                error_def = "Invalid syntax";
                register_new_error(line_counter, error_def);
                return -1;
            }
        }else{
            if(is_symbol == 1 && is_imidiate == 1){
                if(isdigit(current_char)){
                    printf("Number OK\n");
                    is_digit++;
                }else{
                    error_def = "Invalid syntax";
                    register_new_error(line_counter, error_def);
                    return -1;
                }
            }
            else if(isdigit(current_char) && is_imidiate == 1){
                /* Opening digit */
                if(char_num == 0){
                    is_digit++;
                }
            }else if(isdigit(current_char) && is_imidiate == 0){
                if(is_char == 0){
                    error_def = "Invalid syntax";
                    register_new_error(line_counter, error_def);
                    return -1;
                }
            }else if(current_char == ' '){
                if(is_open != 0 && is_char == 0){
                    error_def = "Invalid syntax";
                    register_new_error(line_counter, error_def);
                    return -1;
                }
                if(is_char != 0 || is_digit != 0){
                    is_space++;
                }
            }else{
                if(is_digit > 0){
                    error_def = "Invalid syntax";
                    register_new_error(line_counter, error_def);
                    return -1;
                }else{
                    if(is_imidiate!=0){
                        error_def = "Invalid syntax";
                        register_new_error(line_counter, error_def);
                        return -1;
                    }
                    is_char++;
                }
            }
            temp_number_of_chars = char_num;
            if(current_char != ' '){
                full_operand[char_num] = current_char;
                char_num++;
            }
            if(temp_number_of_chars != char_num && is_space!=0){
                error_def = "Invalid syntax";
                register_new_error(line_counter, error_def);
                return -1;
            }
            printf("char num %d, current char %c \n", char_num, current_char);
        }
    }
    if(is_open != is_close){
        error_def = "Invalid syntax";
        register_new_error(line_counter, error_def);
        return -1;
    }
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
    /* saving .data line if not empty parameters */
    prev_full_number = malloc(strlen(string)+1);
    full_number = malloc(strlen(string)+1);
    temp_string = malloc(strlen(string)+1);
    strcpy(temp_string,string);

    for(number = *temp_string; number != '\0'; number = *++temp_string) {
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
                    /* Catching comma next to each other */
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

void insert_new_symbol(int line ,char *symbol_name){
    char *error_def;
    if(re_occuring_symbol_name(symbol_head, symbol_name) != NULL) {
        insert_symbol(symbol_name);
    }else if(re_occuring_symbol_name(symbol_head, symbol_name) == NULL){
        error_def = "Reoccurring symbol name";
        register_new_error(line, error_def);
    }
}


int allocate_memory_for_symbol(){
    symbol = malloc(sizeof(struct Symbol));
    if(symbol == NULL){
        printf("Unable to allocate memory for symbol\n");
        return -1;
    }
    return 0;
}

void append_decimal_adress_to_symbol(int decimal_adress){
    symbol->decimal_adress = decimal_adress;
}

void insert_symbol(char* symbol_name){
    symbol->name = symbol_name;
    symbol->next = NULL;
    /* Linked list setters */
    if (symbol_head == NULL) {
        symbol_head = symbol;
        symbol_tail = symbol;
    } else {
        symbol_tail->next = symbol;
        symbol_tail = symbol;
        symbol_tail->next = NULL;
    }
}

int return_if_symbol_head_null(){
    if(symbol_head!=NULL){
        return 0;
    }
    return 1;
}

void print_symbols(){
    while(symbol_head != NULL){
        printf("Symbol: %s in adress: %d\n", symbol_head->name, symbol_head->decimal_adress);
        symbol_head = symbol_head->next;
    }
}

void free_symbols(){
    while(symbol_head != NULL){
        free(symbol_head->name);
        free(symbol_head);
        symbol_head = symbol_head->next;
    }
}
