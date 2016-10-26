#ifndef LIB_H
#define LIB_H

#include <stdbool.h>
#include <stdio.h>

/* Imprime una línea de un archivo, de a un caracter por vez, sin incluir el \n del final
Pre: el archivo existe y es de texto.
Post: devuelve true si se pudo imprimir correctamente, o false si se llegó al final del archivo o hubo un error.
*/
bool print_line(FILE *file);

#endif