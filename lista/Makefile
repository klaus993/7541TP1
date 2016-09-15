# NOMBRE DEL EJECUTABLE DEL TP
EXEC = pruebas.out
CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
BIN = $(filter-out $(EXEC).c, $(wildcard *.c))
BINFILES = $(BIN:.o)
PROG = main.c

all: $(EXEC)

testing.o: testing.c testing.h
	$(CC) $(CFLAGS) -c testing.c

lista.o: lista.c lista.h
	$(CC) $(CFLAGS) -c lista.c

pruebas_alumno.o: pruebas_alumno.c
	$(CC) $(CFLAGS) -c pruebas_alumno.c
	
$(EXEC): $(BINFILES) $(PROG)
	$(CC) $(CFLAGS) $(BINFILES) $(PROG) -o $(EXEC)

clean:
	rm -f $(wildcard *.o) $(EXEC)

# .PHONY: clean main
