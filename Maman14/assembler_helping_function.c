#include "assembler_helping_function.h"
#include "structures.h"
#include "global_operations.h"
#include "error_handeling.h"



/* intialization for saving the Symbols */
struct Symbol *symbol_head = NULL;
struct Symbol *symbol_tail = NULL;
struct Symbol *symbol = NULL;

/* intialization for saving the Binary machine code */
struct BinaryList *binary_head = NULL;
struct BinaryList *binary_tail = NULL;
struct BinaryList *current_binary = NULL;

/* intialization for saving the Entry instruction */
struct Entry *entry_head = NULL;
struct Entry *entry_tail = NULL;
struct Entry *current_entry = NULL;

/* intialization for saving the Entry instruction */
struct Extern *extern_head = NULL;
struct Extern *extern_tail = NULL;
struct Extern *current_extern = NULL;


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
    return strtol(string, NULL, 10);
}

int int_to_ascii(int number){
    return '0' + number;
}

int calc_ascii_in_string (char char_string){
    return (int)char_string;
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
            
            /* Resetting indexes for next operand*/
            char_num = 0;
            is_symbol = 0;
            is_char = 0;
            is_digit = 0;
            is_space = 0;
            is_imidiate = 0;
            /* Works on op codes that can take ( or ) but algorithm stays the same just resetting points differ */
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
            
            char_num = 0;
            is_char = 0;
            /* One closing one Opening */
        }else if(current_char == ')' && is_open == 1){
            is_close++;
            /* Spaces not allowed */
            if(is_close != 0 && is_space!=0){
                error_def = "Invalid syntax";
                register_new_error(line_counter, error_def);
                return -1;
            }
            char_num = 0;
            /* No opening */
        }else if(current_char == ')' && is_open == 0){
            error_def = "Invalid syntax";
            register_new_error(line_counter, error_def);
            return -1;
            /* Symbol conditioning */
        }else if(current_char == '+' || current_char == '-'){
            is_symbol++;
            /* Symbol and a char together */
            if(is_symbol > 1 || is_char > 0 ){
                error_def = "Invalid syntax";
                register_new_error(line_counter, error_def);
                return -1;
            /* symbol index is not right in the operand  */
            }else if(is_symbol == 1 && char_num != 0){
                error_def = "Invalid syntax";
                register_new_error(line_counter, error_def);
                return -1;
            }
            full_operand[char_num] = current_char;
            char_num++;
            /* immediate action */
        }else if(current_char == '#'){
            is_imidiate++;
            if(char_num != 0){
                error_def = "Invalid syntax";
                register_new_error(line_counter, error_def);
                return -1;
            }
        }else{
            /* Symbol and Immediate action */
            if(is_symbol == 1 && is_imidiate == 1){
                /* Has to be digit */
                if(isdigit(current_char)){
                    is_digit++;
                }else{
                    error_def = "Invalid syntax";
                    register_new_error(line_counter, error_def);
                    return -1;
                }
            }
            /* Digit with Immediate action no symbol */
            else if(isdigit(current_char) && is_imidiate == 1){
                /* Opening digit */
                if(char_num == 0){
                    is_digit++;
                }
                /* Opening number without immediate action */
            }else if(isdigit(current_char) && is_imidiate == 0){
                if(is_char == 0){
                    error_def = "Invalid syntax";
                    register_new_error(line_counter, error_def);
                    return -1;
                }
                /* Spaces conditioning */
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
                /* digits with chars */
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
        }
    }
    if(is_open != is_close){
        error_def = "Invalid syntax";
        register_new_error(line_counter, error_def);
        return -1;
    }
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
                digits = 0;
            }else if(is_comma == 2 && digits != 0 && is_symbol == 0){
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
    struct Symbol *temp = NULL;
    temp = symbol_head;
    while(symbol_head != NULL){
        symbol_head = symbol_head->next;
    }
    symbol_head = temp;
}

void free_symbols(){
    while(symbol_head != NULL){
        free(symbol_head->name);
        free(symbol_head);
        symbol_head = symbol_head->next;
    }
}

int allocate_memory_for_binary_code(){
    int current_digit = 0;
    current_binary = malloc(sizeof(struct BinaryList));
    if(current_binary == NULL){
        printf("Unable to allocate memory for symbol\n");
        return -1;
    }
    for(; current_digit<WORD_SIZE; current_digit++){
        current_binary->binary_code[current_digit] = '0';
    }
    /* Struct size is bigger then binary code size which is hard coded that why we delocate memory from the 14 bit*/
    current_binary->binary_code[WORD_SIZE] = '\0';
    return 0;
}

