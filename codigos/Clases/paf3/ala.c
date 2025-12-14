#include <stdio.h>

// Códigos UTF-8 (C3 XX) para caracteres especiales
#define U_ACENTO 0xC3, 0xBA // ú
#define A_ACENTO 0xC3, 0xA1 // á
#define O_ACENTO 0xC3, 0xB3 // ó

// Prototipos de funciones
void limpiar_pantalla_simulado();
int mostrar_menu_con_estado(float caudal, char *planta, int plantas, float litros);
void calcular_tiempo(int cantidad_plantas, float litros_por_planta, float caudal, float *tiempo_min_ptr, float *litros_totales_ptr);
void generar_archivo(int cantidad_plantas, float litros_por_planta, float caudal, float tiempo_minutos, float litros_totales, char *tipo_planta);

// Función de limpieza de pantalla simulada (ANSI C)
void limpiar_pantalla_simulado() {
    // Imprime m%c%cs de 50 saltos de l%c%cnea para simular la limpieza de pantalla
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("--- Redibujando Men%c%c ---\n", U_ACENTO);
}

// Muestra el men%c%c y el estado actual de las variables
int mostrar_menu_con_estado(float caudal, char *planta, int plantas, float litros) {
    int opcion;
    
    // El formato de la salida se ajusta a lo solicitado, con los valores actuales:
    printf("----------------------------------------\n");
    printf("Sistema de riego\n");
    printf("----------------------------------------\n");
    printf("1. Caudal m%c%cximo (L/min): %.1f\n", A_ACENTO, caudal); // á
    printf("2. Tipo de planta o cultivo: %s\n", planta);
    printf("3. N%c%cmero de plantas: %d\n", U_ACENTO, plantas); // ú
    printf("4. Litros requeridos por planta: %.1f\n", litros);
    printf("5. Calcular y generar archivo\n");
    printf("6. Salir\n");
    printf("----------------------------------------\n");
    
    printf("Seleccione una opci%c%cn: ", O_ACENTO); // ó
    
    if (scanf("%d", &opcion) != 1) {
        // Limpiar el b%c%cfer en caso de entrada no num%c%crica.
        while (getchar() != '\n');
        opcion = -1; // Valor inv%c%clido.
    }
    
    return opcion;
}

// Funci%c%cn de c%c%clculo (igual que antes)
void calcular_tiempo(int cantidad_plantas, float litros_por_planta, float caudal, float *tiempo_min_ptr, float *litros_totales_ptr) {
    *litros_totales_ptr = (float)cantidad_plantas * litros_por_planta;

    if (caudal > 0) {
        *tiempo_min_ptr = (*litros_totales_ptr) / caudal;
    } else {
        *tiempo_min_ptr = 0.0;
    }
}

// Funci%c%cn para generar archivo (incluye el tipo de planta)
void generar_archivo(int cantidad_plantas, float litros_por_planta, float caudal, float tiempo_minutos, float litros_totales, char *tipo_planta) {
    FILE *archivo = fopen("riego.txt", "w");
    
    if (archivo == NULL) {
        printf("Error: No se pudo crear o abrir el archivo riego.txt\n");
        return;
    }

    fprintf(archivo, "/*\n");
    fprintf(archivo, "Sistema de riego por goteo\n");
    fprintf(archivo, "Tipo de cultivo: %s\n", tipo_planta);
    fprintf(archivo, "Plantas              : %d\n", cantidad_plantas);
    fprintf(archivo, "Litros por planta    : %.1f\n", litros_por_planta);
    fprintf(archivo, "Caudal v%c%clvula L/min : %.1f\n", A_ACENTO, caudal);
    fprintf(archivo, "*/\n");
    
    fprintf(archivo, "Tiempo de apertura   : %.2f min\n", tiempo_minutos);
    fprintf(archivo, "Tiempo en segundos   : %.0f S\n", tiempo_minutos * 60.0);
    fprintf(archivo, "Litros totales       : %.2f L\n", litros_totales);
    
    fprintf(archivo, "/*\n");
    fprintf(archivo, "*/\n");
    
    fclose(archivo);
    printf("\nArchivo 'riego.txt' generado con %c%cxito.\n", 0xC3, 0xA9);
}


int main() {
    // Variables de entrada: inicializadas a valores por defecto
    float caudal_max = 0.0;
    char tipo_planta[50] = "No definido";
    int num_plantas = 0;
    float litros_req_planta = 0.0;
    
    // Variables de salida:
    float tiempo_min = 0.0;
    float litros_totales = 0.0;
    
    int opcion;
    
    do {
        limpiar_pantalla_simulado();
        opcion = mostrar_menu_con_estado(caudal_max, tipo_planta, num_plantas, litros_req_planta);

        switch (opcion) {
            case 1:
                printf("\n--- INGRESO ---\n");
                printf("Ingrese nuevo Caudal m%c%cximo (Litros/min): ", A_ACENTO); // á
                scanf("%f", &caudal_max);
                // Limpiar el b%c%cfer despu%c%cs de scanf float
                while (getchar() != '\n'); 
                break;
            case 2:
                printf("\n--- INGRESO ---\n");
                printf("Ingrese Tipo de planta/cultivo: ");
                // Usamos gets() o fgets() pero solo con scanf() para el requisito
                scanf("%s", tipo_planta); 
                // Limpiar el b%c%cfer despu%c%cs de scanf string
                while (getchar() != '\n'); 
                break;
            case 3:
                printf("\n--- INGRESO ---\n");
                printf("Ingrese nuevo N%c%cmero de plantas: ", U_ACENTO); // ú
                scanf("%d", &num_plantas);
                 // Limpiar el b%c%cfer despu%c%cs de scanf int
                while (getchar() != '\n'); 
                break;
            case 4:
                printf("\n--- INGRESO ---\n");
                printf("Ingrese nuevos Litros requeridos por planta: ");
                scanf("%f", &litros_req_planta);
                // Limpiar el b%c%cfer despu%c%cs de scanf float
                while (getchar() != '\n'); 
                break;
            case 5:
                // Calcular y generar archivo
                if (caudal_max > 0 && num_plantas > 0 && litros_req_planta > 0) {
                    calcular_tiempo(num_plantas, litros_req_planta, caudal_max, &tiempo_min, &litros_totales);
                    generar_archivo(num_plantas, litros_req_planta, caudal_max, tiempo_min, litros_totales, tipo_planta);
                    printf("\nPresione ENTER para continuar...\n");
                    while (getchar() != '\n'); // Espera
                    opcion = 0; // Para que el ciclo se repita y muestre el men%c%c
                } else {
                    printf("\nERROR: Faltan datos necesarios (Caudal, Plantas o Litros).\n");
                    printf("Presione ENTER para continuar...\n");
                    while (getchar() != '\n'); // Espera
                    opcion = 0; // Para que el ciclo se repita y muestre el men%c%c
                }
                break;
            case 6:
                printf("\nSaliendo del programa. %c%cGracias!\n", A_ACENTO); // á
                break;
            default:
                printf("\nOpci%c%cn inv%c%clida. Presione ENTER para reintentar...\n", O_ACENTO, A_ACENTO); // ó, á
                while (getchar() != '\n'); // Espera
        }

    } while (opcion != 6);

    return 0;
}