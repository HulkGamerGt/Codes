#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estudiante.h"

Estudiante* insertar_lista(Estudiante *lista, char rut[], char nombre[], float nota) {
    Estudiante *nuevo = (Estudiante*)malloc(sizeof(Estudiante));
    if (nuevo == NULL) return lista;

    strcpy(nuevo->rut, rut);
    strcpy(nuevo->nombre, nombre);
    nuevo->nota = nota;
    nuevo->sig = NULL;

    if (lista == NULL) return nuevo;

    Estudiante *aux = lista;
    while (aux->sig != NULL) aux = aux->sig;
    aux->sig = nuevo;
    return lista;
}

Estudiante* leer_archivo(Estudiante *lista) {
    FILE *archivo = fopen("estudiantes.txt", "r");
    if (archivo == NULL) {
        printf("\nError: No se encontro 'estudiantes.txt'\n");
        return lista;
    }

    liberar_lista(lista);
    lista = NULL;

    char rut[15], nombre[50];
    float nota;
    while (fscanf(archivo, "%s %s %f", rut, nombre, &nota) == 3) {
        lista = insertar_lista(lista, rut, nombre, nota);
    }

    fclose(archivo);
    printf("\n[OK] Datos cargados exitosamente.\n");
    return lista;
}

void mostrar_lista(Estudiante *lista) {
    if (lista == NULL) {
        printf("\nLa lista esta vacia.\n");
        return;
    }
    printf("\n--- LISTA DE ESTUDIANTES ---\n");
    printf("%-15s %-20s %-5s\n", "RUT", "NOMBRE", "NOTA");
    Estudiante *aux = lista;
    while (aux != NULL) {
        printf("%-15s %-20s %.1f\n", aux->rut, aux->nombre, aux->nota);
        aux = aux->sig;
    }
}

void calcular_promedio(Estudiante *lista) {
    if (lista == NULL) {
        printf("\nNo hay datos para calcular promedio.\n");
        return;
    }
    float suma = 0;
    int cont = 0;
    Estudiante *aux = lista;
    while (aux != NULL) {
        suma += aux->nota;
        cont++;
        aux = aux->sig;
    }
    printf("\nPromedio general del curso: %.2f\n", suma / cont);
}

void guardar_aprobados(Estudiante *lista) {
    if (lista == NULL) {
        printf("\nNada que guardar, lista vacia.\n");
        return;
    }
    FILE *archivo = fopen("aprobados.txt", "w");
    if (archivo == NULL) return;

    Estudiante *aux = lista;
    while (aux != NULL) {
        if (aux->nota >= 4.0)
            fprintf(archivo, "%s %s %.1f\n", aux->rut, aux->nombre, aux->nota);
        aux = aux->sig;
    }
    fclose(archivo);
    printf("\nSe ha creado 'aprobados.txt' con los estudiantes con nota >= 4.0\n");
}

void liberar_lista(Estudiante *lista) {
    Estudiante *aux;
    while (lista != NULL) {
        aux = lista;
        lista = lista->sig;
        free(aux);
    }
}
