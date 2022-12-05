#ifndef ALGORITHM_FUNCTIONS_H
#include <string.h>
#include <stdlib.h>
#define ALGORITHM_FUNCTIONS_H
#define INDEX_OFFSET 1
#define MAX_LENGTH 513

void create_substring(char substring[],char main_string[], int index,int len){
    memcpy(substring, &main_string[index], len);
    substring[len] ='\0';
}

int my_bcmp(const void *b1, const void *b2, int len){
    const char *first_substring = (const char *)b1;
    const char *second_substring = (const char *)b2;
    if(memcmp(first_substring, second_substring, len)==0){
        return 0;
    }
    else{
        return -1;
    }
}

#endif