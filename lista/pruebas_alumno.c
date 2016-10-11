#include "lista.h"
#include "testing.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTOS 500

void pruebas_lista_vacia() {
	lista_t *lista = lista_crear();
	printf("- PRUEBAS CON LISTA VACÍA -\n");
	print_test("Veo que la lista esté vacía", lista_esta_vacia(lista));
	print_test("Veo que borrar primero devuelva NULL", lista_borrar_primero(lista) == NULL);
	print_test("Veo que ver primero devuelva NULL", lista_ver_primero(lista) == NULL);
	print_test("Veo que ver ultimo devuelva NULL", lista_ver_ultimo(lista) == NULL);
	print_test("Veo que el largo sea cero", lista_largo(lista) == 0);	
	lista_destruir(lista, NULL);
}

void pruebas_enteros() {
	printf("- PRUEBAS CON NÚMEROS ENTEROS -\n");

	lista_t *lista = lista_crear();
	int arr[MAX_ELEMENTOS];
	int i;
	bool ok, primero;
	for (i = 0; i < MAX_ELEMENTOS; i++) {  // Lleno el array con números del 1 al MAX_ELEMENTOS
		arr[i] = i + 1;
	}

	ok = true;
	primero = true;
	for (i = 0; i < MAX_ELEMENTOS; i++) {
		ok &= lista_insertar_primero(lista, &arr[0]);
		primero &= *(int*)lista_borrar_primero(lista) == 1;
	}
	print_test("Se puede agregar y borrar elementos muchas veces (insertar_primero)", ok);
	print_test("El valor borrado fue siempre el correcto", primero);

	ok = true;
	primero = true;
	for (i = 0; i < MAX_ELEMENTOS; i++) {
		ok &= lista_insertar_ultimo(lista, &arr[0]);
		primero &= *(int*)lista_borrar_primero(lista) == 1;
	}
	print_test("Se puede agregar y borrar elementos muchas veces (insertar_ultimo)", ok);
	print_test("El valor borrado fue siempre el correcto", primero);

	print_test("La lista está vacía", lista_esta_vacia(lista));

	ok = true;
	for (i = 0; i < MAX_ELEMENTOS; i++) {
		ok &= lista_insertar_ultimo(lista, &arr[i]);
	}
	printf("%d elementos insertados al final", MAX_ELEMENTOS); print_test("", ok);

	print_test("Veo que el largo de la lista sea el correcto", lista_largo(lista) == MAX_ELEMENTOS);

	print_test("Puebo lista_ver_ultimo es correcto", *(int*)lista_ver_ultimo(lista) == MAX_ELEMENTOS);

	ok = true;
	for (i = 0; i < MAX_ELEMENTOS; i++) {
		ok &= lista_insertar_primero(lista, &arr[i]);
		primero &= *(int*)lista_ver_primero(lista) == arr[i];
	}
	printf("%d elementos insertados al principio", MAX_ELEMENTOS); print_test("", ok);
	print_test("Uso lista_ver_primero y veo que cada valor insertado sea el correcto", primero);

	print_test("Veo que el largo de la lista sea el correcto", lista_largo(lista) == MAX_ELEMENTOS * 2);

	ok = true;
	primero = true;
	for (i = MAX_ELEMENTOS; i > 0; i--) {
		primero &= *(int*)lista_ver_primero(lista) == i;
		ok &= *(int*)lista_borrar_primero(lista) == i;
	}

	print_test("Uso lista_ver_primero y veo que cada valor a borrar sea el correcto", ok);
	printf("Borro los %d primeros, y veo que los valores sean correctos", MAX_ELEMENTOS); print_test("", ok);

	print_test("Veo que el largo de la lista sea el correcto", lista_largo(lista) == MAX_ELEMENTOS);

	lista_destruir(lista, NULL);
}

