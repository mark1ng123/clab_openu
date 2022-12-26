/*
 * algo program file:
 * Will implement all the methods written in the algo header file.
 */
#include "algo.h"

void swap(char* first, char* second){
    char temp;
    temp = *first;
    *first = *second;
    *second = temp;
}

void permute(char* wanted_string, char* current_word, int start, int end){
    int char_idx;
    /* Backtrack */
    if(start == end && (strstr(current_word, wanted_string) != NULL)){
        printf("%s\n", wanted_string);
    }
    else{
        for(char_idx = start; char_idx <= end; char_idx++){
            swap((wanted_string + start), (wanted_string + char_idx));
            permute(wanted_string,current_word, start+1, end);
            swap((wanted_string + start), (wanted_string + char_idx));
        }
    }
}

