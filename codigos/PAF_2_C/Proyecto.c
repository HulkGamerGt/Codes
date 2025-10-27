/*
  Docentes académicos: Mg. Hugo Araya - Mg. Luis Ponce Rosales.
  Carrera :  Ingeniería Civil Informática.  
  Estudiantes : Matias Pereira Muñoz && Diego Solis Rojas.
  Fecha de entrega : 25 / 10 / 2025
  Descripcion del programa : Este programa lee desde la entrada estándar conjuntos de hasta máximo 150 sets de 6 triángulos (1 hexágono)
    con lados de valor mínimo 1 y máximo 100, después de realizada la lectura pasa a la parte de verificación
    de los sets leídos son válidos y así poder calcular la puntuación máxima que se puede obtener al formar
    un hexágono con los triángulos dados, para luego imprimir los resultados obtenidos desde la salida estándar.
 Compatible con el estandar C89.
*/
#include <stdio.h>

/* Constantes y Estructuras de Datos */
#define NUM_TRIANGULOS 6
#define NUM_LADOS 3
#define MAX_NUM_SETS 150 
#define NO_ENCONTRADO -1 // Valor especial para indicar que no se encontró una solución válida.

/* Estructura para representar un triángulo */
typedef struct {
    int lados[NUM_LADOS];
} TRIANGULO;

/* Estructura para almacenar un caso de prueba completo y su resultado */
typedef struct {
    TRIANGULO triangulos[NUM_TRIANGULOS];
    int puntuacion_maxima_encontrada; 
    int lado_valido;
} CASOPRUEBA;


/* Prototipos de funciones */

int leer_datos_de_entrada(CASOPRUEBA *, int *); /* Lee los datos de entrada estándar */
void calcular_y_almacenar_resultado(CASOPRUEBA *); /* Calcula y almacena el resultado para un caso de prueba */

void rotar_triangulo(const TRIANGULO , int , TRIANGULO* );/* Recibe la estructura de triangulo para asi poder girarlo*/
void buscar_max_puntuacion(int , const TRIANGULO *, TRIANGULO *, int *, int *);/* Busca formar el triangulo más alto posible */
void imprimir_resultados(const CASOPRUEBA *, int ); /* Imprime los resultados almacenados */


/* Función Principal del juego de triangulos */
int main(){
    CASOPRUEBA todos_los_sets[MAX_NUM_SETS];
    int num_sets_leidos, i;

    leer_datos_de_entrada(todos_los_sets, &num_sets_leidos);

    /* Procesar cada conjunto de triángulos */
    for (i = 0; i < num_sets_leidos; i++){
        if(todos_los_sets[i].lado_valido){
            calcular_y_almacenar_resultado(&todos_los_sets[i]);
        }else{
            todos_los_sets[i].puntuacion_maxima_encontrada = NO_ENCONTRADO;
        }
    }

    imprimir_resultados(todos_los_sets, num_sets_leidos);
    return 0;
}

/* Lee los datos de entrada hasta encontrar '$' */
int leer_datos_de_entrada(CASOPRUEBA *todos_los_sets, int *num_sets_leidos){
    int i, j, lado, resultado_lectura, sets_leidos_temp;
    char separador[5];
    CASOPRUEBA *set_actual;

    sets_leidos_temp = 0;

    /* Leer conjuntos de triángulos */
    while(sets_leidos_temp < MAX_NUM_SETS){
        set_actual = &todos_los_sets[sets_leidos_temp];
        (*set_actual).puntuacion_maxima_encontrada = NO_ENCONTRADO;
        (*set_actual).lado_valido = 1;

        for(i = 0; i < NUM_TRIANGULOS; i++){
            resultado_lectura = scanf("%d %d %d", &(*set_actual).triangulos[i].lados[0], &(*set_actual).triangulos[i].lados[1], &(*set_actual).triangulos[i].lados[2]);

            if(resultado_lectura != 3){
                if(i == 0){
                    *num_sets_leidos = sets_leidos_temp;
                    return 1;
                }
                (*set_actual).lado_valido = 0;
                break;
            }
            /* Validar los lados del triángulo */
            for(j = 0; j < NUM_LADOS; j++){
                lado = (*set_actual).triangulos[i].lados[j];
                if(lado < 1 || lado > 100){
                    (*set_actual).lado_valido = 0;
                    break;
                }
            }
        }
        sets_leidos_temp++;
        if(scanf("%s", separador) != 1){
            *num_sets_leidos = sets_leidos_temp;
            return 1;
        }

        if(separador[0] == '$'){
            *num_sets_leidos = sets_leidos_temp;
            return 1;
        }
    }

    *num_sets_leidos = sets_leidos_temp;
    return 1;
}

