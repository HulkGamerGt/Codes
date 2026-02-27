/*
 - Identificación del autor: Diego Solis Rojas
 - Fecha: 23 / 09 / 2025
 - Descripcion: Programa que maneja un archivo de texto llamado "nombres.txt" para almacenar,
 - ordenar ingresar y mostrar nombres y apellidos ingresados por el usuario, las opciones modificar y eliminar
 - no se encuentran disponibles, pero aparecen en el menu de opciones.
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h> // Para la función sleep solamente (la busque en internet).

#define MAX_NOMBRES 102
#define MAX_NUEVOS_REGISTROS 100

// Prototipos de funciones
void mostrar_menu(int *);
void option(int, char *);
void ingresar_nombres_apellidos(char *);
void mostrar_listado(char *);
void modificar_lista(char *);
void ordenar_nombres(char *);
void ordenar_apellidos(char *);
void eliminar_nombre(char *);

// Funciones auxiliares para la manipulacion de archivos y datos
void cargar_registros(char *, char[][MAX_NOMBRES], char[][MAX_NOMBRES], int *);
void guardar_registros(char *, char[][MAX_NOMBRES], char[][MAX_NOMBRES], int);
void intercambiar_registros_nombres(char[], char[]);
void intercambiar_registros_apellidos(char[], char[]);
//int buscar_registro(char[][MAX_NOMBRES], char[][MAX_NOMBRES], int, char *);

// Función principal
int main() {
    int op = 0;
    char nombre_archivo[] = "nombres.txt";

    FILE *archivo = fopen(nombre_archivo, "a");
    if (archivo == NULL) {
        printf("Error: No se pudo crear o abrir el archivo %s.\n", nombre_archivo);
        return 1;
    }
    fclose(archivo);

    do {
        mostrar_menu(&op);
        option(op, nombre_archivo);
    } while (op != 7);

    return 0;
}

// Muestras las opciones del menu
void mostrar_menu(int *opcion) {
    char input[10];
    printf("\n--------------- Menu de opciones ---------------\n");
    printf("1.- Ingresar nombres y apellidos.\n");
    printf("2.- Modificar.\n");
    printf("3.- Ordenar alfabeticamente por nombres.\n");
    printf("4.- Ordenar alfabeticamente por apellidos.\n");
    printf("5.- Eliminar.\n");
    printf("6.- Mostrar listado.\n");
    printf("7.- Salir / Finalizar.\n");
    printf("------------------------------------------------\n");
    printf("Seleccione una opcion: ");
    
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d", opcion);
}

// LLama a la funcion de la opcion seleccionada
void option(int opcion, char *nombre_archivo) {
    switch (opcion) {
        case 1:
            ingresar_nombres_apellidos(nombre_archivo);
            break;
        case 2:
            modificar_lista(nombre_archivo);
            break;
        case 3:
            ordenar_nombres(nombre_archivo);
            break;
        case 4:
            ordenar_apellidos(nombre_archivo);
            break;
        case 5:
            eliminar_nombre(nombre_archivo);
            break;
        case 6:
            mostrar_listado(nombre_archivo);
            break;
        case 7:
            printf("Programa finalizado. Hasta luego!\n");
            break;
        default:
            printf("Opcion invalida. Por favor, seleccione una opcion del 1 al 7.\n");
            break;
    }
}

// Funcion para manejar los nombres y apellidos
void ingresar_nombres_apellidos(char *nombre_archivo) {
    FILE *archivo = fopen(nombre_archivo, "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para escritura.\n");
        return;
    }
    
    char linea[MAX_NOMBRES];
    printf("Ingresador de nombres y apellidos (para iniciar con 'Enter' y para finalizar con doble 'Enter')\n");
    
    // Consumir el newline pendiente del menu
    while (getchar() != '\n');

    while (1) {
        printf("Nombre y Apellido: ");
        if (fgets(linea, sizeof(linea), stdin) == NULL) {
            break; 
        }

        linea[strcspn(linea, "\n")] = '\0';

        if (strlen(linea) == 0) {
            break;
        }

        // Se agrega un salto de línea antes de cada entrada para asegurar que se guarde en una nueva línea
        fprintf(archivo, "\n%s", linea);
    }
    fclose(archivo);
    printf("Saliendo de Nombres y apellidos...\n");
}

// Función que muestra el listado de nombres y apellidos.
void mostrar_listado(char *nombre_archivo) {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        printf("El archivo de nombres no existe o esta vacio.\n");
        return;
    }

    char linea[MAX_NOMBRES];
    printf("\n--- Listado de nombres y apellidos ---\n");
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        printf("%s", linea);
    }
    printf("\n--------------------------------------\n");
    sleep(3);
    fclose(archivo);
}

// Función que permite modificar un nombre o apellido existente (actualmente no funcional)
void modificar_lista(char *nombre_archivo) {
    printf("\n");
    printf("La opcion de 'Modificar' no disponible temporalmente, disculpe las molestias.\n");
    sleep(1.5);
    printf("Porfavor elija otra opcion del menu\n");
    sleep(2.5);
    /*
    char nombres[MAX_NUEVOS_REGISTROS][MAX_NOMBRES];
    char apellidos[MAX_NUEVOS_REGISTROS][MAX_NOMBRES];
    int num_registros = 0;
    cargar_registros(nombre_archivo, nombres, apellidos, &num_registros);

    char nombre_a_buscar[MAX_NOMBRES];
    printf("Ingrese el nombre completo (nombre y apellido) a modificar: ");
    while (getchar() != '\n'); 
    fgets(nombre_a_buscar, sizeof(nombre_a_buscar), stdin);
    nombre_a_buscar[strcspn(nombre_a_buscar, "\n")] = '\0';

    int indice = buscar_registro(nombres, apellidos, num_registros, nombre_a_buscar);
    if (indice != -1) {
        printf("Registro encontrado: %s %s\n", nombres[indice], apellidos[indice]);
        printf("Ingrese el nuevo nombre y apellido: ");
        char nueva_linea[MAX_NOMBRES];
        fgets(nueva_linea, sizeof(nueva_linea), stdin);
        nueva_linea[strcspn(nueva_linea, "\n")] = '\0';
        
        char *ptr_nombre = nueva_linea;
        char *ptr_espacio = strchr(ptr_nombre, ' ');
        if (ptr_espacio) {
            *ptr_espacio = '\0';
            strcpy(nombres[indice], ptr_nombre);
            strcpy(apellidos[indice], ptr_espacio + 1);
        } else {
            strcpy(nombres[indice], ptr_nombre);
            apellidos[indice][0] = '\0';
        }

        guardar_registros(nombre_archivo, nombres, apellidos, num_registros);
        printf("Registro modificado con exito.\n");
    } else {
        printf("Registro no encontrado.\n");
    }
    */
}

