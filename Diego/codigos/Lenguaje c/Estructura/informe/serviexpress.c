/*
    Nombres : Ruben Sanchez, Diego Solis, Benjamin Vasquez, Joaquin Vasquez.
    Tema : Informe Estructuras de Datos - Serviexpress
    Fecha : 03/06/2026
    Descripcion : Este programa simula la gestion de clientes en una oficina de atencion al 
    cliente llamada "Serviexpress".
    El programa utiliza una lista enlazada para manejar los clientes agendados, una cola para 
    manejar los clientes en espera, y una pila para registrar el historial de atenciones.
    El programa carga inicialmente los clientes desde archivos de texto, procesa una serie de
    operaciones y muestra un informe final con la estadística de clientes atendidos, pendientes 
    y cancelados.
*/

#include "serviexpress.h"

int total_cargados_inicial = 0; /* Cantidad total de clientes ledos exitosamente desde los archivos */
int total_cancelados = 0; /* NNmero de cancelaciones exitosas realizadas */

/* ----- Funciones auxiliares estaticas ----- */

/* Esta función convierte una cadena en el tipo de cliente correspondiente */
static int parsearTipo(const char *str){
    if(strcmp(str, "CONSULTA") == 0) return TIPO_CONSULTA;
    if(strcmp(str, "PAGO") == 0)     return TIPO_PAGO;
    if(strcmp(str, "RECLAMO") == 0)  return TIPO_RECLAMO;
    if(strcmp(str, "TRAMITE") == 0)  return TIPO_TRAMITE;
    return TIPO_CONSULTA; /* Valor por defecto si la cadena no coincide */
}

/* Esta función convierte un tipo de cliente en una cadena */
static const char* tipoAStr(int t){
    switch(t){
        case TIPO_CONSULTA: return "CONSULTA";
        case TIPO_PAGO:     return "PAGO";
        case TIPO_RECLAMO:  return "RECLAMO";
        case TIPO_TRAMITE:  return "TRAMITE";
    }
    return "DESCONOCIDO";
}

/* Esta función convierte un estado de cliente en una cadena */
static const char* estadoAStr(int e){
    switch(e){
        case ESTADO_AGENDADO:  return "AGENDADO";
        case ESTADO_EN_ESPERA: return "EN_ESPERA";
        case ESTADO_ATENDIDO:  return "ATENDIDO";
        case ESTADO_CANCELADO: return "CANCELADO";
        case ESTADO_ANULADO:   return "ANULADO";
    }
    return "DESCONOCIDO";
}

static int validarHora(const char *hora){
    int h, m;
    if(sscanf(hora, "%d:%d", &h, &m) != 2) return 0;
    if(h < 0 || h > 23 || m < 0 || m > 59) return 0;
    return 1;
}

/* Estas funciones son las encargadas de inicializar las estructuras */

void inicializarLista(ListaEnlazada *l){
    l->cabeza = l->cola = NULL;
}

void inicializarCola(Cola *c){
    c->frente = c->final = NULL;
}

void inicializarPila(Pila *p){
    p->tope = NULL;
}

/* Estas funciones son las encargadas de liberar la memoria de las estructuras */
void liberarLista(ListaEnlazada *l){
    NodoLista *actual = l->cabeza;
    while(actual){
        NodoLista *temp = actual;
        actual = actual->sig;
        free(temp);
    }
    l->cabeza = l->cola = NULL; /* Lista queda vacia */
}

void liberarCola(Cola *c){
    NodoCola *actual = c->frente;
    while(actual){
        NodoCola *temp = actual;
        actual = actual->sig;
        free(temp);
    }
    c->frente = c->final = NULL; /* Cola queda vacia */
}

void liberarPila(Pila *p){
    NodoPila *actual = p->tope;
    while(actual){
        NodoPila *temp = actual;
        actual = actual->sig;
        free(temp);
    }
    p->tope = NULL; /* Pila queda vacia */
}

/* ----- Lista enlazada ----- */

