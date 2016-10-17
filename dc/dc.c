#include "dc.h"
#include "../pila/pila.h"
#include <stdlib.h>

bool dc(char *input, double *result) {
	char *i;
	pila_t *pila = pila_crear();
	double x, y, r, a;
	i = input;
	while (*i != '\0') {
		a = atof(*i);
		if (a != 0) {
			pila_apilar(pila, &a);
		} else if (*i != ' ') {
			if (pila_cantidad(pila) < 2) {
				return false;
			}
			y = *(double*)pila_desapilar(pila);
			x = *(double*)pila_desapilar(pila);
			switch (*i) {
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
					return false;
			}
			pila_apilar(pila, &r);
			if (pila_cantidad(pila) == 1) {
				*result = r;
				return true;
			}
		}
		i++;
	}
}