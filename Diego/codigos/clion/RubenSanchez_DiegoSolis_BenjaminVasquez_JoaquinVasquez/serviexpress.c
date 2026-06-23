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

/* Variables globales para estadisticas acumuladas */
int total_cargados_inicial = 0;   /* Total de clientes cargados desde archivos al inicio */
int total_agendados_acum = 0;     /* Total de clientes que han estado en lista de agendados (carga inicial + AGENDAR) */
int total_cola_acum = 0;          /* Total de clientes que han estado en cola (carga inicial + LLEGADA) */
int total_cancelados = 0;         /* Numero de cancelaciones exitosas realizadas */
int total_anulados = 0;           /* Numero de atenciones anuladas exitosamente */

/* --------------------- Funciones auxiliares estaticas --------------------- */

/* Convierte una cadena al tipo de solicitud correspondiente. Retorna -1 si no es valido. */
static int parsearTipo(const char *str) {
    if (strcmp(str, "CONSULTA") == 0) return TIPO_CONSULTA;
    if (strcmp(str, "PAGO") == 0)     return TIPO_PAGO;
    if (strcmp(str, "RECLAMO") == 0)  return TIPO_RECLAMO;
    if (strcmp(str, "TRAMITE") == 0)  return TIPO_TRAMITE;
    return -1;  /* Tipo invalido (no coincide con ninguno) */
}

/* Convierte un tipo de solicitud a su representacion en cadena (para mostrar) */
static const char* tipoAStr(int t) {
    switch(t) {
        case TIPO_CONSULTA: return "CONSULTA";
        case TIPO_PAGO:     return "PAGO";
        case TIPO_RECLAMO:  return "RECLAMO";
        case TIPO_TRAMITE:  return "TRAMITE";
        default:            return "DESCONOCIDO";
    }
}

/* Convierte un estado de cliente a su representacion en cadena */
static const char* estadoAStr(int e) {
    switch(e) {
        case ESTADO_AGENDADO:  return "AGENDADO";
        case ESTADO_EN_ESPERA: return "EN_ESPERA";
        case ESTADO_ATENDIDO:  return "ATENDIDO";
        case ESTADO_CANCELADO: return "CANCELADO";
        case ESTADO_ANULADO:   return "ANULADO";
        default:               return "DESCONOCIDO";
    }
}

/* Valida que la hora tenga formato HH:MM y valores correctos (00:00 a 23:59) */
static int validarHora(const char *hora) {
    int h, m;
    if (strlen(hora) != 5 || hora[2] != ':') return 0;
    if (sscanf(hora, "%d:%d", &h, &m) != 2) return 0;
    if (h < 0 || h > 23 || m < 0 || m > 59) return 0;
    return 1;
}

/* Copia una cadena de forma segura evitando desbordamiento (agrega terminador nulo) */
static void copiarCadena(char *dest, const char *src, size_t tam) {
    strncpy(dest, src, tam - 1);  /* Copia maximo tam-1 caracteres */
    dest[tam - 1] = '\0';         /* Asegura terminacion nula */
}

/* --------------------- Inicializacion y liberacion de estructuras --------------------- */

/* Inicializa una lista enlazada vacia (cabeza y cola NULL) */
void inicializarLista(ListaEnlazada *l) {
    l->cabeza = l->cola = NULL;
}

/* Inicializa una cola vacia (frente y final NULL) */
void inicializarCola(Cola *c) {
    c->frente = c->final = NULL;
}

/* Inicializa una pila vacia (tope NULL) */
void inicializarPila(Pila *p) {
    p->tope = NULL;
}

/* Libera toda la memoria utilizada por la lista enlazada */
void liberarLista(ListaEnlazada *l) {
    NodoLista *actual = l->cabeza;
    while (actual) {                               /* Recorre cada nodo de la lista */
        NodoLista *temp = actual;                 /* Guarda referencia al nodo actual */
        actual = actual->sig;                     /* Avanza al siguiente nodo */
        free(temp);                               /* Libera el nodo actual */
    }
    l->cabeza = l->cola = NULL;                   /* Deja la lista en estado consistente */
}

/* Libera toda la memoria utilizada por la cola */
void liberarCola(Cola *c) {
    NodoCola *actual = c->frente;
    while (actual) {                               /* Recorre cada nodo de la cola */
        NodoCola *temp = actual;
        actual = actual->sig;
        free(temp);
    }
    c->frente = c->final = NULL;
}

