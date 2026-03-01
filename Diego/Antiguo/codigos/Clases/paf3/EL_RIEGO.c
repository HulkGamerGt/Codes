#include <stdio.h>

typedef struct {
    // Variables de Entrada
    float caudal_max;             // 1. Caudal máximo en Litros/min
    char tipo_planta[50];         // 2. Tipo de planta o cultivo (String para texto)
    int num_plantas;              // 3. Número de plantas (entero)
    float litros_req_planta;      // 4. Litros requeridos por planta (float)
    
    // Variables de Salida / Resultados
    float tiempo_minutos;         // Tiempo de apertura calculado en minutos
    float litros_totales;         // Litros totales requeridos (num_plantas * litros_req_planta)
} DatosRiego;

void inicializacion(DatosRiego);
void menu();
void menu_de_lectura(DatosRiego, int *);
void analizar_opcion(DatosRiego, int);

void calculos();

/*Inicializaciones de cada variable para el calculo*/
void ini_caudal_max(float);
void ini_tipo_planta(char);
void ini_num_plantas(int);
void ini_litros_req_planta(int);
void impresion(DatosRiego);

int main(){
    DatosRiego Riego;
    int option = 0;
    inicializacion(Riego);
    menu();

    while(option != 5){
        menu_de_lectura(Riego, &option);
        analizar_opcion(Riego, option);
    }
    calculos();
    impresion(Riego);

    return 0;
}

void inicializacion(DatosRiego Riego){
    Riego.caudal_max = 0;
    Riego.litros_req_planta = 0;
    Riego.litros_totales = 0;
    Riego.num_plantas = 0;
    Riego.tiempo_minutos = 0;
    Riego.tipo_planta = "Especifique";
}

void menu(){
    // ú = 0xC3 0xBA && á = 0xC3 0xA1
    printf("--------- Men%c%c ------------\n", 0xC3, 0xBA);
    printf("1.- Caudal m%c%cximo\n", 0xC3, 0xA1);
    printf("2.- Tipo de planta o cultivo\n");
    printf("3.- N%c%cmero de plantas\n", 0xC3, 0xBA);
    printf("4.- Litros requeridos por planta\n"); 
    printf("5.- Salir\n"); 
    printf("------------------------------\n");
}

void menu_de_lectura(DatosRiego Riego, int *option){
    printf("--------- Men%c%c ------------\n", 0xC3, 0xBA);
    printf("1.- Caudal m%c%cximo : %.1f\n", 0xC3, 0xA1, Riego.caudal_max);
    printf("2.- Tipo de planta o cultivo : %s\n", Riego.tipo_planta);
    printf("3.- N%c%cmero de plantas : %d\n", 0xC3, 0xBA, Riego.num_plantas);
    printf("4.- Litros requeridos por planta : %.1f\n", Riego.litros_req_planta); 
    printf("5.- Salir\n"); 
    printf("------------------------------\n");
    printf("Seleccione una opcion : ");
    scanf("%d",&option);
}

void analizar_opcion(DatosRiego Riego, int option){

    switch(option){
    case 1:
        ini_caudal_max(Riego.caudal_max);
        break;
    case 2:
        ini_tipo_planta(&Riego.tipo_planta);
        break;
    case 3:
        ini_num_plantas(Riego.num_plantas);
        break;
    case 4:
        ini_litros_req_planta(Riego.litros_req_planta);
        break;
    case 5:
        impresion(Riego);
        break;
    default:
        break;
    }
}