void pruebas_iter() {
	printf("- PRUEBAS ITERADOR EXTERNO -\n");

	int arr[MAX_ELEMENTOS];
	int i;
	for (i = 0; i < MAX_ELEMENTOS; i++) {
		arr[i] = i;
	}

	lista_t *lista = lista_crear(); print_test("Creo lista", lista != NULL);

	bool ok = true;
	for (i = 0; i < MAX_ELEMENTOS; i++) {
		ok &= lista_insertar_ultimo(lista, &arr[i]);
	}

	printf("Inserto %d elementos con primitiva de lista", MAX_ELEMENTOS); print_test("", ok);

	lista_iter_t *iter = lista_iter_crear(lista); print_test("Creo iterador", iter != NULL);

	print_test("El iterador no esta en el final", !lista_iter_al_final(iter));

	lista_iter_destruir(iter); print_test("Destruyo iterador", true);

	int a = 231;
	iter = lista_iter_crear(lista); print_test("Nuevo iterador creado", iter != NULL);
	ok = true;
	bool ok1 = true;
	for (i = 0; i < MAX_ELEMENTOS; i++) {
		ok &= *(int*)lista_iter_ver_actual(iter) == i;
		ok1 &= lista_iter_avanzar(iter);
	}

	printf("Pude avanzar %d veces", MAX_ELEMENTOS); print_test("", ok1);
	print_test("Cada vez que avancé, el valor del actual fue el correcto", ok);
	print_test("Estoy al final", lista_iter_al_final(iter));
	print_test("Inserto un elemento", lista_iter_insertar(iter, &a));
	print_test("Veo que el elemento insertado sea el actual", *(int*)lista_iter_ver_actual(iter) == 231 && lista_iter_ver_actual(iter) == &a);
	
	print_test("No estoy al final", !lista_iter_al_final(iter));
	printf("Veo que el largo de la lista sea %d", MAX_ELEMENTOS + 1); print_test("", lista_largo(lista) == MAX_ELEMENTOS + 1);

	print_test("Borro ultimo elemento", *(int*)lista_iter_borrar(iter) == 231);

	printf("Veo que el largo de la lista sea %d", MAX_ELEMENTOS); print_test("", lista_largo(lista) == MAX_ELEMENTOS);

	lista_iter_destruir(iter); print_test("Destruyo iterador", true);

	iter = lista_iter_crear(lista); print_test("Nuevo iterador creado", iter != NULL);

	ok = true;
	for (i = 0; i < MAX_ELEMENTOS / 2; i++) {
		ok &= lista_iter_avanzar(iter);
	}

	print_test("Avanzo hasta la mitad de la lista", ok);
	print_test("Veo que el valor actual sea el correcto", *(int*)lista_iter_ver_actual(iter) == MAX_ELEMENTOS / 2);

	int b = 0;
	print_test("Inserto un elemento", lista_iter_insertar(iter, &b));
	print_test("Veo que el elemento insertado sea el actual", *(int*)lista_iter_ver_actual(iter) == 0 && lista_iter_ver_actual(iter) == &b);

	print_test("Borro un elemento, veo que el valor sea correcto", *(int*)lista_iter_borrar(iter) == 0);

	print_test("Veo que el valor actual sea el correcto", *(int*)lista_iter_ver_actual(iter) == MAX_ELEMENTOS / 2);

	lista_iter_destruir(iter); print_test("Destruyo iterador", true);

	iter = lista_iter_crear(lista); print_test("Nuevo iterador creado", iter != NULL);

	print_test("Borro el primero, veo que sea 0", *(int*)lista_iter_borrar(iter) == 0);

	print_test("Verifico que el actual sea 1", *(int*)lista_iter_ver_actual(iter) == 1);

	print_test("Inserto un elemento", lista_iter_insertar(iter, &b));
	print_test("Veo que el elemento insertado sea el actual", *(int*)lista_iter_ver_actual(iter) == 0 && lista_iter_ver_actual(iter) == &b);

	lista_iter_destruir(iter); print_test("Destruyo iterador", true);

	int arr1[MAX_ELEMENTOS];
	for (i = 0; i < MAX_ELEMENTOS; i++) {  // Array del 1 al MAX_ELEMENTOS
		arr1[i] = i + 1;
	}

	lista_t *lista1 = lista_crear(); print_test("Creo lista1", lista1 != NULL);

	ok = true;
	ok1 = true;
	for (i = 0; i < MAX_ELEMENTOS; i++) {
		ok &= lista_insertar_ultimo(lista1, &arr1[i]);
	}

	printf("Inserto %d elementos con primitiva de lista", MAX_ELEMENTOS); print_test("", ok);

    iter = lista_iter_crear(lista1); print_test("Creo nuevo iterador sobre lista1", iter != NULL);
    print_test("Ver actual con el iterador", lista_iter_ver_actual(iter) == &arr1[0]);
    ok = true;
    while (!lista_iter_al_final(iter)) {
        ok &= lista_iter_avanzar(iter);
    }
    int x = 132, y = 133;
    print_test("Avanzo hasta el final", ok);
    print_test("Está al final", lista_iter_al_final(iter));
    size_t largo = lista_largo(lista1);
    print_test("Inserto un elemento al final", lista_iter_insertar(iter, &x));
    print_test("No está al final", !lista_iter_al_final(iter));
    print_test("Veo que el actual sea el correcto", *(int*)lista_iter_ver_actual(iter) == 132);
    print_test("Se actualizó el largo", largo + 1 == lista_largo(lista1));
    largo = lista_largo(lista1);
    print_test("Avanzo", lista_iter_avanzar(iter));
    print_test("Inserta uno más luego del insertado", lista_iter_insertar(iter, &y));
    print_test("Se actualizó el largo", largo + 1 == lista_largo(lista1));
    lista_iter_t *jter = lista_iter_crear(lista1); print_test("Creacion de un nuevo iterador", jter != NULL);

    ok = true;
    i = 0;
    while (i < MAX_ELEMENTOS - 1) {
        ok &= lista_iter_avanzar(jter);
        i++;
    }

    print_test("Avanzo hasta el ultimo elemento", ok);

    print_test("No estoy al final", !lista_iter_al_final(jter));

    print_test("Ver actual", *(int*)lista_iter_ver_actual(jter) == MAX_ELEMENTOS); printf("Ver actual = %d\n", *(int*)lista_iter_ver_actual(jter));
    
    lista_iter_destruir(jter); print_test("Destruyo jter", true);

    lista_iter_destruir(iter); print_test("Destruyo iter", true);
    lista_destruir(lista1, NULL); print_test("Destruyo lista1", true);
	lista_destruir(lista, NULL); print_test("Destruyo lista", true);
	
}