/* Libera toda la memoria utilizada por la pila */
void liberarPila(Pila *p) {
    NodoPila *actual = p->tope;
    while (actual) {                               /* Recorre cada nodo de la pila */
        NodoPila *temp = actual;
        actual = actual->sig;
        free(temp);
    }
    p->tope = NULL;
}

/* --------------------- Operaciones sobre lista simplemente enlazada --------------------- */

/* Inserta un cliente al final de la lista enlazada (operacion eficiente con puntero a cola) */
void insertarFinalLista(ListaEnlazada *l, Cliente c) {
    NodoLista *nuevo = (NodoLista*)malloc(sizeof(NodoLista));
    nuevo->dato = c;
    nuevo->sig = NULL;
    if (l->cola == NULL) {         /* Lista vacia */
        l->cabeza = l->cola = nuevo;
    } else {                       /* Lista no vacia: enlazar al final y actualizar cola */
        l->cola->sig = nuevo;
        l->cola = nuevo;
    }
}

/* Busca un cliente por RUT en la lista. Devuelve el nodo encontrado y su anterior (para posible eliminacion) */
NodoLista* buscarEnLista(ListaEnlazada *l, const char *rut, NodoLista **anterior) {
    NodoLista *act = l->cabeza;
    *anterior = NULL;
    while (act) {                                  /* Recorre la lista hasta encontrar el RUT o llegar al final */
        if (strcmp(act->dato.rut, rut) == 0) return act;  /* Encontrado */
        *anterior = act;                           /* Actualizar anterior antes de avanzar */
        act = act->sig;
    }
    return NULL;  /* No encontrado */
}

/* Elimina un nodo especifico de la lista (dado el nodo y su anterior). Retorna 1 si exito. */
int eliminarNodoLista(ListaEnlazada *l, NodoLista *nodo, NodoLista *anterior) {
    if (!nodo) return 0;
    if (anterior == NULL) {        /* El nodo a eliminar es la cabeza */
        l->cabeza = nodo->sig;
        if (l->cabeza == NULL) l->cola = NULL;  /* Lista quedo vacia */
    } else {
        anterior->sig = nodo->sig; /* Saltar el nodo */
        if (nodo == l->cola) l->cola = anterior;  /* Se elimino el ultimo */
    }
    free(nodo);
    return 1;
}

/* Verifica si un RUT existe en la lista enlazada (busqueda simple) */
int existeEnLista(ListaEnlazada *l, const char *rut) {
    NodoLista *act = l->cabeza;
    while (act) {                                  /* Recorre la lista buscando el RUT */
        if (strcmp(act->dato.rut, rut) == 0) return 1;
        act = act->sig;
    }
    return 0;
}

/* --------------------- Operaciones sobre cola FIFO --------------------- */

/* Encola un cliente al final de la cola (puntero final optimiza insercion) */
void encolar(Cola *c, Cliente cl) {
    NodoCola *nuevo = (NodoCola*)malloc(sizeof(NodoCola));
    nuevo->dato = cl;
    nuevo->sig = NULL;
    if (c->final == NULL) {        /* Cola vacia: frente y final apuntan al nuevo */
        c->frente = c->final = nuevo;
    } else {                       /* Cola no vacia: agregar al final y actualizar puntero final */
        c->final->sig = nuevo;
        c->final = nuevo;
    }
}

/* Desencola el primer cliente de la cola. Retorna 1 y lo devuelve en salida, o 0 si cola vacia. */
int desencolar(Cola *c, Cliente *salida) {
    if (c->frente == NULL) return 0;
    NodoCola *temp = c->frente;
    *salida = temp->dato;
    c->frente = temp->sig;         /* Avanzar el frente */
    if (c->frente == NULL) c->final = NULL;  /* Cola quedo vacia */
    free(temp);
    return 1;
}

/* Busca un cliente por RUT en la cola. Devuelve nodo y su anterior (para eliminacion arbitraria, necesaria para prioridad) */
NodoCola* buscarEnCola(Cola *c, const char *rut, NodoCola **anterior) {
    NodoCola *act = c->frente;
    *anterior = NULL;
    while (act) {                                  /* Recorre la cola buscando el RUT */
        if (strcmp(act->dato.rut, rut) == 0) return act;
        *anterior = act;
        act = act->sig;
    }
    return NULL;
}

