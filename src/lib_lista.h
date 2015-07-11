struct nodo {
        int valor;
        struct nodo *sgte;
};

typedef struct nodo t_nodo;
typedef t_nodo *tipo_lista;  /* Equivalente a Struct Nodo *Lista */


extern tipo_lista lista_vacia(void);
extern int es_lista_vacia(tipo_lista lista);
extern tipo_lista crea_nodo(int valor);
extern tipo_lista insertar_principio(tipo_lista lista, int valor);
extern tipo_lista insertar_final(tipo_lista lista, int valor);
extern void imprime_lista(tipo_lista lista);
extern tipo_lista libera_lista(tipo_lista lista);
extern tipo_lista insertar_ordenada(tipo_lista lista, int valor);
extern tipo_lista insertar_posicion(tipo_lista lista, int pos, int valor);
extern int largo_lista(tipo_lista lista);
extern int buscar_elemento(tipo_lista lista, int valor);
extern int localizar_posicion(tipo_lista lista, int valor);
extern tipo_lista eliminar_elemento(tipo_lista lista, int valor);
extern tipo_lista eliminar_valor(tipo_lista lista, int valor);
extern tipo_lista interseccion(tipo_lista lista_a, tipo_lista lista_b);
extern int valor_posicion_lista(tipo_lista lista, int posicion);
extern int sumar_nodos(tipo_lista lista, int posicion);
int calcular_su_numero(tipo_lista lista, int id_creacion_hebra, int numero_gritado);
