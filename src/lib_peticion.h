extern lista_peticion crear_peticion(char nombre_proceso[20], char tipo_peticion[9], unsigned long cantidad_peticion);
extern lista_peticion insertar_peticion(lista_peticion lista, char nombre_proceso[20], char tipo_peticion[9], unsigned long cantidad_peticion);
extern int largo_lista_peticiones(lista_peticion lista);
extern void imprimir_peticiones(lista_peticion lista);
