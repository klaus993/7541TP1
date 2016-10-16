#include "more.h"
#include "../lib/lib.h"

int more(const char *dir, const int n) {
	FILE *file = fopen(dir, "r");
	if (!file) {
		return 1;
	}
	bool ok = true;
	for (int i = 0; i < n; i++) {
		ok &= print_line(file);
		putchar('\n');
		if (!ok) {
			break;
		}
	}
	while(print_line(file)) {
		getc(stdin);
	}
	putchar('\n');
	fclose(file);
	return 0;
}