void insertarFinalLista(ListaEnlazada *l, Cliente c){
    NodoLista *nuevo = (NodoLista*) malloc(sizeof(NodoLista));
    nuevo->dato = c;
    nuevo->sig = NULL;
    if(l->cola == NULL){
        l->cabeza = l->cola = nuevo; /* Si esta la Lista vacia, nuevo nodo es cabeza y cola */
    } else{                          /* En caso contrario pasa a ser el 1er nodo */
        l->cola->sig = nuevo;
        l->cola = nuevo;
    }
}

NodoLista* buscarEnLista(ListaEnlazada *l, const char *rut, NodoLista **anterior){
    NodoLista *act = l->cabeza; 
    *anterior = NULL;
    while(act){
        if(strcmp(act->dato.rut, rut) == 0){ /* Si el rut coincide, devuelve el nodo encontrado */
            return act; 
        }
        *anterior = act;  /* Guarda el nodo anterior antes de avanzar */
        act = act->sig;
    }
    return NULL;
}

int eliminarNodoLista(ListaEnlazada *l, NodoLista *nodo, NodoLista *anterior){
    if(!nodo) return 0;
    if(anterior == NULL){  /* El nodo a eliminar es la cabeza */
        l->cabeza = nodo->sig;
        if(l->cabeza == NULL) l->cola = NULL; /* Lista quedo vacia */
    } else{
        anterior->sig = nodo->sig; /* El nodo anterior salta el nodo a eliminar */
        if(nodo == l->cola) l->cola = anterior; /* Se elimino el ultimo */
    }
    free(nodo);
    return 1;
}

int existeEnLista(ListaEnlazada *l, const char *rut){
    NodoLista *act = l->cabeza;
    while(act){
        if(strcmp(act->dato.rut, rut) == 0) return 1;  /* Si encuentra el rut, devuelve 1 */
        act = act->sig;
    }
    return 0;
}

/* ----- Cola ----- */

void encolar(Cola *c, Cliente cl){
    NodoCola *nuevo = (NodoCola*) malloc(sizeof(NodoCola));
    nuevo->dato = cl;
    nuevo->sig = NULL;
    if(c->final == NULL){ /* Si la cola esta vacia, nuevo nodo es frente y final */
        c->frente = c->final = nuevo;
    } else{ /* En caso contrario, el nuevo nodo se agrega al final 
             y se actualiza el puntero final */
        c->final->sig = nuevo;
        c->final = nuevo;
    }
}

int desencolar(Cola *c, Cliente *salida){
    if(c->frente == NULL) return 0;
    NodoCola *temp = c->frente;
    *salida = temp->dato;
    c->frente = temp->sig; /* El frente de la cola apunta al siguiente nodo */
    if(c->frente == NULL) c->final = NULL; /* Cola quedo vacia */
    free(temp);
    return 1;
}

NodoCola* buscarEnCola(Cola *c, const char *rut, NodoCola **anterior){
    NodoCola *act = c->frente;
    *anterior = NULL;
    while(act){
        if(strcmp(act->dato.rut, rut) == 0) return act; /* Si el rut coincide, 
                                                        devuelve el nodo encontrado */
        *anterior = act;
        act = act->sig;
    }
    return NULL;
}

int eliminarNodoCola(Cola *c, NodoCola *nodo, NodoCola *anterior){
    if(!nodo) return 0;
    if(anterior == NULL){  /* El nodo es el frente de la cola */
        c->frente = nodo->sig;
        if(c->frente == NULL) c->final = NULL; /* Cola quedo vacia */
    }else{
        anterior->sig = nodo->sig;
        if(nodo == c->final) c->final = anterior; /* Se elimino el ultimo */
    }
    free(nodo);
    return 1;
}

int existeEnCola(Cola *c, const char *rut){
    NodoCola *act = c->frente;
    while(act){
        if(strcmp(act->dato.rut, rut) == 0) return 1; /* Si encuentra el rut, devuelve 1 */
        act = act->sig;
    }
    return 0;
}

/* ----- Pila ----- */

void apilar(Pila *p, Cliente c){
    NodoPila *nuevo = (NodoPila*) malloc(sizeof(NodoPila));
    nuevo->dato = c;
    nuevo->sig = p->tope;  /* El nuevo nodo apunta al antiguo tope */
    p->tope = nuevo;
}