char* int_to_binary(int number, int op_code){
    char* reversed_binary_number;
    unsigned char char_idx = 0;
    int new_number = 0;
    int left = 0;
    int right = 0;
    int char_iterator = 0;
    char temp;
    /* Size depends on the op_code used */
    if(op_code < 15){
        reversed_binary_number = malloc(BINARY_TWOS);
        right = BINARY_TWOS;
    }else if(op_code == SYMBOL_TO_BINARY_OP_CODE){    /* Second parse */
        reversed_binary_number = malloc(BINARY_TWOS + 2);
        right = BINARY_TWOS;
        reversed_binary_number[13] = '0';
        reversed_binary_number[12] = '1';
    }else if(op_code == EXTERN_OP_CODE){ /* Second parse extern */
        reversed_binary_number = malloc(BINARY_TWOS + 2);
        for(;char_iterator < BINARY_TWOS+2; char_iterator++){
            reversed_binary_number[char_iterator] = '0';
            if(char_iterator == BINARY_TWOS + 1){
                reversed_binary_number[char_iterator] = '1';
            }
        }
        return reversed_binary_number;
    }
    else{
        reversed_binary_number = malloc(BINARY_TWOS + 2);
        right = BINARY_TWOS + 2;
    }
    /* Initialize */
    for(; char_idx<right; char_idx++){
        reversed_binary_number[char_idx]='0';
    }
    /* Calc binary */
    char_idx = 0;
    for(; number != 0; char_idx++){
        new_number = number % 2;
        reversed_binary_number[char_idx] = abs(new_number) + '0';
        number = number/2;
    }
    /* Reversing from right to left -> left to right */
    right = right - 1;
    while(left < right){
        temp = reversed_binary_number[right];
        reversed_binary_number[right] = reversed_binary_number[left];
        reversed_binary_number[left] = temp;
        left++;
        right--;
    }
    return reversed_binary_number;
}

char* compliment_two_binary(char* binary_number, int number){
    int char_idx = 0;
    int secondery_idx = 0;
    /* if number is positive we dont need to do anything*/
    if(number > 0){
        return binary_number;
    }else{
        /* Initialize */
        for(char_idx = strlen(binary_number)-1; char_idx >= 0; char_idx--){
            if(binary_number[char_idx]=='1')
                break;
        }
        if(char_idx == -1){
            binary_number[strlen(binary_number)-1] = '1';
            return binary_number;
        }
        /* Saved char idx from 1st iteration to make it more effecient */
        for(secondery_idx = char_idx-1; secondery_idx>=0; secondery_idx--){
            if(binary_number[secondery_idx] == '1'){
                binary_number[secondery_idx] = '0';
            }else{
                binary_number[secondery_idx] = '1';
            }
        }
    }
    return binary_number;
}



