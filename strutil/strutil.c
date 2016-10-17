#include "strutil.h"
#define _POSIX_C_SOURCE 200809L
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

size_t strlen(const char *s);

char** split(const char* str, char sep) {
	if (sep == '\0') {
		return NULL;
	}
	char **result;
	size_t count = 0;
	int i;
	char *tmp = str;
	while (*tmp) {
		if (*tmp == sep) {
			count++;
		}
		tmp++;
	}
	count++;
	result = malloc(sizeof(char*) * (count + 1));  // el +1 es para el NULL del final
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
		if (*tmp == '\0') break;
		tmp++;
	}
	result[i] = NULL;
	return result;
}

size_t count_chars_strv(char** strv) {
	
}

char* join(char** strv, char sep) {
	return NULL;
}

void free_strv(char* strv[]) {
	for (int i = 0; strv[i] != NULL; i++) {
		free(strv[i]);
	}
	free(strv);
}

int main() {
	int i;
	char ** splited = split(",", ',');
	putchar('[');
	for (i = 0; splited[i] != NULL; i++) {
		printf("\"%s\", ", splited[i]);
	}
	putchar(']');
	putchar('\n');
	free_strv(splited);
	return 0;
}
