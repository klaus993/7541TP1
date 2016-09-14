#include "lista.h"
#include "testing.h"
#include <stdio.h>

void pruebas_lista_vacia() {

}

void pruebas_enteros() {
	lista_t *lista = lista_crear();
	int arr[20];
	int i;
	for (i = 0; i < 20; i++) {
		arr[i] = i + 1;
	}
	bool ok = true;
	for (i = 0; i < 20; i++) {
		ok &= lista_insertar_ultimo(lista, &arr[i]);
	}
	print_test("20 elementos insertados al final", ok);

	ok = true;
	for (i = 0; i < 20; i++) {
		ok &= lista_insertar_primero(lista, &arr[i]);
	}
	print_test("20 elementos insertados al principio", ok);

	lista_imprimir_enteros(lista);
}

void pruebas_lista_alumno() {
	pruebas_enteros();
}