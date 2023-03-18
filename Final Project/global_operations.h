#ifndef GLOBAL_OPERATIONS_H
#define GLOBAL_OPERATIONS_H

/* Globals for input checking,parsing and binary encoding */
char *valid_opcode[] = {"mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec","jmp", "bne", "red", "prn",
                              "jsr", "rts", "stop"};
char *data_instruction[] = {".data", ".string"};
char *entry_extern_instruction[] = {".extern", ".entry"};
char *valid_register_names[] = {"r0","r1", "r2", "r3", "r4", "r5", "r6","r7"};

char *binary_op_code_array[] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110","0111", "1000", "1001", "1010",
                                "1011", "1100", "1101", "1110", "1111"};

char *binary_register_code_array[] = {"000000", "000001", "000010", "000011", "000100", "000101", "000110","000111"};


/* Exporting the globals */
extern char *valid_opcode[];
extern char *data_instruction[];
extern char *entry_extern_instruction[];
extern char *valid_register_names[];
extern char *binary_op_code_array[];
extern char *binary_register_code_array[];

#endif