#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

/* Pruebas para verificar el comportamiento de las primitivas cuando la pila está vacía */
void pruebas_pila_vacia() {
    pila_t *pila = pila_crear();

    printf("- PRUEBAS PILA VACÍA -\n");

    print_test("Veo que pila está vacía.", pila_esta_vacia(pila));

    print_test("Veo que tope sea NULL", pila_ver_tope(pila) == NULL);

    print_test("Veo que al desapilar devuelva NULL", pila_desapilar(pila) == NULL);

    pila_destruir(pila);
}


/* Pruebas apilando punteros a números enteros */
void pruebas_enteros() {
    pila_t *pila = pila_crear();
    int arr[] = {1, 2, 3};
    size_t largo_arr = 3;
    int arr1[500];
    bool ok;
    int i;

    for (i = 0; i < 500; i++) {
        arr1[i] = i;
    }

    printf("- PRUEBAS CON ENTEROS -\n");

    ok = true;
    for (i = 0; i < largo_arr; i++) {
        ok &= pila_apilar(pila, &arr[i]);
    }

    print_test("Apilo tres elementos", ok);

    print_test("Desapilo = 3", *(int*)pila_desapilar(pila) == 3);
    print_test("Veo tope = arr[1]", pila_ver_tope(pila) == &arr[1]);

    arr[1] = 7;
    print_test("Cambio valor de arr[1] a 7, veo si tope = 7", *(int*)pila_ver_tope(pila) == 7);

    print_test("Desapilo = 7", *(int*)pila_desapilar(pila) == 7);

    print_test("Veo tope = 1", *(int*)pila_ver_tope(pila) == 1); // Tope = 1

    print_test("Veo que pila no esté vacía.", !pila_esta_vacia(pila));

    printf("- Apilo 500 elementos -\n");
    ok = true;
    for (i = 0; i < 500; i++) {
        ok &= pila_apilar(pila, &arr1[i]);
    }
    print_test("Se apilaron los 500", ok);

    print_test("Veo que tope sea 499", *(int*)pila_ver_tope(pila) == 499);

    ok = true;
    for (i = 499; i >= 0; i--) {
        ok &= *(int*)pila_desapilar(pila) == i;
    }
    print_test("Verifico que cada valor desapilado sea correcto", ok); // El tope debería haber quedado nuevamente = 1
    
    print_test("Veo que el tope sea 1", *(int*)pila_ver_tope(pila) == 1);

    printf("Desapilo el resto de los elementos.\n");
    while (!pila_esta_vacia(pila)) {
        pila_desapilar(pila);
    }

    print_test("Veo que la pila esté vacía", pila_esta_vacia(pila));
    print_test("Veo que desapilar devuelva NULL", pila_desapilar(pila) == NULL);

    pila_destruir(pila);
}


/* Pruebas apilando punteros a char */
void pruebas_vector_char() {
    pila_t *pila = pila_crear();
    char u[] = "Hola", v[] = "Mundo", w[] = "Algoritmo";

    printf("- PRUEBAS CADENAS -\n");

    pila_apilar(pila, u);
    print_test("Veo tope, veo si es \"Hola\"", strcmp("Hola", pila_ver_tope(pila)) == 0);

    pila_apilar(pila, v);
    print_test("Veo tope, veo si es \"Mundo\"", strcmp("Mundo", pila_ver_tope(pila)) == 0);

    pila_apilar(pila, w);
    print_test("Veo tope, veo si es \"Algoritmo\"", strcmp("Algoritmo", pila_ver_tope(pila)) == 0);

    print_test("Veo que la pila no esté vacía.", !pila_esta_vacia(pila));

    print_test("Desapilo = \"Algoritmos\"", strcmp("Algoritmo", pila_desapilar(pila)) == 0);

    print_test("Desapilo = \"Mundo\"", strcmp("Mundo", pila_desapilar(pila)) == 0);

    print_test("Desapilo = \"Hola\"", strcmp("Hola", pila_desapilar(pila)) == 0);

    pila_destruir(pila);
}

void pruebas_pila_alumno() {
    pruebas_pila_vacia();
    pruebas_enteros();
    pruebas_vector_char();
}
