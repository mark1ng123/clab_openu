/*
// The abc program:
// The purpose of the program is to receive a string input from the user,
// Check for sequence from the english alphabet.
// For example: abc is a sequence, abcdef, xyz, etc.
// When we get a sequence as described above we would want to adjust the sequence from: abc->a-c, abcdef->a-f and so on.
// If we receive anything other than the wanted abc chars we will just ignore it.
*/

/*Includes*/
#include "abc_helper_functions.h"
#include <stdio.h>

/*Declarations:
// Input size we assume is 80 chars.
*/
#define INPUT_SIZE 80

/*main function, as minimal as possible.*/
int main(int argc, char* argv[]){
    char input_string[INPUT_SIZE];
    printf("Welcome to the abc program\n");
    receive_new_input_and_create_seq(input_string);
    return 0;
}