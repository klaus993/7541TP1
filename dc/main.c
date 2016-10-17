#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dc.h"

#define INPUT_ERROR "%s error: no se ha ingresado ninguna operación.\n"

int main(int argc, char* argv[]) {
	char *input = NULL;
	double result;
	ssize_t read = getline(&input, NULL, stdin);
	if (read == -1) {
		printf(INPUT_ERROR, argv[0]);
		return -1;
	}
	input[strlen(input) - 1] = '\0';
	printf("%s\n", input);
	if (dc(input, &result)) {
		printf("%lf\n", result);
	}
	/*while (getline(&input, NULL, stdin) != -1) {
		input[strlen(input) - 1] = '\0';
		if (dc(input, &result)) {
			printf("%lf\n", result);
		}
	}*/
	return 0;
}