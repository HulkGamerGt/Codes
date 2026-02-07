#include <stdio.h>

typedef struct {
    float caudal_max;
    char tipo_planta[50];
    int num_plantas;
    float litros_req_planta;
    float tiempo_minutos;
    float litros_totales;
} DatosRiego;

void inicializacion(DatosRiego *);
void menu();
void menu_de_lectura(DatosRiego, int *);
void analizar_opcion(DatosRiego *, int);
void calculo(DatosRiego *);
void ini_caudal_max(DatosRiego *);
void ini_tipo_planta(DatosRiego *);
void ini_num_plantas(DatosRiego *);
void ini_litros_req_planta(DatosRiego *);
void impresion(DatosRiego);
void generar_archivo(DatosRiego);

int main(){
    DatosRiego Riego;
    int option = 0;

    inicializacion(&Riego);
    menu();
    
    while(option != 5){
        
        menu_de_lectura(Riego, &option);
        analizar_opcion(&Riego, option);
    }
    calculo(&Riego);
    impresion(Riego);
    generar_archivo(Riego);

    return 0;
}

void inicializacion(DatosRiego *Riego){
    int i;
    char *texto = "Especifique";

    Riego->caudal_max = 0;
    Riego->litros_req_planta = 0;
    Riego->litros_totales = 0;
    Riego->num_plantas = 0;
    Riego->tiempo_minutos = 0;
    
    for(i = 0; i < 49 && texto[i] != '\0'; i++) {
        Riego->tipo_planta[i] = texto[i];
    }
    Riego->tipo_planta[i] = '\0';
}

void menu(){
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
    if(scanf("%d", option) != 1) {
        while(getchar() != '\n');
        *option = 0;
    }
}

void analizar_opcion(DatosRiego *Riego, int option){
    switch(option){
    case 1:
        ini_caudal_max(Riego);
        break;
    case 2:
        ini_tipo_planta(Riego);
        break;
    case 3:
        ini_num_plantas(Riego);
        break;
    case 4:
        ini_litros_req_planta(Riego);
        break;
    case 5:
        break;
    default:
        break;
    }
}

void ini_caudal_max(DatosRiego *Riego){
    printf("Ingrese Caudal: ");
    scanf("%f", &Riego->caudal_max);
}

void ini_tipo_planta(DatosRiego *Riego){
    printf("Ingrese Tipo: ");
    scanf("%s", Riego->tipo_planta);
}

void ini_num_plantas(DatosRiego *Riego){
    printf("Ingrese Numero: ");
    scanf("%d", &Riego->num_plantas);
}

void ini_litros_req_planta(DatosRiego *Riego){
    printf("Ingrese Litros: ");
    scanf("%f", &Riego->litros_req_planta);
}

void calculo(DatosRiego *Riego){
    Riego->litros_totales = Riego->num_plantas * Riego->litros_req_planta;
    if(Riego->caudal_max > 0){
        Riego->tiempo_minutos = Riego->litros_totales / Riego->caudal_max;
    } else {
        Riego->tiempo_minutos = 0;
    }
}

void impresion(DatosRiego Riego){
    printf("\nResultados en consola:\n");
    printf("Cultivo: %s\n", Riego.tipo_planta);
    printf("Tiempo: %.2f min\n", Riego.tiempo_minutos);
    printf("Litros Totales: %.2f\n", Riego.litros_totales);
}

void generar_archivo(DatosRiego Riego) {
    FILE *archivo = fopen("riego.txt", "w");
    
    if (archivo == NULL) {
        printf("Error: No se pudo crear o abrir el archivo riego.txt\n");
        return;
    }

    fprintf(archivo, "/* ------------------------------------------------------- */\n");
    fprintf(archivo, "Sistema de riego por goteo\n");
    fprintf(archivo, "Plantas : %d\n", Riego.num_plantas);
    fprintf(archivo, "Litros por planta : %.0f\n", Riego.litros_req_planta);
    fprintf(archivo, "Caudal v%c%clvula L/min : %.0f\n", 0xC3, 0xA1, Riego.caudal_max); 
    fprintf(archivo, "------------------------------------------------------------\n");
    fprintf(archivo, "Tiempo de apertura : %.2f min\n", Riego.tiempo_minutos);
    fprintf(archivo, "Tiempo en segundos : %.0f s\n", Riego.tiempo_minutos * 60.0);
    fprintf(archivo, "Litros totales : %.2f L\n", Riego.litros_totales);
    fprintf(archivo, "/* ------------------------------------------------------- */\n");
    
    fclose(archivo);
    printf("\nArchivo 'riego.txt' generado con %c%cxito.\n", 0xC3, 0xA9); 
}