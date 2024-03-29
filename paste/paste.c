#define _POSIX_C_SOURCE 200809L
#include "paste.h"
#include <string.h>
#include "../lib/lib.h"

#define SEP '\t'

int print_pasted_files(const char *dir1, const char *dir2) {
	FILE *file1 = fopen(dir1, "r");
	FILE *file2 = fopen(dir2, "r");
	if (!file1 || !file2) {
		return 1;
	}
	bool ok1 = true;
	bool ok2 = true;
	while (ok1 && ok2) {
		ok1 &= print_line(file1);
		putchar(SEP);
		ok2 &= print_line(file2);
		putchar('\n');
		if ((!ok1 && ok2) || (ok1 && !ok2)) {
			fclose(file1);
			fclose(file2);
			return -1;
		}
	}
	fclose(file1);
	fclose(file2);
	return 0;
}