int desapilar(Pila *p, Cliente *salida){
    if(p->tope == NULL) return 0;
    NodoPila *temp = p->tope;
    *salida = temp->dato; /* El cliente a devolver es el del nodo tope */
    p->tope = temp->sig;  /* El nuevo tope es el siguiente nodo en la pila */
    free(temp);
    return 1;
}

int existeEnPila(Pila *p, const char *rut){
    NodoPila *act = p->tope;
    while(act){
        if(strcmp(act->dato.rut, rut) == 0) return 1; /* Si encuentra el rut, devuelve 1 */
        act = act->sig;
    }
    return 0;
}

/* Verificacion global */

int existeRutGlobal(ListaEnlazada *lista, Cola *cola, Pila *pila, const char *rut){
    return existeEnLista(lista, rut) || existeEnCola(cola, rut) || existeEnPila(pila, rut);
}

/* Funciones de atencion */

int atenderCliente(ListaEnlazada *lista, Cola *cola, Pila *historial, Cliente *atendido){
    if(lista->cabeza != NULL){  /* Prioridad 1: agendados */
        NodoLista *nodo = lista->cabeza;
        *atendido = nodo->dato; /* El cliente a atender es el del nodo cabeza */
        lista->cabeza = nodo->sig;
        if(lista->cabeza == NULL) lista->cola = NULL; /* Lista quedo vacia */
        free(nodo);
        atendido->estado = ESTADO_ATENDIDO; /* Cambia el estado a ATENDIDO */
        apilar(historial, *atendido);
        return 1;
    }

    if(cola->frente != NULL){  /* Prioridad 2: cola de espera */
        if(desencolar(cola, atendido)){
            atendido->estado = ESTADO_ATENDIDO; /* Cambia el estado a ATENDIDO */
            apilar(historial, *atendido); /* Registra en historial */
            return 1;
        }
    }
    return 0;
}

/* Esta función atiende al cliente con mayor prioridad (1..3) entre agendados (lista) y cola de espera */
int atenderConPrioridad(ListaEnlazada *lista, Cola *cola, Pila *historial, Cliente *atendido){
    int max_prioridad = 0;
    NodoLista *actL = lista->cabeza;
    while(actL){  /* Encuentra la maxima prioridad entre agendados */
        if(actL->dato.prioridad > max_prioridad) max_prioridad = actL->dato.prioridad; 
        actL = actL->sig; 
    }

    NodoCola *actC = cola->frente;
    while(actC){  /* Encuentra la maxima prioridad entre la cola */
        if(actC->dato.prioridad > max_prioridad) max_prioridad = actC->dato.prioridad;
        actC = actC->sig;
    }
    if(max_prioridad == 0) return 0;

    /* Buscar primero en lista (agendados) */
    NodoLista *anteriorL = NULL;
    actL = lista->cabeza;
    while(actL){
        /* Si encuentra un cliente con la maxima prioridad */
        if(actL->dato.prioridad == max_prioridad){ 
            *atendido = actL->dato;
            eliminarNodoLista(lista, actL, anteriorL); /* Elimina el nodo de la lista */
            atendido->estado = ESTADO_ATENDIDO; 
            apilar(historial, *atendido); /* Registra en historial */
            return 1;  /* Devuelve el cliente atendido */
        }
        anteriorL = actL; /* Guarda el nodo anterior lista antes de avanzar */
        actL = actL->sig;
    }

    /* Buscar en cola */
    NodoCola *anteriorC = NULL;
    actC = cola->frente;
    while(actC){
        if(actC->dato.prioridad == max_prioridad){ /* Si encuentra un cliente con la maxima prioridad */
            *atendido = actC->dato;
            eliminarNodoCola(cola, actC, anteriorC);
            atendido->estado = ESTADO_ATENDIDO;
            apilar(historial, *atendido); /* Registra en historial */
            return 1; /* Elimina el nodo de la cola y devuelve el cliente atendido */
        }
        anteriorC = actC; /* Guarda el nodo anterior cola antes de avanzar */
        actC = actC->sig;
    }
    return 0; /* no deberia ocurrir */
}