// Función que ordena el listado por nombres.(elimina algunos, no se porque, creo que son por los acentos)
void ordenar_nombres(char *nombre_archivo) {
    char nombres[MAX_NUEVOS_REGISTROS][MAX_NOMBRES];
    char apellidos[MAX_NUEVOS_REGISTROS][MAX_NOMBRES];
    int num_registros = 0;
    cargar_registros(nombre_archivo, nombres, apellidos, &num_registros);

    for (int i = 0; i < num_registros - 1; i++) {
        for (int j = 0; j < num_registros - i - 1; j++) {
            if (strcmp(nombres[j], nombres[j + 1]) > 0) {
                intercambiar_registros_nombres(nombres[j], nombres[j + 1]);
                intercambiar_registros_apellidos(apellidos[j], apellidos[j + 1]);
            }
        }
    }
    guardar_registros(nombre_archivo, nombres, apellidos, num_registros);
    printf("Listado ordenado por nombres exitosamente.\n");
}

// Función que ordena el listado por apellidos.(elimina algunos, no se porque, creo que son por los acentos)
void ordenar_apellidos(char *nombre_archivo) {
    char nombres[MAX_NUEVOS_REGISTROS][MAX_NOMBRES];
    char apellidos[MAX_NUEVOS_REGISTROS][MAX_NOMBRES];
    int num_registros = 0;
    cargar_registros(nombre_archivo, nombres, apellidos, &num_registros);

    for (int i = 0; i < num_registros - 1; i++) {
        for (int j = 0; j < num_registros - i - 1; j++) {
            if (strcmp(apellidos[j], apellidos[j + 1]) > 0) {
                intercambiar_registros_nombres(nombres[j], nombres[j + 1]);
                intercambiar_registros_apellidos(apellidos[j], apellidos[j + 1]);
            }
        }
    }
    guardar_registros(nombre_archivo, nombres, apellidos, num_registros);
    printf("Listado ordenado por apellidos exitosamente.\n");
}

