

/*how this program work:
  it will change the int value of an integer to his ascii char value
  according to its table value + according to the given base, then shift it,
  and it will print it shifted according to its base*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BITS 32


#ifndef MAMAN11_HELPER_FUNCTIONS_H
#define MAMAN11_HELPER_FUNCTIONS_H

/* printing the array */
void print_array(int arr[]){
    int idx;
    for (idx=0;  idx<MAX_BITS ; idx++){
        printf("%d", arr[idx]);
    }
    printf("\n");
}

/* rotates the binary array by one to the right */
void rotate_by_one(int arr[])
{
    int bit_idx, last_element;
    last_element = arr[MAX_BITS - 1];
    for(bit_idx=MAX_BITS-1; bit_idx>0; bit_idx--)
    {
        arr[bit_idx] = arr[bit_idx - 1];
    }
    arr[0] = last_element;
}

/* receive an integer array representing a binary number, and converts it to decimal */
unsigned binary_to_decimal(const int arr[]){
    int base_10_num = 0;
    int bit_idx;
    for(bit_idx=0; bit_idx<MAX_BITS;bit_idx++){
        base_10_num<<=1;
        base_10_num += arr[bit_idx];
    }
    return base_10_num;
}

/* Function to rotate array by 'b' bits as described*/
unsigned rotate(int arr[], int b)
{
    /* Declaring a temp integer array to receive the right bits after conversion*/
    int temp[MAX_BITS];
    int new_bit_idx = 0;
    int bit_idx;
    /* rotation is left when b is negative */
    if (b < 0) {
        /* convert to abs value, so we can declare a right movement to the left*/
        b = abs(b);
        /* Sorting the MAX_BITS - b elements to the front of the new array */
        for (bit_idx = b; bit_idx < MAX_BITS; bit_idx++) {
            temp[new_bit_idx] = arr[bit_idx];
            new_bit_idx++;
        }
        /* Taking the remains and putting it in the last spots */
        for (bit_idx = 0; bit_idx < b; bit_idx++) {
            temp[new_bit_idx] = arr[bit_idx];
            new_bit_idx++;
        }
        /* copying it back */
        for (bit_idx = 0; bit_idx < MAX_BITS; bit_idx++) {
            arr[bit_idx] = temp[bit_idx];
        }
        printf("binary representation for rotated number is: \n");
        print_array(arr);
    }
    else {
        /* b is positive or 0 and that's why we rotate it to the right
         * Rotate it by one b times*/
        for(bit_idx=1; bit_idx<=b; bit_idx++)
        {
            rotate_by_one(arr);
        }
        printf("binary representation for rotated number is: \n");
        print_array(arr);
    }
    return binary_to_decimal(arr);
}

/* The method receives two arguments, 1 is the number we want to rotate, and 2 is the number of rotations.
 * The output is the number rotated by 'rotation bits' left or right depending on  rotation > 0 or < 0.
 */
unsigned decimal_to_binary_and_rotation(unsigned int num, int rotation)
{
    int binary_num[MAX_BITS];
    int bit_index = 0;
    for (; bit_index<MAX_BITS ;bit_index++){
        binary_num[bit_index] = 0;
    }
    bit_index = MAX_BITS-1;
    for ( ;bit_index >= 0 ;bit_index--){
        binary_num[bit_index] = num % 2;
        num /= 2;
    }
    printf("binary representation for entered number is: \n");
    print_array(binary_num);
    printf("\n");
    return rotate(binary_num, rotation); /* Returns the number after the rotation and conversion to decimal*/
}

/* The asked method in the program, receive parameter a and rotate it by 'b' bits */
unsigned int my_rottate (unsigned int a, int b){
    unsigned int rotated_a;
    printf("Decimal representation for entered number is : %d\n", a);
    printf("Hexadecimal representation for entered number is : %x\n",a);
    printf("Octal decimal representation for entered number is:  %o\n",a);
    rotated_a = decimal_to_binary_and_rotation(a, b);
    printf("Decimal representation for rotated number is : %d\n", rotated_a);
    printf("Hexadecimal representation for rotated number is : %x\n",rotated_a);
    printf("Octal decimal representation for rotated number is:  %o\n",rotated_a);
    return rotated_a;
}

#endif
