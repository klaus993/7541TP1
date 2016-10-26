#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dc.h"

#define OP_ERROR "%s error: no se ha ingresado ninguna operación.\n"
#define INPUT_ERROR "%s error: entrada inválida: \"%s\".\n"

int main(int argc, char *argv[]) {
	int exit_status = 0;
	char *input = NULL;
	double result;
	size_t size = 0;
	ssize_t read = getline(&input, &size, stdin);
	if (input == NULL) {
		printf(OP_ERROR, argv[0]);
		return -1;
	}
	if (input[read - 1] == '\n') {
		input[read - 1] = '\0';
	}
	if (dc(input, &result)) {
		printf("%.2lf\n", result);
	} else {
		printf(INPUT_ERROR, argv[0], input);
		exit_status = 1;
	}
	while ((read = getline(&input, &size, stdin)) != -1) {
		if (input[read - 1] == '\n') {
			input[read - 1] = '\0';
		}
		if (dc(input, &result)) {
			printf("%.2lf\n", result);
		} else {
			printf(INPUT_ERROR, argv[0], input);
			exit_status = 1;
		}
	}
	free(input);
	return exit_status;
}
