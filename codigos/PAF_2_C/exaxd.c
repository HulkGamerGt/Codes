#include <stdio.h>

/* Definición de constantes y límites para el almacenamiento */
#define NUM_TRIANGULOS 6
#define NUM_LADOS 3
#define MAX_SETS 150         /* Límite máximo de sets de datos a almacenar */
#define NO_ENCONTRADO -1

/* Estructura para representar un triángulo */
typedef struct {
    int lados[NUM_LADOS]; /* Los tres números del triángulo en sentido horario */
} Triangulo;

/* Estructura para almacenar un set completo y su resultado */
typedef struct {
    Triangulo triangulos[NUM_TRIANGULOS];
    int resultado; 
} SetDeDatos;

/* Almacenamiento global para todos los sets de datos leídos */
SetDeDatos todos_los_sets[MAX_SETS];
int num_sets_leidos = 0;

/* Variables globales usadas por la función recursiva (se resetean por set) */
Triangulo hexagono_formado[NUM_TRIANGULOS]; 
int usado[NUM_TRIANGULOS];
int max_puntuacion;

/* Prototipos de funciones (Estilo K&R y ANSI C compatible) */
void rotar_triangulo(Triangulo t, int rotacion, Triangulo* rotado);
void buscar_max_puntuacion(int posicion, Triangulo *input_triangulos);
void calcular_y_almacenar_resultado(SetDeDatos *set);
int leer_datos_de_entrada(void);
void imprimir_resultados(void);


/* -----------------------------------------------------------------------------
 * Función de Ayuda: Rotar un triángulo (Estilo K&R)
 * -----------------------------------------------------------------------------
 */
void rotar_triangulo(t, rotacion, rotado)
Triangulo t;
int rotacion;
Triangulo* rotado;
{
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

/* -----------------------------------------------------------------------------
 * Función Recursiva: Backtracking (Estilo K&R)
 * -----------------------------------------------------------------------------
 */
void buscar_max_puntuacion(posicion, input_triangulos)
int posicion;
Triangulo *input_triangulos;
{
    /* Declaración de variables al inicio del bloque (C89) */
    int i;
    int r;
    int acoplamiento_valido;
    int puntuacion_actual;
    Triangulo t_rotado;

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

    /* Paso Recursivo: Explorar Permutaciones y Rotaciones */
    for (i = 0; i < NUM_TRIANGULOS; i++) { 
        if (!usado[i]) {
            for (r = 0; r < NUM_LADOS; r++) { 
                
                rotar_triangulo(input_triangulos[i], r, &t_rotado);

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
                    
                    buscar_max_puntuacion(posicion + 1, input_triangulos);
                    
                    usado[i] = 0; /* Backtrack */
                }
            }
        }
    }
}

/* -----------------------------------------------------------------------------
 * Función para ejecutar la búsqueda en un set y guardar el resultado
 * -----------------------------------------------------------------------------
 */
void calcular_y_almacenar_resultado(set)
SetDeDatos *set;
{
    /* Declaración de variables al inicio del bloque (C89) */
    int i;
    
    /* 1. Inicialización para el set actual. */
    for (i = 0; i < NUM_TRIANGULOS; i++) {
        usado[i] = 0;
    }
    max_puntuacion = NO_ENCONTRADO;

    /* 2. Ejecución del algoritmo. */
    buscar_max_puntuacion(0, set->triangulos);

    /* 3. Almacenar el resultado. */
    set->resultado = max_puntuacion;
}


/* -----------------------------------------------------------------------------
 * Función para leer toda la entrada de datos hasta el '$'
 * -----------------------------------------------------------------------------
 */
int leer_datos_de_entrada()
{
    /* Declaración de variables al inicio del bloque (C89) */
    int i;
    char separador[5];
    int resultado_lectura;
    
    num_sets_leidos = 0;
    
    while (num_sets_leidos < MAX_SETS) {
        
        /* 1. Intenta leer los 6 triángulos */
        for (i = 0; i < NUM_TRIANGULOS; i++) {
            resultado_lectura = scanf("%d %d %d", 
                      &todos_los_sets[num_sets_leidos].triangulos[i].lados[0], 
                      &todos_los_sets[num_sets_leidos].triangulos[i].lados[1], 
                      &todos_los_sets[num_sets_leidos].triangulos[i].lados[2]);
            
            if (resultado_lectura != 3) {
                if (i == 0 && num_sets_leidos == 0) return 0; /* EOF o error al inicio */
                if (i > 0) return 0; /* Set incompleto (error de formato) */
                break; /* Salir del bucle de lectura de triángulos si se ha leído un set previamente */
            }
        }
        
        /* 2. Si se leyeron 6 triángulos, leemos el separador */
        if (i == NUM_TRIANGULOS) {
            num_sets_leidos++;
            
            if (scanf("%s", separador) != 1) {
                return 0; 
            }

            if (separador[0] == '$') {
                return 1; /* FIN DE ENTRADA: éxito */
            }
        } else {
            /* Si no se leyeron 6 triángulos, salimos */
            break;
        }
    }
    
    return 1;
}

/* -----------------------------------------------------------------------------
 * Función para imprimir todos los resultados almacenados
 * -----------------------------------------------------------------------------
 */
void imprimir_resultados()
{
    /* Declaración de variables al inicio del bloque (C89) */
    int i;
    
    for (i = 0; i < num_sets_leidos; i++) {
        if (todos_los_sets[i].resultado == NO_ENCONTRADO) {
            printf("None\n");
        } else {
            printf("%d\n", todos_los_sets[i].resultado);
        }
    }
}

/* -----------------------------------------------------------------------------
 * Función Principal del Programa
 * -----------------------------------------------------------------------------
 */
int main()
{
    /* 1. Leer y almacenar todos los sets de datos */
    if (!leer_datos_de_entrada()) {
        /* Si la lectura falla o no hay datos, salimos */
        return 1; 
    }

    /* 2. Calcular los resultados de todos los sets leídos */
    { 
        /* Usamos un bloque para la declaración de la variable 'i' en C89 */
        int i;
        for (i = 0; i < num_sets_leidos; i++) {
            calcular_y_almacenar_resultado(&todos_los_sets[i]);
        }
    }
    
    /* 3. Imprimir todos los resultados después de procesar toda la entrada */
    imprimir_resultados();

    return 0;
}