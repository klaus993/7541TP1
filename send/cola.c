#include "cola.h"
#include <stdlib.h>


typedef struct nodo {
	void *dato;
	struct nodo *prox;
} nodo_t;

nodo_t *nodo_crear() {
	return (nodo_t*)malloc(sizeof(nodo_t));
}

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

void cola_destruir(cola_t *cola, void destruir_dato(void*)) {
	void *dato;
	while (!cola_esta_vacia(cola)) {
		dato = cola_desencolar(cola);
		if (destruir_dato != NULL) {
			destruir_dato(dato);
		}
	}
	free(cola);
}

bool cola_esta_vacia(const cola_t *cola){
	return cola->prim == NULL;
}

bool cola_encolar(cola_t *cola, void* valor){
	nodo_t *nodo_nuevo = nodo_crear();
	if (nodo_nuevo == NULL) {
		return false;
	}
	nodo_nuevo->dato = valor;
	nodo_nuevo->prox = NULL;
	if (cola_esta_vacia(cola)) {
		cola->prim = nodo_nuevo;
	} else {
		cola->ult->prox = nodo_nuevo;
	}
	cola->ult = nodo_nuevo;
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
	cola->prim = cola->prim->prox;
	free(aux);
	if (cola_esta_vacia(cola)) {
		cola->ult = NULL;
	}
	return dato;
}
