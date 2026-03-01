#include <stdio.h>
#include <string.h>

// Pregunta al usuario si desea crear un archivo nuevo
int ask_create_new_file() {
    int choice;
    printf("¿Desea crear un archivo nuevo? (1 para sí, 0 para no): ");
    scanf("%d", &choice);
    getchar(); // Consumir el salto de línea
    return choice;
}

// Crea un archivo nuevo y permite escribir contenido en él
void create_new_file(char *filename) {
    printf("Ingrese el nombre del archivo nuevo: ");
    fgets(filename, 100, stdin);
    filename[strcspn(filename, "\n")] = '\0'; // Eliminar el salto de línea
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error al crear el archivo.\n");
        return;
    }
    printf("Ingrese contenido (termine con 'END' en una nueva línea):\n");
    char content[1000];
    while (fgets(content, sizeof(content), stdin) != NULL) {
        if (strcmp(content, "END\n") == 0) {
            break;
        }
        fprintf(fp, "%s", content);
    }
    fclose(fp);
    printf("Archivo creado y guardado con éxito.\n");
}

// Obtiene un nombre de archivo existente válido
void get_existing_file_name(char *filename) {
    while (1) {
        printf("Ingrese el nombre del archivo existente: ");
        fgets(filename, 100, stdin);
        filename[strcspn(filename, "\n")] = '\0'; // Eliminar el salto de línea
        FILE *fp = fopen(filename, "r");
        if (fp != NULL) {
            fclose(fp);
            break;
        } else {
            printf("El archivo no existe. Intente de nuevo.\n");
        }
    }
}

// Lee el carácter a buscar desde la entrada del usuario
char get_search_char() {
    char search_char;
    printf("Ingrese el carácter a buscar: ");
    scanf("%c", &search_char);
    getchar(); // Consumir el salto de línea
    return search_char;
}

// Verifica si un carácter está presente en el archivo
int check_char_in_file(const char *filename, char search_char) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error al abrir el archivo.\n");
        return -1; // Indicador de error
    }
    int found = 0;
    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == search_char) {
            found = 1;
            break;
        }
    }
    fclose(fp);
    return found;
}

int main() {
    char filename[100];
    int create_new = ask_create_new_file();
    if (create_new == 1) {
        create_new_file(filename);
    } else {
        get_existing_file_name(filename);
    }
    char search_char = get_search_char();
    int result = check_char_in_file(filename, search_char);
    if (result == 1) {
        printf("El carácter '%c' está en el archivo.\n", search_char);
    } else if (result == 0) {
        printf("El carácter '%c' no está en el archivo.\n", search_char);
    } else {
        printf("Error al verificar el archivo.\n");
    }
    return 0;
}