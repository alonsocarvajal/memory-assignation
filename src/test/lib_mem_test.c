puts("FRAG");
                    if (aux_frag->es_libre == 1) {
                        if (posicion == 1) {    /* Primera posicion de la lista */
                                aux_frag->tamano_fragmento = aux_frag->tamano_fragmento - aux_pet->cantidad_peticion;
                                lista_fragmentos = insertar_fragmento_principio(lista_fragmentos,
                                                                                aux_pet->nombre_proceso,
                                                                                aux_pet->cantidad_peticion,
                                                                                0,
                                                                                0,
                                                                                0);
                                establecer_rango_memoria(lista_fragmentos);
                                break;
                        }
                        else {
                                aux_frag->tamano_fragmento = aux_frag->tamano_fragmento - aux_pet->cantidad_peticion;
                                lista_fragmentos = insertar_fragmento_posicion(lista_fragmentos,
                                                                               aux_pet->nombre_proceso,
                                                                               posicion,
                                                                               aux_pet->cantidad_peticion,
                                                                               0,
                                                                               0,
                                                                               0);
                                establecer_rango_memoria(lista_fragmentos);
                                break;
                        }
                    }



/*Algorito first fit*/
lista_memoria first_fit(lista_memoria lista_fragmentos, lista_peticion lista_peticiones)
{
    int posicion = 0, tipo_de_peticion = 0;
    lista_memoria aux_frag = NULL;
    lista_peticion aux_pet = NULL;


    /* Recorriendo las peticiones */
    for (aux_pet = lista_peticiones; aux_pet!= NULL; aux_pet= aux_pet->sgte) {
        tipo_de_peticion = obtener_tipo_peticion(aux_pet);
        for (posicion = 1, aux_frag = lista_fragmentos; aux_frag != NULL; aux_frag = aux_frag->sgte, posicion++) {
            if (tipo_de_peticion == 1) {    /* Allocate */
                /* No hay memmoria */
                if ( hay_memoria_suficiente(aux_pet, lista_fragmentos) == 0) {
                    puts("NO HAY MEMORIA DISPONIBLE");
                    break;
                }
                /* Hay memoria pero se necesita fragmentar */
                else if ( hay_memoria_suficiente(aux_pet, lista_fragmentos) == 1 ) {
                    lista_fragmentos = desfragmentar(lista_fragmentos);
                }
                /* Hay memoria suficiente */
                else if ( hay_memoria_suficiente(aux_pet, lista_fragmentos) == 2 ) {
                    if (aux_frag->es_libre == 1) {
                        puts("Memoria disponible");
                        if (posicion == 1) {    /* Primera posicion de la lista */
                            aux_frag->tamano_fragmento = aux_frag->tamano_fragmento - aux_pet->cantidad_peticion;
                            lista_fragmentos = insertar_fragmento_principio(lista_fragmentos,
                                                                            aux_pet->nombre_proceso,
                                                                            aux_pet->cantidad_peticion,
                                                                            0,
                                                                            0,
                                                                            0);
                            establecer_rango_memoria(lista_fragmentos);
                            break;
                        }
                        else {
                            aux_frag->tamano_fragmento = aux_frag->tamano_fragmento - aux_pet->cantidad_peticion;
                            lista_fragmentos = insertar_fragmento_posicion(lista_fragmentos,
                                                                           aux_pet->nombre_proceso,
                                                                           posicion,
                                                                           aux_pet->cantidad_peticion,
                                                                           0,
                                                                           0,
                                                                           0);
                            establecer_rango_memoria(lista_fragmentos);
                            break;
                        }
                    }
                }
            }
            else if (tipo_de_peticion == 0) {   /* free */
                /* LLiberar memoria */
                liberar_fragmento(lista_fragmentos, aux_pet->nombre_proceso, aux_pet->cantidad_peticion);
                establecer_rango_memoria(lista_fragmentos);
                break;
            }
        }
    }
    return lista_fragmentos;
}

