#include "nodo.h"

/***************************************************
 *               ESTRUCTURA NODO                   *
 ***************************************************/

struct nodo {
	void *dato;
	nodo_t *prox;
};

nodo_t *nodo_crear(void *dato) {
	nodo_t *nodo = malloc(sizeof(nodo_t));
	if (nodo == NULL) {
		return NULL;
	}
	nodo->dato = dato;
	nodo->prox = NULL;
	return nodo;
}