/* Elimina un nodo especifico de la cola (usado en atencion por prioridad). Retorna 1 si exito. */
int eliminarNodoCola(Cola *c, NodoCola *nodo, NodoCola *anterior) {
    if (!nodo) return 0;
    if (anterior == NULL) {        /* El nodo es el frente */
        c->frente = nodo->sig;
        if (c->frente == NULL) c->final = NULL;
    } else {
        anterior->sig = nodo->sig;
        if (nodo == c->final) c->final = anterior;  /* Se elimino el ultimo */
    }
    free(nodo);
    return 1;
}

/* Verifica si un RUT existe en la cola */
int existeEnCola(Cola *c, const char *rut) {
    NodoCola *act = c->frente;
    while (act) {                                  /* Recorre la cola buscando el RUT */
        if (strcmp(act->dato.rut, rut) == 0) return 1;
        act = act->sig;
    }
    return 0;
}

/* --------------------- Operaciones sobre pila LIFO --------------------- */

/* Apila un cliente en el tope de la pila (insercion al inicio) */
void apilar(Pila *p, Cliente c) {
    NodoPila *nuevo = (NodoPila*)malloc(sizeof(NodoPila));
    nuevo->dato = c;
    nuevo->sig = p->tope;   /* El nuevo nodo apunta al antiguo tope */
    p->tope = nuevo;        /* Actualizar tope */
}

/* Desapila el cliente del tope. Retorna 1 y lo devuelve en salida, o 0 si pila vacia. */
int desapilar(Pila *p, Cliente *salida) {
    if (p->tope == NULL) return 0;
    NodoPila *temp = p->tope;
    *salida = temp->dato;
    p->tope = temp->sig;    /* El tope ahora es el siguiente nodo */
    free(temp);
    return 1;
}

/* Verifica si un RUT existe en la pila (recorrido completo) */
int existeEnPila(Pila *p, const char *rut) {
    NodoPila *act = p->tope;
    while (act) {                                  /* Recorre la pila desde el tope hacia abajo */
        if (strcmp(act->dato.rut, rut) == 0) return 1;
        act = act->sig;
    }
    return 0;
}

/* --------------------- Verificacion global de RUT duplicado --------------------- */

/* Comprueba si un RUT ya existe en lista de agendados, cola de espera o historial (pila) */
int existeRutGlobal(ListaEnlazada *lista, Cola *cola, Pila *historial, const char *rut) {
    return existeEnLista(lista, rut) || existeEnCola(cola, rut) || existeEnPila(historial, rut);
}

/* --------------------- Funciones de atencion de clientes --------------------- */

/* Atiende al primer cliente: prioridad a agendados (lista), luego cola. Retorna 1 si atendio, 0 si no hay clientes. */
int atenderCliente(ListaEnlazada *lista, Cola *cola, Pila *historial, Cliente *atendido) {
    /* 1. Intentar atender desde lista de agendados (primer elemento) */
    if (lista->cabeza != NULL) {
        NodoLista *nodo = lista->cabeza;
        *atendido = nodo->dato;
        lista->cabeza = nodo->sig;   /* Eliminar cabeza */
        if (lista->cabeza == NULL) lista->cola = NULL;  /* Actualizar cola si lista vacia */
        free(nodo);
        atendido->estado = ESTADO_ATENDIDO;
        apilar(historial, *atendido); /* Registrar en historial */
        return 1;
    }
    /* 2. Si no hay agendados, atender desde cola */
    if (cola->frente != NULL) {
        if (desencolar(cola, atendido)) {
            atendido->estado = ESTADO_ATENDIDO;
            apilar(historial, *atendido);
            return 1;
        }
    }
    return 0;  /* No hay clientes disponibles */
}

