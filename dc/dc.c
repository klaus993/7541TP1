#include "dc.h"
#include "../pila/pila.h"
#include <stdlib.h>

bool dc(char *input, double *result) {
	char *i;
	pila_t *pila = pila_crear();
	double *x, *y, *r, *a;
	r = malloc(sizeof(double));
	i = input;
	while (*i != '\0') {
		if (*i != ' ') {
			a = malloc(sizeof(double));
			*a = atof(i);
			if (*a != 0) {
				pila_apilar(pila, a);
			} else {
				if (pila_cantidad(pila) < 2) {
					free(r);
					pila_destruir(pila);
					return false;
				}
				y = pila_desapilar(pila);
				x = pila_desapilar(pila);
				//r = malloc(sizeof(double));
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
						pila_destruir(pila);
						free(x);
						free(y);
						free(r);
						free(a);
						return false;
				}
				pila_apilar(pila, r);
				if (pila_cantidad(pila) == 1 && *(i + 1) == '\0') {
					*result = *r;
					pila_destruir(pila);
					return true;
				}
				free(x);
				free(y);
			}
		}
		i++;
	}
	//free(r);
	pila_destruir(pila);
	return false;
}
