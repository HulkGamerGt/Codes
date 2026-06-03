#include <stdio.h>      // printf, scanf
#include <stdlib.h>     // malloc, free, NULL

typedef struct NodoSimple {
    int dato;                       // valor que guarda el nodo
    struct NodoSimple* siguiente;   // puntero al siguiente nodo
} NodoSimple;

typedef struct {
    NodoSimple* cabeza; // puntero al primer nodo
    NodoSimple* cola;   // puntero al último nodo
    int tam;            // cantidad actual de nodos
} ListaSimple;

/* ---------- Inicialización ---------- */
void inicializarLista(ListaSimple* l) {
    l->cabeza = NULL;   // todavía no hay nodos
    l->cola = NULL;     // el final tampoco existe
    l->tam = 0;         // tamaño cero
}

/* ---------- Creación de nodo (con validación) ---------- */
NodoSimple* crearNodoSimple(int dato) {
    NodoSimple* n = (NodoSimple*)malloc(sizeof(NodoSimple)); // pedir memoria
    if (!n) {                                              // si malloc falla
        printf("Error: memoria insuficiente para el nodo.\n");
        return NULL;                                       // avisar y salir
    }
    n->dato = dato;        // guardar el valor
    n->siguiente = NULL;   // por ahora no apunta a nadie
    return n;              // devolver el nuevo nodo
}

/* ---------- Inserciones ---------- */
int insertarInicio(ListaSimple* l, int dato) {
    NodoSimple* n = crearNodoSimple(dato); // crear nodo
    if (!n) return 0;                      // fallo de memoria -> error
    n->siguiente = l->cabeza;              // enlazar con la antigua cabeza
    l->cabeza = n;                         // ahora n es la nueva cabeza
    if (!l->cola) l->cola = n;            // si era el primer nodo, también es la cola
    l->tam++;                              // un nodo más
    return 1;                              // éxito
}

int insertarFinal(ListaSimple* l, int dato) {
    NodoSimple* n = crearNodoSimple(dato); // crear nodo
    if (!n) return 0;                      // sin memoria
    if (!l->cola) {                        // lista vacía?
        l->cabeza = l->cola = n;           // cabeza y cola apuntan al mismo nodo
    } else {
        l->cola->siguiente = n;            // enganchar al final actual
        l->cola = n;                       // mover cola al nuevo último
    }
    l->tam++;                              // aumentar tamaño
    return 1;
}

int insertarOrdenado(ListaSimple* l, int dato) {
    NodoSimple* n = crearNodoSimple(dato); // crear nodo
    if (!n) return 0;                      // validar memoria
    if (!l->cabeza || l->cabeza->dato >= dato) { // lista vacía o menor que la cabeza
        n->siguiente = l->cabeza;           // insertar al principio
        l->cabeza = n;
        if (!l->cola) l->cola = n;         // si estaba vacía, cola = n
    } else {
        NodoSimple* ant = l->cabeza;       // buscar dónde insertar
        while (ant->siguiente && ant->siguiente->dato < dato)
            ant = ant->siguiente;          // avanzar mientras el siguiente sea menor
        n->siguiente = ant->siguiente;     // enlazar n con el resto
        ant->siguiente = n;                // colocar n después de ant
        if (!n->siguiente) l->cola = n;    // si n queda al final, actualizar cola
    }
    l->tam++;                              // ajustar tamaño
    return 1;
}

int insertarPosicion(ListaSimple* l, int dato, int pos) {
    if (pos < 0 || pos > l->tam) return 0;    // posición no válida -> error
    if (pos == 0) return insertarInicio(l, dato); // delegar en insertarInicio
    if (pos == l->tam) return insertarFinal(l, dato); // delegar en insertarFinal
    NodoSimple* ant = l->cabeza;              // empezar desde el principio
    for (int i = 0; i < pos - 1; i++)         // avanzar hasta el nodo anterior a la posición
        ant = ant->siguiente;
    NodoSimple* n = crearNodoSimple(dato);    // crear nodo
    if (!n) return 0;
    n->siguiente = ant->siguiente;            // enlazar con el que estaba en esa posición
    ant->siguiente = n;                       // insertar n después de ant
    l->tam++;                                 // un nodo más
    return 1;
}

