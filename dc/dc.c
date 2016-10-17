#include "dc.h"
#include "../pila/pila.h"
#include <stdlib.h>

bool dc(char *input, double *result) {
	char *i;
	pila_t *pila = pila_crear();
	double *x, *y, *r, *a;
	i = input;
	while (*i != '\0') {
		a = malloc(sizeof(double));
		a[0] = atof(i);
		if (*a != 0) {
			pila_apilar(pila, &a[0]);
		} else if (*i != ' ') {
			if (pila_cantidad(pila) < 2) {
				return false;
			}
			y = pila_desapilar(pila);
			x = pila_desapilar(pila);
			r = malloc(sizeof(double));
			switch (*i) {
				case '+':
					r[0] = *x + *y;
					break;
				case '-':
					r[0] = *x - *y;
					break;
				case '*':
					r[0] = *x * *y;
					break;
				case '/':
					r[0] = *x / *y;
					break;
				default:
					return false;
			}
			//free(x);
			//free(y);
			pila_apilar(pila, &r[0]);
			if (pila_cantidad(pila) == 1) {
				*result = *r;
				return true;
			}
		}
		i++;
	}
	return true;
}
