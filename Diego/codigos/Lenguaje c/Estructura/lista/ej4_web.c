#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define URL_MAX 100
#define FECHA_MAX 20

typedef struct Nodo {
    char url[URL_MAX];
    char fecha[FECHA_MAX];
    struct Nodo *sig;
} Nodo;

// Prototipos de funciones
Nodo* crear_nodo(char* url, char* fecha);
Nodo* insertar_al_final(Nodo *cabeza, char* url, char* fecha);
void mostrar_historial(Nodo *cabeza);
Nodo* eliminar_url(Nodo *cabeza, char* url);
int contar_por_dominio(Nodo *cabeza, char* dominio);
Nodo* vaciar_historial(Nodo *cabeza);

int main() {
    Nodo *lista = NULL;
    int opcion;
    char temp_url[URL_MAX], temp_fecha[FECHA_MAX];

    do {
        printf("\n--- SIMULADOR DE HISTORIAL WEB ---\n");
        printf("1. Agregar pagina\n");
        printf("2. Mostrar historial\n");
        printf("3. Eliminar una URL\n");
        printf("4. Contar paginas de un dominio\n");
        printf("5. Vaciar historial\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar el salto de linea

        switch(opcion){
            case 1:
                printf("Ingrese URL: ");
                fgets(temp_url, URL_MAX, stdin);
                temp_url[strcspn(temp_url, "\n")] = 0; // Quitar el salto de linea

                printf("Ingrese Fecha (DD/MM/AAAA): ");
                fgets(temp_fecha, FECHA_MAX, stdin);
                temp_fecha[strcspn(temp_fecha, "\n")] = 0;

                lista = insertar_al_final(lista, temp_url, temp_fecha);
                printf("Pagina agregada.\n");
                break;

            case 2:
                mostrar_historial(lista);
                break;

            case 3:
                printf("Ingrese la URL exacta a eliminar: ");
                fgets(temp_url, URL_MAX, stdin);
                temp_url[strcspn(temp_url, "\n")] = 0;
                lista = eliminar_url(lista, temp_url);
                break;

            case 4:
                printf("Ingrese el dominio a buscar (ej: google): ");
                fgets(temp_url, URL_MAX, stdin);
                temp_url[strcspn(temp_url, "\n")] = 0;
                printf("Se encontraron %d paginas de ese dominio.\n", contar_por_dominio(lista, temp_url));
                break;

            case 5:
                lista = vaciar_historial(lista);
                printf("Historial vaciado.\n");
                break;

            case 0:
                printf("Saliendo...\n");
                lista = vaciar_historial(lista);
                break;

            default:
                printf("Opcion no valida.\n");
        }
    }while(opcion != 0);

    return 0;
}

// Crea un nuevo nodo en memoria
Nodo* crear_nodo(char* url, char* fecha) {
    Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo) {
        strcpy(nuevo->url, url);
        strcpy(nuevo->fecha, fecha);
        nuevo->sig = NULL;
    }
    return nuevo;
}

// Inserta al final para mantener orden cronologico
Nodo* insertar_al_final(Nodo *cabeza, char* url, char* fecha) {
    Nodo *nuevo = crear_nodo(url, fecha);
    if (cabeza == NULL) return nuevo;
    
    Nodo *aux = cabeza;
    while (aux->sig != NULL) aux = aux->sig;
    aux->sig = nuevo;
    return cabeza;
}

// Recorre la lista imprimiendo los datos
void mostrar_historial(Nodo *cabeza) {
    if (cabeza == NULL) {
        printf("\nEl historial esta vacio.\n");
        return;
    }
    printf("\n--- HISTORIAL ---\n");
    Nodo *aux = cabeza;
    while (aux != NULL) {
        printf("[%s] - URL: %s\n", aux->fecha, aux->url);
        aux = aux->sig;
    }
}

// Busca una URL y la elimina de la lista
Nodo* eliminar_url(Nodo *cabeza, char* url) {
    Nodo *actual = cabeza;
    Nodo *anterior = NULL;

    while (actual != NULL) {
        if (strcmp(actual->url, url) == 0) {
            if (anterior == NULL) {
                cabeza = actual->sig;
            } else {
                anterior->sig = actual->sig;
            }
            free(actual);
            printf("URL eliminada con exito.\n");
            return cabeza;
        }
        anterior = actual;
        actual = actual->sig;
    }
    printf("URL no encontrada.\n");
    return cabeza;
}

// Cuenta cuantas URLs contienen el texto buscado
int contar_por_dominio(Nodo *cabeza, char* dominio) {
    int contador = 0;
    Nodo *aux = cabeza;
    while (aux != NULL) {
        if (strstr(aux->url, dominio) != NULL) {
            contador++;
        }
        aux = aux->sig;
    }
    return contador;
}

// Libera toda la memoria de la lista
Nodo* vaciar_historial(Nodo *cabeza) {
    Nodo *aux;
    while (cabeza != NULL) {
        aux = cabeza;
        cabeza = cabeza->sig;
        free(aux);
    }
    return NULL;
}