/* Atiende al cliente con mayor prioridad (1..3). Empate: prioridad agendado sobre cola. */
int atenderConPrioridad(ListaEnlazada *lista, Cola *cola, Pila *historial, Cliente *atendido) {
    int max_prioridad = 0;
    /* Primera pasada: recorrer lista de agendados para encontrar la máxima prioridad */
    NodoLista *actL = lista->cabeza;
    while (actL) {                                 /* Recorre lista de agendados */
        if (actL->dato.prioridad > max_prioridad) max_prioridad = actL->dato.prioridad;
        actL = actL->sig;
    }
    /* Recorrer cola de espera para encontrar la máxima prioridad */
    NodoCola *actC = cola->frente;
    while (actC) {                                 /* Recorre cola de espera */
        if (actC->dato.prioridad > max_prioridad) max_prioridad = actC->dato.prioridad;
        actC = actC->sig;
    }
    if (max_prioridad == 0) return 0;  /* No hay clientes */

    /* Segunda pasada: buscar en lista (agendados) el primero con esa prioridad */
    NodoLista *anteriorL = NULL;
    actL = lista->cabeza;
    while (actL) {                                 /* Recorre lista buscando prioridad maxima */
        if (actL->dato.prioridad == max_prioridad) {
            *atendido = actL->dato;
            eliminarNodoLista(lista, actL, anteriorL);  /* Eliminar de la lista */
            atendido->estado = ESTADO_ATENDIDO;
            apilar(historial, *atendido);
            return 1;
        }
        anteriorL = actL;
        actL = actL->sig;
    }

    /* Si no se encontro en lista, buscar en cola */
    NodoCola *anteriorC = NULL;
    actC = cola->frente;
    while (actC) {                                 /* Recorre cola buscando prioridad maxima */
        if (actC->dato.prioridad == max_prioridad) {
            *atendido = actC->dato;
            eliminarNodoCola(cola, actC, anteriorC); /* Eliminar de la cola */
            atendido->estado = ESTADO_ATENDIDO;
            apilar(historial, *atendido);
            return 1;
        }
        anteriorC = actC;
        actC = actC->sig;
    }
    return 0; /* No deberia ocurrir */
}

/* Deshace la ultima atencion: la saca del historial, cambia su estado a ANULADO y la guarda en pila de anulados */
int deshacerAtencion(Pila *historial, Pila *anulados, FILE *logFile) {
    if (historial->tope == NULL) return 0;
    Cliente c;
    if (!desapilar(historial, &c)) return 0;   /* Extraer ultimo atendido */
    c.estado = ESTADO_ANULADO;
    apilar(anulados, c);                       /* Guardar en pila separada para reporte */
    total_anulados++;
    fprintf(logFile, "DESHACER_ATENCION: Atencion de %s anulada.\n", c.rut);
    return 1;
}

/* --------------------- Carga de archivos iniciales --------------------- */

/* Lee el archivo de clientes agendados, valida cada linea y los inserta en la lista enlazada */
int cargarClientesAgendados(const char *nombreArchivo, ListaEnlazada *lista,
                            Cola *cola, Pila *historial, FILE *logFile) {
    FILE *f = fopen(nombreArchivo, "r");
    if (!f) {
        fprintf(logFile, "ADVERTENCIA: No se pudo abrir %s\n", nombreArchivo);
        return 0;
    }
    char linea[256];
    int cargados = 0;
    while (fgets(linea, sizeof(linea), f)) {   /* Lee cada linea del archivo */
        linea[strcspn(linea, "\r\n")] = 0;     /* Eliminar salto de linea */
        if (strlen(linea) == 0) continue;      /* Saltar lineas vacias */

        Cliente c;
        char tipoStr[15];
        char rutTmp[MAX_RUT], nombreTmp[MAX_NOMBRE], horaTmp[MAX_HORA];
        int prioridad;
        /* Parsear linea con formato: rut;nombre;tipo;hora;prioridad */
        if (sscanf(linea, "%[^;];%[^;];%[^;];%[^;];%d",
                   rutTmp, nombreTmp, tipoStr, horaTmp, &prioridad) != 5) {
            fprintf(logFile, "ERROR: Formato incorrecto en agendados: %s\n", linea);
            continue;
        }
        if (!validarHora(horaTmp) || prioridad < 1 || prioridad > 3) {
            fprintf(logFile, "ERROR: Datos invalidos en agendados: %s\n", linea);
            continue;
        }
        int tipo = parsearTipo(tipoStr);
        if (tipo == -1) {
            fprintf(logFile, "ERROR: Tipo de solicitud invalido en agendados: %s\n", linea);
            continue;
        }
        if (existeRutGlobal(lista, cola, historial, rutTmp)) {
            fprintf(logFile, "ERROR: RUT duplicado en agendados: %s\n", rutTmp);
            continue;
        }
        copiarCadena(c.rut, rutTmp, MAX_RUT);
        copiarCadena(c.nombre, nombreTmp, MAX_NOMBRE);
        copiarCadena(c.hora, horaTmp, MAX_HORA);
        c.tipo = tipo;
        c.prioridad = prioridad;
        c.estado = ESTADO_AGENDADO;
        insertarFinalLista(lista, c);
        cargados++;
        total_agendados_acum++;   /* Contador acumulado de agendados (para estadisticas) */
    }
    fclose(f);
    return cargados;
}

