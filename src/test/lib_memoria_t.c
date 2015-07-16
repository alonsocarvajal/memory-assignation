#include <stdio.h>
#include <stdlib.h>
#include "lib_peticion.h"
#include "lib_memoria.h"

/* Funcion para crear cada nodo de la lista de fragmentos */
lista_memoria crear_fragmento_memoria
    (
        char *nombre_proceso,
        unsigned long tamano_fragmento,
        int mem_inicio,
        int mem_fin,
        int es_libre
    )
{
	lista_memoria aux;
	aux = (lista_memoria)malloc(sizeof(Memoria));
	if (aux != NULL) {
		aux->nombre_proceso     = nombre_proceso;
		aux->tamano_fragmento   = tamano_fragmento;
		aux->mem_inicio         = mem_inicio;
		aux->mem_fin            = mem_fin;
		aux->es_libre           = es_libre;
		aux->sgte               = NULL;
	}
	return aux;
}

/* Funcion que retorna el largo de la lista de fragmentos de memoria */
int largo_lista_fragmentos(lista_memoria lista)
{
	int largo = 0;
	lista_memoria aux;

	for (aux = lista; aux != NULL; aux = aux->sgte, largo++);
	return largo;
}

/* Funcion para imprimir la lista de fragmentos de memoria */
void imprimir_fragmentos(lista_memoria lista)
{
    int posicion_fragmento = 1;
	lista_memoria aux;

	if ( lista == NULL ) {  // Lista vacia
		puts("---- Lista sin elementos ----");
	}
	else {
		for (aux = lista; aux != NULL; aux = aux->sgte, posicion_fragmento++) {
            puts("-----------------------------------------");
            printf("Fragmento numero: %d\n", posicion_fragmento);
            printf("Nombre proceso: %s\n", aux->nombre_proceso);
            printf("Tamaño fragmento: %lu\n", aux->tamano_fragmento);
            printf("Rango memoria inicio: %d\n", aux->mem_inicio);
            printf("Rango memoria fin: %d\n", aux->mem_fin);
            printf("Es libre: %d\n", aux->es_libre);
            putchar('\n');
		}
	}
}

/* Funcion para insertar un nodo de la lista de fragmentos en una posicion determinada */
lista_memoria insertar_fragmento_posicion
    (
        lista_memoria lista,
        int posicion,
        char *nombre_proceso,
        unsigned long tamano_fragmento,
        int mem_inicio,
        int mem_fin,
        int es_libre
    )
{
	int i = 0;
	lista_memoria   atras,          /* Puntero al fragmento de memoria anterior */
                    aux,            /* Fragmento de memoria auxiliar */
                    p_fragmento;    /* Puntero a un fragmento de memoria */

    mem_inicio = mem_fin = 0;   /* Variables iniciadas por defecto en 0 */
	p_fragmento = crear_fragmento_memoria(nombre_proceso, tamano_fragmento, mem_inicio, mem_fin, es_libre);

	if (posicion <= largo_lista_fragmentos(lista)) {
		for (i = 1, atras = NULL, aux = lista; i < posicion && aux != NULL; i++, atras = aux, aux = aux->sgte);
		p_fragmento->sgte = aux;
		if (atras == NULL)
			lista = p_fragmento;
		else
			atras->sgte = p_fragmento;
	}
	return lista;
}

/* Funcion: obtener_rango_fragmento
 * Descripcion: Retorna el valor del rango de memoria ubicado en una posicion especifica
 * Entrada: Lista de fragmentos y posicion del fragmento de memoria
 * Salida: Rango de memoria final
 */
int obtener_mem_fin(lista_memoria lista, int posicion)
{
    lista_memoria aux = NULL;
    int i = largo_lista_fragmentos(lista);

    for (aux = lista; aux != NULL; aux = aux->sgte)
        if ( (i--) == posicion )
            break;

    return aux->mem_fin;
}

