/*
 * myset.c:
 * C program which will control all the user input and guide the user input to the right direction,
 * Also will check all the user input if it is valid or not and msg the user properly.
 */
#include <stdio.h>
#include <string.h>
#include "set.h"
#include <ctype.h>
#include <stdlib.h>

#define NUMBER_RANGE 128
#define MAX_LENGTH 512
#define NUMBER_OF_SETS 6
#define SET_NAME_LENGTH 4
/* valid operations is storing all the actions the user can use in the program */
const char *valid_operations[] = {"read_set", "print_set", "union_set", "intersect_set", "sub_set", "symdiff_set",
                                  "stop"};
/* set names is storing all the valid set names a user can use in the program */
const char *set_names[] = {"SETA", "SETB", "SETC", "SETD", "SETE", "SETF"};

/* sets is storing in every element a set struct, so we can use and identify it by his index, for example SETA = sets[0]
 * and so on.*/
set *sets[NUMBER_OF_SETS];

/*
 * intialize_all_sets method:
 * The method will initialize every element in the sets array, using the create_set method in the set.c program.
 */
int intialize_all_sets() {
    int set_idx = 0;
    for (; set_idx < NUMBER_OF_SETS; set_idx++) {
        sets[set_idx] = create_set();
        if (sets[set_idx] == NULL) {
            printf("Unable to allocate memory for you\n");
            return 1;
        }
    }
    return 0;
}

/*
 * check_input_numbers method:
 * The method will receive the user inputted numbers, and the amount of numbers inputted as len param,
 * The method will iterate over the inputted numbers and will check if they are a valid input,
 * returns 0 if all the input is valid or -1 if there is even on number that is not valid.
 */
int check_input_numbers(int *user_input, int len) {
    int number_idx = 0;
    int real_number_length = len - 1;
    for (; number_idx < real_number_length; number_idx++) {
        if ((user_input[number_idx] < 0 || user_input[number_idx] > 127) && (number_idx != real_number_length - 1)) {
            printf("Invalid set member - value out of range\n");
            return -1;
        } else if (user_input[real_number_length - 1] != -1) {
            printf("List of set members is not terminated correctly or you entered something different then integer\n");
            return -1;
        }
    }
    return 0;
}

/*
 * check_if_not_null_set method:
 * The method will receive the user input numbers, and the amount of numbers inputted as len param,
 * The method will return if the set the user inputted is not the null set,
 * 0 for not null, -1 for null.
 */
int check_if_not_null_set(int *user_input, int len) {
    int number_idx = 0;
    int real_number_length = len - 1;
    for (; number_idx < real_number_length; number_idx++) {
        if (user_input[number_idx] != 0) {
            return 0;
        }
    }
    return -1;
}

/*
 * check_set_name method:
 * The method will receive a pointer to the user input which should contain the set of the name,
 * The method will iterate over the set names, and check which name was picked by the user,
 * return the set name index in the sets_name array if there is a match between the user input to our stored names,
 * and returns -1 when the name is undefined by us.
 */
int check_set_name(char *user_input) {
    int set_idx;
    for (set_idx = 0; set_idx < NUMBER_OF_SETS; set_idx++) {
        if (memcmp(user_input, set_names[set_idx], 4) == 0)
            return set_idx;
    }
    return -1;
}

/*
 * check_command method:
 * The method will receive a pointer to the user input which should contain the user wanted command,
 * The method will iterate over the valid operations array and try to find a match between the user input and the
 * saved operations,
 * returns the index for the operation in the valid operations array if there is a match and -1 if there is not.
 */
int check_command(char *user_input) {
    int operation_idx = 0;
    for (; operation_idx < 7; operation_idx++) {
        if (memcmp(user_input, valid_operations[operation_idx], strlen(valid_operations[operation_idx])) == 0) {
            return operation_idx;
        }
    }
    return -1;
}

