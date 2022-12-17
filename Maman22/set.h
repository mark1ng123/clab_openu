
/*
 * Set.h:
 * The header will declare and define all the basic set actions,
 * And the set type itself.
 */
#ifndef SET_H
#define SET_H

/* Declaring the set type */
typedef struct set set;

/*
 * set_bit_map method:
 * The method will receive a pointer for a set and an integer, and will flag with 1 or 0 in the set storage if
 * the integer was received from the user.
*/
void set_bit_map(set *s, int idx);

/*
 * read_set method:
 * The method will receive a pointer for a specific wanted set by the user, defined by the user inputted set name,
 * a pointer for an integer array which is the user inputted numbers for the set, and a length which is the
 * amount of inputted numbers by the user.
 * The method will iterate over the integer array and will set the right index in the set storage using the set_bit_map
 * method.
 */
void read_set(set *s, int *number, int length);

/*
 * print_set method:
 * The method will receive a pointer for a wanted set by the user, defined by the user inputted set name.
 * The method will print all the integer stored in the set.
 * */
void print_set(set *s);

/*
 * get_bit_from_index method:
 * The method will receive a pointer for a wanted set by the user, defined by the user inputted set name, and an index.
 * The method will return whether the user inputted this index or not.
 */
int get_bit_from_index(set *s, int index);

/*
 * create_set method:
 * This method will allocate 16 bytes for each set created, so the set can represent 128 numbers with bits, and also
 * initialize the set storage.
 * Once everything is done it will return the pointer for the created set memory.
 */
set *create_set();

/*
 * union_set method:
 * The method will receive three pointers for wanted sets by the user, defined by the user inputted set names,
 * The method will union the first set and the second set aligning on set theorem union and will store the outcome in
 * the third set.
 */
void union_set(set *first_set, set *second_set, set *united_set);

/*
 * intersect_set method:
 * The method will receive three pointers for wanted sets by the user, defined by the user inputted set names,
 * The method will intersect the first set and the second set aligning on set theorem union and will store the outcome
 * in the third set.
 */
void intersect_set(set *first_set, set *second_set, set *united_set);

/*
 * sub_set method:
 * The method will receive three pointers for wanted sets by the user, defined by the user inputted set names,
 * The method will take every element in the first set which is NOT also in the second set, and store it the third set.
 */
void sub_set(set *first_set, set *second_set, set *united_set);

/*
 * symdiff_set method:
 * The method will receive three pointers for wanted sets by the user, defined by the user inputted set names,
 * The method will take every element in the first set and in the second set which is not in the intersection between them.
 * and store the outcome it the third set.
 */
void symdiff_set(set *first_set, set *second_set, set *united_set);

#endif
