#include "dc.h"
#include "../pila/pila.h"
#include "../strutil/strutil.h"
#include <stdlib.h>
#include <ctype.h>

bool dc(const char *raw_input, double *result) {
	char **input = split(raw_input, ' ');
	pila_t *pila = pila_crear();
	double x = 0, y = 0, r;//, a;
	int i = 0;
	while (input[i] != NULL) {
		if (*input[i] == ' ') {
			i++;
			continue;
		}
		if (atof(input[i]) != 0) {
			pila_apilar(pila, atof(input[i]));
		} else {
			y = pila_desapilar(pila);
			x = pila_desapilar(pila);
			if (x == 0|| y == 0) {
				free_strv(input);
				pila_destruir(pila);
				return false;
			}
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
			if (pila_ver_tope(pila) == 0 && input[i + 1] == NULL) {
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
