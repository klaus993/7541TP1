# deps.mk: cada línea indica de qué OBJETOS se compone el programa.
lib.o: ../lib/lib.c ../lib/lib.h
paste: paste.o lib.o
more: more.o lib.o