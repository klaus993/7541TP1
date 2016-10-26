#ifndef PASTE_H
#define PASTE_H

#include <stdio.h>
#include <stdbool.h>

/* Imprime dos archivos de texto dados por rutas (dir1 y dir2) uno al lado de otro, cada línea de cada archivo separada por tabs
Pre: los archivos existen y son de texto
Post: Devuelve 0 si todo fue bien, -1 si uno de los archivos tenía más ĺíneas que el otro, o 1 si alguno de los archivos no pudo abrirse.
*/
int print_pasted_files(const char *dir1, const char *dir2);

#endif