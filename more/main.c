#include "more.h"
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>

#define USAGE "uso: %s [ARCHIVO] [líneas a mostrar]\n"
#define FILE_ERROR "%s error: el archivo %s no es un archivo existente.\n"
#define FOPEN_ERROR "%s error: no se pudo abrir el archivo\n"
#define NUM_ERROR "%s error: el segundo parámetro debe ser un número entero positivo.\n"

int main(int argc, char *argv[]) {
	int n = atoi(argv[2]);
	int exit_status;
	if (argc != 3) {
		printf(USAGE, argv[0]);
		return -1;
	}
	if (access(argv[1], F_OK) != 0) {
		printf(FILE_ERROR, argv[0], argv[1]);
		return -1;
	}
	if (n <= 0) {
		printf(NUM_ERROR, argv[0]);
		return -1;
	}
	exit_status = more(argv[1], n);
	if (exit_status == 1) {
		printf(FOPEN_ERROR, argv[0]);
	}
	return 0;
}
