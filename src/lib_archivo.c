/* Libreria para el tratamiento de entrada y salida de archivos */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib_archivo.h"

/* Funcion que lee el archivo de peticion y almacena cada peticion en una lista enlazada */
lista_peticion leer_archivo_peticion(lista_peticion lista, char *nombre_archivo)
{
    /* Variables para el tratamiento de la lista de peticiones */
    char nombre_proceso[20];
    char tipo_peticion[9];
    unsigned long cantidad_peticion;

    /* Variables para la lectura del archivo de peticiones */
    char linea[100];
    FILE *archivo;

    archivo = fopen(nombre_archivo, "r");

    /* Por cada peticion leida desde el archivo se crea un elemento de la lista de peticiones */
    while ( fgets(linea, sizeof(linea), archivo) ) {
        sscanf(linea, "%[^;];%[^;];%ld[^;];", nombre_proceso, tipo_peticion, &cantidad_peticion);
        /*printf( "-----------------------------------\n"
                "nombre_proceso: %s\n"
                "tipo_peticion: %s\n"
                "cantidad %ld\n", nombre_proceso, tipo_peticion, cantidad_peticion);
        */
        lista = insertar_peticion(lista, nombre_proceso, tipo_peticion, cantidad_peticion);
    }
    fclose(archivo);
    return lista;
}
