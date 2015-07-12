/* Libreria para el tratamiento de entrada y salida de archivos */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void leer_peticion(void)
{
    int estado = 0;
    char linea[100];
    char *token;
    Peticion peticion;
    FILE *archivo;

    archivo = fopen("../../config/peticiones", "r");

    // Usando sscanf
    while ( fgets(linea, sizeof(linea), archivo) ) {
        estado = sscanf(linea, "%[^;];%[^;];%[^;];", peticion.nombre_proceso, peticion.tipo_peticion, peticion.cantidad_peticion);
        printf("%s %s %s\n", peticion.nombre_proceso, peticion.tipo_peticion, peticion.cantidad_peticion);
        printf("[%ld]\n", clock());
    }

    fclose(archivo);
}