void binary_encoding(int op_code, int decimal_adress, char* operand_phrase, int number_of_registers, int line){
    /*Indexing declarations */
    int op_code_index_start = 4;
    int dest_operand_start_idx = 10;
    int source_operand_start_idx = 8;
    int source_operand_solo_line = 0;
    int dest_operand_solo_line = 6;
    int dest_operand_idx_jumping_sort = 2;
    int source_operand_idx_jumping_sort = 0;
    int register_index = 0;
    /* Flag declarations */
    int number_of_operand = 0;
    int solo_operand = 0;
    int total_lines_needed = 0;
    char *number;
    int src_number = 0;
    int dest_number = 0;
    int ascii_number;
    char *ascii_in_binary;
    /* Setting the base for input of the two operands */
    char *binary_src_operand_code = malloc(OPERANDS_OFFSET);
    char *binary_dest_operand_code = malloc(OPERANDS_OFFSET);
    /* Insert new binary */
    if(allocate_memory_for_binary_code() == 0){
        /* Setting known vars */
        current_binary->line = line;
        current_binary->decimal_adress = decimal_adress;
        memcpy(current_binary->binary_code + op_code_index_start, binary_op_code_array[op_code], BINARY_OP_CODE);
        if(op_code != 9 && op_code != 10 && op_code !=13){ /* Parsing by op_code */
            operand_phrase = strtok(operand_phrase, "\n, ");
            while(operand_phrase!=NULL) {
                number_of_operand++;
                if (check_if_word_is_register(operand_phrase) != -1) {
                    register_index = check_if_word_is_register(operand_phrase);
                    /* Source register operand */
                    if(number_of_operand == 1){
                        strcpy(binary_src_operand_code, binary_register_code_array[register_index]);
                        memcpy(current_binary->binary_code+source_operand_start_idx, "11", REGISTER_SORTING);
                    }else{  /* Dest register operand */
                        strcpy(binary_dest_operand_code, binary_register_code_array[register_index]);
                        memcpy(current_binary->binary_code+dest_operand_start_idx, "11", REGISTER_SORTING);
                    }
                    /* Imediate sorting for numbers*/
                } else if(strchr(operand_phrase, '#')){
                    /* Source */
                    if(number_of_operand == 1){
                        
                        number = malloc(strlen(operand_phrase)-1);
                        strcpy(number, operand_phrase+1);
                        ascii_number = string_to_number_conv(number);
                        ascii_in_binary = compliment_two_binary(int_to_binary(ascii_number, op_code), ascii_number);
                        binary_src_operand_code = malloc(BINARY_TWOS+2);/*i added this*/
                        strcpy(binary_src_operand_code, ascii_in_binary);
                        memcpy(current_binary->binary_code+source_operand_start_idx, "00", REGISTER_SORTING);
                        src_number++;
                    }else{  /* Dest operand */
                        number = malloc(strlen(operand_phrase)-1);
                        strcpy(number, operand_phrase+1);
                        ascii_number = int_to_ascii(string_to_number_conv(number));
                        ascii_in_binary = compliment_two_binary(int_to_binary(ascii_number, op_code), ascii_number);
                        binary_dest_operand_code = malloc(BINARY_TWOS);/*i added this? should we add +2 here also?*/
                        strcpy(binary_dest_operand_code, ascii_in_binary);
                        memcpy(current_binary->binary_code+dest_operand_start_idx, "00", REGISTER_SORTING);
                        dest_number++;
                    }
                }
                else{
                    /* Source label operand */
                    if(number_of_operand == 1 && op_code < 14){
                        memcpy(current_binary->binary_code+source_operand_start_idx, "01", REGISTER_SORTING);
                        binary_src_operand_code = NULL;
                    }else{  /* Dest label operand */
                        memcpy(current_binary->binary_code+dest_operand_start_idx, "01", REGISTER_SORTING);
                        binary_dest_operand_code = NULL;
                    }
                }
                operand_phrase = strtok(NULL, "\n, ");
            }
        }else {
            /* Insert Jumping sort every 1st operand we skip we know its a label and will be treated as it needs */

            operand_phrase = strtok(operand_phrase, "(, ");
            while (operand_phrase != NULL) {
                number_of_operand++;
                if (check_if_word_is_register(operand_phrase) != -1) {
                    register_index = check_if_word_is_register(operand_phrase);
                    /* Source register operand */
                    if(number_of_operand == 2){
                        strcpy(binary_src_operand_code, binary_register_code_array[register_index]);
                        memcpy(current_binary->binary_code+source_operand_idx_jumping_sort, "11", REGISTER_SORTING);
                    }else if (number_of_operand == 3){/* Dest register operand */
                        strcpy(binary_dest_operand_code, binary_register_code_array[register_index]);
                        memcpy(current_binary->binary_code+dest_operand_idx_jumping_sort, "11", REGISTER_SORTING);
                    }else{
                        operand_phrase = strtok(NULL, ",) \n");
                        continue;
                    }
                    /* Imediate sorting for numbers*/
                } else if(strchr(operand_phrase, '#')){
                    /* Source */
                    if(number_of_operand == 2){
                        number = malloc(strlen(operand_phrase)-1);
                        strcpy(number, operand_phrase+1);
                        ascii_number = string_to_number_conv(number);
                        ascii_in_binary = compliment_two_binary(int_to_binary(ascii_number, op_code), ascii_number);
                        binary_src_operand_code = malloc(BINARY_TWOS);
                        strcpy(binary_src_operand_code, ascii_in_binary);
                        memcpy(current_binary->binary_code+source_operand_idx_jumping_sort, "00", REGISTER_SORTING);
                        src_number++;
                    }else if(number_of_operand == 3){  /* Dest operand */
                        number = malloc(strlen(operand_phrase)-1);
                        strcpy(number, operand_phrase+1);
                        ascii_number = int_to_ascii(string_to_number_conv(number));
                        ascii_in_binary = compliment_two_binary(int_to_binary(ascii_number, op_code), ascii_number);
                        binary_dest_operand_code = malloc(BINARY_TWOS);
                        strcpy(binary_dest_operand_code, ascii_in_binary);
                        memcpy(current_binary->binary_code+dest_operand_idx_jumping_sort, "00", REGISTER_SORTING);
                        dest_number++;
                    }else{
                        operand_phrase = strtok(NULL, ",) \n");
                        continue;
                    }
                }
                else{
                    /* Source label operand */
                    if(number_of_operand == 2){
                        memcpy(current_binary->binary_code+source_operand_idx_jumping_sort, "01", REGISTER_SORTING);
                        if(binary_src_operand_code != NULL){
                            binary_src_operand_code = NULL;
                        }
                    }else if(number_of_operand == 3){  /* Dest label operand */
                        memcpy(current_binary->binary_code+dest_operand_idx_jumping_sort, "01", REGISTER_SORTING);
                        if(binary_dest_operand_code != NULL){
                            binary_dest_operand_code = NULL;
                        }
                    }else{
                        operand_phrase = strtok(NULL, ",) \n");
                        continue;
                    }

                }
                operand_phrase = strtok(NULL, ",) \n");
            }
        }
        /*Checking how many lines of binary we need */
        if(number_of_operand == 1){
            if(op_code < 14){
                solo_operand = 1;
                memcpy(current_binary->binary_code+source_operand_start_idx, "00", REGISTER_SORTING);
                if(dest_number == 1 || src_number == 1){
                    memcpy(current_binary->binary_code+dest_operand_start_idx, "00", REGISTER_SORTING);
                }else{
                    memcpy(current_binary->binary_code+dest_operand_start_idx, "01", REGISTER_SORTING);
                }
                free(binary_dest_operand_code);
            }else{
                solo_operand = 1;
                memcpy(current_binary->binary_code+source_operand_start_idx, "00", REGISTER_SORTING);
                memcpy(current_binary->binary_code+dest_operand_start_idx, "00", REGISTER_SORTING);
                free(binary_dest_operand_code);
            }
        }else if(number_of_operand == 3){
            memcpy(current_binary->binary_code + 8, "0010", 4);
        }
        /* Add to first line of binary to the list */
        insert_new_binary();
        /* Need only one line of binary*/
        if((number_of_registers == 2 || op_code>=14) && op_code != 10 && op_code !=9 && op_code != 13){
            if(op_code >= 14){
                number_of_operand = 0;
            }
            total_lines_needed = 1;
        }else{
            if(op_code == 10 || op_code == 9 || op_code == 13){
                if(number_of_operand == 1 || number_of_registers == 2){
                    total_lines_needed = 2;
                }else{
                    total_lines_needed = 3;
                }
            }else{
                total_lines_needed = 2;
            }
        }
        /* Inserting operand lines of binary indexing works backwards, beacuse we count from the X operands to 0*/
        while(number_of_operand!=0){
            if(total_lines_needed == 2 && op_code != 9 && op_code !=10 && op_code != 13){
                if(allocate_memory_for_binary_code() == 0) {
                    if(number_of_operand == 2){
                        if(binary_src_operand_code == NULL){
                            memcpy(current_binary->binary_code, "??????????????", WORD_SIZE);
                        }else if(src_number == 0 ){
                            memcpy(current_binary->binary_code+source_operand_solo_line, binary_src_operand_code, OPERANDS_OFFSET);
                        }else{
	                    memcpy(current_binary->binary_code, binary_src_operand_code, BINARY_TWOS);
                        }
                    }
                    else{
                        if(binary_dest_operand_code == NULL && op_code < 14){
                            memcpy(current_binary->binary_code, "??????????????", WORD_SIZE);
                        }else{
                            if(solo_operand == 0){
                                if(dest_number == 0){
                                    memcpy(current_binary->binary_code+dest_operand_solo_line, binary_dest_operand_code, OPERANDS_OFFSET);
                                }
                                else{
                                    memcpy(current_binary->binary_code, binary_dest_operand_code, BINARY_TWOS);
                                }
                            }else{
                                if(src_number == 0){
                                    if(binary_src_operand_code == NULL) {
                                        memcpy(current_binary->binary_code, "??????????????", WORD_SIZE);
                                    }else{
                                        memcpy(current_binary->binary_code+source_operand_solo_line, binary_src_operand_code, OPERANDS_OFFSET);
                                    }
                                }else{
                                    memcpy(current_binary->binary_code, binary_src_operand_code, BINARY_TWOS);
                                }
                            }
                        }
                    }
                }
            }else{
                if(op_code < 14 && op_code != 10 && op_code !=9 && op_code !=13){
                    if(allocate_memory_for_binary_code()==0){
                        number_of_operand--;
                        memcpy(current_binary->binary_code+source_operand_solo_line, binary_src_operand_code, OPERANDS_OFFSET);
                        memcpy(current_binary->binary_code+dest_operand_solo_line, binary_dest_operand_code, OPERANDS_OFFSET);
                    }
                }else{
                    if(allocate_memory_for_binary_code()==0){
                        if(number_of_operand == 3 && solo_operand == 0) {
                            memcpy(current_binary->binary_code, "??????????????", WORD_SIZE);
                        }
                        else if(binary_dest_operand_code == NULL && number_of_operand == 1 && solo_operand == 0){
                            memcpy(current_binary->binary_code, "??????????????", WORD_SIZE);
                        }else if(binary_src_operand_code == NULL && number_of_operand == 2 && solo_operand == 0){
                            memcpy(current_binary->binary_code, "??????????????", WORD_SIZE);
                        }else if(number_of_operand == 2 && solo_operand == 0){
                            if(number_of_registers == 2){
                                number_of_operand--;
                                memcpy(current_binary->binary_code+source_operand_solo_line, binary_src_operand_code, OPERANDS_OFFSET);
                                memcpy(current_binary->binary_code+dest_operand_solo_line, binary_dest_operand_code, OPERANDS_OFFSET);
                            }
                            if(src_number == 0){
                                memcpy(current_binary->binary_code+source_operand_solo_line, binary_src_operand_code, OPERANDS_OFFSET);
                            }else{
                                memcpy(current_binary->binary_code, binary_src_operand_code, BINARY_TWOS);
                            }
                        }else if(number_of_operand == 1 && solo_operand == 0){
                            if(dest_number == 0){
                                memcpy(current_binary->binary_code+dest_operand_solo_line, binary_dest_operand_code, OPERANDS_OFFSET);
                            }else{
                                memcpy(current_binary->binary_code, binary_dest_operand_code, BINARY_TWOS);
                            }
                        }else if(solo_operand == 1){
                            memcpy(current_binary->binary_code, "??????????????", WORD_SIZE);
                        }
                    }
                }
            }
            if(total_lines_needed == 1){
                decimal_adress++;
                total_lines_needed--;
            }else if(total_lines_needed == 2){
                decimal_adress++;
            }else if(total_lines_needed == 3){
                decimal_adress++;
            }
            current_binary->line = line;
            current_binary->decimal_adress = decimal_adress;
            insert_new_binary();
            number_of_operand--;
        }
        solo_operand = 0;
    }
}

