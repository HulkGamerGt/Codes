/*
 | Identificación del autor: Diego M. Solis Rojas.
 | Curso: PROGRAMACIÓN-S1 [INF123]
 | Fecha: ( 30 / 09 / 2025 )
 | Descripcion: Este programa es un gestor de nombres y apellidos que funciona a través de un menú que se ve en la terminal. 
 | |||||||||||  Permite al usuario administrar una lista de personas que se guarda de forma permanente  en un archivo de texto,
 | |||||||||||  ofreciendo funciones para agregar, modificar, eliminar, mostrar y ordenar los registros. 
*/
#include <stdio.h>
#include <string.h>

#define MAX_NOMBRES 110           // Máxima longitud para nombres y apellidos
#define MAX_NUEVOS_REGISTROS 110  // Máximo número de registros en la lista

// Prototipos de funciones
void mostrar_menu(int *);
void option(int, char *);
void ingresar_nombres_apellidos(char *);
void mostrar_listado(char *);
void modificar_lista(char *);
void ordenar_nombres(char *);
void ordenar_apellidos(char *);
void eliminar_nombre(char *);
void Encontrar_nombre_mas_largo(char *);
void Invertir_lista_con_apellido_nombre(char *);

// Funciones auxiliares
void cargar_registros(char *, char[][MAX_NOMBRES], char[][MAX_NOMBRES], int *);
void guardar_registros(char *, char[][MAX_NOMBRES], char[][MAX_NOMBRES], int);
void intercambiar_registros(char[], char[]);
int buscar_registro(char[][MAX_NOMBRES], char[][MAX_NOMBRES], int, char *);
void normalize(const char *, char *);
int compare_normalized(const char *, const char *);

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
    } while (op != 9);

    return 0;
}

// Muestra las opciones del menú
void mostrar_menu(int *opcion) {
    char input[10];
    printf("\n---------------- Menu de opciones ----------------\n");
    printf("1.- Ingresar nombres y apellidos.\n");
    printf("2.- Modificar.\n");
    printf("3.- Ordenar alfabeticamente por nombres.\n");
    printf("4.- Ordenar alfabeticamente por apellidos.\n");
    printf("5.- Encontrar el nombre más largo. \n");
    printf("6.- Invertir la lista con el apellido y el nombre.\n");
    printf("7.- Eliminar.\n");
    printf("8.- Mostrar listado.\n");
    printf("9.- Salir / Finalizar.\n");
    printf("----------------------------------------------------\n");
    printf("Seleccione una opcion: ");
    if (fgets(input, sizeof(input), stdin)) {
        sscanf(input, "%d", opcion);
    } else {
        *opcion = 0;
    }
}

// Llama a la función de la opción seleccionada
void option(int opcion, char *nombre_archivo) {
    switch (opcion) {
        case 1: ingresar_nombres_apellidos(nombre_archivo); break;
        case 2: modificar_lista(nombre_archivo); break;
        case 3: ordenar_nombres(nombre_archivo); break;
        case 4: ordenar_apellidos(nombre_archivo); break;
        case 5: Encontrar_nombre_mas_largo(nombre_archivo); break;
        case 6: Invertir_lista_con_apellido_nombre(nombre_archivo); break;
        case 7: eliminar_nombre(nombre_archivo); break;
        case 8: mostrar_listado(nombre_archivo); break;
        case 9: printf("Programa finalizado. Hasta luego!\n"); break;
        default: printf("Opcion invalida. Por favor, seleccione una opcion del 1 al 9.\n"); break;
    }
}

// Función para ingresar nombres y apellidos
void ingresar_nombres_apellidos(char *nombre_archivo) {
    char modo_apertura[2];
    char linea[MAX_NOMBRES];
    char opcion_modo;
    FILE *archivo;

    printf("¿Desea agregar al final (a) o sobreescribir el archivo (s)? (a/s): ");
    scanf(" %c", &opcion_modo);
    getchar(); // Consumir el salto de línea

    strcpy(modo_apertura, (opcion_modo == 's' || opcion_modo == 'S') ? "w" : "a");

    archivo = fopen(nombre_archivo, modo_apertura);
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    printf("Ingrese nombres y apellidos (presione Enter para agregar, doble Enter para finalizar)\n");
    while (1) {
        printf("Nombre y Apellido: ");
        fgets(linea, sizeof(linea), stdin);
        linea[strcspn(linea, "\n")] = '\0';
        if (strlen(linea) == 0) break;
        fprintf(archivo, "%s\n", linea);
    }

    fclose(archivo);
    printf("Saliendo del modo de ingreso...\n");
}

