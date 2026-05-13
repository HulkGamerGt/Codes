#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "at_clientes.h"


// Inserta un CLIENTE al final de la lista
CLIENTE* insertar_lista(CLIENTE *lista,int numero, char nombre[], char accion[]) {
    CLIENTE *nuevo = (CLIENTE*)malloc(sizeof(CLIENTE));
    if(nuevo == NULL) return lista;

    strcpy(nuevo->nombre, nombre);
    strcpy(nuevo->accion, accion);
    nuevo->numero = numero;
    nuevo->sig = NULL;

    if(lista == NULL){
        return nuevo;
    }else{
        CLIENTE *aux = lista;
        while(aux->sig != NULL){
            aux = aux->sig;
        }
        aux->sig = nuevo;
        return lista;
    }
}

// 1. Leer datos desde el archivo 'acciones.txt'
CLIENTE* leer_archivo(CLIENTE *lista) {
    FILE *archivo = fopen("acciones.txt", "r");

    if (archivo == NULL) {
        printf("\nError: No se encontro 'acciones.txt''\n");
        return lista;
    }

    // Limpiamos la lista actual para evitar duplicados si se lee dos veces
    liberar_lista(lista);
    lista = NULL;

    while (fscanf(archivo, "%d %s %s", numero, nombre, accion) != EOF) {
        lista = insertar_lista(lista, numero, ombre, accion);
    }

    fclose(archivo);
    printf("\n[OK] Datos cargados exitosamente.\n");
    return lista;
}

// 2. Mostrar todos los CLIENTEs por pantalla
void mostrar_lista(CLIENTE *lista) {
    if (lista == NULL) {
        printf("\nLa lista esta vacia.\n");
        return;
    }
    CLIENTE *aux = lista;
    printf("\n--- PERSONAS EN ESPERA ---\n");
    printf("%-15s %-20s %-5s\n", "NUMERO", "NOMBRE", "ACCION");
    while (aux != NULL) {
        printf("%-15s %-20s %.1f\n", aux->numero, aux->nombre, aux->accion);
        aux = aux->sig;
    }
}

// Libera la memoria dinámica
void liberar_lista(CLIENTE *lista) {
    CLIENTE *aux;
    while (lista != NULL) {
        aux = lista;
        lista = lista->sig;
        free(aux);
    }
}