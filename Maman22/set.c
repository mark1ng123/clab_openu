/*
 * set.c:
 * C programming file, implementing all the declared function in the set.h header file.
 */
#include "set.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define NUMBER_RANGE 128
#define BITS_IN_BYTE 8
#define FLAG 1
#define BYTES_NEEDED 16

/*
 * Set struct, our main data type in the project.
 */
struct set {
    char bit_map[NUMBER_RANGE];
};


void set_bit_map(set *s, int idx) {
    s->bit_map[idx / BITS_IN_BYTE] |= FLAG << idx % BITS_IN_BYTE;    /* Shifting the 1 to the right bit position in the byte and
 *  setting it in the right byte in the set storage */
}

int get_bit_from_index(set *s, int index) {
    return (s->bit_map[index / BITS_IN_BYTE] & (FLAG << index % BITS_IN_BYTE)); /* Going to the right byte pos in the set storage
 * and returning the address for the wanted index */
}

set *create_set() {
    /* Allocating and returning the pointer for the allocated memory*/
    set *s = (set *) calloc(BYTES_NEEDED, BITS_IN_BYTE);
    if (s == NULL) {
        return NULL;
    }
    s->bit_map[0] = '\0';
    return s;
}

void read_set(set *s, int *number, int length) {
    int idx = 0;
    for (; idx < length && *number != -1; idx++) {
        set_bit_map(s, *number);
        ++number;
    }
}

void union_set(set *first_set, set *second_set, set *united_set) {
    int idx = 0;
    for (; idx < NUMBER_RANGE; idx++) {
        if ((get_bit_from_index(first_set, idx) || get_bit_from_index(second_set, idx))) {
            set_bit_map(united_set, idx);
        }
    }
}

void intersect_set(set *first_set, set *second_set, set *united_set) {
    int idx = 0;
    for (; idx < NUMBER_RANGE; idx++) {
        if ((get_bit_from_index(first_set, idx) && get_bit_from_index(second_set, idx))) {
            set_bit_map(united_set, idx);
        }
    }
}

void symdiff_set(set *first_set, set *second_set, set *united_set) {
    set *united = create_set();
    set *intersected = create_set();
    union_set(first_set, second_set, united);
    intersect_set(first_set, second_set, intersected);
    sub_set(united, intersected, united_set); /* Using the union method and the intersection method to find which element
 *  in each set but not in both.*/
}

void sub_set(set *first_set, set *second_set, set *united_set) {
    int idx = 0;
    for (; idx < NUMBER_RANGE; idx++) {
        if ((get_bit_from_index(first_set, idx) && !get_bit_from_index(second_set, idx))) {
            set_bit_map(united_set, idx);
        }
    }
}

void print_set(set *s) {
    int idx = 0, is_empty = 1, number_counter = 0;
    for (; idx < NUMBER_RANGE; idx++) {
        if (get_bit_from_index(s, idx)) {
            is_empty = 0;
            ++number_counter;
            printf(" %d ", idx);
        }
    }
    if (is_empty) {
        printf("Set is empty");
    }
    printf("\n");
}