/* Lee el archivo de clientes que llegan sin reserva (cola de espera) y los encola */
int cargarClientesLlegada(const char *nombreArchivo, Cola *cola,
                          ListaEnlazada *lista, Pila *historial, FILE *logFile) {
    FILE *f = fopen(nombreArchivo, "r");
    if (!f) {
        fprintf(logFile, "ADVERTENCIA: No se pudo abrir %s\n", nombreArchivo);
        return 0;
    }
    char linea[256];
    int cargados = 0;
    while (fgets(linea, sizeof(linea), f)) {   /* Lee cada linea del archivo */
        linea[strcspn(linea, "\r\n")] = 0;
        if (strlen(linea) == 0) continue;

        Cliente c;
        char tipoStr[15];
        char rutTmp[MAX_RUT], nombreTmp[MAX_NOMBRE], horaTmp[MAX_HORA];
        int prioridad;
        if (sscanf(linea, "%[^;];%[^;];%[^;];%[^;];%d",
                   rutTmp, nombreTmp, tipoStr, horaTmp, &prioridad) != 5) {
            fprintf(logFile, "ERROR: Formato incorrecto en llegada: %s\n", linea);
            continue;
        }
        if (!validarHora(horaTmp) || prioridad < 1 || prioridad > 3) {
            fprintf(logFile, "ERROR: Datos invalidos en llegada: %s\n", linea);
            continue;
        }
        int tipo = parsearTipo(tipoStr);
        if (tipo == -1) {
            fprintf(logFile, "ERROR: Tipo de solicitud invalido en llegada: %s\n", linea);
            continue;
        }
        if (existeRutGlobal(lista, cola, historial, rutTmp)) {
            fprintf(logFile, "ERROR: RUT duplicado en llegada: %s\n", rutTmp);
            continue;
        }
        copiarCadena(c.rut, rutTmp, MAX_RUT);
        copiarCadena(c.nombre, nombreTmp, MAX_NOMBRE);
        copiarCadena(c.hora, horaTmp, MAX_HORA);
        c.tipo = tipo;
        c.prioridad = prioridad;
        c.estado = ESTADO_EN_ESPERA;
        encolar(cola, c);
        cargados++;
        total_cola_acum++;   /* Contador acumulado de clientes que pasaron por cola */
    }
    fclose(f);
    return cargados;
}

/* --------------------- Procesamiento del archivo de operaciones --------------------- */