void insert_new_binary(){
    if (binary_head == NULL) {
        binary_head = current_binary;
        binary_tail = current_binary;
        binary_tail->next = NULL;
    } else {
        binary_tail->next = current_binary;
        binary_tail = current_binary;
        binary_tail->next = NULL;
    }
}

void print_binary_list(){
    struct BinaryList *temp = NULL;
    temp = binary_head;
    while(binary_head != NULL){
        binary_head = binary_head->next;
    }
    binary_head = temp;
}

void free_binary_list(){
    while(binary_head != NULL){
        free(binary_head);
        binary_head = binary_head->next;
    }
}

void binary_encoding_for_data(int decimal_adress, char *operand_phrase, int line){
    int number = 0;
    int op_code = 15;
    char *number_in_binary;
    operand_phrase = strtok(operand_phrase, ", \n");
    while(operand_phrase != NULL){
        if(allocate_memory_for_binary_code() == 0){
            current_binary->line =line;
            current_binary->decimal_adress = decimal_adress;
            number = string_to_number_conv(operand_phrase);
            number_in_binary = compliment_two_binary(int_to_binary(number, op_code), number);
            memcpy(current_binary->binary_code, number_in_binary, BINARY_TWOS + 2);
        }
        insert_new_binary();
        decimal_adress++;
        operand_phrase = strtok(NULL, ", \n");
    }
}

