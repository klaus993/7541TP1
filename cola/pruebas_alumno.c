#include "cola.h"
#include "testing.h"
#include <stdio.h>
#include "pila/pila.c"

#define MAX_ELEMENTOS 500

/* Pruebas con cola vacía */
void pruebas_cola_vacia() {
	printf("- PRUEBAS COLA VACÍA -\n");

	cola_t *cola = cola_crear();

	print_test("Verifico que la cola esté vacía", cola_esta_vacia(cola));

	print_test("Verifico que desencolar devuelva NULL", cola_desencolar(cola) == NULL);

	print_test("Verifico que ver_primero devuelva NULL", cola_ver_primero(cola) == NULL);

	cola_destruir(cola, NULL);
}

/* Pruebas encolando números enteros */
void pruebas_enteros() {
	printf("- PRUEBAS NÚMEROS ENTEROS -\n");

	cola_t *cola = cola_crear();
	int a = 1, b = 2;

	print_test("Encolo un 1", cola_encolar(cola, &a));
	print_test("Verifico que lo encolado sea un 1", *(int*)cola_ver_primero(cola) == 1);
	print_test("Verifico que la cola no esté vacía", !cola_esta_vacia(cola));

	print_test("Encolo un 2", cola_encolar(cola, &b));
	print_test("Verifico que el primer elemento sea un 1", *(int*)cola_ver_primero(cola) == 1);

	print_test("Desencolo y veo que sea un 1", *(int*)cola_desencolar(cola) == 1);

	print_test("Desencolo y veo que sea un 2", *(int*)cola_desencolar(cola) == 2);

	print_test("Verifico que la cola esté vacía", cola_esta_vacia(cola));

	int arr[MAX_ELEMENTOS];
	int i;
	for (i = 0; i < MAX_ELEMENTOS; i++) {
		arr[i] = i;
	}
	bool ok = true;
	for (i = 0; i < MAX_ELEMENTOS; i++) {
		ok &= cola_encolar(cola, &arr[i]);
	}

	printf("Encolo %d elementos", MAX_ELEMENTOS); print_test("", ok);
	print_test("Veo que el primero sea 0", *(int*)cola_ver_primero(cola) == 0);

	ok = true;
	for (i = 0; i < MAX_ELEMENTOS; i++) {
		ok &= *(int*)cola_desencolar(cola) == arr[i];
	}

	print_test("Desencolo todos los elementos... verifico que sus valores sean correctos", ok);

	cola_destruir(cola, NULL);
}

/* Función creada para poder pasársela por parámetro a cola_destruir (ya que recibe void*)
y así poder destruir la(s) pila(s) que tenga encoladas */
void destruir_pila(void *pila) {
	pila_destruir((pila_t*)pila);
}

/* Pruebas encolando pilas dinámicas */
void pruebas_pila() {
	printf("- PRUEBAS CON PILAS -\n");

	cola_t *cola = cola_crear();
	pila_t *pila = pila_crear();
	pila_t *pila_1 = pila_crear();
	int arr[] = {1, 2, 3, 4, 5, 6};
	int i;
	for (i = 0; i < 6; i++) {
		pila_apilar(pila, &arr[i]);
	}
	print_test("Encolo pila", cola_encolar(cola, pila));
	print_test("Veo si el tope = 6 de la pila encolada", *(int*)pila_ver_tope((pila_t*)cola_ver_primero(cola)) == 6);
	
	pila_t *pila_aux = (pila_t*)cola_desencolar(cola);
	print_test("Desencolo pila, veo si tope = 6", *(int*)pila_ver_tope(pila_aux));

	int arr1[MAX_ELEMENTOS];
	for (i = 0; i < MAX_ELEMENTOS; i++) {
		arr1[i] = i;
	}
	bool ok = true;
	for(i = 0; i < MAX_ELEMENTOS; i++) {
		ok &= pila_apilar(pila_1, &arr1[i]);
	}
	printf("Creo pila_1 y le apilo %d elementos", MAX_ELEMENTOS); print_test("", ok);

	print_test("Encolo pila_1", cola_encolar(cola, pila_1));
	print_test("Veo si el tope de la pila_1 encolada es correcto", *(int*)pila_ver_tope((pila_t*)cola_ver_primero(cola)) == MAX_ELEMENTOS - 1);

	print_test("Vuelvo a encolar pila", cola_encolar(cola, pila_aux));

	printf("Destruyo datos pasando función propia"); print_test("", true);

	cola_destruir(cola, destruir_pila);
}

void pruebas_cola_alumno() {
	pruebas_cola_vacia();
	pruebas_enteros();
	pruebas_pila();
}
