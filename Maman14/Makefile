assembler: assembler.c pre_assembler.o check_input_files.o
	gcc -g -ansi -pedantic -Wall assembler.c pre_assembler.c check_input_files.c -o assembler

check_input_files: check_input_files.c check_input_files.h
	gcc -c -ansi -pedantic -Wall check_input_files.c

pre_assembler: pre_assembler.c pre_assembler.h
	gcc -c -ansi -pedantic -Wall pre_assembler.c
