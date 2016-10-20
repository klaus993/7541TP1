#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dc.h"

#define INPUT_ERROR "%s error: no se ha ingresado ninguna operación.\n"

char *fgets(char *s, int size, FILE *stream);

int main(int argc, char *argv[]) {
	char input[] = "5 2 / 2 *";
	double result;
	//fgets(input, 30, stdin);
	//getline(&input, NULL, stdin);
	//if (getline(&input, NULL, stdin) == -1) {
	//	printf(INPUT_ERROR, argv[0]);
	//	return -1;
	//}
	//input[strlen(input) - 1] = '\0';
	printf("%s\n", input);
	if (dc(input, &result)) {
	//dc(input, &result);
		printf("%.2lf\n", result);
	}
	//free(&result);
	/*while (getline(&input, NULL, stdin) != -1) {
		input[strlen(input) - 1] = '\0';
		if (dc(input, &result)) {
			printf("%lf\n", result);
		}
	}*/
	return 0;
}
