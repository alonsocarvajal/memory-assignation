#include <stdio.h>
#include "lib_archivo.h"

int main(int argc, char *argv[])
{
    lista_peticion lista_peticiones = NULL;

    /* Leer peticiones */
    lista_peticiones = leer_archivo_peticion(lista_peticiones, "../config/peticiones");

    imprimir_peticiones(lista_peticiones);

    return(0);
}