/* Funcion para calcular los rangos de memoria de cada fragmento */
void calcular_rango_memoria(lista_memoria lista)
{
    int posicion_lista          = 1,
        numero_de_fragmentos    = largo_lista_fragmentos(lista);
        printf("<<<<<<<<<<<<<< tamano lista = %d\n", numero_de_fragmentos);
    lista_memoria aux;

    for (aux = lista; aux != NULL; aux = aux->sgte, posicion_lista++)
    {
        printf("<<<<<<<<<<<< pos %d tamano frag %lu\n", posicion_lista, aux->tamano_fragmento);
        /*Poscion 1*/
        if (posicion_lista == 1) {
            aux->mem_inicio = 0;
            aux->mem_fin    = aux->tamano_fragmento - 1;
        }
        /*Posicion 2 hasta N -1 */
        else if (posicion_lista > 1 && posicion_lista < numero_de_fragmentos && posicion_lista != numero_de_fragmentos) {
            aux->mem_inicio = obtener_mem_fin(lista, posicion_lista - 1) + 1;
            aux->mem_fin    = (aux->mem_inicio + aux->tamano_fragmento) - 1;
        }
        /* Posicion N */
        else if (posicion_lista == numero_de_fragmentos){
            aux->mem_inicio = obtener_mem_fin(lista, posicion_lista - 1);
            //aux->mem_inicio = 108;
            aux->mem_fin    = (aux->mem_inicio + aux->tamano_fragmento) - 1;
        }
    }
}

/* ALGORITMOS DE ASIGNACION DE MEMORIA */

/* Funcion para el algoritmo First Fit */
lista_memoria first_fit(lista_memoria lista_fragmentos, lista_peticion lista_peticiones)
{
    int posicion_f_libre;       /* posicion del fragmento libre     */
    lista_peticion  aux_p;      /* puntero auxiliar de la peticion  */
    lista_memoria   aux_f;      /* puntero auxiliar del fragmento   */

    /* Iterando sobre las peticiones */
    for (aux_p = lista_peticiones; aux_p != NULL; aux_p = aux_p->sgte) {
        printf("Peticion proceso %s\n", aux_p->nombre_proceso);
        /* Por cada peticion se analiza si hay un fragmento libre */
        posicion_f_libre = 1;
        for (aux_f = lista_fragmentos; aux_f != NULL; aux_f = aux_f->sgte, posicion_f_libre++) {
            puts("en  ---------------");
            printf("nombre fragmento: %s\n", aux_f->nombre_proceso);
            /* Si existe un fragmento libre mayor o igual que la peticion */
            if ( (aux_f->es_libre = 1) && (aux_f->tamano_fragmento >= aux_p->cantidad_peticion) ) {
                //lista_fragmentos = insertar_fragmento_posicion
                lista_fragmentos = insertar_fragmento
                    (
                        lista_fragmentos,           /* */
                        posicion_f_libre,
                        aux_p->nombre_proceso,
                        aux_p->cantidad_peticion,
                        0,                          /* Variable mem_inicio  */
                        0,                          /* Variable mem_final   */
                        0                           /* Variable es_libre. Fragmento ocupado */
                    );
                    break;
            }
        }
    }
    calcular_rango_memoria(lista_fragmentos);
    return lista_fragmentos;
}

/* Funcion de prueba */
lista_memoria insertar_fragmento
    (
        lista_memoria lista,
        int posicion,
        char *nombre_proceso,
        unsigned long tamano_fragmento,
        int mem_inicio,
        int mem_fin,
        int es_libre
    )
{
    lista_memoria p_fragmento, aux;

    p_fragmento = crear_fragmento_memoria(nombre_proceso, tamano_fragmento, mem_inicio, mem_fin, es_libre);

    if (lista == NULL) {
        lista = p_fragmento;
    }
    else if (lista->sgte == NULL){
        lista->sgte = p_fragmento;
    }
    else {
        for(aux = lista; aux->sgte != NULL; aux = aux->sgte);
		aux->sgte = p_fragmento;
		aux = NULL;
    }
    p_fragmento = NULL;
    return lista;
}
