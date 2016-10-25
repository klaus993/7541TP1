#include "pila.h"
#include <stdlib.h>

#define TAM_INICIAL 10
/* Modificador utilizado en caso de necesitar redimensionar la pila, se multiplica
o se divide por este número, dependiendo si se quiere agrandar o achicar. */
#define MOD_REDIMENSION 2
/* Modificador utilizado para decidir cuándo disminuir la capacidad de la pila. */
#define MOD_DISMINUCION 4

/**	*************************
	Nombre: Klaus Lungwitz
	Padrón: 96416
	Ayudante: Martín Buchwald
  *	************************* */

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    double *datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/


bool pila_redimensionar(pila_t *pila, size_t tamanio);

pila_t* pila_crear(void) {
	pila_t *pila = malloc(sizeof(pila_t));
	if (pila == NULL) {
		return NULL;
	}
	pila->datos = malloc(TAM_INICIAL * sizeof(double));
	if (pila->datos == NULL) {
		free(pila);
		return NULL;
	}
	pila->capacidad = TAM_INICIAL;
	pila->cantidad = 0;
	return pila;
}

void pila_destruir(pila_t *pila) {
	free(pila->datos);
	free(pila);
}

bool pila_esta_vacia(const pila_t *pila) {
	return pila->cantidad == 0;
}

bool pila_apilar(pila_t *pila, double valor) {
	if (pila->cantidad >= pila->capacidad) {
		if (!pila_redimensionar(pila, pila->capacidad * (MOD_REDIMENSION))) {
			return false;
		}
	}
	pila->datos[pila->cantidad++] = valor;
	return true;
}

double pila_ver_tope(const pila_t *pila) {
	if (pila_esta_vacia(pila)) {
		return 0;
	}
	return pila->datos[pila->cantidad - 1];
}

double pila_desapilar(pila_t *pila) {
	if (pila_esta_vacia(pila)) {
		return 0;
	}
	if (pila->cantidad <= pila->capacidad / MOD_DISMINUCION) {
		pila_redimensionar(pila, pila->capacidad / (MOD_REDIMENSION));
	}
	return pila->datos[--pila->cantidad];
}

/* Primitiva privada, cambia el tamaño de la pila */
bool pila_redimensionar(pila_t *pila, size_t tamanio) {
	double *aux = realloc(pila->datos, sizeof(double) * tamanio);
	if (aux == NULL) {
		return false;
	}
	pila->datos = aux;
	pila->capacidad = tamanio;
	return true;
}
