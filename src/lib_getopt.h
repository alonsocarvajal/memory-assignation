/* Estructura utilizada para las opciones del sistema */
typedef struct opcion {
    char **argv;
    char *nombre_programa;
    char *archivo_peticiones;
    char *archivo_salida;
    char algoritmo;
    char modo;
    unsigned long cantidad_memoria;
    int argc;
}Opcion;

extern char *obtener_fecha_inicio(void);
extern void imprimir_uso(char *nombre_programa);
extern void obtener_argumentos(Opcion *opciones_del_sistema, int *estado_opcion);
