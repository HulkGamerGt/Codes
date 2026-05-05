#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMBRE 40

typedef struct Nodo {
    int codigo;
    char nombre[MAX_NOMBRE];
    int stock;
    float precio;
    struct Nodo *sig;
} Nodo;

Nodo *crear_nodo(int codigo, const char *nombre, int stock, float precio) {
    Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        printf("Error de memoria.\n");
        exit(1);
    }
    nuevo->codigo = codigo;
    strcpy(nuevo->nombre, nombre);
    nuevo->stock = stock;
    nuevo->precio = precio;
    nuevo->sig = NULL;
    return nuevo;
}

Nodo* insertar_ordenado(Nodo *cabeza, int codigo, const char *nombre, int stock, float precio) {
    Nodo *nuevo = crear_nodo(codigo, nombre, stock, precio);
    Nodo *actual = cabeza;
    Nodo *anterior = NULL;

    while (actual != NULL && actual->codigo < codigo) {
        anterior = actual;
        actual = actual->sig;
    }

    if (actual != NULL && actual->codigo == codigo) {
        printf("Ya existe un producto con código %d. No se insertó.\n", codigo);
        free(nuevo);
        return cabeza;
    }

    nuevo->sig = actual;
    if (anterior == NULL) {
        cabeza = nuevo;
    } else {
        anterior->sig = nuevo;
    }
    printf("Producto insertado correctamente.\n");
    return cabeza;
}

void mostrar_productos(Nodo *cabeza) {
    if (cabeza == NULL) {
        printf("No hay productos registrados.\n");
        return;
    }
    printf("\n=== LISTA DE PRODUCTOS ===\n");
    Nodo *aux = cabeza;
    int cont = 1;
    while (aux != NULL) {
        printf("%d. Código: %d, Nombre: %s, Stock: %d, Precio: %.2f\n",
               cont++, aux->codigo, aux->nombre, aux->stock, aux->precio);
        aux = aux->sig;
    }
    printf("===========================\n\n");
}

void actualizar_stock(Nodo *cabeza, int codigo, int nuevo_stock) {
    Nodo *aux = cabeza;
    while (aux != NULL) {
        if (aux->codigo == codigo) {
            aux->stock = nuevo_stock;
            printf("Stock del producto %d actualizado a %d.\n", codigo, nuevo_stock);
            return;
        }
        aux = aux->sig;
    }
    printf("Producto con código %d no encontrado.\n", codigo);
}

float valor_total_inventario(Nodo *cabeza) {
    float total = 0.0;
    Nodo *aux = cabeza;
    while (aux != NULL) {
        total += aux->stock * aux->precio;
        aux = aux->sig;
    }
    return total;
}

Nodo* eliminar_stock_cero(Nodo *cabeza) {
    Nodo *actual = cabeza;
    Nodo *anterior = NULL;
    int eliminados = 0;

    while (actual != NULL) {
        if (actual->stock == 0) {
            // Eliminar nodo actual
            Nodo *temp = actual;
            if (anterior == NULL) {
                cabeza = actual->sig;
                actual = cabeza;
            } else {
                anterior->sig = actual->sig;
                actual = actual->sig;
            }
            free(temp);
            eliminados++;
        } else {
            anterior = actual;
            actual = actual->sig;
        }
    }
    if (eliminados > 0)
        printf("Se eliminaron %d producto(s) con stock cero.\n", eliminados);
    else
        printf("No hay productos con stock cero.\n");
    return cabeza;
}

void liberar_lista(Nodo *cabeza) {
    Nodo *aux;
    while (cabeza != NULL) {
        aux = cabeza;
        cabeza = cabeza->sig;
        free(aux);
    }
}

void leer_cadena(char *buffer, int max_len) {
    fgets(buffer, max_len, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n')
        buffer[len-1] = '\0';
}

int main() {
    Nodo *lista = NULL;
    int opcion;
    int codigo, stock, nuevo_stock;
    char nombre[MAX_NOMBRE];
    float precio;

    do {
        printf("\n===== GESTIÓN DE PRODUCTOS =====\n");
        printf("1. Insertar producto (ordenado por código)\n");
        printf("2. Actualizar stock de un producto\n");
        printf("3. Calcular valor total del inventario\n");
        printf("4. Eliminar productos con stock = 0\n");
        printf("5. Mostrar lista de productos\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar();  
        
        switch (opcion) {
            case 1:
                printf("\n--- Insertar nuevo producto ---\n");
                printf("Código: ");
                scanf("%d", &codigo);
                getchar();
                printf("Nombre: ");
                leer_cadena(nombre, MAX_NOMBRE);
                printf("Stock: ");
                scanf("%d", &stock);
                printf("Precio: ");
                scanf("%f", &precio);
                getchar();
                lista = insertar_ordenado(lista, codigo, nombre, stock, precio);
                break;

            case 2:
                printf("\n--- Actualizar stock ---\n");
                printf("Código del producto: ");
                scanf("%d", &codigo);
                printf("Nuevo stock: ");
                scanf("%d", &nuevo_stock);
                actualizar_stock(lista, codigo, nuevo_stock);
                break;

            case 3:
                printf("\n--- Valor total del inventario ---\n");
                printf("Total: $%.2f\n", valor_total_inventario(lista));
                break;

            case 4:
                printf("\n--- Eliminar productos con stock cero ---\n");
                lista = eliminar_stock_cero(lista);
                break;

            case 5:
                mostrar_productos(lista);
                break;

            case 0:
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 0);

    liberar_lista(lista);
    return 0;
}