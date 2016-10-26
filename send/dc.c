#include "dc.h"
#include "pila.h"
#include "strutil.h"
#include <stdlib.h>
#include <ctype.h>

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>

#define OP_ERROR "%s error: no se ha ingresado ninguna operación.\n"
#define INPUT_ERROR "%s error: entrada inválida: \"%s\".\n"

bool dc(const char *raw_input, double *result) {
	char **input = split(raw_input, ' ');
	pila_t *pila = pila_crear();
	double x = 0, y = 0, r;
	int i = 0;
	while (input[i] != NULL) {
		if (atof(input[i]) != 0) {
			pila_apilar(pila, atof(input[i]));
		} else {
			if (pila_esta_vacia(pila)) {
				free_strv(input);
				pila_destruir(pila);
				return false;
			}
			y = pila_desapilar(pila);
			if (pila_esta_vacia(pila)) {
				free_strv(input);
				pila_destruir(pila);
				return false;
			}
			x = pila_desapilar(pila);
			switch (*input[i]) {
				case '+':
					r = x + y;
					break;
				case '-':
					r = x - y;
					break;
				case '*':
					r = x * y;
					break;
				case '/':
					r = x / y;
					break;
				default:
					free_strv(input);
					pila_destruir(pila);
					return false;
			}
			if (pila_esta_vacia(pila) && input[i + 1] == NULL) {
				*result = r;
				free_strv(input);
				pila_destruir(pila);
				return true;
			}
			pila_apilar(pila, r);
		}
		i++;
	}
	free_strv(input);
	pila_destruir(pila);
	return false;
}

size_t getline(char** buffer, size_t* capacidad, FILE* archivo);

int main(int argc, char *argv[]) {
	int exit_status = 0;
	char *input = NULL;
	double result;
	size_t size = 0;
	size_t read = getline(&input, &size, stdin);
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
