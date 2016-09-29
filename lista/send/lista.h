#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H

#include <stdbool.h>
#include <stdlib.h>

struct lista;
typedef struct lista lista_t;

lista_t *lista_crear(void);

/* Pre: la lista fue creada.
Post: devuelve true si la lista está vacía, false en caso contrario. */
bool lista_esta_vacia(const lista_t *lista);

/* Inserta el dato como primer elemento de la lista.
Pre: la lista fue creada.
Post: el nuevo elemento es el primero de la lista. */
bool lista_insertar_primero(lista_t *lista, void *dato);

/* Inserta el dato como último elemento de la lista.
Pre: la lista fue creada.
Post: el nuevo elemento es el último de la lista. */
bool lista_insertar_ultimo(lista_t *lista, void *dato);

/* Borra el primer elemento de la lista.
Pre: la lista fue creada.
Post: el que antes era el segundo elemento es ahora el primero.
*/
void *lista_borrar_primero(lista_t *lista);

/* Pre: la lista fue creada.
Post: devuelve el dato del primer elemento de la lista.
*/
void *lista_ver_primero(const lista_t *lista);

/* Pre: la lista fue creada.
Post: devuelve el largo de la lista.
*/
size_t lista_largo(const lista_t *lista);

/* Libera la lista de la memoria, y si es necesario, libera los elementos dinámicos que haya guardados.
Pre: la lista fue creada. Si se guardaron elementos en memoria dinámica, se le debe pasar por parámetro
una función acorde para liberar cada uno de estos elementos. En caso de no haber elementos dinámicos, se pasa NULL.
Post: la lista fue destruida, completamente liberada de la memoria.
*/
void lista_destruir(lista_t *lista, void destruir_dato(void *));

/******************************************************************/

struct lista_iter;

typedef struct lista_iter lista_iter_t;

/* Crea un iterador de lista enlazada sobre la lista pasada por parámetro.
Pre: la lista fue creada.
Post: devuelve un puntero al iterador creado, o a NULL si no se pudo crear. */
lista_iter_t *lista_iter_crear(lista_t *lista);

/* Avanza al elemento siguiente en la lista.
Pre: el iterador fue creado.
Post: el nuevo actual es el siguiente elemento en la lista. */
bool lista_iter_avanzar(lista_iter_t *iter);

/* Pre: el iterador fue creado.
Post: devuelve un puntero genérico al elemento actual. */
void *lista_iter_ver_actual(const lista_iter_t *iter);

/* Pre: el iterador fue creado.
Post: devuelve true si el iterador se encuentra al final, sino false */
bool lista_iter_al_final(const lista_iter_t *iter);

/* Pre: el iterador fue creado.
Post: se liberó de la memoria al iterador. */
void lista_iter_destruir(lista_iter_t *iter);

/* Inserta un elemento en la lista.
Pre: el iterador fue creado.
Post: se insertó un elemento antes del actual, y el nuevo actual 
es el elemento insertado. */
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

/* Borra un elemento de la lista.
Pre: el iterador fue creado.
Post: se borró el elemento actual, y el nuevo actual
es el elemento siguiente. */
void *lista_iter_borrar(lista_iter_t *iter);

/* Itera por cada elemento de la lista, aplicándole la función visitar
 (definida por el usuario) a cada uno.
 La función visitar debe devolver un valor booleano
 y recibe por parámetro dos punteros genéricos dato y extra. "dato" es un puntero el dato a evaluar en
 cada iteración. "extra" es un puntero que le debe pasar el usuario a la función para almacenar
 los datos que requiera necesarios.
Itera hasta que la función visitar devuelva false.
Pre: la lista fue creada.
Post: no devuelve nada. */
void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra);

#endif
