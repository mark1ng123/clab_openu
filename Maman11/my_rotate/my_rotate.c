/*
// The my_rotate program:
// The purpose of the program is to receive a number positive negative or equal to zero, and another
 number of rotation the user wants to make as input from the user,
// convert the number to binary and rotate it as much as the user wanted, convert it to back to decimal.
// And as an output to print the representation of the number in hexadecimal, octal, and binary representations.
 // meaning base 16,8,2 for the number that is the user input and one for the rotated one.
*/
#include "helper_functions.h"

int main()
{
    unsigned int inputNum;
    int rotate;
    printf("Please give your number: \n");
    scanf("%u", &inputNum);
    printf("Please give your rotation: \n");
    scanf("%d", &rotate);
    printf("\n");
    my_rottate(inputNum, rotate);
    return 0;
}