bool sumar_int(void *dato, void *extra) {
	*(int*)extra += *(int*)dato;
	return true;
}

bool contar_elementos(void *dato, void *extra) {
	*(int*)extra += 1;
	return true;
}

bool contar_numeros_pares(void *dato, void *extra) {
	if (*(int*)dato % 2 == 0) {
		*(int*)extra += 1;	
	}
	return true;
}

bool numeros_pares_a_lista(void *dato, void *extra) {
	if (*(int*)dato % 2 == 0) {
		lista_insertar_ultimo((lista_t*)extra, dato);
	}
	return true;
}

bool _existe_numero(void *dato, void *extra, int num) {
	if (*(int*)dato == num) {
		*(bool*)extra = true;
		return false;
	}
	*(bool*)extra = false;
	return true;
}

bool existe_fuera(void *dato, void *extra) {
	return _existe_numero(dato, extra, MAX_ELEMENTOS + 10);
}

bool existe_dentro(void *dato, void *extra) {
	return _existe_numero(dato, extra, MAX_ELEMENTOS - 10);
}

long sumar_consecutivos(int tope) {
	long suma = 0;
	for(int i = 1; i <= tope; i++) {
		suma += i;
	}
	return suma;
}

bool imprimir_enteros(void *dato, void *extra) {
	printf("%d, ", *(int*)dato);
	return true;
}