/* Lee el archivo de operaciones linea por linea y ejecuta el comando correspondiente */
void procesarOperaciones(const char *nombreArchivo, ListaEnlazada *lista, Cola *cola,
                         Pila *historial, Pila *anulados, FILE *logFile) {
    FILE *f = fopen(nombreArchivo, "r");
    if (!f) {
        fprintf(logFile, "ERROR: No se pudo abrir el archivo de operaciones %s\n", nombreArchivo);
        return;
    }
    char linea[256];
    int numLinea = 0;
    while (fgets(linea, sizeof(linea), f)) {   /* Lee cada linea del archivo de operaciones */
        numLinea++;
        linea[strcspn(linea, "\r\n")] = 0;     /* Eliminar salto de linea */
        if (strlen(linea) == 0) continue;

        char comando[30];
        char *token = strtok(linea, ";");      /* Primer token: comando */
        if (!token) {
            fprintf(logFile, "Linea %d: Formato incorrecto.\n", numLinea);
            continue;
        }
        strcpy(comando, token);

        /* Comando AGENDAR: agregar nuevo cliente a la lista de agendados */
        if (strcmp(comando, "AGENDAR") == 0) {
            char *rut = strtok(NULL, ";");
            char *nombre = strtok(NULL, ";");
            char *tipoStr = strtok(NULL, ";");
            char *hora = strtok(NULL, ";");
            char *priorStr = strtok(NULL, ";");
            if (!rut || !nombre || !tipoStr || !hora || !priorStr) {
                fprintf(logFile, "AGENDAR: Faltan parametros.\n");
                continue;
            }
            int prioridad = atoi(priorStr);
            if (!validarHora(hora) || prioridad < 1 || prioridad > 3) {
                fprintf(logFile, "AGENDAR %s: Datos invalidos.\n", rut);
                continue;
            }
            int tipo = parsearTipo(tipoStr);
            if (tipo == -1) {
                fprintf(logFile, "AGENDAR %s: Tipo de solicitud invalido.\n", rut);
                continue;
            }
            if (existeRutGlobal(lista, cola, historial, rut)) {
                fprintf(logFile, "AGENDAR %s: RUT duplicado.\n", rut);
                continue;
            }
            Cliente c;
            copiarCadena(c.rut, rut, MAX_RUT);
            copiarCadena(c.nombre, nombre, MAX_NOMBRE);
            copiarCadena(c.hora, hora, MAX_HORA);
            c.tipo = tipo;
            c.prioridad = prioridad;
            c.estado = ESTADO_AGENDADO;
            insertarFinalLista(lista, c);
            total_agendados_acum++;
            fprintf(logFile, "AGENDAR: Cliente %s agregado a agendados.\n", rut);
        }
        /* Comando CANCELAR_AGENDA: eliminar cliente de la lista de agendados por RUT */
        else if (strcmp(comando, "CANCELAR_AGENDA") == 0) {
            char *rut = strtok(NULL, ";");
            if (!rut) {
                fprintf(logFile, "CANCELAR_AGENDA: Faltan parametros.\n");
                continue;
            }
            NodoLista *anterior = NULL;
            NodoLista *nodo = buscarEnLista(lista, rut, &anterior);
            if (!nodo) {
                fprintf(logFile, "CANCELAR_AGENDA %s: No encontrado en agendados.\n", rut);
                continue;
            }
            eliminarNodoLista(lista, nodo, anterior);
            total_cancelados++;
            fprintf(logFile, "CANCELAR_AGENDA: Cliente %s cancelado.\n", rut);
        }
        /* Comando LLEGADA: agregar cliente a la cola de espera */
        else if (strcmp(comando, "LLEGADA") == 0) {
            char *rut = strtok(NULL, ";");
            char *nombre = strtok(NULL, ";");
            char *tipoStr = strtok(NULL, ";");
            char *hora = strtok(NULL, ";");
            char *priorStr = strtok(NULL, ";");
            if (!rut || !nombre || !tipoStr || !hora || !priorStr) {
                fprintf(logFile, "LLEGADA: Faltan parametros.\n");
                continue;
            }
            int prioridad = atoi(priorStr);
            if (!validarHora(hora) || prioridad < 1 || prioridad > 3) {
                fprintf(logFile, "LLEGADA %s: Datos invalidos.\n", rut);
                continue;
            }
            int tipo = parsearTipo(tipoStr);
            if (tipo == -1) {
                fprintf(logFile, "LLEGADA %s: Tipo de solicitud invalido.\n", rut);
                continue;
            }
            if (existeRutGlobal(lista, cola, historial, rut)) {
                fprintf(logFile, "LLEGADA %s: RUT duplicado.\n", rut);
                continue;
            }
            Cliente c;
            copiarCadena(c.rut, rut, MAX_RUT);
            copiarCadena(c.nombre, nombre, MAX_NOMBRE);
            copiarCadena(c.hora, hora, MAX_HORA);
            c.tipo = tipo;
            c.prioridad = prioridad;
            c.estado = ESTADO_EN_ESPERA;
            encolar(cola, c);
            total_cola_acum++;
            fprintf(logFile, "LLEGADA: Cliente %s encolado.\n", rut);
        }
        /* Comando ATENDER: atencion normal (primero agendados, luego cola) */
        else if (strcmp(comando, "ATENDER") == 0) {
            Cliente atendido;
            if (atenderCliente(lista, cola, historial, &atendido)) {
                fprintf(logFile, "ATENDER: Atendido %s (%s).\n", atendido.rut, tipoAStr(atendido.tipo));
            } else {
                fprintf(logFile, "ATENDER: No hay clientes para atender.\n");
            }
        }
        /* Comando ATENDER_PRIORIDAD: atender cliente con mayor prioridad */
        else if (strcmp(comando, "ATENDER_PRIORIDAD") == 0) {
            Cliente atendido;
            if (atenderConPrioridad(lista, cola, historial, &atendido)) {
                fprintf(logFile, "ATENDER_PRIORIDAD: Atendido %s (%s) prioridad %d.\n",
                        atendido.rut, tipoAStr(atendido.tipo), atendido.prioridad);
            } else {
                fprintf(logFile, "ATENDER_PRIORIDAD: No hay clientes para atender.\n");
            }
        }
        /* Comando DESHACER_ATENCION: deshacer la ultima atencion */
        else if (strcmp(comando, "DESHACER_ATENCION") == 0) {
            if (!deshacerAtencion(historial, anulados, logFile)) {
                fprintf(logFile, "DESHACER_ATENCION: No hay atenciones que deshacer.\n");
            }
        }
        /* Comando BUSCAR_CLIENTE: buscar RUT en lista, cola o historial */
        else if (strcmp(comando, "BUSCAR_CLIENTE") == 0) {
            char *rut = strtok(NULL, ";");
            if (!rut) {
                fprintf(logFile, "BUSCAR_CLIENTE: RUT faltante.\n");
                continue;
            }
            /* Buscar en agendados */
            NodoLista *anteriorL;
            NodoLista *nodoL = buscarEnLista(lista, rut, &anteriorL);
            if (nodoL) {
                Cliente c = nodoL->dato;
                fprintf(logFile, "BUSCAR %s: Encontrado en AGENDADOS - %s, %s, %s, prioridad %d\n",
                        rut, c.nombre, tipoAStr(c.tipo), c.hora, c.prioridad);
                continue;
            }
            /* Buscar en cola */
            NodoCola *anteriorC;
            NodoCola *nodoC = buscarEnCola(cola, rut, &anteriorC);
            if (nodoC) {
                Cliente c = nodoC->dato;
                fprintf(logFile, "BUSCAR %s: Encontrado en COLA - %s, %s, %s, prioridad %d\n",
                        rut, c.nombre, tipoAStr(c.tipo), c.hora, c.prioridad);
                continue;
            }
            /* Buscar en historial (pila) */
            if (existeEnPila(historial, rut)) {
                NodoPila *act = historial->tope;
                while (act) {
                    if (strcmp(act->dato.rut, rut) == 0) {
                        Cliente c = act->dato;
                        fprintf(logFile, "BUSCAR %s: Encontrado en HISTORIAL (%s) - %s, %s, %s, prioridad %d\n",
                                rut, estadoAStr(c.estado), c.nombre, tipoAStr(c.tipo), c.hora, c.prioridad);
                        break;
                    }
                    act = act->sig;
                }
                continue;
            }
            /* Buscar en pila de ANULADOS */
            if (existeEnPila(anulados, rut)) {
                NodoPila *act = anulados->tope;
                while (act) {
                    if (strcmp(act->dato.rut, rut) == 0) {
                        Cliente c = act->dato;
                        fprintf(logFile, "BUSCAR %s: Encontrado en ANULADOS - %s, %s, %s, prioridad %d\n",
                                rut, c.nombre, tipoAStr(c.tipo), c.hora, c.prioridad);
                        break;
                    }
                    act = act->sig;
                }
            } else {
                fprintf(logFile, "BUSCAR %s: No encontrado.\n", rut);
            }
        }
        /* Comando MOSTRAR_ESTADO: mostrar el estado actual de todas las estructuras (solo en log) */
        else if (strcmp(comando, "MOSTRAR_ESTADO") == 0) {
            fprintf(logFile, "=== ESTADO ACTUAL ===\n");
            fprintf(logFile, "Agendados pendientes:\n");
            NodoLista *actL = lista->cabeza;
            if (!actL) fprintf(logFile, "  (vacio)\n");
            while (actL) {                                 /* Recorre la lista de agendados */
                Cliente c = actL->dato;
                fprintf(logFile, "  %s - %s (%s) %s\n", c.rut, c.nombre, tipoAStr(c.tipo), c.hora);
                actL = actL->sig;
            }
            fprintf(logFile, "Cola de espera:\n");
            NodoCola *actC = cola->frente;
            if (!actC) fprintf(logFile, "  (vacio)\n");
            while (actC) {                                 /* Recorre la cola de espera */
                Cliente c = actC->dato;
                fprintf(logFile, "  %s - %s (%s) %s\n", c.rut, c.nombre, tipoAStr(c.tipo), c.hora);
                actC = actC->sig;
            }
            fprintf(logFile, "Historial (ultimos primero):\n");
            NodoPila *actP = historial->tope;
            if (!actP) fprintf(logFile, "  (vacio)\n");
            while (actP) {                                 /* Recorre la pila de historial */
                Cliente c = actP->dato;
                fprintf(logFile, "  %s - %s (%s) estado: %s\n", c.rut, c.nombre, tipoAStr(c.tipo), estadoAStr(c.estado));
                actP = actP->sig;
            }
            fprintf(logFile, "========================\n");
        }
        else {
            fprintf(logFile, "Linea %d: Comando desconocido '%s'\n", numLinea, comando);
        }
    }
    fclose(f);
}

