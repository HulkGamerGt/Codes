#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "at_clientes.h"

CLIENTE* encolar(CLIENTE *cola, int numero, const char *nombre, const char *tramite) {
    CLIENTE *nuevo = (CLIENTE*)malloc(sizeof(CLIENTE));
    if (nuevo == NULL) return cola;
    nuevo->numero = numero;
    strcpy(nuevo->nombre, nombre);
    strcpy(nuevo->tramite, tramite);
    nuevo->sig = NULL;

    if (cola == NULL) return nuevo;

    CLIENTE *aux = cola;
    while (aux->sig != NULL) aux = aux->sig;
    aux->sig = nuevo;
    return cola;
}

CLIENTE* desencolar(CLIENTE *cola, int *num, char nombre[], char tramite[]) {
    if (cola == NULL) {
        *num = -1;
        nombre[0] = '\0';
        tramite[0] = '\0';
        return NULL;
    }
    CLIENTE *primero = cola;
    *num = primero->numero;
    strcpy(nombre, primero->nombre);
    strcpy(tramite, primero->tramite);
    cola = cola->sig;
    free(primero);
    return cola;
}

void mostrar_cola(CLIENTE *cola) {
    if (cola == NULL) {
        printf("\nCola de espera vacia.\n");
        return;
    }
    printf("\n--- COLA DE ATENCION ---\n");
    printf("%-8s %-20s %-15s\n", "NUMERO", "NOMBRE", "TRAMITE");
    CLIENTE *aux = cola;
    while (aux != NULL) {
        printf("%-8d %-20s %-15s\n", aux->numero, aux->nombre, aux->tramite);
        aux = aux->sig;
    }
}

void guardar_pendientes(CLIENTE *cola, const char *archivo) {
    if (cola == NULL) {
        printf("\nNo hay clientes pendientes.\n");
        return;
    }
    FILE *f = fopen(archivo, "w");
    if (f == NULL) {
        printf("Error al crear archivo.\n");
        return;
    }
    CLIENTE *aux = cola;
    while (aux != NULL) {
        fprintf(f, "%d %s %s\n", aux->numero, aux->nombre, aux->tramite);
        aux = aux->sig;
    }
    fclose(f);
    printf("\nClientes pendientes guardados en '%s'\n", archivo);
}

void liberar_cola(CLIENTE *cola) {
    CLIENTE *aux;
    while (cola != NULL) {
        aux = cola;
        cola = cola->sig;
        free(aux);
    }
}

CLIENTE* cargar_clientes_desde_archivo(CLIENTE *cola, const char *archivo) {
    FILE *f = fopen(archivo, "r");
    if (f == NULL) {
        printf("\nError: No se encontro '%s'\n", archivo);
        return cola;
    }
    int num;
    char nombre[50], tramite[50];
    while (fscanf(f, "%d %s %s", &num, nombre, tramite) == 3) {
        cola = encolar(cola, num, nombre, tramite);
    }
    fclose(f);
    printf("\nClientes cargados desde '%s'.\n", archivo);
    return cola;
}
