#include "cola.h"
#include <stdlib.h>

typedef struct nodo {
	void *dato;
	struct nodo *prox;
} nodo_t;

struct cola {
	nodo_t *prim;
	nodo_t *ult;
};

cola_t* cola_crear(void) {
	cola_t *cola = malloc(sizeof(cola_t));
	if (cola == NULL) {
		return NULL;
	}
	cola->prim = NULL;
	cola->ult = NULL;
	return cola;
}

void cola_destruir(cola_t *cola, void destruir_dato(void*)){
	nodo_t *actual = cola->prim;
	// Si se pasó una función, libero los datos
	if (destruir_dato != NULL) {
		while (actual != NULL) {
			destruir_dato(actual->dato);
			actual = actual->prox;
		}
	}
	// Libero todos los nodos
	while (cola->prim != NULL) {
		actual = cola->prim;
		cola->prim = cola->prim->prox;
		free(actual);
	}
	free(cola);
}

bool cola_esta_vacia(const cola_t *cola){
	return cola->prim == NULL;
}

bool cola_encolar(cola_t *cola, void* valor){
	nodo_t *nodo_nuevo = malloc(sizeof(nodo_t));
	if (nodo_nuevo == NULL) {
		return false;
	}
	nodo_nuevo->dato = valor;
	nodo_nuevo->prox = NULL;	
	if (cola_esta_vacia(cola)) {
		cola->prim = nodo_nuevo;
		cola->ult = nodo_nuevo;
		return true;
	}
	cola->ult->prox = nodo_nuevo;
	cola->ult = cola->ult->prox;
	return true;
}

void* cola_ver_primero(const cola_t *cola){
	if (cola_esta_vacia(cola)) {
		return NULL;
	}
	return cola->prim->dato;
}

void* cola_desencolar(cola_t *cola){
	if (cola_esta_vacia(cola)) {
		return NULL;
	}
	nodo_t *aux = cola->prim;
	void *dato = aux->dato;
	cola->prim = cola->prim->	prox;
	free(aux);
	return dato;
}