void pruebas_iter_interno() {
	printf("- PRUEBAS ITERADOR INTERNO -\n");
	lista_t *lista = lista_crear(); print_test("Creo lista", lista != NULL);
	bool ok = true;
	int arr[MAX_ELEMENTOS];
	int i;
	for (i = 0; i < MAX_ELEMENTOS; i++) {
		arr[i] = i + 1;
	}
	for (i = 0; i < MAX_ELEMENTOS; i++) {
		ok &= lista_insertar_ultimo(lista, &arr[i]);
	}
	printf("Inserto %d elementos en la lista", MAX_ELEMENTOS); print_test("", ok);
	int contador = 0;
	lista_iterar(lista, contar_elementos, &contador);
	print_test("Cuento elementos de la lista", contador == MAX_ELEMENTOS);

	int suma = 0;
	lista_iterar(lista, sumar_int, &suma);
	print_test("Sumo todos los elementos de la lista", suma == sumar_consecutivos(MAX_ELEMENTOS));

	contador = 0;
	lista_iterar(lista, contar_numeros_pares, &contador);
	print_test("Cuento los elementos pares de la lista", contador == MAX_ELEMENTOS / 2);

	lista_t *lista_1 = lista_crear(); print_test("Creo lista_1", lista_1 != NULL);
	lista_iterar(lista_1, NULL, lista);
	lista_iterar(lista, numeros_pares_a_lista, lista_1);
	print_test("Inserto elementos pares de lista en lista_1", lista_largo(lista_1) == MAX_ELEMENTOS / 2);

	bool existe;
	lista_iterar(lista, existe_fuera, &existe);
	print_test("Busco un número, el número no existe", !existe);
	lista_iterar(lista, existe_dentro, &existe);
	print_test("Busco un número, el número existe", existe);

	lista_destruir(lista, NULL);
	lista_destruir(lista_1, NULL);
	print_test("Destruyo listas", true);
}

void pruebas_elementos_dinamicos() {
	printf("- PRUEBAS CON ELEMENTOS DINÁMICOS -\n");
	lista_t *lista = lista_crear();
	bool ok = true;
	int i;
	for (i = 0; i < MAX_ELEMENTOS; i++) {
		ok &= lista_insertar_ultimo(lista, malloc(MAX_ELEMENTOS * sizeof(int)));
	}
	printf("%d elementos agregados al final", MAX_ELEMENTOS); print_test("", ok);

	printf("Verifico que el largo de la lista sea %d", MAX_ELEMENTOS); print_test("", lista_largo(lista) == MAX_ELEMENTOS);

	ok = true;
	for (i = 0; i < MAX_ELEMENTOS; i++) {
		ok &= lista_insertar_primero(lista, malloc(MAX_ELEMENTOS * sizeof(int)));
	}
	printf("%d elementos agregados al principio", MAX_ELEMENTOS); print_test("", ok);

	printf("Verifico que el largo de la lista sea %d", MAX_ELEMENTOS * 2); print_test("", lista_largo(lista) == MAX_ELEMENTOS * 2);

	for (i = 0; i < MAX_ELEMENTOS; i++) {
		free(lista_borrar_primero(lista));
	}
	printf("Elimino %d elementos, veo que el largo sea nuevamente %d", MAX_ELEMENTOS, MAX_ELEMENTOS); print_test("", lista_largo(lista) == MAX_ELEMENTOS);

	lista_destruir(lista, free); print_test("Destruyo la lista pasando funcion propia", true);

}

void pruebas_iter_2() {
	lista_t *lista = lista_crear(); print_test("Creo lista", lista != NULL);
	lista_iter_t *iter = lista_iter_crear(lista);
	int a = 1, b = 2, c = 3;
	print_test("Estoy al final", lista_iter_al_final(iter));
	print_test("Inserto un elemento", lista_iter_insertar(iter, &a));
	print_test("No estoy al final", !lista_iter_al_final(iter));

	print_test("Avanzo iterador", lista_iter_avanzar(iter));
	print_test("Estoy al final", lista_iter_al_final(iter));
	print_test("Inserto un elemento", lista_iter_insertar(iter, &b));

	lista_iter_destruir(iter); print_test("Destuyo iterador", true);


	print_test("Inserto un elemento", lista_insertar_ultimo(lista, &c));


	lista_destruir(lista, NULL); print_test("Destruyo lista", true);
}

void pruebas_lista_alumno() {
	pruebas_lista_vacia();
	pruebas_enteros();
	pruebas_iter();
	pruebas_iter_2();
	pruebas_iter_interno();
	pruebas_elementos_dinamicos();
}
