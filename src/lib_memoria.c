#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib_peticion.h"
#include "lib_memoria.h"

/* Funcion para crear cada nodo de la lista de fragmentos */
lista_memoria crear_fragmento_memoria
    (
        char nombre_proceso[20],
        unsigned long tamano_fragmento,
        int mem_inicio,
        int mem_fin,
        int es_libre
    )
{
	lista_memoria aux;
	aux = (lista_memoria)malloc(sizeof(tipo_memoria));
	if (aux != NULL) {
		strcpy(aux->nombre_proceso, nombre_proceso);
		//aux->nombre_proceso     = nombre_proceso;
		aux->tamano_fragmento   = tamano_fragmento;
		aux->mem_inicio         = mem_inicio;
		aux->mem_fin            = mem_fin;
		aux->es_libre           = es_libre;
		aux->sgte               = NULL;
		aux->atras              = NULL;
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

/* Funcion para insertar al principio de la lista */
lista_memoria insertar_fragmento_principio
    (
        lista_memoria lista,
        char nombre_proceso[20],
        unsigned long tamano_fragmento,
        int mem_inicio,
        int mem_fin,
        int es_libre
    )
{
    p_nodo fragmento = NULL;
    lista_memoria aux;

    fragmento = crear_fragmento_memoria(nombre_proceso, tamano_fragmento, mem_inicio, mem_fin, es_libre);
    aux = lista;
    fragmento->sgte     = aux;
    fragmento->atras    = aux->atras;
    aux->atras          = fragmento;
    aux                 = NULL;
    return fragmento;
}

/* Funcion para insertar un fragmento en una posicion de la lista */
lista_memoria insertar_fragmento_posicion
    (
        lista_memoria lista,
        char nombre_proceso[20],
        int posicion,
        unsigned long tamano_fragmento,
        int mem_inicio,
        int mem_fin,
        int es_libre
    )
{
    int contador = 1;
    p_nodo fragmento = NULL;
    lista_memoria aux;

    fragmento = crear_fragmento_memoria(nombre_proceso, tamano_fragmento, mem_inicio, mem_fin, es_libre);
    for (aux = lista; aux != NULL; aux = aux->sgte, contador++) {
        if (posicion == contador) {
            aux = aux->atras;
            break;
        }
    }
    fragmento->sgte = aux->sgte;
    aux->sgte = fragmento;
    fragmento->atras = aux;
    fragmento->sgte->atras = fragmento;
    aux = NULL;
    return lista;
}

/* Funcion para establecer los rangos de memoria dentro de un fragmento de memoria */
void establecer_rango_memoria(lista_memoria lista)
{   int contador = 1;
    lista_memoria aux;

    for (aux = lista; aux != NULL; aux = aux->sgte, contador++)
    {
        /* Primer nodo de la lista*/
        if (contador == 1){
            aux->mem_inicio = 0;
            aux->mem_fin    = aux->tamano_fragmento - 1;
        } else {
            aux->mem_inicio = aux->atras->mem_inicio + aux->atras->tamano_fragmento;
            aux->mem_fin    = (aux->mem_inicio + aux->tamano_fragmento) - 1;
        }
    }
}

lista_memoria first_fit(lista_memoria lista_fragmentos, lista_peticion lista_peticiones)
{
    int estado = 0, tipo_peticion = 0, posicion = 1;
    lista_peticion aux_p = NULL;
    lista_memoria aux_m = NULL;

    for (aux_p = lista_peticiones; aux_p != NULL; aux_p = aux_p->sgte) {
        tipo_peticion = obtener_tipo_peticion(aux_p);
        estado = hay_memoria_suficiente(aux_p, lista_fragmentos);

        if (tipo_peticion == 1) {   /* Allocate */
            if (estado == 0) {
                puts("NO HAY MEMORIA PARA ESTA PETICION");
                continue;
            }
            else if (estado == 1) {
                printf("Peticion de mem %s %lu\n", aux_p->nombre_proceso, aux_p->cantidad_peticion);
                if ( es_necesario_desfragmentar(aux_p, lista_fragmentos) == 1 ) {
                   //    puts("HAY MEMORIA PERO NECESITA DESFRAGMENTACION");
                    //puts("*******************DESFRAGMENTANDO...");
                    lista_fragmentos = desfragmentar(lista_fragmentos);
                    //puts("TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT");
                    //imprimir_fragmentos(lista_fragmentos);
                    //puts("RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR");
                }
                for (posicion = 1, aux_m = lista_fragmentos; aux_m != NULL; aux_m = aux_m->sgte, posicion++) {
                    if (aux_m->es_libre == 1) {
                        /* Primera posicion de la lista */
                        if (posicion == 1) {
                            aux_m->tamano_fragmento = aux_m->tamano_fragmento - aux_p->cantidad_peticion;
                            lista_fragmentos = insertar_fragmento_principio(lista_fragmentos,
                                                                            aux_p->nombre_proceso,
                                                                            aux_p->cantidad_peticion,
                                                                            0,
                                                                            0,
                                                                            0);
                            establecer_rango_memoria(lista_fragmentos);
                            break;
                        }
                        /* Ultima posicion */
                        else if ( (aux_m->sgte == NULL) && (aux_p->cantidad_peticion == aux_m->tamano_fragmento) ) {
                            strcpy(aux_m->nombre_proceso, aux_p->nombre_proceso);
                            aux_m->tamano_fragmento = aux_p->cantidad_peticion;
                            aux_m->mem_inicio = 0;
                            aux_m->mem_fin = 0;
                            aux_m->es_libre = 0;
                            establecer_rango_memoria(lista_fragmentos);
                            break;
                        }
                        else {
                            aux_m->tamano_fragmento = aux_m->tamano_fragmento - aux_p->cantidad_peticion;
                            lista_fragmentos = insertar_fragmento_posicion(lista_fragmentos,
                                                                           aux_p->nombre_proceso,
                                                                           posicion,
                                                                           aux_p->cantidad_peticion,
                                                                           0,
                                                                           0,
                                                                           0);
                            establecer_rango_memoria(lista_fragmentos);
                            break;
                        }
                    }
                }
            }
        }
        else if (tipo_peticion == 0) {   /* free */
            /* Liberar memoria */
            printf("PETICION PARA LIBERAR MEMORIA %s %lu\n", aux_p->nombre_proceso, aux_p->cantidad_peticion);
            liberar_fragmento(lista_fragmentos, aux_p->nombre_proceso, aux_p->cantidad_peticion);
            establecer_rango_memoria(lista_fragmentos);
            //break;
        }
    }
    return lista_fragmentos;
}


/* Funcion para liberar un fragmento de memoria */
void liberar_fragmento(lista_memoria lista, char nombre_proceso[20], unsigned long cantidad_peticion)
{
    lista_memoria aux = NULL;

    for (aux = lista; aux != NULL; aux = aux->sgte) {
        if ( ( strcmp(aux->nombre_proceso, nombre_proceso) == 0 ) && (aux->tamano_fragmento == cantidad_peticion) ) {
            strcpy(aux->nombre_proceso, "sin_nombre");
            aux->es_libre = 1;
            break;
        }
    }
}

/* Funcion eliminar un elemento de la lista */
lista_memoria eliminar_fragmento(lista_memoria lista)
{
    lista_memoria aux;

    /* Primer nodo de la fila */
    if (lista->atras == NULL) {
        aux = lista;
        lista = lista->sgte;
        aux->sgte->atras = NULL;
        free(aux);
        return lista;
    }
    /* Nodo intermedio */
    else {
        aux = lista;
        lista = lista->atras;
        aux->atras->sgte = aux->sgte;
        aux->sgte->atras = aux->atras;
        free(aux);
        return lista;
    }
}

/* funcion para desfragmentar */
lista_memoria desfragmentar(lista_memoria lista)
{
    int estado = 1;
    lista_memoria aux = NULL;
    unsigned long acumulador_memoria = 0;

    while (estado) {
        for (aux = lista; aux != NULL; aux = aux->sgte) {
            if (aux->sgte == NULL) {    /* Ultimo nodo libre*/
                aux->tamano_fragmento = aux->tamano_fragmento + acumulador_memoria;
                estado = 0;
                break;
            }
            else if (aux->es_libre == 1) {
                acumulador_memoria = acumulador_memoria + aux->tamano_fragmento;
                lista = eliminar_fragmento(aux);
                break;
            }
        }
    }
    establecer_rango_memoria(lista);
    //puts("FRAGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG");
    //imprimir_fragmentos(lista);
    //puts("FRAGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG");
    return lista;
}

/* Funcion para determinar si hay memoria suficiente para atender la peticion */
int hay_memoria_suficiente(lista_peticion peticion, lista_memoria lista)
{
    int bandera = 0;    /* Bandera que indica si existe un fragmento suficiente */

    unsigned long memoria_disponible    = 0;
    lista_memoria aux                   = NULL;

    /* Recorriendo los fragmentos de memoria */
    for (aux = lista; aux != NULL; aux = aux->sgte) {
        if (aux->es_libre == 1) {
            memoria_disponible = memoria_disponible + aux->tamano_fragmento;
            if (aux->tamano_fragmento >= peticion->cantidad_peticion) {
                bandera = 1;
            }
        }
    }

    free(aux);

    if ( (memoria_disponible < peticion->cantidad_peticion) && (bandera == 0) ) {
        return 0;   /* No hay memoria disponible */
    }
    /*else if ( (memoria_disponible >= peticion->cantidad_peticion) && (bandera == 0) ) {
        return 1;
    }*/
    else if ( memoria_disponible >= peticion->cantidad_peticion ) {
        return 1;   /* Hay memoria disponible  */
    }
    return -1;  /* Error*/
}

/* Funcion que determina si es necesario desfragmentar */
int es_necesario_desfragmentar(lista_peticion peticion, lista_memoria lista)
{
    int bandera = 0, estado = 0;
    unsigned long memoria_disponible    = 0;
    lista_memoria aux                   = NULL;

    /* Recorriendo los fragmentos de memoria */
    for (aux = lista; aux != NULL; aux = aux->sgte) {
        if (aux->es_libre == 1) {
            memoria_disponible = memoria_disponible + aux->tamano_fragmento;
            if (aux->tamano_fragmento >= peticion->cantidad_peticion) {
                bandera = 1;
            }
        }
    }
    if ( (bandera == 0) && (memoria_disponible >= peticion->cantidad_peticion) )
        estado = 1;
    else
        estado = 0;

    printf ("UUUUUUUUUUUUUUU Es necesario en %s = %lu [%d]\n", peticion->nombre_proceso, peticion->cantidad_peticion, estado);
    return estado;
}
