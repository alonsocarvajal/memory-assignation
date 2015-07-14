/* Estructura utilizada para las opciones del sistema */
typedef struct opcion {
    char *nombre_programa;
    char *archivo_peticiones;
    char *archivo_salida;
    char algoritmo;
    char modo;
    unsigned long cantidad_memoria;
}Opcion;

extern char *obtener_fecha_inicio(void);
extern void imprimir_uso(int p_bandera, int a_bandera, int c_bandera, int s_bandera, int m_bandera, char *nombre_programa);
extern void imprimir_ayuda(char *nombre_programa);
extern Opcion *obtener_argumentos(Opcion *opciones_del_sistema);


