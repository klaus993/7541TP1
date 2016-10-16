#include "paste.h"
#include <stdio.h>
#include <unistd.h>

#define PARAM_ERROR "%s error: se deben indicar dos archivos.\n"
#define FILE_ERROR "%s error: el archivo %s no es un archivo existente.\n"
#define FOPEN_ERROR "%s error: no se pudo abrir el archivo\n"

int main(int argc, char *argv[]) {
	int exit_status;
	if (argc != 3) {
		printf(PARAM_ERROR, argv[0]);
		return -2;
	}
	if (access(argv[1], F_OK) != 0) {
		printf(FILE_ERROR, argv[0], argv[1]);
		return -3;
	}
	if (access(argv[2], F_OK) != 0) {
		printf(FILE_ERROR, argv[0], argv[2]);
		return -3;
	}
	exit_status = print_pasted_files(argv[1], argv[2]);
	if (exit_status == 1) {
		printf(FOPEN_ERROR, argv[0]);
		return -2;
	}
	return exit_status;
}
