/*Docentes académicos: Mg. Hugo Araya - Mg. Luis Ponce Rosales.
  Carrera :  Ingeniería Civil Informática.  
  Estudiantes : Matias Pereira Muñoz && Diego Solis Rojas.
  Fecha de entrega : 25 / 10 / 2025
  Descripcion del programa : 
*/
#include <stdio.h>

/* Definición de constantes y límites para el almacenamiento */
#define NUM_TRIANGULOS 6
#define NUM_LADOS 3
#define MAX_SETS 150         /* Límite máximo de sets de hexagonos a almacenar */
#define NO_ENCONTRADO -1


/* Estructura para representar un triángulo */
typedef struct {
    int lados[NUM_LADOS]; /* Los tres números del triángulo en sentido horario */
} Triangulo;


/* Estructura para almacenar un all_hexa completo y su resultado */
typedef struct {
    Triangulo triangulos[NUM_TRIANGULOS];
    int resultado; 
} SetDeDatos;


/* Almacenamiento global para todos los sets de datos leídos */
SetDeDatos all_hexa[MAX_SETS];
int hexa_leidos = 0;


/* Variables globales usadas por la función recursiva (se resetean por all_hexa) */
Triangulo hexagono_formado[NUM_TRIANGULOS]; 
int usado[NUM_TRIANGULOS]; // marcar triángulos ya usados
int max_puntuacion;



int leer_datos_de_entrada();
void calcular_y_almacenar_resultado(SetDeDatos *);

int main(){
    int i;
    /* 1. Leer y almacenar todos los sets de datos */
    if(!leer_datos_de_entrada()) return 1; /* Si la lectura falla o no hay datos, salimos */

    /* 2. Calcular los resultados de todos los sets leídos */
    for(i = 0; i < hexa_leidos; i++) calcular_y_almacenar_resultado(&all_hexa[i]);
    
    /* 3. Imprimir todos los resultados después de procesar toda la entrada */
    imprimir_resultados();

    return 0;
}

int leer_datos_de_entrada(){

    int i;
    char separador[5];
    int resultado_lectura;
    
    hexa_leidos = 0;
    
    while(hexa_leidos < MAX_SETS){
        
        /* 1. Intenta leer los 6 triángulos */
        for(i = 0; i < NUM_TRIANGULOS; i++){
            resultado_lectura = scanf("%d %d %d", &all_hexa[hexa_leidos].triangulos[i].lados[0], &all_hexa[hexa_leidos].triangulos[i].lados[1], &all_hexa[hexa_leidos].triangulos[i].lados[2]);
            
            if(resultado_lectura != 3){
                if(i == 0 && hexa_leidos == 0) return 0; /* EOF o error al inicio */
                if(i > 0) return 0; /* Set incompleto (error de formato) */
                break; /* Salir del bucle de lectura de triángulos si se ha leído un all_hexa previamente */
            }
        }
        
        /* 2. Si se leyeron 6 triángulos, leemos el separador */
        if(i == NUM_TRIANGULOS){
            hexa_leidos++;

            if(scanf("%s", separador) != 1) return 0;
            if(separador[0] == '$') return 1; /* FIN DE ENTRADA: éxito */
            
        }else{
            break; /* Si no se leyeron 6 triángulos, salimos */
        }
    }
    return 1; // Éxito al leer todos los sets posibles
}

void calcular_y_almacenar_resultado(SetDeDatos *all_hexa){

    int i;

    /* 1. Inicialización para el set actual. */
    for (i = 0; i < NUM_TRIANGULOS; i++) {
        usado[i] = 0;
    }
    max_puntuacion = NO_ENCONTRADO;

    /* 2. Ejecución del algoritmo. */
    buscar_max_puntuacion(0, (*all_hexa).triangulos);

    /* 3. Almacenar el resultado. */
    (*all_hexa).resultado = max_puntuacion;
}

void buscar_max_puntuacion(int posicion, Triangulo *entra_tri){

    int i;
    int r;
    int acoplamiento_valido; // marcar si el triángulo puede acoplarse
    int puntuacion_actual; // puntuación del hexágono actual
    Triangulo t_rotado;// rotado del triángulo actual

    if (posicion == NUM_TRIANGULOS) {
        /* Caso Base: Verificar el CIERRE (lado[2] del T5 == lado[1] del T0) */
        if (hexagono_formado[NUM_TRIANGULOS - 1].lados[2] == hexagono_formado[0].lados[1]) {
            puntuacion_actual = 0;
            for (i = 0; i < NUM_TRIANGULOS; i++) {
                puntuacion_actual += hexagono_formado[i].lados[0]; /* Suma de lados externos (lado[0]) */
            }

            if (puntuacion_actual > max_puntuacion) {
                max_puntuacion = puntuacion_actual;
            }
        }
        return;
    }

    /* Explorar Permutaciones y Rotaciones */
    for (i = 0; i < NUM_TRIANGULOS; i++) { 
        if (!usado[i]) {
            for (r = 0; r < NUM_LADOS; r++) { 
                
                rotar_triangulo(entra_tri[i], r, &t_rotado);

                acoplamiento_valido = 1;
                if (posicion > 0) {
                    /* Restricción: lado[2] del anterior debe coincidir con lado[1] del actual */
                    if (hexagono_formado[posicion - 1].lados[2] != t_rotado.lados[1]) {
                        acoplamiento_valido = 0;
                    }
                }

                if (acoplamiento_valido) {
                    usado[i] = 1;
                    hexagono_formado[posicion] = t_rotado;
                    
                    buscar_max_puntuacion(posicion + 1, entra_tri);
                    
                    usado[i] = 0; /* Backtrack */
                }
            }
        }
    }
}


void rotar_triangulo(Triangulo t,int rotacion,Triangulo* rotado){

    if (rotacion == 0) {
        rotado->lados[0] = t.lados[0];
        rotado->lados[1] = t.lados[1];
        rotado->lados[2] = t.lados[2];
    } else if (rotacion == 1) {
        rotado->lados[0] = t.lados[1];
        rotado->lados[1] = t.lados[2];
        rotado->lados[2] = t.lados[0];
    } else { /* rotacion == 2 */
        rotado->lados[0] = t.lados[2];
        rotado->lados[1] = t.lados[0];
        rotado->lados[2] = t.lados[1];
    }
}