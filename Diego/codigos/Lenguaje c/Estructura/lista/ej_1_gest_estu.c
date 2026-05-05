#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMBRE 50

typedef struct Nodo{
    char nombre[MAX_NOMBRE];
    int edad;
    float promedio;
    struct Nodo *sig;
}Nodo;

Nodo *crear_nodo(const char *nombre, int edad, float promedio){
    Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
    if(nuevo == NULL){
        printf("Error de memoria.\n");
        exit(1);
    }
    strcpy(nuevo->nombre, nombre);
    nuevo->edad = edad;
    nuevo->promedio = promedio;
    nuevo->sig = NULL;
    return nuevo;
}

Nodo* insertar_al_final(Nodo *cabeza, const char *nombre, int edad, float promedio) {
    Nodo *nuevo = crear_nodo(nombre, edad, promedio);
    if(cabeza == NULL){
        return nuevo;
    }
    Nodo *aux = cabeza;
    while(aux->sig != NULL){
        aux = aux->sig;
    }
    aux->sig = nuevo;
    return cabeza;
}

void mostrar_estudiantes(Nodo *cabeza) {
    if(cabeza == NULL){
        printf("No hay estudiantes registrados.\n");
        return;
    }
    printf("\n=== LISTA DE ESTUDIANTES ===\n");
    Nodo *aux = cabeza;
    int cont = 1;
    while(aux != NULL){
        printf("%d. Nombre: %s, Edad: %d, Promedio: %.2f\n",cont++, aux->nombre, aux->edad, aux->promedio);
        aux = aux->sig;
    }
    printf("============================\n\n");
}

void buscar_por_nombre(Nodo *cabeza, const char *nombre) {
    Nodo *aux = cabeza;
    while(aux != NULL){
        if(strcmp(aux->nombre, nombre) == 0){
            printf("\nEstudiante encontrado:\n");
            printf("Nombre: %s, Edad: %d, Promedio: %.2f\n\n",aux->nombre, aux->edad, aux->promedio);
            return;
        }
        aux = aux->sig;
    }
    printf("Estudiante con nombre '%s' no encontrado.\n\n", nombre);
}

Nodo* eliminar_por_nombre(Nodo *cabeza, const char *nombre){
    Nodo *actual = cabeza;
    Nodo *anterior = NULL;

    while(actual != NULL){
        if(strcmp(actual->nombre, nombre) == 0){
            if(anterior == NULL){
                cabeza = actual->sig;
            }else{
                anterior->sig = actual->sig;
            }
            free(actual);
            printf("Estudiante '%s' eliminado correctamente.\n\n", nombre);
            return cabeza;
        }
        anterior = actual;
        actual = actual->sig;
    }
    printf("No se encontró al estudiante '%s' para eliminar.\n\n", nombre);
    return cabeza;
}

void mostrar_mayor_promedio(Nodo *cabeza){
    if(cabeza == NULL){
        printf("No hay estudiantes registrados.\n\n");
        return;
    }
    Nodo *aux = cabeza;
    Nodo *mejor = cabeza;
    while(aux != NULL){
        if(aux->promedio > mejor->promedio){
            mejor = aux;
        }
        aux = aux->sig;
    }
    printf("\nEstudiante con el mayor promedio:\n");
    printf("Nombre: %s, Edad: %d, Promedio: %.2f\n\n",mejor->nombre, mejor->edad, mejor->promedio);
}

void liberar_lista(Nodo *cabeza) {
    Nodo *aux;
    while(cabeza != NULL){
        aux = cabeza;
        cabeza = cabeza->sig;
        free(aux);
    }
}

void leer_cadena(char *buffer, int max_len) {
    fgets(buffer, max_len, stdin);
    size_t len = strlen(buffer);
    if(len > 0 && buffer[len-1] == '\n'){
        buffer[len-1] = '\0';
    }
}

int main() {
    Nodo *lista = NULL;
    int opcion;
    char nombre[MAX_NOMBRE];
    int edad;
    float promedio;

    do{
        printf("===== GESTIÓN DE ESTUDIANTES =====\n");
        printf("1. Insertar estudiante al final\n");
        printf("2. Mostrar todos los estudiantes\n");
        printf("3. Buscar estudiante por nombre\n");
        printf("4. Eliminar estudiante por nombre\n");
        printf("5. Mostrar estudiante con mayor promedio\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar(); // limpiar el salto de línea

        switch (opcion) {
            case 1:
                printf("\n----- Insertar nuevo estudiante -----\n");
                printf("Nombre: ");
                leer_cadena(nombre, MAX_NOMBRE);
                printf("Edad: ");
                scanf("%d", &edad);
                printf("Promedio: ");
                scanf("%f", &promedio);
                getchar();
                lista = insertar_al_final(lista, nombre, edad, promedio);
                printf("Estudiante agregado correctamente.\n\n");
                break;
            case 2:
                mostrar_estudiantes(lista);
                break;
            case 3:
                printf("\nNombre a buscar: ");
                leer_cadena(nombre, MAX_NOMBRE);
                buscar_por_nombre(lista, nombre);
                break;
            case 4:
                printf("\nNombre del estudiante a eliminar: ");
                leer_cadena(nombre, MAX_NOMBRE);
                lista = eliminar_por_nombre(lista, nombre);
                break;
            case 5:
                mostrar_mayor_promedio(lista);
                break;
            case 0:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n\n");
        }
    }while(opcion != 0);

    liberar_lista(lista);
    return 0;
}