void binary_encoding_for_string(int decimal_adress, char *operand_phrase, int line){
    char *temp_string;
    char char_string;
    int ascii_number = 0;
    char *binary_num;
    int is_quote = 0;
    int op_code = 16;

    temp_string = malloc(strlen(operand_phrase)+1);
    strcpy(temp_string,operand_phrase);

    for (char_string = *temp_string; char_string != '\0'; char_string = *++temp_string) {
        if(char_string == '"') {
            is_quote++;
        }
        else if ((char_string == ' ') && (is_quote == 0 || is_quote == 2)){
            continue;
        }
        else {
            if(allocate_memory_for_binary_code() == 0){
                current_binary->line = line;
                current_binary->decimal_adress = decimal_adress;
                ascii_number = calc_ascii_in_string(char_string);
                binary_num = compliment_two_binary(int_to_binary(ascii_number, op_code), ascii_number);
                memcpy(current_binary->binary_code, binary_num, BINARY_TWOS+2);
                insert_new_binary();
                decimal_adress ++;
            }
        }
    }
    if(allocate_memory_for_binary_code() == 0){
        current_binary->line = line;
        current_binary->decimal_adress = decimal_adress;
        memcpy(current_binary->binary_code, "00000000000000", BINARY_TWOS+2);
        insert_new_binary();
    }
}