/* --------------------- Generacion de reportes finales --------------------- */

/* Genera el archivo reporte_final.txt con el estado final de agendados, cola, historial y anulaciones */
void generarReporteFinal(const char *nombreArchivo, ListaEnlazada *lista, Cola *cola,
                         Pila *historial, Pila *anulados) {
    FILE *f = fopen(nombreArchivo, "w");
    if (!f) return;

    fprintf(f, "REPORTE FINAL DEL SISTEMA SERVIEXPRESS\n\n");
    fprintf(f, "CLIENTES AGENDADOS PENDIENTES:\n");
    NodoLista *actL = lista->cabeza;
    if (!actL) fprintf(f, "  Ninguno.\n");
    while (actL) {                                 /* Recorre la lista de agendados pendientes */
        Cliente c = actL->dato;
        fprintf(f, "  %s - %s, %s, %s, prioridad %d\n", c.rut, c.nombre, tipoAStr(c.tipo), c.hora, c.prioridad);
        actL = actL->sig;
    }

    fprintf(f, "\nCLIENTES EN COLA DE ESPERA:\n");
    NodoCola *actC = cola->frente;
    if (!actC) fprintf(f, "  Ninguno.\n");
    while (actC) {                                 /* Recorre la cola de espera */
        Cliente c = actC->dato;
        fprintf(f, "  %s - %s, %s, %s, prioridad %d\n", c.rut, c.nombre, tipoAStr(c.tipo), c.hora, c.prioridad);
        actC = actC->sig;
    }

    fprintf(f, "\nHISTORIAL DE ATENCIONES:\n");
    NodoPila *actP = historial->tope;
    if (!actP) fprintf(f, "  Ninguna.\n");
    while (actP) {                                 /* Recorre la pila de historial */
        Cliente c = actP->dato;
        fprintf(f, "  %s - %s, %s, estado: %s\n", c.rut, c.nombre, tipoAStr(c.tipo), estadoAStr(c.estado));
        actP = actP->sig;
    }

    fprintf(f, "\nATENCIONES ANULADAS:\n");
    NodoPila *actA = anulados->tope;
    if (!actA) fprintf(f, "  Ninguna.\n");
    while (actA) {                                 /* Recorre la pila de anulados */
        Cliente c = actA->dato;
        fprintf(f, "  %s - %s\n", c.rut, c.nombre);
        actA = actA->sig;
    }
    fclose(f);
}

