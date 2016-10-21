#include "dc.h"
#include "../pila/pila.h"
#include <stdlib.h>
#include <ctype.h>

bool dc(char *input, double *result) {
	char *i;
	pila_t *pila = pila_crear();
	double *x, *y, *r = NULL, *a;
	i = input;
	while (*i != '\0') {
		if (*i == ' ') {
			i++;
			continue;
		}
		a = malloc(sizeof(double));
		*a = atof(i);
		if (*a != 0) {
			if (isdigit(*(i + 1)) || *(i + 1) == '.') {
				i++;
				continue;
			}
			pila_apilar(pila, a);
		} else {
			free(a);
			y = pila_desapilar(pila);
			x = pila_desapilar(pila);
			if (x == NULL || y == NULL) {
				if (x) free(x);
				if (y) free(y);
				// if (r) free(r);
				pila_destruir(pila);
				return false;
			}
			r = malloc(sizeof(double));
			switch (*i) {
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
					pila_destruir(pila);
					return false;
			}
			if (pila_ver_tope(pila) == NULL && *(i + 1) == '\0') {
				*result = *r;
				free(x);
				free(y);
				pila_destruir(pila);
				return true;
			}
			pila_apilar(pila, &r);
		}
		i++;
	}
	free(x);
	free(y);
	pila_destruir(pila);
	free(r);
	return false;
}
