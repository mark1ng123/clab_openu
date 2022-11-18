/*
 The header file for the abc_helper_functions,
 mostly to declare which functions we will need to declare in the program to use it.
 */

/* The algorithm:
 We will receive the input from the user using the receive_new_input method,
 Then we will run another function declared in the abc_helper_functions that
 will iterate over the string we're receiving and check for sequences from the abc alphabet.
 The way we are iterating is:
 Two for loops, the first loop will set the first index that we will check from.
 The second loop will keep advancing in the array and compare to his pre-successor.
 When the comparison in no longer valid we will adjust our string by the two edges set with the first index in the
 first for loop and the second index in the second loop.
*/
#ifndef MAMAN11_ABC_HELPER_FUNCTIONS_H
#define MAMAN11_ABC_HELPER_FUNCTIONS_H

/*
abc program helper functions,
This functions was made to make the abc.c program to be more readable,
All is explained in the header file of this program.
*/

/* includes*/
#include "abc_helper_functions.h"
#include <stdio.h>
#include <string.h>

/*defines:
 Input size we assume is 80 chars.
*/
#define INPUT_SIZE 80

/* input -> user string input.
output -> None
The method adjusts the user input string and changes it as we described in the abc.c file and in the header file.
And lastly will print the adjusted string.
*/
void get_sequence_string(char input_string[]){
    /* Declarations:*/
    int count = 0;
    int first_char_idx = 0;
    char last_seq_char;
    int moving_idx;
    int temp_idx;

    printf("received input string: \n%s\n", input_string);
    printf("Input is good, running algorithm...\n");

    /* Two for loops, running and calculating the sequence for the 'abc' alphabet only.*/
    for(; first_char_idx < strlen(input_string);){
        /* Complex expression to check whether we need to start calculating sequence or not depending on the value of the element. (alphabet or not)*/
        if(!((input_string[first_char_idx] >= 'a' && input_string[first_char_idx]<='z' )|| (input_string[first_char_idx] >= 'A' && input_string[first_char_idx]<='Z')))
        {
            first_char_idx++;
            continue;
        }
        else{
            /* If we came to the else statement it means our element is between A-Z or a-z:
            We define the second index to be the first index we checked +1, so we could always compare two elements in our char array.
            */
            int second_char_idx=first_char_idx+1;
            for(; second_char_idx < strlen(input_string); second_char_idx++){
                /* The expression is checking whether the second element is higher than the first one by one step in
                the alphabet, using the ASCII values.
                */
                if(input_string[first_char_idx] + count == input_string[second_char_idx]-1){
                    /* if we enter the if statement we count the number of elements that continue to make this
                    statement true to understand what is the seq size at the end.
                    */
                    count++;
                    last_seq_char = input_string[second_char_idx];
                }
                    /* We don't really need the expression here, but it is more readable to understand that we want to break
                    the loop because the next element is either last or not qualified for our sequence.
                    */
                else {
                    break;
                }
            }
            /*If we caught a sequence bigger than 1 we need to adjust our string as we wanted and explained in the abc.c file.*/
            if(count > 1){
                /* Adjusting the first place in the sequence to be the first element
                the second place in the sequence to be -
                 and the third one is the second element closing the seq.
                */
                input_string[first_char_idx+1] = '-';
                input_string[first_char_idx+2] = last_seq_char;
                moving_idx = first_char_idx + 3;
                temp_idx = first_char_idx + count + 1;
                first_char_idx = first_char_idx + 3;
                /* after the adjustment we move all the elements that was further then the second element to the left,
                 so we can receive a clean string with no spaces.
                */
                while(temp_idx<=strlen(input_string)){
                    input_string[moving_idx] = input_string[temp_idx];
                    temp_idx++;
                    moving_idx++;
                    if(input_string[temp_idx]=='\n'){
                        input_string[moving_idx] = '\0';
                    }
                }
            }
                /*If we enter this statement it means our sequence is the whole string, so we adjust the whole string.*/
            else if(count==strlen(input_string)-first_char_idx-2 && (count !=1 && count !=0)){
                input_string[first_char_idx+1] = '-';
                input_string[first_char_idx+2] = last_seq_char;
                moving_idx = first_char_idx + 3;
                input_string[moving_idx] = '\0';
            }
                /*This statement is when we had a seq size of 1 or 0, and it is not qualified for us.*/
            else{
                first_char_idx++;
            }
            /*resting the counter for the next seq to arrive.*/
            count=0;
        }
    }
    printf("After algo: %s\n", input_string);
}


/* The method receives the user input.*/
void receive_new_input_and_create_seq(char input_string[]){
    printf("Enter a string containing only the 'abc' alphabet: ");
    fgets(input_string, INPUT_SIZE, stdin); /*Input from stdin.*/
    get_sequence_string(input_string);
}

#endif
