#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dc.h"

#define OP_ERROR "%s error: no se ha ingresado ninguna operación.\n"
#define INPUT_ERROR "%s error: entrada inválida.\n"

char *fgets(char *s, int size, FILE *stream);

int main(int argc, char *argv[]) {
	char *input = NULL;// = "2 5 + 2 * 2 /	";
	double result;
	ssize_t read = getline(&input, NULL, stdin);
	printf("%s\n", input);
	if (input == NULL) {
		printf(OP_ERROR, argv[0]);
		return -1;
	}
	if (input[strlen(input) - 1] == '\n') {
		input[strlen(input) - 1] = '\0';
	}
	printf("%s\n", input);
	if (dc(input, &result)) {
	//dc(input, &result);
		printf("%.2lf\n", result);
	} else {
		printf(INPUT_ERROR, argv[0]);
	}
	//free(&result);
	//char s[] = "12.123a";
	//printf("%lf\n", atof(s));
	//free(&result);
	/*while (getline(&input, NULL, stdin) != -1) {
		input[strlen(input) - 2] = '\0';
		if (dc(input, &result)) {
			printf("%lf\n", result);
		}
	}*/
	return 0;
}