int check_if_extern_using_a_symbol_from_current_file(){
    struct Extern *extern_it = NULL;
    struct Symbol *symbol_it = NULL;
    char *error_def;
    extern_it = extern_head;
    symbol_it = symbol_head;
    while(extern_head != NULL){
        while(symbol_head != NULL){
            if(strcmp(extern_head->symbol_name, symbol_head->name) == 0){
                error_def = "extern using symbol name in current file";
                register_new_error(-1, error_def);
                return -1;
            }
            symbol_head = symbol_head->next;
        }
        symbol_head = symbol_it;
        extern_head = extern_head->next;
    }
    extern_head = extern_it;
    symbol_head = symbol_it;
    return 0;
}


void potential_symbol_to_binary(char* potential_symbol_name, int line_counter){
    int is_symbol, is_entry, is_extern;
    char *error_def;
    struct Symbol *symbol_temp = NULL;
    struct Entry *entry_temp = NULL;
    struct Extern *extern_temp = NULL;
    struct BinaryList *list_temp = NULL;
    list_temp = binary_head;
    symbol_temp = symbol_head;
    entry_temp = entry_head;
    extern_temp = extern_head;
    is_symbol = check_if_in_symbol_table(potential_symbol_name);
    is_entry = check_if_in_entry_table(potential_symbol_name);
    is_extern = check_if_in_extern_table(potential_symbol_name);
    if(check_if_potential_symbol_name(potential_symbol_name) != -1){
        if(is_symbol != 0){
            if(is_entry == 0){
                    write_symbol_binary(int_to_binary(is_symbol,SYMBOL_TO_BINARY_OP_CODE));
                }else{
                    if(entry_head->decimal_adress == 0){
                        entry_head->decimal_adress = is_symbol;
                        write_symbol_binary(int_to_binary(is_symbol,SYMBOL_TO_BINARY_OP_CODE));
                    }else{
                        error_def = "Entry symbol was found in more then one place";
                        register_new_error(line_counter, error_def);
                    }
                }
            }else if(is_extern != 0){
                if(extern_head->decimal_adress.array == NULL){
                    initArray(&extern_head->decimal_adress, 1);
                }
                while(binary_head != NULL){
                    if(strcmp(binary_head->binary_code, "??????????????") == 0){
                        insertArray(&extern_head->decimal_adress, binary_head->decimal_adress);
                        binary_head = list_temp;
                        write_symbol_binary(int_to_binary(is_symbol,EXTERN_OP_CODE));
                        break;
                    }
                    binary_head = binary_head->next;
                }
        }else{
                write_symbol_binary("**************");
                error_def = "Unidentified symbol";
                register_new_error(line_counter, error_def);
            }
        }
    symbol_head = symbol_temp;
    entry_head = entry_temp;
    extern_head = extern_temp;

}

int check_if_in_symbol_table(char* potential_symbol_name){
    while(symbol_head != NULL){
        if(strcmp(symbol_head->name, potential_symbol_name) == 0){
            return symbol_head->decimal_adress;
        }
        symbol_head = symbol_head->next;
    }
    return 0;
}
int check_if_in_entry_table(char* potential_symbol_name){
    while(entry_head != NULL){
        if(strcmp(entry_head->symbol_name, potential_symbol_name) == 0){
            return 1;
        }
        entry_head = entry_head->next;
    }
    return 0;
}
int check_if_in_extern_table(char* potential_symbol_name){
    while(extern_head != NULL){
        if(strcmp(extern_head->symbol_name, potential_symbol_name) == 0){
            return 1;
        }
        extern_head = extern_head->next;
    }
    return 0;
}

void write_symbol_binary(char* decimal_address){
    struct BinaryList *temp_binary = NULL;
    temp_binary = binary_head;
    while(binary_head != NULL) {
       if(strcmp(binary_head->binary_code, "??????????????") == 0){
            memcpy(binary_head->binary_code,decimal_address,BINARY_TWOS + 2);/*14*/
            break;
       }
       binary_head = binary_head->next;
    }
    binary_head = temp_binary;

}

