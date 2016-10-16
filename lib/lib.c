#include "lib.h"

bool print_line(FILE *file) {
	char c = fgetc(file);
	if (c == EOF) {
		return false;
	}
	while (c != '\n') {
		putchar(c);
		c = fgetc(file);
		if (c == EOF) {
			return false;
		}
	}
	return true;
}