/* ---------- Eliminaciones ---------- */
int eliminarDato(ListaSimple* l, int dato) {
    NodoSimple *act = l->cabeza, *ant = NULL; // act = nodo actual, ant = anterior
    while (act) {                             // recorrer la lista
        if (act->dato == dato) {              // ¿es el valor buscado?
            if (ant)                           // hay un nodo anterior?
                ant->siguiente = act->siguiente; // saltar act
            else                               // es la cabeza
                l->cabeza = act->siguiente;    // nueva cabeza
            if (act == l->cola)                // si eliminamos la cola
                l->cola = ant;                 // el anterior pasa a ser la nueva cola
            free(act);                         // liberar memoria del nodo
            l->tam--;                          // reducir tamaño
            return 1;                          // éxito
        }
        ant = act;                             // mover anterior
        act = act->siguiente;                  // avanzar al siguiente
    }
    return 0;                                  // no encontrado
}

int eliminarPosicion(ListaSimple* l, int pos) {
    if (pos < 0 || pos >= l->tam) return 0;    // posición inválida
    NodoSimple* act = l->cabeza;
    if (pos == 0) {                             // eliminar el primero
        l->cabeza = act->siguiente;             // cabeza avanza al siguiente
        if (!l->cabeza) l->cola = NULL;         // si quedó vacía, cola = NULL
        free(act);                              // liberar nodo
    } else {
        NodoSimple* ant = l->cabeza;
        for (int i = 0; i < pos - 1; i++)       // llegar al anterior a la posición
            ant = ant->siguiente;
        act = ant->siguiente;                   // nodo a borrar
        ant->siguiente = act->siguiente;        // puentear el nodo
        if (!act->siguiente)                    // si era el último
            l->cola = ant;                      // la cola retrocede a ant
        free(act);
    }
    l->tam--;                                   // un nodo menos
    return 1;
}

/* ---------- Búsqueda y consultas ---------- */
int buscar(const ListaSimple* l, int dato) {
    const NodoSimple* act = l->cabeza;          // empezar por la cabeza
    while (act) {                               // mientras haya nodos
        if (act->dato == dato) return 1;        // encontrado
        act = act->siguiente;                   // avanzar
    }
    return 0;                                   // no está
}

int longitud(const ListaSimple* l) {
    return l->tam;                              // el tamaño guardado, O(1)
}

/* ---------- Copia ---------- */
int copiarLista(const ListaSimple* origen, ListaSimple* destino) {
    inicializarLista(destino);                  // preparar destino vacío
    const NodoSimple* p = origen->cabeza;       // recorrer origen
    while (p) {
        if (!insertarFinal(destino, p->dato)) { // copiar cada dato al final
            liberarLista(destino);              // si falla, liberar lo copiado
            return 0;
        }
        p = p->siguiente;                       // siguiente nodo origen
    }
    return 1;
}

/* ---------- Inversión ---------- */
void invertir(ListaSimple* l) {
    NodoSimple *ant = NULL, *act = l->cabeza, *sig; // tres punteros para invertir enlaces
    l->cola = l->cabeza;                     // la nueva cola será la antigua cabeza
    while (act) {                            // recorrer hasta el final
        sig = act->siguiente;                // guardar siguiente antes de cambiar
        act->siguiente = ant;                // invertir el enlace
        ant = act;                           // avanzar anterior
        act = sig;                           // avanzar actual
    }
    l->cabeza = ant;                         // la cabeza es el último nodo procesado
}

/* ---------- Concatenación ---------- */
void concatenar(ListaSimple* l1, ListaSimple* l2) {
    if (!l2->cabeza) return;                 // si l2 vacía, no hacer nada
    if (!l1->cabeza) {                       // si l1 vacía, copiar punteros
        l1->cabeza = l2->cabeza;
        l1->cola = l2->cola;
    } else {
        l1->cola->siguiente = l2->cabeza;    // enganchar l2 al final de l1
        l1->cola = l2->cola;                 // actualizar cola de l1
    }
    l1->tam += l2->tam;                      // sumar tamaños
    l2->cabeza = l2->cola = NULL;            // l2 queda vacía (sus nodos ahora son de l1)
    l2->tam = 0;
}

/* ---------- MergeSort ---------- */
static void dividir(NodoSimple* cabeza, NodoSimple** izq, NodoSimple** der) {
    NodoSimple* rapido = cabeza->siguiente; // avanza de a dos
    NodoSimple* lento = cabeza;             // avanza de a uno
    while (rapido) {
        rapido = rapido->siguiente;
        if (rapido) {                       // si puede avanzar otro paso
            lento = lento->siguiente;
            rapido = rapido->siguiente;
        }
    }
    *izq = cabeza;                          // primera mitad
    *der = lento->siguiente;                // segunda mitad
    lento->siguiente = NULL;                // cortar la lista
}

