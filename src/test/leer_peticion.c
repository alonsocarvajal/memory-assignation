#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../lib_lista.h"

// <Nombre de proceso>;<Tipo de petición>;<Cantidad de KiloBytes o Dirección de memoria>;

// Estructura para almacenar cada peticion
/*typedef struct peticion {
    char    nombre_proceso[20];
    int     tipo_peticion;      // 0: Allocate, 1: Free
    long    cantidad_peticion;
} Peticion;
*/

// Estructura para almacenar cada peticion
typedef struct peticion {
    unsigned long       marca_de_tiempo;
    char                nombre_proceso[20];
    char                tipo_peticion[9];      // 0: Allocate, 1: Free
    unsigned long       cantidad_peticion;
    struct  peticion    *sgte;
} Peticion;

// Funcion leer peticion
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

void main(void)
{
    printf("[%ld]\n", clock());

    leer_peticion();
}
