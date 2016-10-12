#include "strutil.h"
#define _POSIX_C_SOURCE 200809L
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

size_t strlen(const char *s);

char** split(const char* str, char sep) {
	if (sep == '\0') {
		return NULL;
	}
	//size_t strlen = strlen(str);
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
	printf("count = %zu\n", count);
	count++;
	result = malloc(sizeof(char*) * (count));
	for (i = 0; i < count; i++) {
		result[i] = malloc(sizeof(char) * (count / 2));
	}
	int j = 0;
	for (i = 0; i < count; i++) {
		while (str[j] != sep && str[j] != '\0') {
			// guardar caracter
			//putchar(str[j]);
			result[i][j] = str[j];
			j++;
		}
		j++;
		result[i][j] = '\0';
		//putchar('-');
	}

	return result;
}

char* join(char** strv, char sep) {
	return NULL	;
}

void free_strv(char* strv[]) {
	for (int i = 0; strv[i] != NULL; i++) {
		free(strv[i]);
	}
	free(strv);
}

int main() {
	//char **strv = malloc(sizeof(char*) * 4);
	//strv[0] = strdup("abc");
	//strv[1] = strdup("def");
	//strv[2] = strdup("ghi");
	//strv[3] = NULL;
	int i;
	char ** splited = split("asd,asd,asd", ',');
	for (i = 0; i < 3; i++) {
		printf("%s\n", splited[i]);
	}
	//for (i = 0; i < 3; i++) {
	//	free(strv[i]);
	//}
	//free(strv);
	return 0;
}