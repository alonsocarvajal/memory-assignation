/* Libreria utilizada para crear listas de peticiones */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lib_peticion.h"


/* Funcion crear peticion */
lista_peticion crear_peticion
    (
        //unsigned long marca_de_tiempo,
        char nombre_proceso[20],
        char tipo_peticion[9],
        unsigned long cantidad_peticion
    )
{
    lista_peticion aux;

    aux = (lista_peticion)malloc( sizeof(Peticion) );
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
        //unsigned long marca_de_tiempo,
        char nombre_proceso[20],
        char tipo_peticion[9],
        unsigned long cantidad_peticion
    )
{
    lista_peticion p_peticion, aux;

    p_peticion = crear_peticion(nombre_proceso, tipo_peticion, cantidad_peticion);

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
            printf("Proceso: %s\n", aux->nombre_proceso);
            printf("\t+ Marca de tiempo\t\t: %ld\n", aux->marca_de_tiempo);
            printf("\t+ Tipo de peticion\t\t: %s\n", aux->tipo_peticion);
            printf("\t+ Cantidad de memoria requerida\t: %ld\n", aux->cantidad_peticion);
            putchar('\n');
		}
	}
}

/* Funcion complemento para determinar el tipo de peticion "Allocate o Free" */
int obtener_tipo_peticion(lista_peticion peticion)
{
    /* Retorna 1 para allocate y 0 para free */
    if ( strcmp(peticion->tipo_peticion, "allocate") == 0 )
        return 1;
    else if ( strcmp(peticion->tipo_peticion, "free") == 0 )
        return 0;
    else
        return -1;  /* Error */
}