int deshacerAtencion(Pila *historial){
    if(historial->tope == NULL) return 0;
    Cliente c;
    if(!desapilar(historial, &c)) return 0;
    c.estado = ESTADO_ANULADO;  /* Cambia el estado a ANULADO */
    apilar(historial, c);       /* Lo vuelve a apilar para mantener el registro */
    return 1;
}

/* Carga de archivos iniciales */

int cargarClientesAgendados(const char *nombreArchivo, ListaEnlazada *lista, Cola *cola, Pila *pila){
    FILE *f = fopen(nombreArchivo, "r");
    if(!f){
        printf("Advertencia: no se pudo abrir %s\n", nombreArchivo);
        return 0;
    }
    char linea[256];
    int cargados = 0;
    while(fgets(linea, sizeof(linea), f)){ /* Lee cada linea del archivo */
        linea[strcspn(linea, "\r\n")] = 0; /* Elimina salto de linea independiente del sistema operativo */
        if(strlen(linea) == 0) continue; 

        Cliente c;
        char tipoStr[15];
        /* Parsea los datos del cliente */
        if(sscanf(linea, "%[^;];%[^;];%[^;];%[^;];%d", c.rut, c.nombre, tipoStr, c.hora, &c.prioridad) != 5){
            printf("Formato incorrecto en agendados: %s\n", linea);
            continue;
        }
        /* Valida los datos del cliente */
        if(!validarHora(c.hora) || c.prioridad < 1 || c.prioridad > 3){
            printf("Datos invalidos en agendados: %s\n", linea);
            continue;
        }
        /* Verifica que el RUT no exista ya en ninguna de las estructuras */
        if(existeRutGlobal(lista, cola, pila, c.rut)){
            printf("RUT duplicado en agendados: %s\n", c.rut); 
            continue;
        }
        c.tipo = parsearTipo(tipoStr);/* Convierte la cadena del tipo a su valor entero correspondiente */
        c.estado = ESTADO_AGENDADO;
        insertarFinalLista(lista, c);/* Inserta el cliente al final de la lista de agendados */
        cargados++;
    }
    fclose(f);
    return cargados; /* Devuelve la cantidad de clientes cargados exitosamente */
}

int cargarClientesLlegada(const char *nombreArchivo, Cola *cola, ListaEnlazada *lista, Pila *pila){
    FILE *f = fopen(nombreArchivo, "r");
    if(!f){
        printf("Advertencia: no se pudo abrir %s\n", nombreArchivo);
        return 0;
    }
    char linea[256];
    int cargados = 0;

    while(fgets(linea, sizeof(linea), f)){
        linea[strcspn(linea, "\r\n")] = 0; /* Elimina salto de linea */
        if(strlen(linea) == 0) continue;

        Cliente c;
        char tipoStr[15];
        /* Parsea los datos del cliente */
        if(sscanf(linea, "%[^;];%[^;];%[^;];%[^;];%d", c.rut, c.nombre, tipoStr, c.hora, &c.prioridad) != 5){
            printf("Formato incorrecto en llegada: %s\n", linea);
            continue;
        }
        /* Valida los datos del cliente */
        if(!validarHora(c.hora) || c.prioridad < 1 || c.prioridad > 3){
            printf("Datos invalidos en llegada: %s\n", linea);
            continue;
        }
        /* Verifica que el RUT no exista ya en ninguna de las estructuras */
        if(existeRutGlobal(lista, cola, pila, c.rut)){
            printf("RUT duplicado en llegada: %s\n", c.rut);
            continue;
        }
        c.tipo = parsearTipo(tipoStr); /* Convierte la cadena del tipo a su valor entero correspondiente */
        c.estado = ESTADO_EN_ESPERA;
        encolar(cola, c); /* Encola el cliente en la cola de espera */
        cargados++;
    }
    fclose(f);
    return cargados; /* Devuelve la cantidad de clientes cargados exitosamente */
}

/* Procesamiento de operaciones */