// Función que muestra el listado de nombres y apellidos
void mostrar_listado(char *nombre_archivo) {
    FILE *archivo = fopen(nombre_archivo, "r");
    char linea[MAX_NOMBRES];
    if (archivo == NULL) {
        printf("El archivo de nombres no existe o esta vacio.\n");
        return;
    }
    printf("\n--- Listado de nombres y apellidos ---\n");
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        printf("%s", linea);
    }
    printf("--------------------------------------\n");
    fclose(archivo);
}

// Función que permite modificar un nombre o apellido existente
void modificar_lista(char *nombre_archivo) {
    char nombres[MAX_NUEVOS_REGISTROS][MAX_NOMBRES];
    char apellidos[MAX_NUEVOS_REGISTROS][MAX_NOMBRES];
    char nombre_a_buscar[MAX_NOMBRES];
    char nueva_linea[MAX_NOMBRES];
    int num_registros = 0;
    int indice;

    cargar_registros(nombre_archivo, nombres, apellidos, &num_registros);
    if (num_registros == 0) {
        printf("No hay registros para modificar.\n");
        return;
    }

    printf("Ingrese el nombre completo (nombre y apellido) a modificar: ");
    fgets(nombre_a_buscar, sizeof(nombre_a_buscar), stdin);
    nombre_a_buscar[strcspn(nombre_a_buscar, "\n")] = '\0';

    indice = buscar_registro(nombres, apellidos, num_registros, nombre_a_buscar);
    if (indice != -1) {
        printf("Registro encontrado: %s %s\n", nombres[indice], apellidos[indice]);
        printf("Ingrese el nuevo nombre y apellido: ");
        fgets(nueva_linea, sizeof(nueva_linea), stdin);
        nueva_linea[strcspn(nueva_linea, "\n")] = '\0';

        char *ptr_espacio = strchr(nueva_linea, ' ');
        if (ptr_espacio) {
            *ptr_espacio = '\0';
            strcpy(nombres[indice], nueva_linea);
            strcpy(apellidos[indice], ptr_espacio + 1);
        } else {
            strcpy(nombres[indice], nueva_linea);
            apellidos[indice][0] = '\0';
        }
        guardar_registros(nombre_archivo, nombres, apellidos, num_registros);
        printf("Registro modificado con exito.\n");
    } else {
        printf("Registro no encontrado.\n");
    }
}

// Función que ordena el listado por nombres alfabéticamente
void ordenar_nombres(char *nombre_archivo) {
    char nombres[MAX_NUEVOS_REGISTROS][MAX_NOMBRES];
    char apellidos[MAX_NUEVOS_REGISTROS][MAX_NOMBRES];
    int num_registros = 0;
    cargar_registros(nombre_archivo, nombres, apellidos, &num_registros);

    if (num_registros < 2) {
        printf("No hay suficientes registros para ordenar.\n");
        return;
    }

    for (int i = 0; i < num_registros - 1; i++) {
        for (int j = 0; j < num_registros - i - 1; j++) {
            if (compare_normalized(nombres[j], nombres[j + 1]) > 0) {
                intercambiar_registros(nombres[j], nombres[j + 1]);
                intercambiar_registros(apellidos[j], apellidos[j + 1]);
            }
        }
    }
    guardar_registros(nombre_archivo, nombres, apellidos, num_registros);
    printf("Listado ordenado por nombres exitosamente.\n");
}

