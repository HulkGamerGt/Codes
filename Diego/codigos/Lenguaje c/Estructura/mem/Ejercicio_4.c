#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nombre[50];
    int edad;
    char carrera[50];
    float promedio_final;
} ESTUDIANTE;

int main(){
    ESTUDIANTE *estudiantes;
    int cant, mejor_idx_prom = 0;
    float suma = 0;

    printf("Ingrese la cantidad de estudiantes: ");
    scanf("%d", &cant);

    estudiantes = (ESTUDIANTE *)malloc(cant * sizeof(ESTUDIANTE));
    if (estudiantes == NULL) return 1;

    for (int i = 0; i < cant; i++) {
        getchar(); 
        printf("Nombre: ");
        fgets(estudiantes[i].nombre, 50, stdin);
        estudiantes[i].nombre[strcspn(estudiantes[i].nombre, "\n")] = 0;

        printf("Edad: ");
        scanf("%d", &estudiantes[i].edad);
        
        getchar();
        printf("Carrera: ");
        fgets(estudiantes[i].carrera, 50, stdin);
        estudiantes[i].carrera[strcspn(estudiantes[i].carrera, "\n")] = 0;

        printf("Promedio: ");
        scanf("%f", &estudiantes[i].promedio_final);

        suma += estudiantes[i].promedio_final;
        if (estudiantes[i].promedio_final > estudiantes[mejor_idx_prom].promedio_final) {
            mejor_idx_prom = i;
        }
    }

    printf("\n--- Lista de Estudiantes ---\n");
    for (int i = 0; i < cant; i++) {
        printf("%s | %d | %s | %.2f\n", estudiantes[i].nombre, estudiantes[i].edad, estudiantes[i].carrera, estudiantes[i].promedio_final);
    }

    printf("\nPromedio general: %.2f\n", suma / cant);
    printf("Mejor promedio: %s\n", estudiantes[mejor_idx_prom].nombre);

    free(estudiantes);
    return 0;
}