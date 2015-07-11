/* Libreria para el uso de listas */

#include <stdio.h>
#include <stdlib.h>
#include "lib_lista.h"

tipo_lista lista_vacia(void)
{
	return NULL;
}

int es_lista_vacia(tipo_lista lista)
{
	return lista == NULL;
}

tipo_lista crea_nodo(int valor)
{
	tipo_lista aux;
	aux = (tipo_lista)malloc(sizeof(t_nodo));
	if (aux != NULL) {
		aux->banda = valor;
		aux->sgte = NULL;
	}
	return aux;
}

tipo_lista insertar_principio(tipo_lista lista, int valor)
{
	tipo_lista p_nodo;

	p_nodo = crea_nodo(valor);
	p_nodo->sgte = lista;
	lista = p_nodo;
	p_nodo = NULL;
	return lista;
}

tipo_lista insertar_final(tipo_lista lista, int valor)
{
	tipo_lista p_nodo, aux;

	p_nodo = crea_nodo(valor);

	if (lista == NULL) {
		lista = p_nodo;
	}
	else if (lista->sgte == NULL) {
        lista->sgte = p_nodo;
	}
	else {
		for(aux = lista; aux->sgte != NULL; aux = aux->sgte);
		aux->sgte = p_nodo;
		aux = NULL;
	}
	p_nodo = NULL;

	return lista;
}

void imprime_lista(tipo_lista lista)
{
    puts("Lista de elementos:\n");

	tipo_lista aux;
	if ( es_lista_vacia(lista) == 1 ) {
		puts("[]");
	}
	else {
		printf("[");
		for(aux = lista; aux != NULL; aux = aux->sgte)
			printf("%d,", aux->banda);
		puts("\b]");
	}
	putchar('\n');
}

tipo_lista libera_lista(tipo_lista lista)
{
	tipo_lista aux, otro_aux;

	aux = lista;

	while (aux != NULL) {
		otro_aux = aux->sgte;
		free(aux);
		aux = otro_aux;
	}
	return NULL;
}

tipo_lista insertar_ordenada(tipo_lista lista, int valor)
{
	tipo_lista atras, aux, p_nodo;
	p_nodo = crea_nodo(valor);

	for (atras = NULL, aux = lista; aux != NULL; atras = aux, aux = aux->sgte)
		if (valor <= aux->banda) {
			/* Aqui insertamos el nodo entre atras y aux */
			p_nodo->sgte = aux;
			if (atras == NULL)
				lista = p_nodo;
			else
				atras->sgte = p_nodo;
			/* Como ya esta insertado, acabamos */
			return lista;
		}
	/* Si llegamos aqui, es que p_nodo va al final de la lista */
	p_nodo->sgte = NULL;
	if (atras == NULL)
		lista = p_nodo;
	else
		atras->sgte = p_nodo;

	return lista;
}

int largo_lista(tipo_lista lista)
{
	int contador = 0;
	tipo_lista aux;
	for (aux = lista; aux != NULL; aux = aux->sgte, contador++);
	return contador;
}

tipo_lista insertar_posicion(tipo_lista lista, int pos, int valor)
{
	int i = 0;
	tipo_lista atras, aux, p_nodo;
	p_nodo = crea_nodo(valor);

	if (pos <= largo_lista(lista)) {
		for (i = 0, atras = NULL, aux = lista; i < pos && aux != NULL; i++, atras = aux, aux = aux->sgte);
		p_nodo->sgte = aux;
		if (atras == NULL)
			lista = p_nodo;
		else
			atras->sgte = p_nodo;
	}
	return lista;
}

int buscar_elemento(tipo_lista lista, int valor)
{
	int retorno = 0;
	tipo_lista aux;

	for (aux = lista; aux != NULL; aux = aux->sgte) {
		if (aux->banda == valor)
			retorno = 1;
	}
	return retorno;
}

int localizar_posicion(tipo_lista lista, int valor)
{
	int posicion = 0, tmp = 0;
	tipo_lista aux;

	tmp = buscar_elemento(lista, valor);

	// Nos aseguramos que el nodo por lo menos existe
	if (tmp == 1) {
		aux = lista;
		while (aux->banda != valor) {
			aux = aux->sgte;
			posicion++;
		}
		return posicion;
	}
	else {
		return -1;  /* Elemento no encontrado */
	}
}

tipo_lista eliminar_elemento(tipo_lista lista, int valor)
{
	int tmp = 0;
	tipo_lista aux, otro_aux;
	tmp = buscar_elemento(lista, valor);
	if (tmp == 1) {
		if (lista->banda == valor) {
			aux = lista;
			lista = lista->sgte;
			aux->sgte = NULL;
			free(aux);
		}
		else {
			aux = lista;
			while (aux->banda != valor) {
				aux = aux->sgte;
			}
			otro_aux = lista;
			while (otro_aux != aux) {
				otro_aux = otro_aux->sgte;
			}
			otro_aux->sgte = aux->sgte;
			aux->sgte = NULL;
			free(aux);
			otro_aux = NULL;
		}
	}
	return lista;
}

tipo_lista eliminar_valor(tipo_lista lista, int valor)
{
	tipo_lista aux, otro_aux;

	otro_aux = NULL;
	aux = lista;

	while (aux != NULL) {
		if (aux->banda == valor) {
			if (otro_aux == NULL)
				lista = aux->sgte;
			else
				otro_aux->sgte = aux->sgte;
			free(aux);
			if (otro_aux == NULL)
				aux = lista;
			else
				aux = otro_aux->sgte;
		}
		else {
			otro_aux = aux;
			aux = aux->sgte;
		}
	}
	return lista;
}

tipo_lista interseccion(tipo_lista lista_a, tipo_lista lista_b)
{
	tipo_lista lista, aux;

	lista = lista_vacia();

	for(aux = lista_a; aux != NULL; aux = aux->sgte)
		lista = insertar_principio(lista, aux->banda);
	for(aux = lista_b; aux != NULL; aux = aux->sgte)
		lista = insertar_principio(lista, aux->banda);
	return lista;
}

/* Funcion: valor_psoci
 * Descripcion: Suma los nodos de una lista segun una posicion dada.
 * Entrada: Posicion desde la cual se sumara.
 * Salida: Suma.
 */
int valor_posicion_lista(tipo_lista lista, int posicion)
{
    tipo_lista aux = NULL;
    int i = largo_lista(lista);

    for (aux = lista; aux != NULL; aux = aux->sgte)
        if ( (i--) == posicion )
                break;

    return aux->banda;
}

/* Funcion: sumar_nodos
 * Descripcion: Suma los nodos de una lista segun una posicion dada.
 * Entrada: Posicion desde la cual se sumara.
 * Salida: Suma.
 */
int sumar_nodos(tipo_lista lista, int posicion)
{
    tipo_lista aux = NULL;
    int i = 0,
        suma = 0;

    for (i = posicion; i > 0; i--)
        suma = suma + valor_posicion_lista(lista, i);

    free(aux);
    return suma;
}

/* Funcion para calcular numero */
int calcular_su_numero(tipo_lista lista, int id_creacion_hebra, int numero_gritado)
{
    /* Para realizar el calculo de su banda debe
     * considerar el numero que esta guardado en la
     * variable global.
     */
     int suma_nodo_delantero = 0;

     suma_nodo_delantero = sumar_nodos(lista, id_creacion_hebra - 1);
     //printf("Hebra %d - Suma %d - Numero gritado %d\n", id_creacion_hebra, suma_nodo_delantero, numero_gritado);

     return numero_gritado - suma_nodo_delantero;
}
