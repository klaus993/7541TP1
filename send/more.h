#ifndef MORE_H
#define MORE_H
#include <stdbool.h>
#include <stdio.h>

/* Imprime las primeras n líneas del archivo indicado por dir, y queda a la espera
   a que el usuario presione ENTER para ir imprimiendo de a una línea hasta que se termine el archivo.
Pre: el archivo indicado por dir debe ser un archivo de texto existente.
Post: devuelve 0 si todo fue bien, o 1 si no se pudo abrir el archivo.
*/
int more(const char *dir, const int n);

#endif
