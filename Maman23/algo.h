/*
 * Algo header file:
 * Declaring and including all the functions needed from the main permutation algorithm to run.
 */
#include <stdio.h>
#include <string.h>

#ifndef ALGO_H
#define ALGO_H

/*
 * Swap method:
 * Input:
 * 1. Pointer for the first char.
 * 2. Pointer for the second char.
 * The method will swap places of any given chars in a string.
 */
void swap(char* first, char* second);

/*
 * Permute method:
 * Input:
 * 1. Pointer to the given argument string.
 * 2. Pointer to the current word read from the file.
 * 3. Start point in the string, will always be 0 in our case.
 * 4. End point in the string, will always be the strlen(string)-1 in our case.
 * The method will run using recursion, on every iteration it will check if the start integer equals the end integer
 * this will allow us to implement the backtrack method, and the second check will be if it equals to the word read from
 * file.
 * This will give us the option to iterate over any permutation the given string has and compare it to any word in the file.
 */
void permute(char* wanted_string,char* current_word, int start, int end);


#endif