// Función que ordena el listado por apellidos alfabéticamente
void ordenar_apellidos(char *nombre_archivo) {
    char nombres[MAX_NUEVOS_REGISTROS][MAX_NOMBRES];
    char apellidos[MAX_NUEVOS_REGISTROS][MAX_NOMBRES];
    int num_registros = 0;
    cargar_registros(nombre_archivo, nombres, apellidos, &num_registros);

    if (num_registros < 2) {
        printf("No hay suficientes registros para ordenar.\n");
        return;
    }
    
    for (int i = 0; i < num_registros - 1; i++) {
        for (int j = 0; j < num_registros - i - 1; j++) {
            if (compare_normalized(apellidos[j], apellidos[j + 1]) > 0) {
                intercambiar_registros(nombres[j], nombres[j + 1]);
                intercambiar_registros(apellidos[j], apellidos[j + 1]);
            }
        }
    }
    guardar_registros(nombre_archivo, nombres, apellidos, num_registros);
    printf("Listado ordenado por apellidos exitosamente.\n");
}

// Función que elimina un nombre o apellido existente
void eliminar_nombre(char *nombre_archivo) {
    char nombres[MAX_NUEVOS_REGISTROS][MAX_NOMBRES];
    char apellidos[MAX_NUEVOS_REGISTROS][MAX_NOMBRES];
    char nombre_a_eliminar[MAX_NOMBRES];
    char confirmacion = 'n';
    int num_registros = 0;
    int indice;
    cargar_registros(nombre_archivo, nombres, apellidos, &num_registros);
    
    if (num_registros == 0) {
        printf("No hay registros para eliminar.\n");
        return;
    }

    printf("Ingrese el nombre completo a eliminar: ");
    fgets(nombre_a_eliminar, sizeof(nombre_a_eliminar), stdin);
    nombre_a_eliminar[strcspn(nombre_a_eliminar, "\n")] = '\0';
    
    indice = buscar_registro(nombres, apellidos, num_registros, nombre_a_eliminar);
    if (indice != -1) {
        printf("Registro encontrado: %s %s\n", nombres[indice], apellidos[indice]);
        printf("¿Está seguro de que desea eliminarlo? (s/n): ");
        scanf(" %c", &confirmacion);
        getchar();

        if (confirmacion == 's' || confirmacion == 'S') {
            for (int i = indice; i < num_registros - 1; i++) {
                strcpy(nombres[i], nombres[i + 1]);
                strcpy(apellidos[i], apellidos[i + 1]);
            }
            num_registros--;
            guardar_registros(nombre_archivo, nombres, apellidos, num_registros);
            printf("Registro eliminado con exito.\n");
        } else {
            printf("Eliminación cancelada.\n");
        }
    } else {
        printf("Registro no encontrado.\n");
    }
}

// Encuentra el nombre (no el nombre completo) más largo en la lista
void Encontrar_nombre_mas_largo(char *nombre_archivo) {
    char nombres[MAX_NUEVOS_REGISTROS][MAX_NOMBRES];
    char apellidos[MAX_NUEVOS_REGISTROS][MAX_NOMBRES];
    int num_registros = 0;
    int max_len = -1;
    int idx = -1;

    cargar_registros(nombre_archivo, nombres, apellidos, &num_registros);
    if (num_registros == 0) {
        printf("No hay registros para evaluar.\n");
        return;
    }

    for (int i = 0; i < num_registros; i++) {
        int len = strlen(nombres[i]);
        if (len > max_len) {
            max_len = len;
            idx = i;
        }
    }

    if (idx != -1) {
        char nombre_completo[MAX_NOMBRES * 2];
        if (apellidos[idx][0] != '\0') {
            sprintf(nombre_completo, "%s %s", nombres[idx], apellidos[idx]);
        } else {
            strcpy(nombre_completo, nombres[idx]);
        }
        printf("El nombre mas largo es \"%s\" (en la entrada \"%s\") con %d caracteres.\n", nombres[idx], nombre_completo, max_len);
    }
}

// Invierte el orden de nombre y apellido en cada línea
void Invertir_lista_con_apellido_nombre(char *nombre_archivo) {
    char nombres[MAX_NUEVOS_REGISTROS][MAX_NOMBRES];
    char apellidos[MAX_NUEVOS_REGISTROS][MAX_NOMBRES];
    int num_registros = 0;
    cargar_registros(nombre_archivo, nombres, apellidos, &num_registros);

    if (num_registros == 0) {
        printf("No hay registros para invertir.\n");
        return;
    }

    for (int i = 0; i < num_registros; i++) {
        char temp[MAX_NOMBRES];
        strcpy(temp, nombres[i]);
        strcpy(nombres[i], apellidos[i]);
        strcpy(apellidos[i], temp);
    }

    guardar_registros(nombre_archivo, nombres, apellidos, num_registros);
    printf("Lista invertida (apellido, nombre) exitosamente.\n");
}

