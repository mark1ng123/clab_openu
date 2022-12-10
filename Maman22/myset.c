#include <stdio.h>
#include <string.h>
#include "set.h"
#include <ctype.h>
#include <stdlib.h>

#define NUMBER_RANGE 128
#define MAX_LENGTH 512

const char *valid_operations[] = {"read_set", "print_set"};
set* sets[6];

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

int check_command(char *user_input){
    int operation_idx = 0;
    for(; operation_idx < 2; operation_idx++){
        if(memcmp(user_input, valid_operations[operation_idx], strlen(valid_operations[operation_idx])) == 0){
            return operation_idx;
        }
    }
    return operation_idx;
}

int main(){
    char user_input[MAX_LENGTH];
    int user_input_numbers[NUMBER_RANGE];
    int number_idx;
    int operation_idx;
    char *valid_sets[]={"SETA", "SETB", "SETC", "SETD", "SETE", "SETF"};
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
    while (fgets(user_input, MAX_LENGTH, stdin) != NULL){
        user_input_pointer = user_input;
        printf("input: %s", user_input_pointer);
        while(isspace(*user_input_pointer)){
            ++user_input_pointer;
        }
        operation_idx = check_command(user_input_pointer);
        user_input_set = sets[0];
        printf("operation idx: %d\n", operation_idx);
        if(operation_idx == 0){
            number_idx = 0;
            user_input_pointer += strlen(valid_operations[operation_idx]);
            printf("wanted: %s\n", user_input_pointer);
            while(isspace(*user_input_pointer)){
                ++user_input_pointer;
            }
            while(*user_input_pointer != '\0'){
                while(isspace((*user_input_pointer)) || *user_input_pointer==','){
                    ++user_input_pointer;
                }
                user_input_numbers[number_idx] = strtol(user_input_pointer, &user_input_pointer, 10);
                printf("got numbers: %d\n", user_input_numbers[number_idx]);
                number_idx++;
            }
            memset(user_input_set, 0, 16);
            read_set(user_input_set, user_input_numbers, number_idx);
        }
        else{
            printf("First set printed: \n");
            print_set(user_input_set);
        }
        printf("prompt: \n");
    }



    return 0;
}