void clean_potential_symbol_to_binray(){
    struct Symbol *temp = NULL;
    temp = symbol_head;
    while(symbol_head != NULL){
        symbol_head->name[strlen(symbol_head->name)-1] = '\0';
        symbol_head = symbol_head->next;
    }
    symbol_head = temp;
}

int check_if_potential_symbol_name(char *potential_symbol){
    int char_idx = 1;

    if (check_if_word_is_op(potential_symbol) != -1 || check_if_word_is_data_instruction(potential_symbol) != -1
        || check_if_word_is_register(potential_symbol) != -1 || check_if_word_entry_extern_instruction(potential_symbol) != -1){
            return -1;
        }
    if(isalpha(potential_symbol[0]) == 0){
        return -1;
    }
    for (; char_idx < strlen(potential_symbol)-1; char_idx++) {
        if (isdigit(potential_symbol[char_idx]) == 0 && isalpha(potential_symbol[char_idx]) == 0) {
            return -1;
        }
    }
    return 0;
}

int allocate_memory_for_entry(){
    current_entry = malloc(sizeof(struct Symbol));
    if(current_entry == NULL){
        printf("Unable to allocate memory for current_entry\n");
        return -1;
    }
    return 0;
}

void insert_new_entry(int line ,char *symbol_name){
    char *error_def;
    if(check_entry_in_extern(symbol_name) != 1) {
        if(re_occuring_entry_name(symbol_name) == 1){
            error_def = "Reoccurring entry name";
            register_new_error(line, error_def);
        }else{
            insert_entry(symbol_name);
        }
    }else{
        error_def = "Entry was found in extern";
        register_new_error(line, error_def);
    }
}

void insert_entry(char* symbol_name){
    current_entry->symbol_name = malloc(sizeof(symbol_name));
    strcpy(current_entry->symbol_name, symbol_name);
    current_entry->next = NULL;
    current_entry->decimal_adress = 0;
    /* Linked list setters */
    if (entry_head == NULL) {
        entry_head = current_entry;
        entry_tail = current_entry;
    } else {
        entry_tail->next = current_entry;
        entry_tail = current_entry;
        entry_tail->next = NULL;
    }
}


int re_occuring_entry_name(char *potential_symbol_name){
    struct Entry *it = NULL;
    it = entry_head;
    while(entry_head != NULL){
        if(strcmp(entry_head->symbol_name, potential_symbol_name) == 0){
            entry_head = it;
            return 1;
        }
        entry_head = entry_head->next;
    }
    entry_head = it;
    return 0;
}

int check_entry_in_extern(char *potential_symbol_name){
    struct Extern *it = NULL;
    it = extern_head;
    while(extern_head != NULL){
        if(strcmp(extern_head->symbol_name, potential_symbol_name) == 0){
            extern_head = it;
            extern_head = it;
            return 1;
        }
        extern_head = extern_head->next;
    }
    extern_head = it;
    return 0;
}

int allocate_memory_for_extern(){
    current_extern = malloc(sizeof(struct Extern));
    if(current_extern == NULL){
        printf("Unable to allocate memory for current_entry\n");
        return -1;
    }
    current_extern->decimal_adress.array = NULL;
    return 0;
}

void insert_new_extern(int line ,char *symbol_name){
    char *error_def;
    if(check_extern_in_entry(symbol_name) != 1) {
        if(re_occuring_extern_name(symbol_name) == 1){
            error_def = "Reoccurring extern name";
            register_new_error(line, error_def);
        }else{
            insert_extern(symbol_name);
        }
    }else{
        error_def = "Extern was found in entry";
        register_new_error(line, error_def);
    }
}

void insert_extern(char* symbol_name){
    current_extern->symbol_name = malloc(sizeof(symbol_name));
    strcpy(current_extern->symbol_name, symbol_name);
    current_extern->next = NULL;
    /* Linked list setters */
    if (extern_head == NULL) {
        extern_head = current_extern;
        extern_tail = current_extern;
    } else {
        extern_tail->next = current_extern;
        extern_tail = current_extern;
        extern_tail->next = NULL;
    }
}


int re_occuring_extern_name(char *potential_symbol_name){
    struct Extern *it = NULL;
    it = extern_head;
    while(extern_head != NULL){
        if(strcmp(extern_head->symbol_name, potential_symbol_name) == 0){
            extern_head = it;
            return 1;
        }
        extern_head = extern_head->next;
    }
    extern_head = it;
    return 0;
}