/* Calcula y almacena la puntuación máxima para un set */
void calcular_y_almacenar_resultado(CASOPRUEBA *set){
    TRIANGULO hexagono_formado[NUM_TRIANGULOS];
    int triangulo_usado[NUM_TRIANGULOS];
    int max_puntuacion, i;
    
    for(i = 0; i < NUM_TRIANGULOS; i++){
        triangulo_usado[i] = 0;
    }
    max_puntuacion = NO_ENCONTRADO;

    buscar_max_puntuacion(0, (*set).triangulos, hexagono_formado, triangulo_usado, &max_puntuacion);
    (*set).puntuacion_maxima_encontrada = max_puntuacion;
}

/* Busca la máxima puntuación formando un hexágono con backtracking */
void buscar_max_puntuacion(int posicion, const TRIANGULO *triangulo_entrante, TRIANGULO *hexagono_formado, int *triangulo_usado, int *max_puntuacion) {
    int i, Rotacion, puntuacion_actual;
    TRIANGULO t_rotado;

    if(posicion == NUM_TRIANGULOS){
        if(hexagono_formado[NUM_TRIANGULOS - 1].lados[2] == hexagono_formado[0].lados[1]){
            puntuacion_actual = 0;
            /* Calcular la puntuación actual */
            for(i = 0; i < NUM_TRIANGULOS; i++){
                puntuacion_actual += hexagono_formado[i].lados[0];
            }
            if(puntuacion_actual > *max_puntuacion){
                *max_puntuacion = puntuacion_actual;
            }
        }
        return;
    }

    for(i = 0; i < NUM_TRIANGULOS; i++){
        if(!triangulo_usado[i]){
            /* Rotar el triángulo y verificar condiciones */
            for(Rotacion = 0; Rotacion < NUM_LADOS; Rotacion++){
                rotar_triangulo(triangulo_entrante[i], Rotacion, &t_rotado);
                if(posicion == 0 || hexagono_formado[posicion - 1].lados[2] == t_rotado.lados[1]){
                    triangulo_usado[i] = 1;
                    hexagono_formado[posicion] = t_rotado;
                    buscar_max_puntuacion(posicion + 1, triangulo_entrante, hexagono_formado, triangulo_usado, max_puntuacion);
                    triangulo_usado[i] = 0;
                }
            }
        }
    }
}

/* Rota un triángulo según la rotación indicada */
void rotar_triangulo(const TRIANGULO t, int rotacion, TRIANGULO *rotado){

    if(rotacion == 0){
        (*rotado).lados[0] = t.lados[0];
        (*rotado).lados[1] = t.lados[1];
        (*rotado).lados[2] = t.lados[2];
    }else if(rotacion == 1){
        (*rotado).lados[0] = t.lados[1];
        (*rotado).lados[1] = t.lados[2];
        (*rotado).lados[2] = t.lados[0];
    }else{/* rotacion == 2 */
        rotado->lados[0] = t.lados[2];
        rotado->lados[1] = t.lados[0];
        rotado->lados[2] = t.lados[1];
    }
}

/* Imprime los resultados de todos los sets */
void imprimir_resultados(const CASOPRUEBA *todos_los_sets, int num_sets_leidos){
    int i;

    for(i = 0; i < num_sets_leidos; i++){
        if(todos_los_sets[i].puntuacion_maxima_encontrada == NO_ENCONTRADO){
            printf("None\n");
        }else{
            printf("%d\n", todos_los_sets[i].puntuacion_maxima_encontrada);
        }
    }
}