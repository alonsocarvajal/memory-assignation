/* Libreria utilizada para crear listas de peticiones */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib_peticion.h"

/* Estructura definida para cada peticion
struct peticion {
    unsigned long       marca_de_tiempo;
    char                nombre_proceso[20];
    char                tipo_peticion[9];      // 0: Allocate, 1: Free
    unsigned long       cantidad_peticion;
    struct  peticion    *sgte;
};

typedef peticion Peticion;
typedef Peticion *lista_peticion;
*/

/* Funcion crear peticion */
lista_peticion crear_peticion
    (
        unsigned long marca_de_tiempo,
        char nombre_proceso[20],
        char tipo_peticion[9],
        unsigned long cantidad_peticion
    )
{
    lista_peticion aux;

    aux = (_lista_peticion)malloc( sizeof(Peticion) );
    if (aux != NULL) {
        aux->marca_de_tiempo = clock();
        strcpy(aux->nombre_proceso, nombre_proceso);
        strcpy(aux->tipo_peticion, tipo_peticion);
        aux->cantidad_peticion = cantidad_peticion;
    }
    return aux;
}

/* Funcion insertar peticion al final de la lista */
lista_peticion insertar_peticion
    (
        lista_peticion lista,
        unsigned long marca_de_tiempo,
        char nombre_proceso[20],
        char tipo_peticion[9],
        unsigned long cantidad_peticion
    )
{
    lista_peticion p_peticion, aux;

    p_peticion = crear_peticion(marca_de_tiempo, nombre_proceso, tipo_peticion, cantidad_peticion);

    if (lista == NULL) {
        lista = p_peticion;
    }
    else if (lista->sgte == NULL){
        lista->sgte = p_peticion;
    }
    else {
        for(aux = lista; aux->sgte != NULL; aux = aux->sgte);
		aux->sgte = p_peticion;
		aux = NULL;
    }
    p_peticion = NULL;
    return lista;
}

/* Funcion para calcular el largo de las peticiones */
int largo_lista_peticiones(lista_peticion lista)
{
	int contador = 0;
	lista_peticion aux;

	for (aux = lista; aux != NULL; aux = aux->sgte, contador++);
	return contador;
}

/* Funcion imprimir lista de peticiones */
void imprimir_peticiones(lista_peticion lista)
{
	lista_peticion aux;

	if ( lista == NULL ) {  // Lista vacia
		puts("---- Lista sin elementos ----");
	}
	else {
		for (aux = lista; aux != NULL; aux = aux->sgte) {
            printf("---- %s ----\n", aux->nombre_proceso);
            printf("\tMarca de tiempo\t: %ld\n", aux->marca_de_tiempo);
            printf("\tTipo de peticion\t: %s\n", aux->tipo_peticion);
            printf("\tCantidad de memoria requerida\t: %ld\n", aux->cantidad_peticion);
            putchar('\n');
		}
	}
}
