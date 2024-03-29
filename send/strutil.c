#define _POSIX_C_SOURCE 200809L
#include "strutil.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

char** split(const char* str, char sep) {
	if (sep == '\0') {
		return NULL;
	}
	char **result;
	size_t count = 0;
	int i;
	const char *tmp = str;
	while (*tmp) {
		if (*tmp == sep) {
			count++;
		}
		tmp++;
	}
	count++;
	result = malloc(sizeof(char*) * (count + 1)); // El +1 es para el NULL del final
	tmp = str;
	size_t last = 0;
	i = 0;
	while (true) {
		if (*tmp == sep || *tmp == '\0') {
			result[i] = strndup(tmp - last, last);
			i++;
			last = 0;
		} else {
			last++;
		}
		if (*tmp == '\0') {
			break;
		}
		tmp++;
	}
	result[i] = NULL;
	return result;
}

char* join(char** strv, char sep) {
	size_t strings = 0, chars = 0;
	char *result;
	int i, j = 0;
	while (strv[strings] != NULL) {
		while (strv[strings][j] != '\0') {
			chars++;	//para contar cantidad de caracteres y luego poder reservar la memoria que haga falta
			j++;		// para recorrer las cadenas dentro de arreglo de punteros
		}
		strings++;	//para calcular la cantidad de cadenas que hay, y por lo tanto calcular la cantidad de separadores a insertar
		j = 0;
	}
	if (strings == 0) {
		result = malloc(sizeof(char));
		result[0] = '\0';
		return result;
	}
	result = malloc(sizeof(char) * chars + strings); //le sumo 'strings' para hacer espacio para los separadores y el \0
	if (!result) {
		return NULL;
	}
	int k = 0;
	for (i = 0; strv[i] != NULL; i++) {
		if (i != 0) {
			result[k] = sep;
			k++;
		}
		for (j = 0; strv[i][j] != '\0'; j++) {
			result[k] = strv[i][j];
			k++;
		}
	}
	result[k] = '\0';
	return result;
}

void free_strv(char* strv[]) {
	for (int i = 0; strv[i] != NULL; i++) {
		free(strv[i]);
	}
	free(strv);
}
