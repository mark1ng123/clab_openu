#include "set.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define NUMBER_RANGE 128
#define BITS_IN_BYTE 8
#define FLAG 1

struct set{
    char bit_map[NUMBER_RANGE];
};

void set_bit_map(set *s, int idx) {
    s->bit_map[idx / BITS_IN_BYTE] |= FLAG << idx % BITS_IN_BYTE;
}

int get_bit_from_index(set* s, int index){
    return (s->bit_map[index/BITS_IN_BYTE] & (FLAG << index % BITS_IN_BYTE));
}

set* create_set() {
    set *s = (set *) calloc(16, BITS_IN_BYTE);
    if (s == NULL){
        return NULL;
    }
    s->bit_map[0] = '\0';
    return s;
}

void read_set(set *s, int *number, int length){
    int idx = 0;
    for(; idx<length && *number!=-1; idx++){
        printf("idx: %d\n", idx);
        set_bit_map(s, *number);
        ++number;
    }
}

void print_set(set *s){
    int idx=0, is_empty=1, number_counter=0;
    for(; idx<NUMBER_RANGE; idx++) {
        if (get_bit_from_index(s, idx)) {
            is_empty = 0;
            ++number_counter;
            printf(" %d ", idx);
        }
    }
    if(is_empty){
        printf("Set is empty");
    }
    printf("\n");
}

