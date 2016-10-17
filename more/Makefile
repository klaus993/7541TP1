# Flags de gcc. Se usan automáticamente para compilar *.c → *.o
CFLAGS := -g -std=c99 -Wall -Wformat=2
CFLAGS += -Wshadow -Wpointer-arith -Wunreachable-code
CFLAGS += -Wconversion -Wno-sign-conversion -Wbad-function-cast

# Se pueden comentar durante el desarrollo.
#CFLAGS += -Werror

# Si se ejecuta `make` a secas, se compilarán paste, more, bc y strutil.
#
# También se puede invocar `make paste`, `make more`, `make dc` o `make strutil.o` para
# compilar una parte del TP solamente.

lib.o: ../lib/lib.c ../lib/lib.h
	cc $(CFLAGS) ../lib/lib.c -o lib.o

all: more

include deps.mk
