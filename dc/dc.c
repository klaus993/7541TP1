#include "dc.h"
#include "../pila/pila.h"
#include "../strutil/strutil.h"
#include <stdlib.h>
#include <ctype.h>

bool dc(const char *raw_input, double *result) {
	char **input = split(raw_input, ' ');
	pila_t *pila = pila_crear();
	double *x = NULL, *y = NULL, *r, *a;
	int i = 0;
	while (input[i] != NULL) {
		if (*input[i] == ' ') {
			i++;
			continue;
		}
		if (atof(input[i]) != 0) {
			a = malloc(sizeof(double));
			*a = atof(input[i]);
			pila_apilar(pila, a);
		} else {
			y = pila_desapilar(pila);
			x = pila_desapilar(pila);
			if (x == NULL || y == NULL) {
				if (x) free(x);
				if (y) free(y);
				free_strv(input);
				pila_destruir(pila);
				return false;
			}
			r = malloc(sizeof(double));
			switch (*input[i]) {
				case '+':
					*r = *x + *y;
					break;
				case '-':
					*r = *x - *y;
					break;
				case '*':
					*r = *x * *y;
					break;
				case '/':
					*r = *x / *y;
					break;
				default:
					free(x);
					free(y);
					free(r);
					free_strv(input);
					pila_destruir(pila);
					return false;
			}
			if (pila_ver_tope(pila) == NULL && input[i + 1] == NULL) {
				*result = *r;
				free(r);
				if (x) free(x);
				if (y) free(y);
				//free(a);
				free_strv(input);
				pila_destruir(pila);
				return true;
			}
			pila_apilar(pila, r);
		}
		i++;
	}
	if (x) free(x);
	if (y) free(y);
	free_strv(NULL);
	pila_destruir(pila);
	//free(r);
	return false;
}

void free_data(double *x, double *y, double *r);