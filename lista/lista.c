#include "lista.h"

/***************************************************
 *               ESTRUCTURA NODO                   *
 ***************************************************/

struct nodo {
	void *dato;
	nodo_t *prox;
};

nodo_t *nodo_crear() {
	return malloc(sizeof(nodo_t));
}

/***************************************************
 *           ESTRUCTURA LISTA ENLAZADA             *
 ***************************************************/


struct lista {
	nodo_t *prim;
	nodo_t *ult;
	size_t cantidad;
};

lista_t *lista_crear() {
	lista_t *lista = malloc(sizeof(lista_t));
	if (lista == NULL) {
		return NULL;
	}
	lista->prim = NULL;
	lista->ult = NULL;
	lista->cantidad = 0;
	return lista;
}

bool lista_esta_vacia(const lista_t *lista) {
	return lista->prim == NULL;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
	nodo_t *nodo_nuevo = nodo_crear();
	if (nodo_nuevo == NULL) {
		return false;
	}
	nodo_nuevo->dato = dato;
	lista->cantidad++;
	if (lista_esta_vacia(lista)) {
		nodo_nuevo->prox = NULL;
		lista->prim = nodo_nuevo;
		lista->ult = nodo_nuevo;
		return true;
	}
	nodo_nuevo->prox = lista->prim;
	lista->prim = nodo_nuevo;
	return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato) {
	nodo_t *nodo_nuevo = nodo_crear();
	if (nodo_nuevo == NULL) {
		return false;
	}
	nodo_nuevo->prox = NULL;
	nodo_nuevo->dato = dato;
	lista->cantidad++;
	if (lista_esta_vacia(lista)) {
		lista->prim = nodo_nuevo;
	} else {
		lista->ult->prox = nodo_nuevo;
	}
	lista->ult = nodo_nuevo;
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
	lista->cantidad--;
	if (lista_esta_vacia(lista)) {
		lista->ult = NULL;
	}
	return dato;
}

void *lista_ver_primero(const lista_t *lista) {
	if (lista_esta_vacia(lista)) {
		return NULL;
	}
	return lista->prim->dato;
}

size_t lista_largo(const lista_t *lista) {
	return lista->cantidad;
}

void lista_destruir(lista_t *lista, void destruir_dato(void *)) {
	void *dato;
	while (!lista_esta_vacia(lista)) {
		dato = lista_borrar_primero(lista);
		if (destruir_dato != NULL) {
			destruir_dato(dato);
		}
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
	while (actual != lista->ult) {
		printf("%d, ", *(int*)actual->dato);
		actual = actual->prox;
	}
	printf("%d", *(int*)actual->dato);
	putchar(']');
	putchar('\n');
}


/***************************************************
 *               ITERADOR DE LISTA                 *
 ***************************************************/


struct lista_iter {
	nodo_t *actual;
	nodo_t *anterior;
	lista_t *lista;
};


lista_iter_t *lista_iter_crear(lista_t *lista) {
	lista_iter_t *iter = malloc(sizeof(lista_iter_t));
	if (iter == NULL) {
		return NULL;
	}
	iter->anterior = NULL;
	iter->actual = lista->prim;
	iter->lista = lista;
	return iter;
}

/* Pre: el iterador fue creado */
bool lista_iter_avanzar(lista_iter_t *iter){
	if (lista_iter_al_final(iter)) {
		return false;
	}
	iter->anterior = iter->actual;
	iter->actual = iter->actual->prox;
	//printf("Dato: %d\n", *(int*)iter->actual->dato);
	return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
	if (lista_iter_al_final(iter)) {
		return NULL;
	}
	return iter->actual->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter) {
	return iter->actual == NULL;
}

void lista_iter_destruir(lista_iter_t *iter) {
	free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato) {
	nodo_t *nodo_nuevo = nodo_crear();
	if (nodo_nuevo == NULL) {
		return false;
	}
	nodo_nuevo->dato = dato;
	nodo_nuevo->prox = iter->actual;
	iter->anterior->prox = nodo_nuevo;
	iter->lista->cantidad++;
	return true;
}

void *lista_iter_borrar(lista_iter_t *iter) {
	if (iter->actual->prox == NULL) {
		return NULL;
	}
	iter->anterior->prox = iter->actual->prox;
	iter->actual = iter->actual->prox;
	nodo_t *aux = iter->actual;
	void *dato = aux->dato;
	free(aux);
	return dato;
}

/* ITERADOR INTERNO */

void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra) {
	nodo_t *actual = lista->prim;
	while (!lista_esta_vacia(lista) && visitar(actual->dato, extra)) {
		actual = actual->prox;
	}
}
