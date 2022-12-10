#ifndef SET_H
#define SET_H

typedef struct set set;


void set_bit_map(set *s, int idx);
void read_set(set *s, int *number, int length);
void print_set(set *s);
int get_bit_from_index(set* s, int index);
set* create_set();

#endif
