#include <stdio.h>
#include "lib_archivo.h"
#include "lib_getopt.h"

int main(int argc, char *argv[])
{
    Opcion opciones_del_sistema;
    lista_peticion lista_peticiones = NULL;

    opciones_del_sistema.nombre_programa = argv[0];
    opciones_del_sistema = obtener_argumentos(&opciones_del_sistema);

    /* Leer peticiones */
    //lista_peticiones = leer_archivo_peticion(lista_peticiones, "../config/peticiones");

    //imprimir_peticiones(lista_peticiones);
    printf("Algoritmo %c\n", opciones_del_sistema.algoritmo);

    return(0);
}
