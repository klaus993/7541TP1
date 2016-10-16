#include "more.h"
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define USAGE "uso: %s [ARCHIVO] [líneas a mostrar]\n"
#define FILE_ERROR "%s error: el archivo %s no es un archivo existente.\n"
#define FOPEN_ERROR "%s error: no se pudo abrir el archivo\n"
#define NUM_ERROR "%s error: el segundo parámetro debe ser un número entero positivo.\n"

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf(USAGE, argv[0]);
		return -1;
	}
	if (access(argv[1], F_OK) != 0) {
		printf(FILE_ERROR, argv[0], argv[1]);
	}
	if (!isdigit(argv[2])) {
		printf(NUM_ERROR, argv[0]);
	}
	if (atoi(argv[2]) <= 0) {
		printf(NUM_ERROR, argv[0]);
	}
	return 0;
}
