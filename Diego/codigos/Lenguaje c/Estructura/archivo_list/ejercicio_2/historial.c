#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "historial.h"

PilaNode* push(PilaNode *pila, const char *accion) {
    PilaNode *nuevo = (PilaNode*)malloc(sizeof(PilaNode));
    if (nuevo == NULL) return pila;
    strcpy(nuevo->accion, accion);
    nuevo->sig = pila;
    return nuevo;
}

PilaNode* pop(PilaNode *pila, char *accion_salida) {
    if (pila == NULL) {
        strcpy(accion_salida, "");
        return NULL;
    }
    PilaNode *temp = pila;
    strcpy(accion_salida, pila->accion);
    pila = pila->sig;
    free(temp);
    return pila;
}

void mostrar_pila(PilaNode *pila) {
    if (pila == NULL) {
        printf("\nLa pila esta vacia.\n");
        return;
    }
    printf("\n--- ACCIONES (orden inverso a realizacion) ---\n");
    PilaNode *aux = pila;
    int num = 1;
    while (aux != NULL) {
        printf("%d. %s\n", num++, aux->accion);
        aux = aux->sig;
    }
}

void guardar_pila_en_archivo(PilaNode *pila, const char *nombre_archivo) {
    if (pila == NULL) {
        printf("\nNo hay acciones que guardar.\n");
        return;
    }
    FILE *f = fopen(nombre_archivo, "w");
    if (f == NULL) {
        printf("Error al crear el archivo.\n");
        return;
    }
    // Guardar en orden de pila (última acción primero, pero se guarda como aparecen)
    PilaNode *aux = pila;
    while (aux != NULL) {
        fprintf(f, "%s\n", aux->accion);
        aux = aux->sig;
    }
    fclose(f);
    printf("\nAcciones guardadas en '%s'\n", nombre_archivo);
}

void liberar_pila(PilaNode *pila) {
    PilaNode *aux;
    while (pila != NULL) {
        aux = pila;
        pila = pila->sig;
        free(aux);
    }
}

PilaNode* cargar_acciones_a_pila(PilaNode *pila, const char *nombre_archivo) {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        printf("\nError: No se encontro '%s'\n", nombre_archivo);
        return pila;
    }
    char linea[100];
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        // Eliminar salto de línea final
        linea[strcspn(linea, "\n")] = '\0';
        pila = push(pila, linea);
    }
    fclose(archivo);
    printf("\nAcciones cargadas desde '%s' y apiladas.\n", nombre_archivo);
    return pila;
}
