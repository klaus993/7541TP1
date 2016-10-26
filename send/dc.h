#ifndef DC_H
#define DC_H

#include <stdbool.h>

// Recibe una cadena con operaciones matemáticas (en notación polaca inversa) a realizar, y un puntero a double para almacenar el resultado.
// Pre: deben ingresarse las operaciones a realizar con los números y operadores separados por espacios.
// Post: devuelve true si el formato de la entrada era válido y se pudo llegar a un resultado, false en caso contrario.
//       almacena el resultado en result. Si retorna false, el valor apuntado por result no es modificado.
bool dc(const char *raw_input, double *result);

#endif
