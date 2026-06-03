
## 1. `lista_1.h`

```c
#ifndef LISTA_1_H
#define LISTA_1_H

#define MAX 100

typedef struct {
    int datos[MAX];
    int n;          // cantidad actual de elementos
} Lista;

// Operaciones básicas (prototipos con extern)
extern int tamano(Lista l);
extern int obtener(Lista l, int pos);
extern void modificar(Lista *l, int pos, int valor);
extern void insertar(Lista *l, int pos, int valor);
extern void eliminar(Lista *l, int pos);
extern void inicializar(Lista *l);

#endif
```

---

## 2. `lista_1.c`

```c
#include "lista_1.h"

int tamano(Lista l) {
    return l.n;
}

int obtener(Lista l, int pos) {
    return l.datos[pos];
}

void modificar(Lista *l, int pos, int valor) {
    if (pos >= 0 && pos < l->n)
        l->datos[pos] = valor;
}

// Inserta un valor en una posición, desplazando el resto a la derecha
void insertar(Lista *l, int pos, int valor) {
    if (l->n >= MAX || pos < 0 || pos > l->n) return;
    for (int i = l->n; i > pos; i--)
        l->datos[i] = l->datos[i-1];
    l->datos[pos] = valor;
    l->n++;
}

// Elimina el elemento en la posición, desplazando hacia la izquierda
void eliminar(Lista *l, int pos) {
    if (pos < 0 || pos >= l->n) return;
    for (int i = pos; i < l->n - 1; i++)
        l->datos[i] = l->datos[i+1];
    l->n--;
}

void inicializar(Lista *l) {
    l->n = 0;
}
```

---

## 3. `ejercicio_1.c` (funciones extendidas)

```c
#include <stdio.h>
#include "lista_1.h"

// 1. Elimina todos los duplicados, dejando solo la primera aparición
void eliminarRepetidos(Lista *l) {
    int i = 0;
    while (i < tamano(*l)) {
        int actual = obtener(*l, i);
        int j = i + 1;
        while (j < tamano(*l)) {
            if (obtener(*l, j) == actual)
                eliminar(l, j);    // elimina y desplaza; no incrementa j
            else
                j++;
        }
        i++;
    }
}

// 2. Invierte los elementos entre inicio y fin (índices base 0)
void invertirSegmento(Lista *l, int inicio, int fin) {
    while (inicio < fin) {
        int temp = obtener(*l, inicio);
        modificar(l, inicio, obtener(*l, fin));
        modificar(l, fin, temp);
        inicio++;
        fin--;
    }
}

// 3. Encuentra el máximo y lo mueve al final sin perder elementos
void moverMaxAlFinal(Lista *l) {
    if (tamano(*l) <= 1) return;

    // Encontrar la primera posición del máximo
    int posMax = 0;
    for (int i = 1; i < tamano(*l); i++) {
        if (obtener(*l, i) > obtener(*l, posMax))
            posMax = i;
    }

    int maximo = obtener(*l, posMax);
    eliminar(l, posMax);                // borra el máximo y desplaza los demás
    insertar(l, tamano(*l), maximo);    // inserta el máximo al final
}

// 4. Retorna 1 si la lista es capicúa, 0 en caso contrario
int esCapicua(Lista l) {
    int i = 0, j = tamano(l) - 1;
    while (i < j) {
        if (obtener(l, i) != obtener(l, j))
            return 0;
        i++;
        j--;
    }
    return 1;
}

// Programa de prueba
int main() {
    Lista lista1;
    inicializar(&lista1);
    int arr1[] = {3, 5, 3, 7, 5};
    for (int i = 0; i < 5; i++) insertar(&lista1, i, arr1[i]);
    eliminarRepetidos(&lista1);
    printf("eliminarRepetidos: ");
    for (int i = 0; i < tamano(lista1); i++) printf("%d ", obtener(lista1, i));
    printf("\n");

    Lista lista2;
    inicializar(&lista2);
    int arr2[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) insertar(&lista2, i, arr2[i]);
    invertirSegmento(&lista2, 1, 3);
    printf("invertirSegmento: ");
    for (int i = 0; i < tamano(lista2); i++) printf("%d ", obtener(lista2, i));
    printf("\n");

    Lista lista3;
    inicializar(&lista3);
    int arr3[] = {3, 5, 4, 7, 5};
    for (int i = 0; i < 5; i++) insertar(&lista3, i, arr3[i]);
    moverMaxAlFinal(&lista3);
    printf("moverMaxAlFinal: ");
    for (int i = 0; i < tamano(lista3); i++) printf("%d ", obtener(lista3, i));
    printf("\n");

    Lista lista4;
    inicializar(&lista4);
    int arr4[] = {1, 2, 3, 2, 1};
    for (int i = 0; i < 5; i++) insertar(&lista4, i, arr4[i]);
    printf("esCapicua: %d\n", esCapicua(lista4));

    Lista lista5;
    inicializar(&lista5);
    int arr5[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) insertar(&lista5, i, arr5[i]);
    printf("esCapicua: %d\n", esCapicua(lista5));

    return 0;
}

