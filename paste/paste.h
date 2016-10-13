#ifndef PASTE_H
#define PASTE_H

#include <stdio.h>
#include <stdbool.h>

bool print_line(FILE *file);

int print_pasted_files(const char *dir1, const char *dir2);

#endif