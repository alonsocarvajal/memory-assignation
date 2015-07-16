/*Estructura (lista doble enlace) utilizada para simular los fragmentos de memoria */
typedef struct _memoria {
    char nombre_proceso[20];
    unsigned long tamano_fragmento; /* Tamano del fragmento de memoria */
    int mem_inicio;                 /* Inicio del rango de memoria */
    int mem_fin;                    /* Fin del rango de memoria */
    int es_libre;                   /* 1: Libre, 0: Utilizado*/
    struct _memoria *sgte;           /* Puntero al siguiente fragmento de memoria */
    struct _memoria *atras;          /* Puntero al fragmento anterior */
}tipo_memoria;

typedef tipo_memoria *p_nodo;
typedef tipo_memoria *lista_memoria;

extern lista_memoria crear_fragmento_memoria
    (
        char nombre_proceso[20],
        unsigned long tamano_fragmento,
        int mem_inicio,
        int mem_fin,
        int es_libre
    );
extern int largo_lista_fragmentos(lista_memoria lista);
extern void imprimir_fragmentos(lista_memoria lista);
extern lista_memoria insertar_fragmento_principio
    (
        lista_memoria lista,
        char nombre_proceso[20],
        unsigned long tamano_fragmento,
        int mem_inicio,
        int mem_fin,
        int es_libre
    );
extern lista_memoria insertar_fragmento_posicion
    (
        lista_memoria lista,
        char nombre_proceso[20],
        int posicion,
        unsigned long tamano_fragmento,
        int mem_inicio,
        int mem_fin,
        int es_libre
    );
extern void establecer_rango_memoria(lista_memoria lista);
extern lista_memoria first_fit(lista_memoria lista_fragmentos, lista_peticion lista_peticiones);
extern void liberar_fragmento(lista_memoria lista, char *nombre_proceso, unsigned long cantidad_peticion);
extern lista_memoria eliminar_fragmento(lista_memoria lista);
extern lista_memoria desfragmentar(lista_memoria lista);
extern int hay_memoria_suficiente(lista_peticion peticion, lista_memoria lista);
extern int es_necesario_desfragmentar(lista_peticion peticion, lista_memoria lista);
