#include "strutil.h"
#define _POSIX_C_SOURCE 200809L
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char** split(const char* str, char sep) {
	if (sep == '\0') {
		return NULL;
	}
	size_t count = 0;
	char *tmp = str;
	while (*tmp) {
		if (*tmp == sep) {
			count++;
		}
		tmp++;
	}
	printf("count = %d\n", count);

	char **result = malloc(sizeof(char*) * count);


	return result;
}

char* join(char** strv, char sep) {
	return NULL;
}

void free_strv(char* strv[]) {
	return;
}

int main() {
	char **strv = malloc(sizeof(char*) * 4);
	strv[0] = strdup("abc");
	strv[1] = strdup("def");
	strv[2] = strdup("ghi");
	strv[3] = NULL;
	int i;
	split("asd,asd,asd", ',');
	for (i = 0; i < 3; i++) {
		printf("%s\n", strv[i]);
	}
	for (i = 0; i < 3; i++) {
		free(strv[i]);
	}
	free(strv);
	return 0;
}