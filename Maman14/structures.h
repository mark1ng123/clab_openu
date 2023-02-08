#ifndef STRUCTURES_H
#define STRUCTURES_H
#define WORD_SIZE 14
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

/*
 * The BinaryList structure,
 * Every time we have a valid line we want to encode her to binary machine code, the binary code represent in 14 bits,
 * decimal adress its the decimal adress of the binary line, next is the next binary line.
 */
struct BinaryList{
    char binary_code[WORD_SIZE];
    int decimal_adress;
    int line;
    struct BinaryList *next;
};
#endif
