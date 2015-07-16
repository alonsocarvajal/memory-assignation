#include <stdio.h>
#include <stdlib.h>
#include "lib_getopt.h"
#include "lib_archivo.h"
#include "lib_memoria.h"

int main(int argc, char *argv[])
{
    /* Pendiente: crear la funcion iniciar_programa que
     * realice una abstraccion de toda la funcion main()
     */
    int estado_opcion = 0;

    Opcion opciones_del_sistema;
    lista_peticion  lista_peticiones    = NULL;
    lista_memoria   lista_fragmentos    = NULL;

    opciones_del_sistema.argv              = argv;
    opciones_del_sistema.argc              = argc;
    opciones_del_sistema.nombre_programa   = argv[0];


    /* + Si ocurre algun problema con los argumentos, el programa termina aqui.
     * + Cambiar el nombre de la funcion
     * + Agregar una condicional "if" para obtener mayor claridad acerca de
     *   la salida del programa
     */
    obtener_argumentos(&opciones_del_sistema, &estado_opcion);

    if (estado_opcion == 1) {   /* Error en el paso de opciones al programa */
        exit(EXIT_FAILURE);
    }

    /* Establecer la memoria inicial con un nodo. Capacidad nodo inicial = N * 1024 KB */

    lista_fragmentos = crear_fragmento_memoria("sin_nombre",
                                               opciones_del_sistema.cantidad_memoria,
                                               0,
                                               opciones_del_sistema.cantidad_memoria - 1,
                                               1);

    /* Leer peticiones */
    lista_peticiones = leer_archivo_peticion(lista_peticiones, opciones_del_sistema.archivo_peticiones);
    imprimir_peticiones(lista_peticiones);

    /* Sección para testear el algoritmo */
    lista_fragmentos = first_fit(lista_fragmentos, lista_peticiones);
    imprimir_fragmentos(lista_fragmentos);


    /* Leyendo datos del sistema */
    /*printf("Algoritmo = %c\nnom_prog = %s\narc_pet = %s\narc_sal = %s\nmodo = %c\ncan_mem = %lu\n",
            opciones_del_sistema.algoritmo,
            opciones_del_sistema.nombre_programa,
            opciones_del_sistema.archivo_peticiones,
            opciones_del_sistema.archivo_salida,
            opciones_del_sistema.modo,
            opciones_del_sistema.cantidad_memoria);
    */
    free(lista_fragmentos);
    free(lista_peticiones);
    return(EXIT_SUCCESS);
}