static NodoSimple* fusionarOrdenado(NodoSimple* a, NodoSimple* b) {
    if (!a) return b;                       // si una lista está vacía, devolver la otra
    if (!b) return a;
    if (a->dato <= b->dato) {               // elegir el menor
        a->siguiente = fusionarOrdenado(a->siguiente, b); // fusionar el resto
        return a;
    } else {
        b->siguiente = fusionarOrdenado(a, b->siguiente);
        return b;
    }
}

static void mergeSortRec(NodoSimple** cabezaRef) {
    NodoSimple* cabeza = *cabezaRef;
    if (!cabeza || !cabeza->siguiente) return; // lista de 0 o 1 nodo -> ya ordenada
    NodoSimple *izq, *der;
    dividir(cabeza, &izq, &der);             // partir en dos mitades
    mergeSortRec(&izq);                      // ordenar izquierda
    mergeSortRec(&der);                      // ordenar derecha
    *cabezaRef = fusionarOrdenado(izq, der); // combinar ordenadamente
}

void mergeSort(ListaSimple* l) {
    mergeSortRec(&(l->cabeza));              // ordenar recursivamente
    if (!l->cabeza) {                        // si quedó vacía
        l->cola = NULL;
        return;
    }
    l->cola = l->cabeza;                     // reconstruir cola recorriendo desde cabeza
    while (l->cola->siguiente) l->cola = l->cola->siguiente;
}

void eliminarDuplicadosOrdenado(ListaSimple* l) {
    NodoSimple* act = l->cabeza;
    while (act && act->siguiente) {          // mientras haya al menos dos nodos
        if (act->dato == act->siguiente->dato) { // duplicado encontrado
            NodoSimple* tmp = act->siguiente;    // nodo a eliminar
            act->siguiente = tmp->siguiente;     // puentear
            if (!act->siguiente) l->cola = act;  // si era el último, actualizar cola
            free(tmp);                            // liberar duplicado
            l->tam--;                             // reducir tamaño
        } else {
            act = act->siguiente;                 // avanzar si no hay duplicado
        }
    }
}

/* ---------- Detección de ciclos (Floyd) ---------- */
int tieneCiclo(const ListaSimple* l) {
    if (!l->cabeza) return 0;                      // vacía -> no hay ciclo
    const NodoSimple *tortuga = l->cabeza,          // avanza 1 paso
                     *liebre = l->cabeza->siguiente; // avanza 2 pasos
    while (liebre && liebre->siguiente) {           // mientras la liebre pueda correr
        if (tortuga == liebre) return 1;            // se encontraron -> ciclo
        tortuga = tortuga->siguiente;               // tortuga avanza 1
        liebre = liebre->siguiente->siguiente;      // liebre avanza 2
    }
    return 0;                                       // no hay ciclo
}

/* ---------- Operaciones circulares ---------- */
void hacerCircular(ListaSimple* l) {
    if (!l->cola) return;                  // si está vacía, nada que hacer
    l->cola->siguiente = l->cabeza;        // enlazar el último con el primero
    l->cola = NULL;                        // ahora es circular, la cola no se define igual
}

void deshacerCircular(ListaSimple* l) {
    if (!l->cabeza) return;
    // Detectar ciclo y encontrar el punto de inicio
    NodoSimple* tortuga = l->cabeza;
    NodoSimple* liebre = l->cabeza;
    while (liebre && liebre->siguiente) {
        tortuga = tortuga->siguiente;
        liebre = liebre->siguiente->siguiente;
        if (tortuga == liebre) break;      // se encontraron -> ciclo confirmado
    }
    if (!liebre || !liebre->siguiente) return; // no hay ciclo, salir
    // Encontrar el primer nodo del ciclo
    tortuga = l->cabeza;
    while (tortuga != liebre) {
        tortuga = tortuga->siguiente;
        liebre = liebre->siguiente;
    }
    // Ahora liebre/tortuga apuntan al inicio del ciclo. Buscar el último nodo.
    NodoSimple* ultimo = liebre;
    while (ultimo->siguiente != liebre)    // recorrer el ciclo hasta encontrar el nodo anterior a liebre
        ultimo = ultimo->siguiente;
    ultimo->siguiente = NULL;              // romper el enlace circular
    l->cola = ultimo;                      // restablecer cola lineal
}

