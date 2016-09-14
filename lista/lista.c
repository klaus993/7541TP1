#include "lista.h"

struct nodo {
	void *dato;
	nodo_t *prox;
};

struct lista {
	nodo_t *prim;
	size_t cantidad;
};

lista_t *lista_crear() {
	lista_t *lista = malloc(sizeof(lista_t));
	if (lista == NULL) {
		return NULL;
	}
	lista->prim = NULL;
	lista->cantidad = 0;
	return lista;
}

bool lista_esta_vacia(const lista_t *lista) {
	return lista->prim == NULL;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
	nodo_t *nodo_nuevo = malloc(sizeof(nodo_t));
	if (nodo_nuevo == NULL) {
		return false;
	}
	nodo_nuevo->dato = dato;
	if (lista_esta_vacia(lista)) {
		nodo_nuevo->prox = NULL;
		lista->prim = nodo_nuevo;
		lista->cantidad++;
		return true;
	}
	nodo_nuevo->prox = lista->prim;
	lista->prim = nodo_nuevo;
	return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato) {
	nodo_t *nodo_nuevo = malloc(sizeof(nodo_t));
	if (nodo_nuevo == NULL) {
		return false;
	}
	nodo_nuevo->prox = NULL;
	nodo_nuevo->dato = dato;
	if (lista_esta_vacia(lista)) {
		lista->prim = nodo_nuevo;
		lista->cantidad++;
		return true;
	}
	nodo_t *actual = lista->prim;
	while (actual->prox != NULL) {
		actual = actual->prox;
	}
	actual->prox = nodo_nuevo;
	return true;
}

void *lista_borrar_primero(lista_t *lista) {
	if (lista_esta_vacia(lista)) {
		return NULL;
	}
	nodo_t *aux = lista->prim;
	void *dato = aux->dato;
	lista->prim = lista->prim->prox;
	free(aux);
	return dato;
}

void *lista_ver_primero(const lista_t *lista) {
	if (lista_esta_vacia(lista)) {
		return NULL;
	}
	return lista->prim->dato;
}

size_t lista_largo(const lista_t *lista) {
	size_t largo = 0;
	if (lista_esta_vacia(lista)) {
		return largo;
	}
	nodo_t *actual = lista->prim;
	while (actual != NULL) {
		largo++;
		actual = actual->prox;
	}
	return largo;
}

void lista_destruir(lista_t *lista, void destruir_dato(void *)) {
	nodo_t *actual = lista->prim;
	// Si se pasó una función, libero los datos
	if (destruir_dato != NULL) {
		while (actual != NULL) {
			destruir_dato(actual->dato);
			actual = actual->prox;
		}
	}
	// Libero todos los nodos
	while (lista->prim != NULL) {
		actual = lista->prim;
		lista->prim = lista->prim->prox;
		free(actual);
	}
	free(lista);
}

void lista_imprimir_enteros(const lista_t *lista) {
	if (lista_esta_vacia(lista)) {
		printf("[]\n");
		return;
	}
	nodo_t *actual = lista->prim;
	putchar('[');
	while (actual->prox != NULL) {
		printf("%d, ", *(int*)actual->dato);
		actual = actual->prox;
	}
	printf("%d", *(int*)actual->dato);
	putchar(']');
	putchar('\n');
}
