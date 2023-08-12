# Compilation macros
 CC = gcc
 CFLAGS = -ansi -Wall -pedantic -g # Flags
 GLOBAL_DEPS = language_definition.h # Dependencies for everything
 EXE_DEPS = assembler_main.o  utils.o symbols_table.o mcro_table.o preprocessor.o first_pass.o second_pass.o code.o directives.o files_creation.o lexer.o # Deps for exe

 ## Executable
assembler: $(EXE_DEPS) $(GLOBAL_DEPS)
	$(CC) -g $(EXE_DEPS) $(CFLAGS) -o $@ 

assembler_main.o:  assembler_main.c $(GLOBAL_DEPS)
	$(CC) -c assembler_main.c $(CFLAGS) -o $@

preprocessor.o: preprocessor.c preprocessor.h $(GLOBAL_DEPS)
	$(CC) -c preprocessor.c $(CFLAGS) -o $@

first_pass.o: first_pass.c first_pass.h $(GLOBAL_DEPS)
	$(CC) -c first_pass.c $(CFLAGS) -o $@

second_pass.o: second_pass.c second_pass.h $(GLOBAL_DEPS)
	$(CC) -c second_pass.c $(CFLAGS) -o $@

code.o: code.c code.h $(GLOBAL_DEPS)
	$(CC) -c code.c $(CFLAGS) -o $@

directives.o: directives.c directives.h $(GLOBAL_DEPS)
	$(CC) -c directives.c $(CFLAGS) -o $@

symbols_table.o: symbols_table.c symbols_table.h $(GLOBAL_DEPS)
	$(CC) -c symbols_table.c $(CFLAGS) -o $@

mcro_table.o: mcro_table.c mcro_table.h $(GLOBAL_DEPS)
	$(CC) -c mcro_table.c $(CFLAGS) -o $@

utils.o: utils.c utils.h $(GLOBAL_DEPS)
	$(CC) -c utils.c $(CFLAGS) -o $@

files_creation.o: files_creation.c files_creation.h $(GLOBAL_DEPS)
	$(CC) -c files_creation.c $(CFLAGS) -o $@

lexer.o: lexer.c lexer.h $(GLOBAL_DEPS)
	$(CC) -c lexer.c $(CFLAGS) -o $@

clean:
	rm -rf *.o *.am *.ob *.ent *.ext