int check_extern_in_entry(char *potential_symbol_name){
    struct Entry *it = NULL;
    it = entry_head;
    while(entry_head != NULL){
        if(strcmp(entry_head->symbol_name, potential_symbol_name) == 0){
            entry_head = it;
            return 1;
        }
        entry_head = entry_head->next;
    }
    entry_head = it;
    return 0;
}

int create_object_file(char* file_name){
    char *only_file_name;
    struct BinaryList *temp = NULL;
    int char_idx = 0;
    FILE *ob_file;
    temp = binary_head;

    only_file_name = strtok(file_name, FILE_DELIMITER);
    ob_file = fopen(strcat(only_file_name, ".ob"), "w");

    /*error in opening file*/
    if(ob_file == NULL) {
        printf("Error opening file\n");
        return -1;
    }
    printf("Creating a object file: %s\n", only_file_name);
    /*printing binary_list data into .ob file*/
    while(binary_head != NULL){
        for(; char_idx < sizeof(binary_head->binary_code); char_idx++){
            if(binary_head->binary_code[char_idx] == '1')
                binary_head->binary_code[char_idx] = '/';
            else
                binary_head->binary_code[char_idx] = '.';
        }
        char_idx = 0;
        fprintf(ob_file,"%s\n",binary_head->binary_code);
        binary_head = binary_head->next;
    }
    binary_head = temp;

    free_binary_list();
    fclose(ob_file);
    return 0;
}


int create_entry_file(char* file_name){
    char *only_file_name;
    struct Entry *temp = NULL;
    FILE *ent_file;
    temp = entry_head;

    only_file_name = strtok(file_name, FILE_DELIMITER);
    ent_file = fopen(strcat(only_file_name, ".ent"), "w");

    /*error in opening file*/
    if(ent_file == NULL) {
        printf("Error opening file\n");
        return -1;
    }
    printf("Creating an entry file: %s\n", only_file_name);
    /*printing binary_list data into .ob file*/
    while(entry_head != NULL){
        if(entry_head->decimal_adress!=0)
            fprintf(ent_file,"%s %d\n",entry_head->symbol_name, entry_head->decimal_adress);
        entry_head = entry_head->next;
    }
    entry_head = temp;

    fclose(ent_file);
    return 0;
}

int create_extern_file(char* file_name){
    char *only_file_name;
    struct Extern *temp = NULL;
    int adress_idx = 0;
    FILE *ext_file;
    temp = extern_head;

    only_file_name = strtok(file_name, FILE_DELIMITER);
    ext_file = fopen(strcat(only_file_name, ".ext"), "w");

    /*error in opening file*/
    if(ext_file == NULL) {
        printf("Error opening file\n");
        return -1;
    }
    printf("Creating an external file: %s\n", only_file_name);
    /*printing binary_list data into .ob file*/
    while(extern_head != NULL){
        for(;adress_idx < extern_head->decimal_adress.size; adress_idx++){
            if(extern_head->decimal_adress.array[adress_idx] != 0)
                fprintf(ext_file,"%s %d\n",extern_head->symbol_name, extern_head->decimal_adress.array[adress_idx]);
        }
        extern_head = extern_head->next;
        adress_idx = 0;
    }
    extern_head = temp;

    fclose(ext_file);
    return 0;
}


void initArray(struct DecimalAdressArray *a, size_t initialSize) {
    a->array = malloc(initialSize * sizeof(int));
    a->used = 0;
    a->size = initialSize;
}

void insertArray(struct DecimalAdressArray *a, int element) {
    if (a->used == a->size) {
        a->size *= 2;
        a->array = realloc(a->array, a->size * sizeof(int));
    }
    a->array[a->used++] = element;
}

void freeArray(struct DecimalAdressArray *a) {
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}


void free_entry_list(){
    while(entry_head != NULL){
        free(entry_head->symbol_name);
        free(entry_head);
        entry_head = entry_head->next;
    }
}

void free_extern_list(){
    while(extern_head != NULL){
        free(extern_head->symbol_name);
        freeArray(&extern_head->decimal_adress);
        free(extern_head);
        extern_head = extern_head->next;
    }
}

int check_if_extern_list_is_empty(){
    if(extern_head == NULL){
        return 1;
    }
    return 0;
}

int check_if_entry_list_is_empty(){
    if(entry_head == NULL){
        return 1;
    }
    return 0;
}
