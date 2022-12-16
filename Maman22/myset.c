#include <stdio.h>
#include <string.h>
#include "set.h"
#include <ctype.h>
#include <stdlib.h>

#define NUMBER_RANGE 128
#define MAX_LENGTH 512
#define NUMBER_OF_SETS 6

const char *valid_operations[] = {"read_set", "print_set", "union_set", "intersect_set", "sub_set", "symdiff_set", "stop"};
const char *set_names[]={"SETA", "SETB", "SETC", "SETD", "SETE", "SETF"};
set* sets[NUMBER_OF_SETS];

int intialize_all_sets(){
    int set_idx=0;
    for(;set_idx < 6; set_idx++){
        sets[set_idx] = create_set();
        if(sets[set_idx] == NULL){
            printf("Unable to allocate memory for you\n");
            return 1;
        }
    }
    return 0;
}

int check_input_numbers(int *user_input, int len){
    int number_idx = 0;
    int real_number_length = len-1;
    for(;number_idx<real_number_length;number_idx++){
        if((user_input[number_idx] < 0 || user_input[number_idx] > 127) && (number_idx != real_number_length-1)){
            printf("Numbers are not in the wanted range [0,127]\n");
            return -1;
        }else if((user_input[number_idx] == -1) && (number_idx != real_number_length-1)) {
            printf("-1 is not in the right place which is the last place\n");
            return -1;
        }else if(user_input[real_number_length-1]!=-1){
            printf("-1 is not closing the read option or you entered something different then integer\n");
            return -1;
        }
    }
    return 0;
}

int check_set_name(char *user_input){
    int set_idx;
    printf("got %s", user_input);
    for(set_idx=0; set_idx < NUMBER_OF_SETS; set_idx++){
        if(memcmp(user_input, set_names[set_idx], 4) == 0)
            return set_idx;
    }
    return -1;
}

int check_command(char *user_input){
    int operation_idx = 0;
    for(; operation_idx < 7; operation_idx++){
        if(memcmp(user_input, valid_operations[operation_idx], strlen(valid_operations[operation_idx])) == 0){
            return operation_idx;
        }
    }
    return -1;
}

int main(){
    char user_input[MAX_LENGTH];
    int user_input_numbers[NUMBER_RANGE];
    int number_idx;
    int operation_idx;
    int name_check;
    int comma_counter = 1;
    char *user_input_pointer;
    set* user_input_set;

    if(intialize_all_sets() == 1){
        printf("exiting\n");
        return 1;
    }

    printf("Hi, Welcome to myset program: \n");
    printf(" 1. Valid set names: SETA, SETB, SETC, SETD, SETE, SETF.\n");
    printf(" 2. Valid operations on sets: read_set, print_set, union_set, intersect_set, sub_set, symdiff_set. \n");
    printf(" 3. Valid integer range for input is: [0-127]\n");
    printf("Here is a simple operation examples: \n");
    printf(" 1. Read set: read_set {SETNAME}, {number}, ..., {number}, -1 \n");
    printf(" 2. Print set: print_set {SETNAME} \n");
    printf(" 3. Union set: union_set {FIRST_SETNAME},{SECOND_SETNAME},{THIRD_SETNAME} \n");
    printf(" 4. Intersect set: intersect_set {FIRST_SETNAME},{SECOND_SETNAME},{THIRD_SETNAME} \n");
    printf(" 5. Sub set: sub_set {FIRST_SETNAME},{SECOND_SETNAME},{THIRD_SETNAME} \n");
    printf(" 6. Symmetrical difference: symdiff_set {FIRST_SETNAME},{SECOND_SETNAME},{THIRD_SETNAME} \n");
    printf(" 7. To quit enter stop\n\n");

    printf("prompt: \n");
    while (fgets(user_input, MAX_LENGTH, stdin) != NULL) {
        user_input_pointer = user_input;
        printf("input: %s", user_input_pointer);
        while (isspace(*user_input_pointer)) {
            ++user_input_pointer;
        }
        operation_idx = check_command(user_input_pointer);
        if (operation_idx != -1) {
            printf("operation idx: %d\n", operation_idx);
            if (operation_idx == 0) {
                number_idx = 0;
                user_input_pointer += strlen(valid_operations[operation_idx]);
                printf("wanted: %s\n", user_input_pointer);
                while (isspace(*user_input_pointer)) {
                    ++user_input_pointer;
                }
                if(*user_input_pointer == ','){
                    printf("Illegal comma\n");
                }
                else{
                    name_check = check_set_name(user_input_pointer);
                    user_input_pointer += 4;
                    if (name_check != -1) {
                        while (isspace(*user_input_pointer)) {
                            ++user_input_pointer;
                        }
                        if (*user_input_pointer != ',') {
                            printf("You didnt put coma before reading the numbers\n");
                        } else {
                            while (*user_input_pointer != '\0') {
                                while (isspace((*user_input_pointer)) || *user_input_pointer == ',') {
                                    if(*user_input_pointer ==','){
                                        comma_counter++;
                                    }
                                    ++user_input_pointer;
                                }
                                user_input_numbers[number_idx] = strtol(user_input_pointer, &user_input_pointer, 10);
                                number_idx ++;
                            }
                            printf("%c\n\n",*(user_input_pointer-2) );
                            if (check_input_numbers(user_input_numbers, number_idx) != 0) {
                                printf("\n");
                            }
                            else if((*(user_input_pointer-2) != '1')){
                                printf("Extraneous text after end of command\n");
                            }
                            else if(comma_counter != number_idx){
                                printf("Multiple consecutive commas\n");
                            }
                            else if (check_input_numbers(user_input_numbers, number_idx) == 0) {
                                user_input_set = sets[name_check];
                                memset(user_input_set, 0, 16);
                                read_set(user_input_set, user_input_numbers, number_idx);
                            }
                            comma_counter = 1;
                        }
                }else {
                        printf("You entered a wrong set name\n");
                }
            }
            }
            else if (operation_idx == 1) {
            user_input_pointer += strlen(valid_operations[operation_idx]);
            printf("wanted: %s\n", user_input_pointer);
            while (isspace(*user_input_pointer)) {
                ++user_input_pointer;
            }
            if(*user_input_pointer == ','){
                printf("Illegal comma\n");
            }
            else{
                name_check = check_set_name(user_input_pointer);
                if (name_check != -1) {
                    printf("Printing the set %s: \n", set_names[name_check]);
                    user_input_pointer += 4;
                    user_input_set = sets[name_check];
                    if(*(user_input_pointer+1) != '\0'){
                        printf("Extraneous text after end of command\n");
                    }
                    else{
                        print_set(user_input_set);
                    }
                } else {
                    printf("Entered a wrong set name\n");
                }
            }
        }else if(operation_idx == 2 || operation_idx == 3 || operation_idx == 4 || operation_idx == 5){

            if(operation_idx == 2){
                printf("union_set\n");
                union_set(sets[0], sets[1], sets[2]);
            }else if(operation_idx == 3){
                printf("intersect_set\n");
                intersect_set(sets[0], sets[1], sets[2]);
            }
            else if(operation_idx == 4){
                printf("sub_set");
                sub_set(sets[0], sets[1], sets[2]);
            }
            else{
                printf("symdiff_set\n");
                symdiff_set(sets[0], sets[1], sets[2]);
            }
        }
        else if(operation_idx == 6){
            printf("stopping \n");
            break;
        }
    }else {
            printf("You entered a wrong command\n");
    }
        printf("prompt: \n");
    }



    return 0;
}