void procesarOperaciones(const char *nombreArchivo,ListaEnlazada *lista, Cola *cola, Pila *historial,FILE *logFile){
    FILE *f = fopen(nombreArchivo, "r");
    if(!f){
        fprintf(logFile, "ERROR: No se pudo abrir el archivo de operaciones %s\n", nombreArchivo);
        return;
    }

    char linea[256];
    int numLinea = 0;
    /* Lee cada linea del archivo de operaciones */
    while(fgets(linea, sizeof(linea), f)){
        numLinea++;
        linea[strcspn(linea, "\r\n")] = 0; /* Elimina salto de linea */
        if(strlen(linea) == 0) continue;

        char comando[30];
        char *token = strtok(linea, ";"); /* El primer token es el comando */

        /* Si no hay token (dato), el formato es incorrecto */
        if(!token){
            fprintf(logFile, "Linea %d: Formato incorrecto.\n", numLinea);
            continue;
        }
        strcpy(comando, token); /* Copia el comando a una variable para compararlo */

        if(strcmp(comando, "AGENDAR") == 0){
            char *rut = strtok(NULL, ";");      /* El siguiente token es el RUT */
            char *nombre = strtok(NULL, ";");   /* Luego el nombre */
            char *tipoStr = strtok(NULL, ";");  /* Luego el tipo de consulta */
            char *hora = strtok(NULL, ";");     /* Luego la hora */
            char *priorStr = strtok(NULL, ";"); /* Finalmente la prioridad */

            /* Verifica que todos los parametros esten presentes */
            if(!rut || !nombre || !tipoStr || !hora || !priorStr){
                fprintf(logFile, "AGENDAR: Faltan parametros.\n");
                continue;
            }
            int prioridad = atoi(priorStr); /* Convierte la prioridad a entero */
            if(!validarHora(hora) || prioridad < 1 || prioridad > 3){
                fprintf(logFile, "AGENDAR %s: Datos invalidos.\n", rut);
                continue;
            }
            /* Verifica que el RUT no exista ya en ninguna de las estructuras */
            if(existeRutGlobal(lista, cola, historial, rut)){
                fprintf(logFile, "AGENDAR %s: RUT duplicado.\n", rut);
                continue;
            }

            /* Crea un cliente con los datos parseados y lo inserta al final de la lista de agendados */
            Cliente c;
            strcpy(c.rut, rut);
            strcpy(c.nombre, nombre);
            c.tipo = parsearTipo(tipoStr);
            strcpy(c.hora, hora);
            c.prioridad = prioridad;
            c.estado = ESTADO_AGENDADO;
            insertarFinalLista(lista, c);
            fprintf(logFile, "AGENDAR: Cliente %s agregado a agendados.\n", rut);

            
        }else if(strcmp(comando, "CANCELAR_AGENDA") == 0){ 
            /* Comando para cancelar una cita agendada */

            char *rut = strtok(NULL, ";");
            if(!rut){
                fprintf(logFile, "CANCELAR_AGENDA: Faltan parametros.\n");
                continue;
            }
            NodoLista *anterior = NULL;
            NodoLista *nodo = buscarEnLista(lista, rut, &anterior); /* Busca el cliente en la lista de agendados */
            if(!nodo){
                fprintf(logFile, "CANCELAR_AGENDA %s: No encontrado en agendados.\n", rut);
                continue;
            }
            eliminarNodoLista(lista, nodo, anterior); 
            total_cancelados++;
            fprintf(logFile, "CANCELAR_AGENDA: Cliente %s cancelado.\n", rut);

        }else if(strcmp(comando, "LLEGADA") == 0){
            /* Comando para registrar la llegada de un cliente a la cola de espera */

            char *rut = strtok(NULL, ";");      /* El siguiente token es el RUT */
            char *nombre = strtok(NULL, ";");   /* Luego el nombre */
            char *tipoStr = strtok(NULL, ";");  /* Luego el tipo de consulta */
            char *hora = strtok(NULL, ";");     /* Luego la hora */
            char *priorStr = strtok(NULL, ";"); /* Finalmente la prioridad */

             /* Verifica que todos los parametros esten presentes */
            if(!rut || !nombre || !tipoStr || !hora || !priorStr){
                fprintf(logFile, "LLEGADA: Faltan parametros.\n");
                continue;
            }
            int prioridad = atoi(priorStr); /* Convierte la prioridad a entero */
            if(!validarHora(hora) || prioridad < 1 || prioridad > 3){
                fprintf(logFile, "LLEGADA %s: Datos invalidos.\n", rut);
                continue;
            }
            /* Verifica que el RUT no exista ya en ninguna de las estructuras */
            if(existeRutGlobal(lista, cola, historial, rut)){
                fprintf(logFile, "LLEGADA %s: RUT duplicado.\n", rut);
                continue;
            }
            
            /* Crea un cliente con los datos parseados y lo encola en la cola de espera */
            Cliente c;
            strcpy(c.rut, rut);
            strcpy(c.nombre, nombre);
            c.tipo = parsearTipo(tipoStr);
            strcpy(c.hora, hora);
            c.prioridad = prioridad;
            c.estado = ESTADO_EN_ESPERA;
            encolar(cola, c);
            fprintf(logFile, "LLEGADA: Cliente %s encolado.\n", rut);

        }else if(strcmp(comando, "ATENDER") == 0){
            /* Comando para atender al siguiente cliente segun el orden de prioridad (agendados primero, luego cola) */
            
            Cliente atendido;
            if(atenderCliente(lista, cola, historial, &atendido)){
                /* Si se atendio a un cliente, se registra en el log */
                fprintf(logFile, "ATENDER: Atendido %s (%s).\n", atendido.rut, tipoAStr(atendido.tipo));
            } else{
                fprintf(logFile, "ATENDER: No hay clientes para atender.\n");
            }

        }else if(strcmp(comando, "ATENDER_PRIORIDAD") == 0){
            /* Comando para atender al cliente con mayor prioridad (1..3) entre agendados y cola de espera */

            Cliente atendido;
            if(atenderConPrioridad(lista, cola, historial, &atendido)){
                /* Si se atendio a un cliente, se registra en el log */

                fprintf(logFile, "ATENDER_PRIORIDAD: Atendido %s (%s) prioridad %d.\n",
                        atendido.rut, tipoAStr(atendido.tipo), atendido.prioridad);
            }else{
                fprintf(logFile, "ATENDER_PRIORIDAD: No hay clientes para atender.\n");
            }

        }else if(strcmp(comando, "DESHACER_ATENCION") == 0){
            /* Comando para deshacer la última atención realizada */

            if(deshacerAtencion(historial)){ 
                /* Si se pudo deshacer una atención, se registra en el log */

                Cliente c = historial->tope->dato; /* Cliente recién anulado (tope actual) */
                fprintf(logFile, "DESHACER_ATENCION: Atención de %s anulada.\n", c.rut);
            }else{
                fprintf(logFile, "DESHACER_ATENCION: No hay atenciones que deshacer.\n");
            }

        }else if(strcmp(comando, "BUSCAR_CLIENTE") == 0){
            /* Comando para buscar un cliente por su RUT */

            char *rut = strtok(NULL, ";");
            if(!rut){
                fprintf(logFile, "BUSCAR_CLIENTE: RUT faltante.\n");
                continue;
            }
            /* Buscar en lista */
            NodoLista *anteriorL;
            NodoLista *nodoL = buscarEnLista(lista, rut, &anteriorL);/* Se busca en la lista de agendados */
            if(nodoL){
                Cliente c = nodoL->dato;
                fprintf(logFile, "BUSCAR %s: Encontrado en AGENDADOS - %s, %s, %s, prioridad %d\n",
                        rut, c.nombre, tipoAStr(c.tipo), c.hora, c.prioridad); /* Si se encuentra en la lista de agendados */
                continue;
            }
            /* Buscar en cola */
            NodoCola *anteriorC;
            NodoCola *nodoC = buscarEnCola(cola, rut, &anteriorC); /* Se busca en la cola de espera */
            if(nodoC){
                Cliente c = nodoC->dato;
                fprintf(logFile, "BUSCAR %s: Encontrado en COLA - %s, %s, %s, prioridad %d\n",
                        rut, c.nombre, tipoAStr(c.tipo), c.hora, c.prioridad); /* Si se encuentra en la cola */
                continue;
            }
            /* Buscar en pila */
            if(existeEnPila(historial, rut)){/* Se busca en el historial */
                NodoPila *act = historial->tope;
                while(act){
                    if(strcmp(act->dato.rut, rut) == 0){/* Si se encuentra en el historial, se muestra su estado actual (ATENDIDO o ANULADO) */
                        Cliente c = act->dato;
                        fprintf(logFile, "BUSCAR %s: Encontrado en HISTORIAL (%s) - %s, %s, %s, prioridad %d\n",
                                rut, estadoAStr(c.estado), c.nombre, tipoAStr(c.tipo), c.hora, c.prioridad);
                                /* Si se encuentra en el historial, se muestra su estado actual (ATENDIDO o ANULADO) */
                        break;
                    }
                    act = act->sig;
                }
            }else{
                fprintf(logFile, "BUSCAR %s: No encontrado.\n", rut);
            }

        }else if(strcmp(comando, "MOSTRAR_ESTADO") == 0){
            /* Mostrar estado actual */

            fprintf(logFile, "=== ESTADO ACTUAL ===\n");
            fprintf(logFile, "Agendados pendientes:\n");
            NodoLista *actL = lista->cabeza;

            /* Si no hay clientes agendados pendientes, se indica que esta vacio */
            if(!actL) fprintf(logFile, "  (vacio)\n");
            while(actL){
                Cliente c = actL->dato;
                fprintf(logFile, "  %s - %s (%s) %s\n", c.rut, c.nombre, tipoAStr(c.tipo), c.hora);
                actL = actL->sig;
            }
            fprintf(logFile, "Cola de espera:\n");
            NodoCola *actC = cola->frente;

            /* Si no hay clientes agendados pendientes, se indica que esta vacio */
            if(!actC) fprintf(logFile, "  (vacio)\n");
            while(actC){
                Cliente c = actC->dato;
                fprintf(logFile, "  %s - %s (%s) %s\n", c.rut, c.nombre, tipoAStr(c.tipo), c.hora);
                actC = actC->sig;
            }
            fprintf(logFile, "Historial (ultimos primero):\n");
            NodoPila *actP = historial->tope;
            /* Si no hay clientes agendados pendientes, se indica que esta vacio */
            if(!actP) fprintf(logFile, "  (vacio)\n");
            while(actP){
                Cliente c = actP->dato;
                fprintf(logFile, "  %s - %s (%s) estado: %s\n", c.rut, c.nombre, tipoAStr(c.tipo), estadoAStr(c.estado));
                actP = actP->sig;
            }
            fprintf(logFile, "========================\n");
        }else{
            fprintf(logFile, "Linea %d: Comando desconocido '%s'\n", numLinea, comando);
        }
    }
    fclose(f);
}

