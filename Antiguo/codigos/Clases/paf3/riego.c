<<<<<<< HEAD:Antiguo/codigos/Clases/paf3/riego.c
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
=======
/*
  Docentes académicos: Mg. Hugo Araya - Mg. Luis Ponce Rosales.
  Carrera :  Ingeniería Civil Informática.  
  Estudiantes : Matias Pereira Muñoz && Diego Solis Rojas.
  Fecha de entrega : 17 / 12 / 2025
  Descripción del programa : Este programa calcula el tiempo de riego necesario para un sistema de riego
    basado en el caudal máximo, tipo de planta, número de plantas y litros requeridos por planta.
    
    -Ademas de pequeños menús para la interacción con el usuario haciendo que el usuario vea los
        datos ingresados en cada paso.

    -Finalmente genera un archivo de texto con los resultados del cálculo.
        
    -Se optó por no incluir tildes en las opciones del menú.
        Esta medida garantiza la máxima compatibilidad del programa, ya que nos adherimos 
        al estándar ANSI C89. Dicho estándar limita el soporte de caracteres al conjunto ASCII básico,
        y evitar las tildes previene fallos de codificación o problemas 
        de visualización en distintos entornos de ejecución.
 Compatible con el estándar C89.
*/
#include <stdio.h>

/*Estructura de datos para Almacenar los valores del riego*/
typedef struct {
    float caudal_max;                    /* Caudal máximo en Litros/min */
    char tipo_planta[100];
    int num_plantas;
    float litros_req_planta;
    float tiempo_apertura_minutos;       /* Tiempo de apertura calculado en minutos */
    float litros_totales_requeridos;     /* Litros totales requeridos (num_plantas * litros_req_planta) */
} DatosRiego;

void inicializacion(DatosRiego *);          /*Inicializa los valores por defecto*/
void menu();                                /*Muestra el menú*/ 
void menu_de_lectura(DatosRiego, int *);    /*Muestra los datos ingresados*/

void analizar_opcion(DatosRiego *, int);    /*Analiza la opción seleccionada*/

void ini_caudal_max(DatosRiego *);          /*Almacena el caudal máximo*/
void ini_tipo_planta(DatosRiego *);         /*Almacena el tipo de planta o cultivo*/
void ini_num_plantas(DatosRiego *);         /*Almacena el número de plantas*/
void ini_litros_req_planta(DatosRiego *);   /*Almacena los datos de litros requeridos para la planta*/

void calculo(DatosRiego *);
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
    generar_archivo(Riego);

    return 0;
}

/*Inicializa los valores por defecto*/
void inicializacion(DatosRiego *Riego){
    int i;
    char *texto = "Especifique";

    Riego->caudal_max = 0;
    Riego->litros_req_planta = 0;
    Riego->litros_totales_requeridos = 0;
    Riego->num_plantas = 0;
    Riego->tiempo_apertura_minutos= 0;
    
    /*Inicializa el tipo de planta con un valor por defecto*/
    for(i = 0; i < 99 && texto[i] != '\0'; i++){
        Riego->tipo_planta[i] = texto[i];
    }
    Riego->tipo_planta[i] = '\0';
}

/*Muestra el menú*/
void menu(){   
    printf("--------- Menu ------------\n");
    printf("1.- Caudal maximo\n");
    printf("2.- Tipo de planta o cultivo\n");
    printf("3.- Numero de plantas\n");
    printf("4.- Litros requeridos por planta\n"); 
    printf("5.- Salir\n"); 
    printf("------------------------------\n");
}
/*Muestra los datos ingresados y después pregunta por la siguiente opción a realizar */
void menu_de_lectura(DatosRiego Riego, int *option){ 
    printf("--------- Menu ------------\n");
    printf("1.- Caudal maximo : %.1f\n", Riego.caudal_max);
    printf("2.- Tipo de planta o cultivo : %s\n", Riego.tipo_planta);
    printf("3.- Numero de plantas : %d\n", Riego.num_plantas);
    printf("4.- Litros requeridos por planta : %.1f\n", Riego.litros_req_planta); 
    printf("5.- Salir\n"); 
    printf("------------------------------\n");
    printf("Seleccione una opcion : ");
    if(scanf("%d", option) != 1){
        while(getchar() != '\n');
        *option = 0;
    }
}
/*Analiza la opción del usuario requiera*/
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

/*Almacena los datos de cada uno*/
void ini_caudal_max(DatosRiego *Riego){
    printf("Ingrese Caudal: ");
    scanf("%f", &Riego->caudal_max);
}

/*Almacena el tipo de planta o cultivo*/
void ini_tipo_planta(DatosRiego *Riego){
    int i, c;

    printf("Ingrese Tipo: ");
    
    /*Elimina el carácter de nueva línea del buffer*/
    while((c = getchar()) != '\n' && c != EOF);

    if(fgets(Riego->tipo_planta, sizeof(Riego->tipo_planta), stdin) != NULL){
        
        i = 0;
        /*Elimina el carácter de nueva línea del buffer*/
        while(Riego->tipo_planta[i] != '\0'){
            if(Riego->tipo_planta[i] == '\n'){
                Riego->tipo_planta[i] = '\0';
                break;
            }
            i++;
        }
    }
}

/*Almacena el número de plantas*/
void ini_num_plantas(DatosRiego *Riego){
    printf("Ingrese Numero: ");
    scanf("%d", &Riego->num_plantas);
}
/*Almacena los datos de litros requeridos para la planta*/
void ini_litros_req_planta(DatosRiego *Riego){
    printf("Ingrese Litros: ");
    scanf("%f", &Riego->litros_req_planta);
}
/*Calcula cuánto se demora en regar, los litros requeridos y cuántas plantas serían*/
void calculo(DatosRiego *Riego){
    
    Riego->litros_totales_requeridos = Riego->num_plantas * Riego->litros_req_planta;

    if(Riego->caudal_max > 0){
        Riego->tiempo_apertura_minutos= Riego->litros_totales_requeridos / Riego->caudal_max;
    }else{
        Riego->tiempo_apertura_minutos= 0;
    }
}
/*Genera el archivo con los datos ingresados con el cálculo correspondiente*/
void generar_archivo(DatosRiego Riego) {
    FILE *archivo = fopen("riego.txt", "w");
    
    if(archivo == NULL){
        printf("Error: No se pudo crear o abrir el archivo riego.txt\n");
        return;
    }

    fprintf(archivo, "/* ------------------------------------------------------- */\n");
    fprintf(archivo, "Sistema de riego por goteo para %s\n\n", Riego.tipo_planta);
    fprintf(archivo, "1.-| Plantas                 : %d\n", Riego.num_plantas);
    fprintf(archivo, "2.-| Litros por planta       : %.0f\n", Riego.litros_req_planta);
    fprintf(archivo, "3.-| Caudal valvula L/min    : %.0f\n\n", Riego.caudal_max); 
    fprintf(archivo, "------------------------------------------------------------\n\n");
    fprintf(archivo, "4.-| Tiempo de apertura      : %.2f min\n", Riego.tiempo_apertura_minutos);
    fprintf(archivo, "5.-| Tiempo en segundos      : %.0f s\n", Riego.tiempo_apertura_minutos* 60);
    fprintf(archivo, "6.-| Litros totales          : %.2f L\n\n", Riego.litros_totales_requeridos);
    fprintf(archivo, "/* ------------------------------------------------------- */\n");
    
    fclose(archivo);
    printf("\nArchivo 'riego.txt' generado con exito.\n"); 
>>>>>>> 9997bfb0a3f373b7e7a2a40038d67a74d783436e:codigos/Clases/paf3/riego.c
}