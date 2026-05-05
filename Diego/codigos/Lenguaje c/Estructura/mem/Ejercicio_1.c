#include <stdio.h>
#include <stdlib.h>

void ingresador_notas(int, float *);
float calc_promedio(int , float *);
float calc_nota_max(int , float *);
float calc_nota_min(int , float *);
void mostrar_resultados(int, float *,float , float, float);

int main(){
    int cant_estudiantes;
    float nota_mayor;
    float nota_minima;
    float *arr_notas_estudiantes;
    float promedio_general;

    printf("Ingrese la cantidad de estudiantes : ");
    scanf("%d",&cant_estudiantes);

    arr_notas_estudiantes = (int *)malloc(cant_estudiantes * sizeof(int));

    if(arr_notas_estudiantes == NULL){ 
        printf("Problemas con la direccion de memoria"); 
        return 0;
    }
    ingresador_notas(cant_estudiantes, arr_notas_estudiantes);
    promedio_general = calc_promedio(cant_estudiantes, arr_notas_estudiantes);

    nota_mayor = calc_nota_max(cant_estudiantes, arr_notas_estudiantes);
    nota_minima = calc_nota_min(cant_estudiantes, arr_notas_estudiantes);

    mostrar_resultados(cant_estudiantes, arr_notas_estudiantes,nota_mayor,nota_minima, promedio_general);

    free(arr_notas_estudiantes);
    return 0;
}

void ingresador_notas(int cant_estudiantes, float *arr_notas_estudiantes){

    for(int i=0; i < cant_estudiantes; i++){
        printf("Ingrese la nota del estudiante %d :",i+1);
        scanf("%f", &(*arr_notas_estudiantes));
        arr_notas_estudiantes++;
    }

}

float calc_promedio(int cant_estudiantes, float *arr_notas_estudiantes){

    float prom = 0;

    for(int i=0; i < cant_estudiantes ; i++){
        prom += *arr_notas_estudiantes;

        arr_notas_estudiantes++;
    }

    return (prom/cant_estudiantes);
}

float calc_nota_max(int cant_estudiantes, float *arr_notas_estudiantes){

    float max = 0;

    for(int i=0; i < cant_estudiantes;i++){
        if(max < *arr_notas_estudiantes){
            max = *arr_notas_estudiantes;
        }
        arr_notas_estudiantes++;
    }

    return max;
}

float calc_nota_min(int cant_estudiantes, float *arr_notas_estudiantes){

    float min = 999;

    for(int i=0; i < cant_estudiantes;i++){
        if(min > *arr_notas_estudiantes){
            min = *arr_notas_estudiantes;
        }
        arr_notas_estudiantes++;
    }
    return min;
}

void mostrar_resultados(int cant_estudiantes, float *arr_notas_estudiantes,float nota_mayor, float nota_minima, float promedio_general){
    
    printf("Las notas ingresadas fueron las siguientes : \n\n");
    for(int i = 0 ; i< cant_estudiantes ; i++){
        printf("Nota %d : %.2f\n", i,*arr_notas_estudiantes);
        arr_notas_estudiantes++;
    }
    printf("De esas notas el promedio fue de : %.2f\n",promedio_general);
    printf("Nota maxima : %.2f\n", nota_mayor);
    printf("Nota minima : %.2f\n", nota_minima);
}