/* Generacion de reportes finales */

void generarReporteFinal(const char *nombreArchivo, ListaEnlazada *lista, Cola *cola, Pila *historial){
    FILE *f = fopen(nombreArchivo, "w");
    if(!f) return;
    fprintf(f, "=== REPORTE FINAL ===\n\n");

    fprintf(f, "Clientes agendados pendientes:\n");
    NodoLista *actL = lista->cabeza;
    /* Si no hay clientes agendados pendientes, se indica que esta vacio */
    if(!actL) fprintf(f, "  Ninguno.\n");
    while(actL){
        Cliente c = actL->dato;/* Recorre la lista de clientes agendados pendientes */
        fprintf(f, "  %s - %s, %s, %s, prioridad %d\n", c.rut, c.nombre, tipoAStr(c.tipo), c.hora, c.prioridad);
        actL = actL->sig;
    }

    fprintf(f, "\nClientes en cola de espera:\n");
    NodoCola *actC = cola->frente;
    /* Si no hay clientes en la cola de espera, se indica que esta vacio */
    if(!actC) fprintf(f, "  Ninguno.\n");
    while(actC){
        Cliente c = actC->dato; /* Recorre la cola de espera */
        fprintf(f, "  %s - %s, %s, %s, prioridad %d\n", c.rut, c.nombre, tipoAStr(c.tipo), c.hora, c.prioridad);
        actC = actC->sig;
    }

    fprintf(f, "\nHistorial de atenciones (orden LIFO):\n");
    NodoPila *actP = historial->tope;
    /* Si no hay clientes agendados pendientes, se indica que esta vacio */
    if(!actP) fprintf(f, "  Ninguna.\n");
    while(actP){
        Cliente c = actP->dato; /* Recorre el historial de atenciones (pila) */
        fprintf(f, "  %s - %s, %s, estado: %s\n", c.rut, c.nombre, tipoAStr(c.tipo), estadoAStr(c.estado));
        actP = actP->sig;
    }

    fprintf(f, "\nAtenciones anuladas:\n");
    actP = historial->tope; /* Recorre el historial de atenciones (pila) */
    int hayAnulados = 0;
    /* Busca atenciones con estado ANULADO */
    while(actP){
        if(actP->dato.estado == ESTADO_ANULADO){
            /* Si encuentra una atencion anulada, la muestra en el reporte */
            
            fprintf(f, "  %s - %s\n", actP->dato.rut, actP->dato.nombre); 
            hayAnulados = 1;
        }
        actP = actP->sig;
    }
    if(!hayAnulados) fprintf(f, "  Ninguna.\n");

    fclose(f);
}

