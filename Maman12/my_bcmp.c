/*
 * my_bcmp program:
 * Overview:
 * The program will receive 4 values, length, two indexs and a string.
 * The program will return a message whether a substring from the first index in the received length and a
 * second substring starting from the second index in the same length as the first one are memory equal (bits).
 * Input:
 *  1. Length - The user will input the length value of the substrings he would like to check.
 *  2. First index - Starting point for the first substring.
 *  3. Second index - Starting point for the second substring.
 *  4. String - The main string he wants to substring and check equality inside.
 *  Output:
 *  The output is a simple message, whether the substrings are bits equal or not.
 */

/* Basic includes*/
#include <stdio.h>
#include <string.h>
/* Header includes*/
#include "input_checking_functions.h"
#include "algorithm_functions.h"

/* Macro definitions */
/* Max length is not 512 because we catch the '\n' char at the end of the input of the user caused by the ENTER key */
#define MAX_LENGTH 513
#define INDEX_OFFSET 1


/* Main function, controlling all inputs and function calls, returns -1 when something fails during the run, and 0 when
 * successful. */
int main(){
    /* Simple declarations:
     * first index - the first index the user inputs.
     * second index - the second index the user inputs.
     * len - the length of the substrings the user would like to check.
     * input string - the string the being substringed.
     * first and second substrings - substrings starting from the first/second index and have the length of the inputted length.
     * first/second/len converted - the integers the user inputted, we receive with fgets that's why we convert to int.
     */
    char first_index[MAX_LENGTH], second_index[MAX_LENGTH], len[MAX_LENGTH];
    char input_string[MAX_LENGTH];
    char first_substring[MAX_LENGTH];
    char second_substring[MAX_LENGTH];
    int first_index_converted, second_index_converted, len_converted;

    printf("Welcome comrad,\nPlease enter checking length in this range [0-512]:\n");
    fgets(len, MAX_LENGTH, stdin);
    len_converted = check_valid_int_and_convert_to_int(len);
    if(len_converted == -1){
        printf("Length is not valid\n");
        return -1;
    }
    /*Entering length of size 0 always return equal as asked*/
    else if(len_converted == 0){
        printf("Substrings of length 0 are always equal\n");
        return 0;
    }

    printf("Enter your first index in range [1-512]\n");
    fgets(first_index, MAX_LENGTH, stdin);
    first_index_converted = check_valid_int_and_convert_to_int(first_index);
    if(first_index_converted == -1){
        printf("First index is not valid\n");
        return -1;
    }

    printf("Enter your second index in range [1-512]\n");
    fgets(second_index, MAX_LENGTH, stdin);
    second_index_converted = check_valid_int_and_convert_to_int(second_index);
    if(second_index_converted == -1){
        printf("Second index is not valid\n");
        return -1;
    }

    printf("Please enter your string of max size 512 chars:\n");
    fgets(input_string, MAX_LENGTH, stdin);
    if(check_string_length_vs_input_len(strlen(input_string), len_converted) == -1){
        printf("You entered a smaller string then your input checking length\n");
        return -1;
    }
    else if(compare_via_index(first_index_converted, second_index_converted, strlen(input_string), len_converted) == -1){
        printf(",The compared sub strings are not the same\n");
        return -1;
    }

    create_substring(first_substring, input_string, first_index_converted-INDEX_OFFSET,len_converted);
    create_substring(second_substring, input_string, second_index_converted-INDEX_OFFSET,len_converted);
    printf("Comparing between: %s, %s\n", first_substring, second_substring);

    if(my_bcmp(first_substring, second_substring, len_converted) == 0){
        printf("The compared sub strings have the same memory values\n");
    }
    else{
        printf("The compared sub strings does not have the same memory values\n");
    }
    return 0;
}