/* ---------- Visualización ---------- */
void mostrarLista(const ListaSimple* l) {
    const NodoSimple* p = l->cabeza;
    while (p) {
        printf("%d -> ", p->dato);         // imprimir cada dato
        p = p->siguiente;
    }
    printf("NULL (tam=%d)\n", l->tam);     // fin de la lista y tamaño
}

/* ---------- Liberación ---------- */
void liberarLista(ListaSimple* l) {
    NodoSimple* act = l->cabeza;
    while (act) {
        NodoSimple* tmp = act;             // nodo a liberar
        act = act->siguiente;              // avanzar al siguiente
        free(tmp);                         // liberar memoria del nodo
    }
    l->cabeza = l->cola = NULL;            // lista vacía
    l->tam = 0;
}

/* ---------- Menú interactivo ---------- */
int main() {
    ListaSimple lista;
    inicializarLista(&lista);              // preparar lista vacía
    int opcion, valor, pos;

    do {
        printf("\n--- MENU LISTA SIMPLE ---\n");
        printf("1. Insertar al inicio\n");
        printf("2. Insertar al final\n");
        printf("3. Insertar ordenado\n");
        printf("4. Insertar en posicion\n");
        printf("5. Eliminar por valor\n");
        printf("6. Eliminar por posicion\n");
        printf("7. Buscar\n");
        printf("8. Mostrar\n");
        printf("9. Invertir\n");
        printf("10. Ordenar (MergeSort)\n");
        printf("11. Copiar a otra lista\n");
        printf("12. Concatenar con lista auxiliar\n");
        printf("13. Hacer circular\n");
        printf("14. Deshacer circular\n");
        printf("15. Detectar ciclo\n");
        printf("0. Salir\n");
        printf("Elija: ");
        scanf("%d", &opcion);              // leer opción del usuario

        switch(opcion) {
            case 1:
                printf("Valor: "); scanf("%d", &valor);
                insertarInicio(&lista, valor);
                break;
            case 2:
                printf("Valor: "); scanf("%d", &valor);
                insertarFinal(&lista, valor);
                break;
            case 3:
                printf("Valor: "); scanf("%d", &valor);
                insertarOrdenado(&lista, valor);
                break;
            case 4:
                printf("Valor y posicion: "); scanf("%d %d", &valor, &pos);
                if (!insertarPosicion(&lista, valor, pos))
                    printf("Posicion invalida\n");
                break;
            case 5:
                printf("Valor a eliminar: "); scanf("%d", &valor);
                if (eliminarDato(&lista, valor))
                    printf("Eliminado\n");
                else
                    printf("No encontrado\n");
                break;
            case 6:
                printf("Posicion a eliminar: "); scanf("%d", &pos);
                if (!eliminarPosicion(&lista, pos))
                    printf("Posicion invalida\n");
                break;
            case 7:
                printf("Valor a buscar: "); scanf("%d", &valor);
                printf(buscar(&lista, valor) ? "Encontrado\n" : "No encontrado\n");
                break;
            case 8:
                mostrarLista(&lista);
                break;
            case 9:
                invertir(&lista);
                printf("Lista invertida.\n");
                break;
            case 10:
                mergeSort(&lista);
                printf("Ordenada con MergeSort.\n");
                break;
            case 11: {
                ListaSimple copia;
                if (copiarLista(&lista, &copia)) {
                    printf("Copia: ");
                    mostrarLista(&copia);
                    liberarLista(&copia);
                }
                break;
            }
            case 12: {
                ListaSimple aux;
                inicializarLista(&aux);
                int n;
                printf("Cuantos elementos en lista auxiliar? ");
                scanf("%d", &n);
                for (int i = 0; i < n; i++) {
                    printf("Elemento %d: ", i+1);
                    scanf("%d", &valor);
                    insertarFinal(&aux, valor);
                }
                concatenar(&lista, &aux);
                printf("Listas concatenadas.\n");
                break;
            }
            case 13:
                hacerCircular(&lista);
                printf("Lista vuelta circular (no usar mostrar normal, puede colgar).\n");
                break;
            case 14:
                deshacerCircular(&lista);
                printf("Circularidad deshecha.\n");
                break;
            case 15:
                printf(tieneCiclo(&lista) ? "Tiene ciclo\n" : "No tiene ciclo\n");
                break;
            case 0:
                break;
            default:
                printf("Opcion invalida\n");
        }
    } while (opcion != 0);

    liberarLista(&lista);                  // liberar toda la memoria antes de salir
    return 0;
}