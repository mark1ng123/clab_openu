assembler: assembler.c pre_assembler.o check_input_files.o first_parse.o assembler_helping_function.o
	gcc -g -ansi -pedantic -Wall assembler.c pre_assembler.c check_input_files.c first_parse.c assembler_helping_function.c -o assembler

check_input_files: check_input_files.c check_input_files.h
	gcc -c -ansi -pedantic -Wall check_input_files.c

pre_assembler: pre_assembler.c pre_assembler.h
	gcc -c -ansi -pedantic -Wall pre_assembler.c

first_parse: first_parse.c first_parse.h assembler_helping_function.o 
	gcc -c -ansi -pedantic -Wall first_parse.c assembler_helping_function.c 

assembler_helping_function: assembler_helping_function.c assembler_helping_function.h
	gcc -c -ansi -pedantic -Wall assembler_helping_function.c 
