#define _POSIX_C_SOURCE 200809L
#include "paste.h"
#include <string.h>
#include "lib.h"

#define SEP '\t'

#include <stdio.h>
#include <unistd.h>

#define PARAM_ERROR "%s error: se deben indicar dos archivos.\n"
#define FILE_ERROR "%s error: el archivo %s no es un archivo existente.\n"
#define FOPEN_ERROR "%s error: no se pudo abrir el archivo\n"

int print_pasted_files(const char *dir1, const char *dir2) {
	FILE *file1 = fopen(dir1, "r");
	FILE *file2 = fopen(dir2, "r");
	if (!file1 || !file2) {
		return 1;
	}
	bool ok1 = true;
	bool ok2 = true;
	while (ok1 && ok2) {
		ok1 &= print_line(file1);
		putchar(SEP);
		ok2 &= print_line(file2);
		putchar('\n');
		if ((!ok1 && ok2) || (ok1 && !ok2)) {
			fclose(file1);
			fclose(file2);
			return -1;
		}
	}
	fclose(file1);
	fclose(file2);
	return 0;
}

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
