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
