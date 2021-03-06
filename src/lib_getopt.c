#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <getopt.h>
#include "lib_getopt.h"

/* Funcion para obtener la fecha del sistema */
char *obtener_fecha_inicio(void)
{
    time_t ahora;
    struct tm *ahora_tm;
    char *fecha;

    fecha = malloc(sizeof(char) * 20);
    time(&ahora);
    ahora_tm = localtime(&ahora);
    strftime(fecha, 20, "%Y-%m-%d %H:%M:%S", ahora_tm);
    return fecha;
}

/* Funcion para imprimir la ayuda del programa */
void imprimir_uso(char *nombre_programa)
{
    printf( "\nUso %s:\n"
            "-p, --peticiones=NOMBRE_ARCHIVO\t Ingresar NOMBRE_ARCHIVO que contiene las peticiones de memoria\n"
            "-a, --algoritmo=OPCION\t\t Ingresar el algoritmo a utilizar. La OPCION puede ser B (Best fit),\n"
            "\t\t\t\t F (First fit) o N (Next fit)\n"
            "-c, --cantidadmemoria=NUM\t Cantidad NUM (expresada en MBytes) de memoria a utilizar\n"
            "-s, --salida=NOMBRE_ARCHIVO\t Registro de las peticiones se almacenan en NOMBRE_ARCHIVO. Esta opcion\n"
            "\t\t\t\t no es obligatoria. Por defecto almacena los registros en un archivo\n"
            "\t\t\t\t nombrado con la fecha y hora de ejecucion del programa\n"
            "-m, --modo=OPCION\t\t Modo de ejecucion del programa. El MODO puede ser H (hablador) o S (silencioso)\n\n",
            nombre_programa);
}

void obtener_argumentos(Opcion *opciones_del_sistema, int *estado_opcion)
{
    char regex[14] = ":p:a:c:s: :m:";   /* Expresion Regural utilizada para las opciones del sistema */

    int opcion              = 0,
        p_bandera           = 0,    /* -p, --peticiones <Nombre archivo> */
        a_bandera           = 0,    /* -a, --algoritmo <B|F|N> */
        c_bandera           = 0,    /* -c, --cantidadmemoria <Cantidad de megas> */
        //s_bandera           = 0,    /* -s, --salida <Nombre archivo> (opcional: por defecto usar fecha y hora de ejecucion */
        m_bandera           = 0;    /* -m, --modo <H|S> */

    struct option longopts[] =
        {
            {"peticiones",          required_argument,  NULL,   'p'},
            {"algoritmo",           required_argument,  NULL,   'a'},
            {"cantidadmemoria",    required_argument,   NULL,   'c'},
            {"salida",              optional_argument,  NULL,   's'},
            {"modo",                required_argument,  NULL,   'm'},
            {0,0,0,0}
        };

    while ( ( opcion = getopt_long(opciones_del_sistema->argc, opciones_del_sistema->argv, regex, longopts, NULL) ) != -1 ) {
        switch (opcion) {
        case 'p':   /* -p, --peticiones */
            p_bandera = 1;
            opciones_del_sistema->archivo_peticiones = optarg;
            break;
        case 'a':   /* -a, --algoritmo <B|F|N> */
            if (optarg[0] == 'B' || optarg[0] == 'F' || optarg[0] == 'N') {
                a_bandera = 1;
                opciones_del_sistema->algoritmo = optarg[0];
            }
            break;
        case 'c':   /* -c, --cantidadmemoria <Cantidad de megas> */
            c_bandera = 1;
            opciones_del_sistema->cantidad_memoria = atoi(optarg);
            break;
        case 's':   /* -s, --salida <Nombre archivo> */
            if(optarg != NULL) {
                //s_bandera = 1;
                opciones_del_sistema->archivo_salida = optarg;
            }
            else {
                //s_bandera = 0;
                opciones_del_sistema->archivo_salida = obtener_fecha_inicio();
            }
            break;
        case 'm':   /* -m, --modo <H|S> */
            if (optarg[0] == 'H' || optarg[0] == 'S') {
                m_bandera = 1;
                opciones_del_sistema->modo = optarg[0];
            }
            break;
        case ':':   /* Problemas con argumento no ingresado */
            fprintf(stderr, "%s: opcion '-%c' requiere un argumento\n", opciones_del_sistema->nombre_programa, optopt);
            break;
        case '?':   /* Opcion invalida */
        default:
            fprintf(stderr, "%s: opcion '-%c' es invalida: ignorada\n", opciones_del_sistema->nombre_programa, optopt);
            break;
        }
    }

    /* Verificando las banderas de las opciones ingresadas. Si alguna bandera
     * es igual a 0, entonces ocurrio un error.
     */
    if (p_bandera == 0 || a_bandera == 0 || c_bandera == 0 || m_bandera == 0) {
        imprimir_uso(opciones_del_sistema->nombre_programa);
        *estado_opcion = 1;
    }
}
