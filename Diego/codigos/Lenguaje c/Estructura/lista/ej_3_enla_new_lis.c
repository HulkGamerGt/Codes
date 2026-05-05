#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int valor;
    struct Nodo *sig;
} Nodo;

Nodo *crear_nodo(int valor) {
    Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (!nuevo) {
        printf("Error: No hay memoria.\n");
        exit(1);
    }
    nuevo->valor = valor;
    nuevo->sig = NULL;
    return nuevo;
}

// Operación 2: Insertar al final (la más usada en tu main)
Nodo* insertar_al_final(Nodo *cabeza, int valor) {
    Nodo *nuevo = crear_nodo(valor);
    if (cabeza == NULL) return nuevo;
    Nodo *aux = cabeza;
    while (aux->sig != NULL) aux = aux->sig;
    aux->sig = nuevo;
    return cabeza;
}

void mostrar_lista(Nodo *cabeza) {
    Nodo *aux = cabeza;
    while (aux != NULL) {
        printf("%d -> ", aux->valor);
        aux = aux->sig;
    }
    printf("NULL\n");
}

void duplicarMayoresAlPromedio(Nodo *cabeza) {
    if (cabeza == NULL) return;

    float suma = 0;
    int contador = 0;
    Nodo *aux = cabeza;
    
    while (aux != NULL) {
        suma += aux->valor;
        contador++;
        aux = aux->sig;
    }
    
    float promedio = suma / contador;
    printf("\nPromedio calculado: %.2f\n", promedio);

    aux = cabeza;
    while (aux != NULL) {
        if (aux->valor > promedio) {
            Nodo *nuevo = crear_nodo(aux->valor * 2);
            nuevo->sig = aux->sig;
            aux->sig = nuevo;
            aux = nuevo->sig; // Saltamos el nuevo para no evaluarlo
        } else {
            aux = aux->sig;
        }
    }
}

int main() {
    Nodo *lista = NULL;
    int n, valor;

    printf("Digite la cantidad de numeros a analizar: ");
    if (scanf("%d", &n) != 1) return 1;

    for (int i = 0; i < n; i++) {
        printf("Ingrese el valor %d: ", i + 1);
        
        if (scanf("%d", &valor) == 1) {
            lista = insertar_al_final(lista, valor);
        } else {
            printf("Entrada no valida. Intente de nuevo.\n");
            while(getchar() != '\n'); // Limpiar búfer en caso de error
            i--; // Repetir este índice
        }
    }

    printf("\nLista original: ");
    mostrar_lista(lista);

    duplicarMayoresAlPromedio(lista);

    printf("Lista final: ");
    mostrar_lista(lista);

    return 0;
}