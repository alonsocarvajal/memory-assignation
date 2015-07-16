/* Libreria para simular la memoria */

/*Estructura utilizada para simular los fragmentos de memoria */
struct memoria {
    char *nombre_proceso;
    unsigned long tamano_fragmento; /* Tamano del fragmento de memoria */
    int mem_inicio;                 /* Inicio del rango de memoria */
    int mem_fin;                    /* Fin del rango de memoria */
    int es_libre;                   /* 1: Libre, 0: Utilizado*/
    struct memoria *sgte;           /* Puntero al siguiente fragmento de memoria */
};

typedef struct memoria Memoria;
typedef Memoria *lista_memoria;


extern lista_memoria crear_fragmento_memoria
    (
        char *nombre_proceso,
        unsigned long tamano_fragmento,
        int mem_inicio,
        int mem_fin,
        int es_libre
    );
extern int largo_lista_fragmentos(lista_memoria lista);
void imprimir_fragmentos(lista_memoria lista);
extern lista_memoria insertar_fragmento_posicion
    (
        lista_memoria lista,
        int posicion,
        char *nombre_proceso,
        unsigned long tamano_fragmento,
        int mem_inicio,
        int mem_fin,
        int es_libre
    );
extern void calcular_rango_memoria(lista_memoria lista);
extern int obtener_mem_fin(lista_memoria lista, int posicion);
extern lista_memoria first_fit(lista_memoria lista_fragmentos, lista_peticion lista_peticiones);
/*test*/
extern lista_memoria insertar_fragmento
    (
        lista_memoria lista,
        int posicion,
        char *nombre_proceso,
        unsigned long tamano_fragmento,
        int mem_inicio,
        int mem_fin,
        int es_libre
    );
