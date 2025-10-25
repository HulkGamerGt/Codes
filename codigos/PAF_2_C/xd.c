#include <stdio.h>

/* Constantes y Estructuras de Datos */

#define NUM_TRIANGULOS 6
#define NUM_LADOS 3
#define MAX_NUM_SETS 150 // Nomenclatura más precisa
#define NO_ENCONTRADO -1

typedef struct {
    int lados[NUM_LADOS];
} Triangulo;

// Renombrado de SetDeDatos a CasoPrueba
typedef struct {
    Triangulo triangulos[NUM_TRIANGULOS];
    int puntuacion_maxima; // Renombrado de 'resultado'
} CasoPrueba;


/* Prototipos de funciones */

// Se añade 'const' para asegurar que 't' no se modifica 
void rotar_triangulo(const Triangulo t, int rotacion, Triangulo* rotado);
void buscar_max_puntuacion(int posicion, const Triangulo *input_triangulos, Triangulo *hexagono_formado, int *triangulo_usado, int *max_puntuacion);


int leer_datos_de_entrada(CasoPrueba *todos_los_sets, int *num_sets_leidos);
void calcular_y_almacenar_resultado(CasoPrueba *set); 
void imprimir_resultados(const CasoPrueba *todos_los_sets, int num_sets_leidos);


/* Función Principal del juego de triangulos */
int main(){

    CasoPrueba todos_los_sets[MAX_NUM_SETS];
    int num_sets_leidos; 
    int i; 

    /* 1. Leer y almacenar todos los casos de prueba */
    // La función devuelve 1 en éxito y 0 en error. Se mantiene la lógica.
    if (!leer_datos_de_entrada(todos_los_sets, &num_sets_leidos)) return 1; 

    /* 2. Calcular los resultados de todos los sets leídos */
    // La función ahora encapsula todas las variables auxiliares
    for (i = 0; i < num_sets_leidos; i++) {
        calcular_y_almacenar_resultado(&todos_los_sets[i]);
    }
    
    /* 3. Imprimir todos los resultados */
    imprimir_resultados(todos_los_sets, num_sets_leidos);

    return 0;
}

/* Funcion que lee los datos de entrada */
int leer_datos_de_entrada(CasoPrueba *todos_los_sets, int *num_sets_leidos){

    int i;
    char separador[5];
    int resultado_lectura;
    
    *num_sets_leidos = 0;
    /* Leer hasta encontrar el separador '$' o EOF */
    while (*num_sets_leidos < MAX_NUM_SETS) {
        
        for (i = 0; i < NUM_TRIANGULOS; i++) {
            resultado_lectura = scanf("%d %d %d", &todos_los_sets[*num_sets_leidos].triangulos[i].lados[0], &todos_los_sets[*num_sets_leidos].triangulos[i].lados[1], &todos_los_sets[*num_sets_leidos].triangulos[i].lados[2]);
            
            // Si no lee 3 enteros, y es el inicio de un set (i==0), es EOF
            if (resultado_lectura != 3) {
                if (i == 0) return 1; // Se asume que no hay más datos, lectura exitosa de sets anteriores.
            }
        }
        
        if (i == NUM_TRIANGULOS) {
            (*num_sets_leidos)++;
            
            // Lectura del separador
            if (scanf("%s", separador) != 1) {
                return 1; // EOF después del último set.
            }

            if (separador[0] == '$') {
                return 1; // Separador de fin de entrada.
            }
        } else {
            break; // Datos incompletos, pero la lógica de salida ya se manejó arriba.
        }
    }
    
    return 1;
}

/* Ejecuta la búsqueda para un set y guarda la puntuación máxima */
// Se eliminan los parámetros auxiliares: son variables locales aquí (encapsulación)
void calcular_y_almacenar_resultado(CasoPrueba *set){
    
    Triangulo hexagono_formado[NUM_TRIANGULOS]; // Declaración movida desde main
    int triangulo_usado[NUM_TRIANGULOS]; // Renombrado y movido desde main
    int max_puntuacion; // Declaración movida desde main
    int i;

    /* Inicializa el estado de los triángulos usados */
    for (i = 0; i < NUM_TRIANGULOS; i++) {
        triangulo_usado[i] = 0;
    }
    max_puntuacion = NO_ENCONTRADO;

    // Llamada ajustada a la nueva nomenclatura de variables
    buscar_max_puntuacion(0, (*set).triangulos, hexagono_formado, triangulo_usado, &max_puntuacion);

    // Se usa la nueva nomenclatura de estructura
    set->puntuacion_maxima = max_puntuacion;
}

/* Funcion que imprime los resultados almacenados */
void imprimir_resultados(const CasoPrueba *todos_los_sets, int num_sets_leidos){ // Añadido 'const'

    int i;
    
    for (i = 0; i < num_sets_leidos; i++) {
        // Se usa la nueva nomenclatura de estructura
        if (todos_los_sets[i].puntuacion_maxima == NO_ENCONTRADO) {
            printf("None\n");
        } else {
            printf("%d\n", todos_los_sets[i].puntuacion_maxima);
        }
    }
}


/* Función Recursiva: Backtracking */
void buscar_max_puntuacion(int posicion, const Triangulo *input_triangulos, Triangulo *hexagono_formado, int *triangulo_usado, int *max_puntuacion){ // Renombrado

    int i;
    int r;
    int puntuacion_actual;
    Triangulo t_rotado;

    /* Caso Base: Hexágono completado */
    if (posicion == NUM_TRIANGULOS) {
        /* Verificar el CIERRE: el lado[2] del T5 debe conectar con el lado[1] del T0 */
        if (hexagono_formado[NUM_TRIANGULOS - 1].lados[2] == hexagono_formado[0].lados[1]) {
            puntuacion_actual = 0;
            for (i = 0; i < NUM_TRIANGULOS; i++) {
                puntuacion_actual += hexagono_formado[i].lados[0];
            }

            if (puntuacion_actual > *max_puntuacion) {
                *max_puntuacion = puntuacion_actual;
            }
        }
        return;
    }

    /* Paso Recursivo: Probar cada triángulo no usado */
    for (i = 0; i < NUM_TRIANGULOS; i++) { 
        if (!triangulo_usado[i]) { // Usando el nuevo nombre
            /* Probar cada rotación */
            for (r = 0; r < NUM_LADOS; r++) { 
                
                rotar_triangulo(input_triangulos[i], r, &t_rotado);

                // Lógica simplificada: eliminamos la variable acoplamiento_valido
                if (posicion == 0 || hexagono_formado[posicion - 1].lados[2] == t_rotado.lados[1]) {
                    
                    triangulo_usado[i] = 1; // Usando el nuevo nombre
                    hexagono_formado[posicion] = t_rotado;
                    
                    buscar_max_puntuacion(posicion + 1, input_triangulos, hexagono_formado, triangulo_usado, max_puntuacion);
                    
                    triangulo_usado[i] = 0; /* Backtrack */ // Usando el nuevo nombre
                }
            }
        }
    }
}


/* Funcion que rota un triángulo recibido */
void rotar_triangulo(const Triangulo t, int rotacion, Triangulo* rotado){ // Añadido 'const'
    /* El lado[0] es siempre el lado externo (el que suma puntos). */
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