void generarEstadisticas(const char *nombreArchivo, ListaEnlazada *lista, Cola *cola, Pila *historial,int totalInicial){
    FILE *f = fopen(nombreArchivo, "w");
    if(!f) return;

    int agendadosPend = 0;
    NodoLista *actL = lista->cabeza; /* Cuenta la cantidad de clientes agendados pendientes */
    while(actL){ agendadosPend++; actL = actL->sig; }

    int colaCount = 0;
    NodoCola *actC = cola->frente; /* Cuenta la cantidad de clientes en la cola de espera */
    while(actC){ colaCount++; actC = actC->sig; }

    int atendidos = 0, anulados = 0;
    int tipoCount[4] = {0};   /* indices: 0=CONSULTA, 1=PAGO, 2=RECLAMO, 3=TRAMITE */
    NodoPila *actP = historial->tope; /* Recorre el historial de atenciones para contar atendidos, anulados y acumular por tipo de solicitud */
    
    /* Recorre el historial de atenciones */
    while(actP){ 
        if(actP->dato.estado == ESTADO_ATENDIDO){
            atendidos++;
            tipoCount[actP->dato.tipo]++; /* Acumula por tipo de solicitud */
        }else if(actP->dato.estado == ESTADO_ANULADO){
            anulados++;
        }
        actP = actP->sig;
    }

    /* Total pendientes es la suma de agendados pendientes y clientes en cola */
    int pendientes = agendadosPend + colaCount; 

    fprintf(f, "=== ESTADISTICAS ===\n\n");
    fprintf(f, "Total cargados inicialmente: %d\n", totalInicial);
    fprintf(f, "Total agendados (pendientes actuales): %d\n", agendadosPend);
    fprintf(f, "Total en cola (pendientes actuales): %d\n", colaCount);
    fprintf(f, "Total atendidos: %d\n", atendidos);
    fprintf(f, "Total cancelados: %d\n", total_cancelados);
    fprintf(f, "Total anulados (deshechos): %d\n", anulados);
    fprintf(f, "Total pendientes (agendados + cola): %d\n", pendientes);
    fprintf(f, "\nAtendidos por tipo de solicitud:\n");
    fprintf(f, "  CONSULTA: %d\n", tipoCount[TIPO_CONSULTA]);
    fprintf(f, "  PAGO:     %d\n", tipoCount[TIPO_PAGO]);
    fprintf(f, "  RECLAMO:  %d\n", tipoCount[TIPO_RECLAMO]);
    fprintf(f, "  TRAMITE:  %d\n", tipoCount[TIPO_TRAMITE]);

    fclose(f);
}