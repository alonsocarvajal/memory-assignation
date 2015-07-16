/* Estructura utilizada para las peticiones */
struct peticion {
    unsigned long       marca_de_tiempo;
    char                nombre_proceso[20];
    char                tipo_peticion[9];      // 0: Allocate, 1: Free
    unsigned long       cantidad_peticion;
    struct  peticion    *sgte;
};

typedef struct peticion Peticion;
typedef Peticion *lista_peticion;

extern lista_peticion crear_peticion(char nombre_proceso[20], char tipo_peticion[9], unsigned long cantidad_peticion);
extern lista_peticion insertar_peticion(lista_peticion lista, char nombre_proceso[20], char tipo_peticion[9], unsigned long cantidad_peticion);
extern int largo_lista_peticiones(lista_peticion lista);
extern void imprimir_peticiones(lista_peticion lista);
extern int obtener_tipo_peticion(lista_peticion peticion);