/* Genera el archivo estadisticas.txt con los totales acumulados y desagregados por tipo de solicitud */
void generarEstadisticas(const char *nombreArchivo, ListaEnlazada *lista, Cola *cola,
                         Pila *historial, int totalInicial,
                         int totalAgendadosAcum, int totalColaAcum) {
    FILE *f = fopen(nombreArchivo, "w");
    if (!f) return;

    /* Contar clientes pendientes actuales en lista de agendados */
    int agendadosPend = 0;
    NodoLista *actL = lista->cabeza;
    while (actL) { agendadosPend++; actL = actL->sig; }  /* Recorre lista contando nodos */

    /* Contar clientes pendientes actuales en cola */
    int colaCount = 0;
    NodoCola *actC = cola->frente;
    while (actC) { colaCount++; actC = actC->sig; }      /* Recorre cola contando nodos */

    /* Recorrer historial para contar atendidos y acumular por tipo de solicitud */
    int atendidos = 0;
    int tipoCount[4] = {0};
    NodoPila *actP = historial->tope;
    while (actP) {                                      /* Recorre la pila de historial */
        if (actP->dato.estado == ESTADO_ATENDIDO) {
            atendidos++;
            tipoCount[actP->dato.tipo]++;
        }
        actP = actP->sig;
    }

    fprintf(f, "ESTADISTICAS DE ATENCION\n\n");
    fprintf(f, "Total de clientes cargados inicialmente: %d\n", totalInicial);
    fprintf(f, "Total de clientes agendados: %d\n", totalAgendadosAcum);
    fprintf(f, "Total de clientes ingresados por cola: %d\n", totalColaAcum);
    fprintf(f, "Total de clientes atendidos: %d\n", atendidos);
    fprintf(f, "Total de clientes cancelados: %d\n", total_cancelados);
    fprintf(f, "Total de atenciones anuladas: %d\n", total_anulados);
    fprintf(f, "Total de clientes pendientes: %d\n", agendadosPend + colaCount);
    fprintf(f, "\nCantidad de reclamos atendidos: %d\n", tipoCount[TIPO_RECLAMO]);
    fprintf(f, "Cantidad de pagos atendidos: %d\n", tipoCount[TIPO_PAGO]);
    fprintf(f, "Cantidad de consultas atendidas: %d\n", tipoCount[TIPO_CONSULTA]);
    fprintf(f, "Cantidad de tramites atendidos: %d\n", tipoCount[TIPO_TRAMITE]);

    fclose(f);
}