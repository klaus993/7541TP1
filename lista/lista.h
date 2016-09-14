#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct lista;
typedef struct lista lista_t;

struct nodo;
typedef struct nodo nodo_t;

lista_t *lista_crear(void);

bool lista_esta_vacia(const lista_t *lista);

bool lista_insertar_primero(lista_t *lista, void *dato);

bool lista_insertar_ultimo(lista_t *lista, void *dato);

void *lista_borrar_primero(lista_t *lista);

void *lista_ver_primero(const lista_t *lista);

size_t lista_largo(const lista_t *lista);

void lista_destruir(lista_t *lista, void destruir_dato(void *));

void lista_imprimir_enteros(const lista_t *lista);

#endif