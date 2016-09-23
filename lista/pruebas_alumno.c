#include "lista.h"
#include "testing.h"

void pruebas_lista_vacia() {
	lista_t *lista = lista_crear();
	printf("- PRUEBAS CON LISTA VACÍA -\n");
	print_test("Veo que la lista esté vacía", lista_esta_vacia(lista));
	print_test("Veo que borrar primero devuelva NULL", lista_borrar_primero(lista) == NULL);
	print_test("Veo que ver primero devuelva NULL", lista_ver_primero(lista) == NULL);
	print_test("Veo que el largo sea cero", lista_largo(lista) == 0);	
	lista_destruir(lista, NULL);
}

void pruebas_enteros() {
	lista_t *lista = lista_crear();
	int arr[20];
	int i;
	for (i = 0; i < 20; i++) {
		arr[i] = i + 1;
	}

	printf("- PRUEBAS CON NÚMEROS ENTEROS -\n");

	lista_imprimir_enteros(lista);

	bool ok = true;
	for (i = 0; i < 20; i++) {
		ok &= lista_insertar_ultimo(lista, &arr[i]);
	}
	print_test("20 elementos insertados al final", ok);

	print_test("Veo que el largo de la lista sea el correcto", lista_largo(lista) == 20);

	ok = true;
	for (i = 0; i < 20; i++) {
		ok &= lista_insertar_primero(lista, &arr[i]);
	}
	print_test("20 elementos insertados al principio", ok);

	print_test("Veo que el largo de la lista sea el correcto", lista_largo(lista) == 40);

	lista_imprimir_enteros(lista);

	ok = true;
	bool primero = true;
	for (i = 20; i > 0; i--) {
		primero &= *(int*)lista_ver_primero(lista) == i;
		ok &= *(int*)lista_borrar_primero(lista) == i;
	}

	print_test("Uso lista_ver_primero y veo que cada valor a borrar sea el correcto", ok);
	print_test("Borro los 20 primeros, y veo que los valores sean correctos", ok);

	print_test("Veo que el largo de la lista sea el correcto", lista_largo(lista) == 20);

	lista_imprimir_enteros(lista);

	lista_destruir(lista, NULL);
}

void pruebas_iter() {
	lista_t *lista = lista_crear();

	printf("- PRUEBAS ITERADOR -\n");

	int arr[20];
	int i;
	for (i = 0; i < 20; i++) {
		arr[i] = i + 1;
	}

	lista_imprimir_enteros(lista);

	bool ok = true;
	for (i = 0; i < 20; i++) {
		ok &= lista_insertar_ultimo(lista, &arr[i]);
	}

	lista_imprimir_enteros(lista);

	lista_iter_t *iter = lista_iter_crear(lista);

	print_test("Creo iterador", iter != NULL);

	print_test("Iterador no esta en el final", !lista_iter_al_final(iter));

	while (!lista_iter_al_final(iter)) {
		printf("%d, ", *(int*)lista_iter_ver_actual(iter));
		lista_iter_avanzar(iter);
	}
	putchar('\n');

	lista_iter_destruir(iter)
	print_test("Destruyo iterador", true);

	int a = 231;
	iter = lista_iter_crear(lista);
	print_test("Nuevo iterador creado", iter != NULL);
	i = 0;
	while (i < 2) {
		print_test("Avanzo", lista_iter_avanzar(iter));
		i++;
	}
	print_test("Estoy al final?", lista_iter_al_final(iter));
	print_test("Inserto un item", lista_iter_insertar(iter, &a));

	lista_imprimir_enteros(lista);

	lista_destruir(lista, NULL);
	
}

bool sumar_int(void *dato, void *extra) {
	*(int*)extra += *(int*)dato;
	return true;
}

void pruebas_iter_interno() {
	lista_t *lista = lista_crear();
	bool ok = true;
	int arr[20];
	int i;
	for (i = 0; i < 20; i++) {
		arr[i] = i + 1;
	}
	for (i = 0; i < 20; i++) {
		ok &= lista_insertar_ultimo(lista, &arr[i]);
	}
	print_test("Inserto 20 elementos", ok);
	lista_imprimir_enteros(lista);
	int extra = 0;
	lista_iterar(lista, sumar_int, &extra);
	printf("%d\n", extra);

	lista_destruir(lista, NULL);
}

void pruebas_lista_alumno() {
	//pruebas_lista_vacia();
	//pruebas_enteros();
	//pruebas_iter();
	pruebas_iter_interno();

}