// Carga los registros desde el archivo a los arreglos
void cargar_registros(char *nombre_archivo, char nombres[][MAX_NOMBRES], char apellidos[][MAX_NOMBRES], int *num_registros) {
    FILE *archivo = fopen(nombre_archivo, "r");
    char linea[MAX_NOMBRES];
    if (archivo == NULL) {
        *num_registros = 0;
        return;
    }

    *num_registros = 0;
    while (fgets(linea, sizeof(linea), archivo) != NULL && *num_registros < MAX_NUEVOS_REGISTROS) {
        linea[strcspn(linea, "\n")] = '\0';
        if (strlen(linea) == 0) continue;

        char *ptr_espacio = strchr(linea, ' ');
        if (ptr_espacio) {
            *ptr_espacio = '\0';
            strcpy(nombres[*num_registros], linea);
            strcpy(apellidos[*num_registros], ptr_espacio + 1);
        } else {
            strcpy(nombres[*num_registros], linea);
            apellidos[*num_registros][0] = '\0';
        }
        (*num_registros)++;
    }
    fclose(archivo);
}

// Guarda los registros de los arreglos al archivo
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

// Intercambia el contenido de dos cadenas
void intercambiar_registros(char a[], char b[]) {
    char temp[MAX_NOMBRES];
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}

// Busca un registro por nombre completo
int buscar_registro(char nombres[][MAX_NOMBRES], char apellidos[][MAX_NOMBRES], int num_registros, char *nombre_completo) {
    char nombre_completo_registro[MAX_NOMBRES * 2];
    for (int i = 0; i < num_registros; i++) {
        if (apellidos[i][0] == '\0') {
            strcpy(nombre_completo_registro, nombres[i]);
        } else {
            sprintf(nombre_completo_registro, "%s %s", nombres[i], apellidos[i]);
        }
        if (strcmp(nombre_completo_registro, nombre_completo) == 0) {
            return i;
        }
    }
    return -1;
}

//Normaliza una cadena: la convierte a minúsculas y le quita las tildes. Lo investigue
void normalize(const char *in, char *out) {
    while (*in) {
        // Usamos 'unsigned char' para manejar correctamente los valores de los bytes
        unsigned char c1 = *in;
        unsigned char c2 = *(in + 1); // Vemos el siguiente byte por si es un carácter especial

        // Si es una letra mayúscula normal (ASCII)
        if (c1 >= 'A' && c1 <= 'Z') {
            *out++ = c1 + 32; // La convertimos a minúscula
            in++;
        }
        // Si es un carácter especial de 2 bytes (como á, é, í, ó, ú, ñ)
        // El primer byte de estos caracteres es 195 
        else if (c1 == 195) {
            // Verificamos el segundo byte para saber qué letra es
            if (c2 == 161 || c2 == 129) { // á (161) o Á (129)
                *out++ = 'a';
            } else if (c2 == 169 || c2 == 137) { // é (169) o É (137)
                *out++ = 'e';
            } else if (c2 == 173 || c2 == 141) { // í (173) o Í (141)
                *out++ = 'i';
            } else if (c2 == 179 || c2 == 147) { // ó (179) o Ó (147)
                *out++ = 'o';
            } else if (c2 == 186 || c2 == 154 || c2 == 188 || c2 == 156) { // ú, Ú, ü, Ü
                *out++ = 'u';
            } else if (c2 == 177 || c2 == 145) { // ñ (177) o Ñ (145)
                *out++ = 'n';
            }
            // Como leímos 2 bytes (c1 y c2), avanzamos el puntero 2 posiciones
            in += 2;
        }
        // Si es cualquier otro carácter normal (minúsculas, números, etc.)
        else {
            *out++ = c1;
            in++;
        }
    }
    *out = '\0'; // Cerramos la cadena de salida
}

// Compara dos cadenas después de normalizarlas
int compare_normalized(const char *a, const char *b) {
    char buf_a[MAX_NOMBRES];
    char buf_b[MAX_NOMBRES];
    normalize(a, buf_a);
    normalize(b, buf_b);
    return strcmp(buf_a, buf_b);
}