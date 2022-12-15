/*
 * Algroithm functions header file:
 * Overview:
 * This header file will handle all algorithm steps to return the final answer:
 * 1. Create a substring for every index inputted.
 * 2. Use my_bcmp to return the final answer wheter the substrings are equal or not.
 */
#ifndef ALGORITHM_FUNCTIONS_H
#include <string.h>
#include <stdlib.h>
#define ALGORITHM_FUNCTIONS_H
#define INDEX_OFFSET 1
#define MAX_LENGTH 513


/*
 * Input:
 * 1. substring - the char array we want to enter the values in
 * 2. mainstring - the string the user inputted for us to check substring on.
 * 3. index - starting index in main string.
 * 4. len - the substring length.
 * Output:
 * No output, filling the substring declared in my_bcmp.c
 */
void create_substring(char substring[],char main_string[], int index,int len){
    memcpy(substring, &main_string[index], len);
    substring[len] ='\0';
}

/*
 * Input:
 * 1. b1 - the first pointer, pointing at the first index position in substring1
 * 2. b2 - the second pointer, pointing at the first index position in substring2
 * 3. len - the length of the substring, the route the pointer covers.
 * Output:
 * 1. 0 if equals
 * 2. -1 if not equals
 */
int my_bcmp(const void *b1, const void *b2, int len){
    unsigned char *first_substring = (unsigned char *)b1;
    unsigned char *second_substring = (unsigned char *)b2;

    while (len > 0)
    {
        if (*first_substring != *second_substring)
            return -1;
        len--;
        first_substring++;
        second_substring++;

    }
    return 0;
}

#endif
