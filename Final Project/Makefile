assembler: assembler.c pre_assembler.o check_input_files.o first_parse.o assembler_helping_function.o error_handeling.o second_parse.o
	gcc -g -ansi -pedantic -Wall assembler.c pre_assembler.c check_input_files.c first_parse.c second_parse.c assembler_helping_function.c error_handeling.c -o assembler

check_input_files: check_input_files.c check_input_files.h
	gcc -c -ansi -pedantic -Wall check_input_files.c

pre_assembler: pre_assembler.c pre_assembler.h
	gcc -c -ansi -pedantic -Wall pre_assembler.c

first_parse: first_parse.c first_parse.h assembler_helping_function.o error_handeling.o
	gcc -c -ansi -pedantic -Wall first_parse.c assembler_helping_function.c error_handeling.c

second_parse: second_parse.c second_parse.h assembler_helping_function.o error_handeling.o
	gcc -c -ansi -pedantic -Wall second_parse.c assembler_helping_function.c error_handeling.c

assembler_helping_function: assembler_helping_function.c assembler_helping_function.h global_operations.h structures.h error_handeling.o
	gcc -c -ansi -pedantic -Wall assembler_helping_function.c error_handeling.c

error_handeling: error_handeling.c error_handeling.h structures.h
	gcc -c -ansi -pedantic -Wall error_handeling.c