// Función que elimina un nombre o apellido existente (actualmente no funcional)
void eliminar_nombre(char *nombre_archivo) {
    printf("La opcion de 'Eliminar' no se encuentra disponible temporalmente, disculpe las molestias\n");
    sleep(1.5);
    printf("Porfavor elija otra opcion del menu\n");
    sleep(2.5);
    /*
    char nombres[MAX_NUEVOS_REGISTROS][MAX_NOMBRES];
    char apellidos[MAX_NUEVOS_REGISTROS][MAX_NOMBRES];
    int num_registros = 0;
    cargar_registros(nombre_archivo, nombres, apellidos, &num_registros);

    char nombre_a_eliminar[MAX_NOMBRES];
    printf("Ingrese el nombre completo (nombre y apellido) a eliminar: ");
    while (getchar() != '\n');
    fgets(nombre_a_eliminar, sizeof(nombre_a_eliminar), stdin);
    nombre_a_eliminar[strcspn(nombre_a_eliminar, "\n")] = '\0';

    int indice = buscar_registro(nombres, apellidos, num_registros, nombre_a_eliminar);
    if (indice != -1) {
        for (int i = indice; i < num_registros - 1; i++) {
            strcpy(nombres[i], nombres[i + 1]);
            strcpy(apellidos[i], apellidos[i + 1]);
        }
        num_registros--;
        guardar_registros(nombre_archivo, nombres, apellidos, num_registros);
        printf("Registro eliminado con exito.\n");
    } else {
        printf("Registro no encontrado.\n");
    }
    */
}

// Funciones Auxiliares para Manipulación de Archivos
void cargar_registros(char *nombre_archivo, char nombres[][MAX_NOMBRES], char apellidos[][MAX_NOMBRES], int *num_registros) {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        *num_registros = 0;
        return;
    }

    char linea[MAX_NOMBRES];
    *num_registros = 0;
    while (fgets(linea, sizeof(linea), archivo) != NULL && *num_registros < MAX_NUEVOS_REGISTROS) {
        linea[strcspn(linea, "\n")] = '\0';
        char *ptr_nombre = linea;
        char *ptr_espacio = strchr(ptr_nombre, ' ');
        if (ptr_espacio) {
            *ptr_espacio = '\0';
            strcpy(nombres[*num_registros], ptr_nombre);
            strcpy(apellidos[*num_registros], ptr_espacio + 1);
        } else {
            strcpy(nombres[*num_registros], ptr_nombre);
            apellidos[*num_registros][0] = '\0';
        }
        (*num_registros)++;
    }
    fclose(archivo);
}

// Guarda los registros en el archivo
void guardar_registros(char *nombre_archivo, char nombres[][MAX_NOMBRES], char apellidos[][MAX_NOMBRES], int num_registros) {
    FILE *archivo = fopen(nombre_archivo, "w");
    if (archivo == NULL) {
        printf("Error al guardar el archivo.\n");
        return;
    }

    for (int i = 0; i < num_registros; i++) {
        if (strlen(apellidos[i]) > 0) {
            fprintf(archivo, "%s %s\n", nombres[i], apellidos[i]);
        } else {
            fprintf(archivo, "%s\n", nombres[i]);
        }
    }
    fclose(archivo);
}

// Intercambia dos registros
void intercambiar_registros_nombres(char a[], char b[]) {
    char temp[MAX_NOMBRES];
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}

// Intercambia dos registros
void intercambiar_registros_apellidos(char a[], char b[]) {
    char temp[MAX_NOMBRES];
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}
/*
int buscar_registro(char nombres[][MAX_NOMBRES], char apellidos[][MAX_NOMBRES], int num_registros, char *nombre_completo) {
    for (int i = 0; i < num_registros; i++) {
        char nombre_completo_registro[MAX_NOMBRES * 2];
        strcpy(nombre_completo_registro, nombres[i]);
        strcat(nombre_completo_registro, " ");
        strcat(nombre_completo_registro, apellidos[i]);

    }
    return -1;
}
*/