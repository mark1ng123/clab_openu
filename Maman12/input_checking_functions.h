/*
 * Input checking functions header file:
 * Overview:
 * This header file will handle all input checking from the user:
 * 1. Negative decimal numbers
 * 2. String instead of a number
 * 3. Inputted numbers are bigger than limits of the maximum length of the string
 * 4. Inputted indexes and length causing a substring outside of the length string limits.
 * Does also simple operations of casting from string to int the needed inputs.
 */
#ifndef INPUT_CHECKING_FUNCTIONS_H
#define INPUT_CHECKING_FUNCTIONS_H
/*Simple include*/
#include <string.h>

#define MAX_LENGTH 513
#define ASCII_OFFSET 48
#define INDEX_OFFSET 1

/*
 * Input:
 * 1. length_string - the length of the inputed string
 * 2. input_len - the length value the user inputted
 * Output:
 * 1. return -1 when the inputted length is bigger then the string length
 * 2 return 1 otherwise
 */
int check_string_length_vs_input_len(int length_string, int input_len){
    if (input_len >= length_string){
        return -1;
    }
    return 1;
}

/*
 * Input:
 * 1. The string the user inputted that supoose to represent an integer.
 * Output:
 * 1. returns the wanted integer after we cast the string to integer.
 */
int calculate_wanted_intger(char checked_intger[]){
    int wanted_intger;
    /*Checking with simple expressions the length of the string to cast it the right way and taking care of the
     * Hundreds digit, decimal digit, etc.
     * We give +1 to our checked lengths because of the '\n' value cause by the ENTER in fgets.
     */
    if(strlen(checked_intger) == 4){
        int hundreds_intger = ((int)checked_intger[0] - ASCII_OFFSET) * 100;
        int decimal_intger = ((int)checked_intger[1]-ASCII_OFFSET) * 10;
        int singles_intger = ((int)checked_intger[2]-ASCII_OFFSET);
        wanted_intger = hundreds_intger + decimal_intger + singles_intger;
    }
    else if(strlen(checked_intger)==3){
        int decimal_intger = ((int)checked_intger[0]-ASCII_OFFSET) * 10;
        int singles_intger = ((int)checked_intger[1] - ASCII_OFFSET);
        wanted_intger = decimal_intger + singles_intger;
    }
    else if (strlen(checked_intger)==2){
        wanted_intger = (int)checked_intger[0] - ASCII_OFFSET;
    }
    printf("%d\n", wanted_intger);
    return wanted_intger;
}

/*
 * Input:
 * 1. The string the user inputted that supposed to represent an integer.
 * Output:
 * returns -1 when the string represent a negative integer.
 * return 1 otherwise.
 */
int check_if_negative(char check_intger[]){
    if(check_intger[0] == '-'){
        return -1;
    }
    return 1;
}

/*
 * Input:
 * 1. The user inputted string that supposed to represent integer.
 * Output:
 * returns -1 when the inputted string doesn't represent an integer and represent a string.
 * returns 1 otherwise.
 */
int check_if_string(char checked_intger[]){
    /*Checking with simple expressions, and depending on the length of the string, we look at the 3 first digits
     * And taking care of negative numbers or some chars inside of it and returning 1 if its an integer, we assume
     * a real number is a string because the dot it has.*/
    if(strlen(checked_intger) == 4) {
        if ((((int) checked_intger[0] < 48 || (int) checked_intger[0] > 57) && checked_intger[0] != '-')||
            ((int) checked_intger[1] < 48 || (int) checked_intger[1] > 57) ||
            ((int) checked_intger[2] < 48 || (int) checked_intger[2] > 57)) {
            return -1;
        }
    }
    else if(strlen(checked_intger)==3) {
        if ((((int) checked_intger[0] < 48 || (int) checked_intger[0] > 57) && checked_intger[0] != '-')||
            ((int) checked_intger[1] < 48 || (int) checked_intger[1] > 57)){
            return -1;
        }
    }
    else if(strlen(checked_intger) == 2){
        if (((int) checked_intger[0] < 48 || (int) checked_intger[0] > 57) && checked_intger[0] != '-'){
            return -1;
        }
    }
    return 1;
}

/*
 * Input:
 * 1. the user inputted string that supossed to represent an integer.
 * Output:
 * return -1 when the string dosent represent an integer
 * return 1 otherwise.
 */
int check_valid_int_and_convert_to_int(char checked_intger[]){
    int wanted_intger;

    /* checked if the inputted string is empty */
    if(strlen(checked_intger) < 2){
        printf("Input is empty, Enter a 3 digit number,");
        return -1;
    }
    /*Checking if the inputted string is bigger then the main string the user inputted*/
    if(strlen(checked_intger) > 4 && checked_intger[0]!= '-'){
        printf("Input size is to big, Enter a 3 digit number,");
        return -1;
    }
    /*Difference between expressions that we negative numbers also*/
    else if(strlen(checked_intger) > 4){
        printf("Input size is to big, Enter a 3 digit number,");
        return -1;
    }
    /*checking if dosent represent an integer*/
    if(check_if_string(checked_intger) == -1){
        printf("You entered a string,");
        return -1;
    }
    /*checking if the represent integer is negative*/
    else if(check_if_negative((checked_intger)) == -1){
        printf("You entered a negative integer,");
        return -1;
    }
    wanted_intger = calculate_wanted_intger(checked_intger);
    /*checking if one of the represent integers is out of the max limit*/
    if(wanted_intger >= MAX_LENGTH){
        printf("You entered number that is to high, Enter less then 512,");
        return -1;
    }
    else{
        return wanted_intger;
    }
}
/*Input:
 * 1.first index user inputted
 * 2.second index user inputted
 * 3. main string length
 * 4. the length the user inputted.
 * Output:
 * returns -1 when one of the substrings created is outside of the main string length
 * returns 1 otherwise
 * */
int compare_via_index(int first_index, int second_index, int string_length, int len){
    if(first_index - INDEX_OFFSET + len >= string_length || second_index - INDEX_OFFSET + len >= string_length){
        printf("The length from one of the indexes is higher then the string length");
        return -1;
    }
    else{
        return 1;
    }
}


#endif
