#ifndef STRUCTURES_H
#define STRUCTURES_H
/*
 * The Error structure,
 * Every time an error will occur, it will have a line number, a text definition of the error
 * and next pointer to another Error.
 */
struct Error{
    int line_number;
    char* error_defenition;
    struct Error *next;
};

/*
 * The Symbol structure,
 * Every time a Symbol will be saved, it will have a name saved, the address in the file
 * and next pointer to another Symbol.
 */
struct Symbol{
    char *name;
    int decimal_adress;
    struct Symbol *next;
};
#endif
