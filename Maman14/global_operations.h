#ifndef GLOBAL_OPERATIONS_H
#define GLOBAL_OPERATIONS_H

/* Globals for input checking and parsing */
char *valid_opcode[] = {"mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec","jmp", "bne", "red", "prn",
                              "jsr", "rts", "stop"};
char *data_instruction[] = {".data", ".string"};
char *entry_extern_instruction[] = {".extern", ".entry"};
char *valid_register_names[] = {"r0","r1", "r2", "r3", "r4", "r5", "r6","r7"};


/* Exporting the globals */
extern char *valid_opcode[];
extern char *data_instruction[];
extern char *entry_extern_instruction[];
extern char *valid_register_names[];

#endif