int main() {

    char user_input[MAX_LENGTH];
    int user_input_numbers[NUMBER_RANGE];
    int number_idx;
    int operation_idx;
    int name_check;
    int comma_counter = 1;
    int is_set_not_null = 0;
    char *user_input_pointer;
    set *user_first_input_set;
    set *user_second_input_set;
    set *user_third_input_set;

    /*Checking if were able to initialize all the sets, if not exit the program there was a problem allocating the needed memory*/
    if (intialize_all_sets() == 1) {
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

    while (fgets(user_input, MAX_LENGTH, stdin) != NULL) { /*User input which is continuous */
        user_input_pointer = user_input; /*Setting a pointer to the user input, so we could check it */

        while (isspace(*user_input_pointer)) {
            ++user_input_pointer; /* Forwarding the pointer if there is a space at the start of the command */
        }

        operation_idx = check_command(user_input_pointer); /* The pointer should be at the point where the command is starting, so we check if it is valid*/
        if (operation_idx != -1) { /* If it is valid keep going and check which command the user asked for */
            /* read_set */
            if (operation_idx == 0) {
                number_idx = 0;
                user_input_pointer += strlen(valid_operations[operation_idx]); /* Forwarding the pointer with the size of the command string */
                while (isspace(*user_input_pointer)) { /* once again skipping spaces */
                    ++user_input_pointer;
                }
                if (*user_input_pointer == '\0') { /* If we got to the null point we miss a parameter to use the read_set method */
                    printf("Missing parameter\n");
                } else if (*user_input_pointer == ',') { /* If we got to a comma before a set name it means we have an illegal comma */
                    printf("Illegal comma\n");
                } else { /* Otherwise we keep going and receiving the user input */
                    name_check = check_set_name(user_input_pointer); /* Next check is our user inputted set name */
                    user_input_pointer += SET_NAME_LENGTH; /* Once again we forward the pointer with the amount we need which is the set name length */
                    if (name_check != -1) { /*If the name is correct we move forward with our checks */
                        while (isspace(*user_input_pointer)) {
                            ++user_input_pointer;
                        }
                        if (*user_input_pointer != ',') { /* If we didn't receive a comma after the set name we have a missing comma */
                            printf("Missing comma\n");
                        } else { /* Otherwise everything is ok we continue to the numbers of the user */
                            while (*user_input_pointer != '\0') {
                                while (isspace((*user_input_pointer)) || *user_input_pointer == ',') { /* Skipping spaces and commas */
                                    if (*user_input_pointer == ',') {
                                        comma_counter++;
                                    }
                                    ++user_input_pointer;
                                }
                                user_input_numbers[number_idx] = strtol(user_input_pointer, &user_input_pointer, 10);
                                number_idx++;
                            }
                            is_set_not_null = check_if_not_null_set(user_input_numbers, number_idx);
                            if (check_input_numbers(user_input_numbers, number_idx) != 0) { /* If something wrong with the input take us out*/
                                printf("\n");
                            } else if ((*(user_input_pointer - 2) != '1') && is_set_not_null == 0) { /* If we have something after the -1 terminator take us out */
                                printf("Extraneous text after end of command\n");
                            } else if ((comma_counter != number_idx) && (is_set_not_null == 0)) { /* If we have more commas than the sets names take us out */
                                printf("Multiple consecutive commas\n");
                            } else if (check_input_numbers(user_input_numbers, number_idx) == 0 && (is_set_not_null == 0)) { /* Everything is ok use read_set */
                                user_first_input_set = sets[name_check];
                                memset(user_first_input_set, 0, 16);
                                read_set(user_first_input_set, user_input_numbers, number_idx);
                            }
                            comma_counter = 1;
                        }
                    } else { /* set name is not stored in our program */
                        printf("Undefined set name\n");
                    }
                }
                /* print_set */
            } else if (operation_idx == 1) {
                /* Checks are pretty similar */
                user_input_pointer += strlen(valid_operations[operation_idx]);
                while (isspace(*user_input_pointer)) {
                    ++user_input_pointer;
                }
                if (*user_input_pointer == '\0') {
                    printf("Missing parameter\n");
                } else if (*user_input_pointer == ',') {
                    printf("Illegal comma\n");
                } else {
                    name_check = check_set_name(user_input_pointer);
                    if (name_check != -1) {
                        printf("Printing the set %s: \n", set_names[name_check]);
                        user_input_pointer += SET_NAME_LENGTH;
                        user_first_input_set = sets[name_check];
                        if (*(user_input_pointer + 1) != '\0') {
                            printf("Extraneous text after end of command\n");
                        } else {
                            print_set(user_first_input_set);
                        }
                    } else {
                        printf("Undefined set name\n");
                    }
                }
                /* Union / Intersect / Sub / Symdiff_set */
            } else if (operation_idx == 2 || operation_idx == 3 || operation_idx == 4 || operation_idx == 5) {
                user_input_pointer += strlen(valid_operations[operation_idx]);
                while (isspace(*user_input_pointer)) {
                    ++user_input_pointer;
                }
                if (*user_input_pointer == '\0') {
                    printf("Missing parameter\n");
                } else if (*user_input_pointer == ',') {
                    printf("Illegal comma\n");
                } else {
                    name_check = check_set_name(user_input_pointer);
                    user_input_pointer += SET_NAME_LENGTH;
                    /* first name check */
                    if (name_check != -1) {
                        user_first_input_set = sets[name_check];
                        while (isspace(*user_input_pointer)) {
                            ++user_input_pointer;
                        }
                        if (*user_input_pointer == '\0') {
                            printf("Missing parameter \n");
                        } else if (*user_input_pointer != ',') {
                            printf("Missing comma\n");
                        } else {
                            ++user_input_pointer;
                            while (isspace(*user_input_pointer)) {
                                ++user_input_pointer;
                            }
                            if (*user_input_pointer == '\0') {
                                printf("Missing parameter\n");
                            } else if (*user_input_pointer == ',') {
                                printf("Multiple comma \n");
                            } else {
                                name_check = check_set_name(user_input_pointer);
                                user_input_pointer += SET_NAME_LENGTH;
                                /* 2nd name check */
                                if (name_check != -1) {
                                    user_second_input_set = sets[name_check];
                                    while (isspace(*user_input_pointer)) {
                                        ++user_input_pointer;
                                    }
                                    if (*user_input_pointer == '\0') {
                                        printf("Missing parameter\n");
                                    } else if (*user_input_pointer != ',') {
                                        printf("Missing comma \n");
                                    } else {
                                        ++user_input_pointer;
                                        while (isspace(*user_input_pointer)) {
                                            ++user_input_pointer;
                                        }
                                        if (*user_input_pointer == '\0') {
                                            printf("Missing parameter\n");
                                        } else if (*user_input_pointer == ',') {
                                            printf("Multiple commas\n");
                                        } else {
                                            name_check = check_set_name(user_input_pointer);
                                            user_input_pointer += SET_NAME_LENGTH;
                                            /* 3rd name check */
                                            if (name_check != -1) {
                                                sets[name_check] = create_set();
                                                user_third_input_set = sets[name_check];
                                                while (isspace(*user_input_pointer)) {
                                                    ++user_input_pointer;
                                                }
                                                if (*user_input_pointer != '\0') {
                                                    printf("Extraneous text after end command\n");
                                                } else {
                                                    /* Separating for each command */
                                                    if (operation_idx == 2) {
                                                        union_set(user_first_input_set, user_second_input_set,
                                                                  user_third_input_set);
                                                    } else if (operation_idx == 3) {
                                                        intersect_set(user_first_input_set, user_second_input_set,
                                                                      user_third_input_set);
                                                    } else if (operation_idx == 4) {
                                                        sub_set(user_first_input_set, user_second_input_set,
                                                                user_third_input_set);
                                                    } else {
                                                        symdiff_set(user_first_input_set, user_second_input_set,
                                                                    user_third_input_set);
                                                    }
                                                }

                                            } else {
                                                printf("Undefined set name\n");
                                            }
                                        }
                                    }
                                } else {
                                    printf("Undefined set name\n");
                                }
                            }
                        }
                    } else {
                        printf("Undefined set name\n");
                    }
                }
                /*Stopping action*/
            } else if (operation_idx == 6) {
                printf("stopping \n");
                break;
            }
        } else {
            printf("You entered a wrong command\n");
        }
        printf("prompt: \n");
    }


    return 0;
}