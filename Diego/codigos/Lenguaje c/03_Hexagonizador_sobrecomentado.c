#include <stdio.h> // Biblioteca estándar de entrada/salida para funciones como printf y scanf

/* Constantes y Estructuras de Datos */
#define NUM_TRIANGULOS 6    // **CRUCIAL:** Define el número fijo de triángulos para formar el hexágono (6 piezas).
#define NUM_LADOS 3         // Define el número de lados de cada triángulo (siempre 3).
#define MAX_NUM_SETS 150    // Límite superior para la cantidad de casos de prueba a procesar.
#define NO_ENCONTRADO -1    // Valor especial usado para inicializar la puntuación máxima. También indica una solución no encontrada/inválida.

// --- Estructuras de Datos ---

/* Estructura para representar un triángulo */
typedef struct {
    int lados[NUM_LADOS]; // Arreglo de 3 enteros. Se interpreta como:
                          // lados[0]: Lado Base (el que contribuye a la puntuación).
                          // lados[1]: Lado Izquierdo (se empareja con el lado[2] del triángulo anterior).
                          // lados[2]: Lado Derecho (se empareja con el lado[1] del triángulo siguiente).
} TRIANGULO;

/* Estructura para almacenar un caso de prueba completo y su resultado */
typedef struct {
    TRIANGULO triangulos[NUM_TRIANGULOS];     // Arreglo que contiene los 6 triángulos iniciales del set de entrada.
    int puntuacion_maxima_encontrada;         // Resultado final: la puntuación más alta lograda (suma de lados base).
    int lado_valido;                          // Bandera (1: Válido, 0: Inválido). Usado para descartar sets con lados fuera del rango [1, 100].
} CASOPRUEBA;

// --- Prototipos de funciones ---
// El compilador necesita saber la firma de las funciones antes de la función 'main'.

int leer_datos_de_entrada(CASOPRUEBA *, int *);              // Maneja la lectura de todos los sets y la validación de rango de lados.
void calcular_y_almacenar_resultado(CASOPRUEBA *);          // Función de orquestación que prepara el Backtracking.

void rotar_triangulo(const TRIANGULO , int , TRIANGULO* );  // Simula el giro de un triángulo para probar orientaciones.
void buscar_max_puntuacion(int , const TRIANGULO *, TRIANGULO *, int *, int *); // **ALGORITMO DE BACKTRACKING (recursivo)**.
void imprimir_resultados(const CASOPRUEBA *, int );          // Función de salida final.

// ----------------------------------------------------------------------
// --- FUNCIÓN PRINCIPAL (main) ---
// ----------------------------------------------------------------------

/* Función Principal: coordina las fases de Lectura, Procesamiento y Salida. */
int main(){
    CASOPRUEBA todos_los_sets[MAX_NUM_SETS]; // Arreglo principal para almacenar toda la entrada y resultados.
    int num_sets_leidos;                      // Almacena el total de sets leídos realmente.
    int i;                                    // Variable de control.

    // 1. Fase de Lectura
    leer_datos_de_entrada(todos_los_sets, &num_sets_leidos);

    /* 2. Fase de Procesamiento: Se itera sobre cada set válido. */
    for (i = 0; i < num_sets_leidos; i++){
        if(todos_los_sets[i].lado_valido){// Si el set es válido (todos los lados en rango).
            // Si el set es válido, se llama a la función que inicia la búsqueda exhaustiva.
            calcular_y_almacenar_resultado(&todos_los_sets[i]);
        }else{
            // Si es inválido (por rango de lados), se marca para imprimir "None".
            todos_los_sets[i].puntuacion_maxima_encontrada = NO_ENCONTRADO;
        }
    }

    // 3. Fase de Salida
    imprimir_resultados(todos_los_sets, num_sets_leidos);
    
    return 0; // Indicador de terminación exitosa.
}

// ----------------------------------------------------------------------
// --- FUNCIONES DE ENTRADA/SALIDA ---
// ----------------------------------------------------------------------

/* Lee los datos de entrada: 6 triángulos seguidos de un separador ('*' o '$'). */
int leer_datos_de_entrada(CASOPRUEBA *todos_los_sets, int *num_sets_leidos) {
    int i, j, lado, resultado_lectura, sets_leidos_temp;
    char separador[5];         // Captura el separador o el finalizador '$'.
    CASOPRUEBA *set_actual;    // Puntero de conveniencia.

    sets_leidos_temp = 0;      // Comienza el conteo de sets.

    /* Bucle principal: Leer sets hasta el límite de capacidad o el final de archivo/entrada ('$'). */
    while (sets_leidos_temp < MAX_NUM_SETS) {
        set_actual = &todos_los_sets[sets_leidos_temp];           // Define el set actual.
        (*set_actual).puntuacion_maxima_encontrada = NO_ENCONTRADO;
        (*set_actual).lado_valido = 1;                            // **Optimista:** Se asume válido inicialmente.

        // Bucle interno: Leer los 6 triángulos del set.
        for (i = 0; i < NUM_TRIANGULOS; i++) {
            // Lectura de los 3 lados del triángulo i.
            resultado_lectura = scanf("%d %d %d",
                                     &(*set_actual).triangulos[i].lados[0],
                                     &(*set_actual).triangulos[i].lados[1],
                                     &(*set_actual).triangulos[i].lados[2]);

            // **Manejo de Fin de Entrada (EOF):**
            if (resultado_lectura != 3) {
                if (i == 0) { // Si falla al leer el primer triángulo, es el final de la entrada.
                    *num_sets_leidos = sets_leidos_temp;
                    return 1;
                }
                // Si falla a mitad de un set, se marca el set como inválido y se sale.
                (*set_actual).lado_valido = 0;
                break;
            }

            /* **Validación de Lados:** Se verifica el rango [1, 100]. */
            for (j = 0; j < NUM_LADOS; j++) {
                lado = (*set_actual).triangulos[i].lados[j];
                if (lado < 1 || lado > 100) {
                    (*set_actual).lado_valido = 0; // Falla la validación: set inválido.
                    break;
                }
            }
        }

        // **Lectura del Separador/Finalizador:**
        if (scanf("%s", separador) != 1) { // Intenta leer el carácter que sigue a los 6 triángulos.
            *num_sets_leidos = sets_leidos_temp; // Fin de archivo.
            return 1;
        }

        // **Validación del Separador:**
        if(separador[0] == '$'){ // Si el separador es '$', se detiene la lectura.
            *num_sets_leidos = sets_leidos_temp;
            return 1;
        }else if(separador[0] == '*'){ // Si el separador no es '*', el set es inválido.
            // Marca el set como inválido.
            sets_leidos_temp++; // Incrementa el contador para el próximo set.
            break; // Continúa con el siguiente set.
        }else{
            // Si el separador no es ni '*' ni '$', el set es inválido.
            (*set_actual).lado_valido = 0;
        }

        sets_leidos_temp++; // Set de 6 triángulos leído correctamente.
    }

    // Caso: Se alcanzó el límite MAX_NUM_SETS.
    *num_sets_leidos = sets_leidos_temp;
    return 1;
}

/* Imprime los resultados de todos los sets en el formato requerido. */
void imprimir_resultados(const CASOPRUEBA *todos_los_sets, int num_sets_leidos){
    int i;
    for(i = 0; i < num_sets_leidos; i++){
        // Si el resultado es NO_ENCONTRADO (o lado inválido), imprime "None".
        if(todos_los_sets[i].puntuacion_maxima_encontrada == NO_ENCONTRADO){
            printf("None\n");
        }else{
            // De lo contrario, imprime la puntuación máxima encontrada.
            printf("%d\n", todos_los_sets[i].puntuacion_maxima_encontrada);
        }
    }
}

// ----------------------------------------------------------------------
// --- FUNCIONES DE LÓGICA Y CÁLCULO (Backtracking) ---
// ----------------------------------------------------------------------

/* Prepara y llama al algoritmo recursivo de Backtracking. */
void calcular_y_almacenar_resultado(CASOPRUEBA *set){

    TRIANGULO hexagono_formado[NUM_TRIANGULOS]; // Arreglo donde se construye la secuencia del hexágono.
    int triangulo_usado[NUM_TRIANGULOS];        // Array de estado: controla si un triángulo original ya fue usado.
    int max_puntuacion;                         // Variable que el Backtracking actualizará con el mejor resultado.
    int i;
    
    // Inicialización del estado.
    for(i = 0; i < NUM_TRIANGULOS; i++){
        triangulo_usado[i] = 0; // Ningún triángulo ha sido usado.
    }
    max_puntuacion = NO_ENCONTRADO; // Se inicializa al valor de no encontrado.

    // Inicia la búsqueda: Comienza a colocar triángulos en la 'posicion' 0.
    buscar_max_puntuacion(0, (*set).triangulos, hexagono_formado, triangulo_usado, &max_puntuacion);

    // Guarda el resultado final.
    (*set).puntuacion_maxima_encontrada = max_puntuacion;
}


/* Rota un triángulo: Cambia la posición lógica de los 3 lados. */
void rotar_triangulo(const TRIANGULO t, int rotacion, TRIANGULO *rotado){
    // rotacion = 0: L0, L1, L2
    // rotacion = 1: L1, L2, L0 (giro de 120 grados)
    // rotacion = 2: L2, L0, L1 (giro de 240 grados)

    if(rotacion == 0){ 
        // No hay rotación (copia directa).
        (*rotado).lados[0] = t.lados[0];
        (*rotado).lados[1] = t.lados[1];
        (*rotado).lados[2] = t.lados[2];
    }else if(rotacion == 1){ 
        // Lado[0] de 't' pasa a Lado[2] de 'rotado'.
        (*rotado).lados[0] = t.lados[1];
        (*rotado).lados[1] = t.lados[2];
        (*rotado).lados[2] = t.lados[0];
    }else{/* rotacion == 2 */ 
        // Lado[0] de 't' pasa a Lado[1] de 'rotado'.
        rotado->lados[0] = t.lados[2];
        rotado->lados[1] = t.lados[0];
        rotado->lados[2] = t.lados[1];
    }
}


/* Función de Backtracking: Prueba todas las combinaciones y rotaciones para maximizar la puntuación. */
// 'posicion': índice del triángulo a colocar actualmente (0 a 5).
// 'triangulo_entrante': Los 6 triángulos originales.
// 'hexagono_formado': La secuencia que se está construyendo.
// 'triangulo_usado': Estado de uso de los triángulos originales.
// 'max_puntuacion': Puntero al máximo global.
void buscar_max_puntuacion(int posicion, const TRIANGULO *triangulo_entrante, TRIANGULO *hexagono_formado, int *triangulo_usado, int *max_puntuacion) {
    int i, Rotacion, puntuacion_actual;
    TRIANGULO t_rotado; // Triángulo con la orientación actual que se intenta colocar.

    // 1. CONDICIÓN DE PARADA (Caso Base)
    if(posicion == NUM_TRIANGULOS){ // Se han colocado los 6 triángulos (índices 0 a 5).
        // **Verificación de Cierre:** El lado derecho del último (5) debe coincidir con el lado izquierdo del primero (0).
        if(hexagono_formado[NUM_TRIANGULOS - 1].lados[2] == hexagono_formado[0].lados[1]){
            puntuacion_actual = 0;
            
            /* Cálculo de la Puntuación:** Suma de los 6 lados base (lados[0]). */
            for(i = 0; i < NUM_TRIANGULOS; i++){
                puntuacion_actual += hexagono_formado[i].lados[0];
            }
            
            // Actualización del Máximo Global.
            if(puntuacion_actual > *max_puntuacion){
                *max_puntuacion = puntuacion_actual;
            }
        }
        return; // Retorna al nivel de recursión anterior.
    }

    // 2. RECURSIÓN (Búsqueda)
    // Se itera sobre cada uno de los 6 triángulos disponibles (Exploración).
    for(i = 0; i < NUM_TRIANGULOS; i++){
        if(!triangulo_usado[i]){ // **Poda:** Solo se consideran triángulos no usados.
            
            /* Bucle para probar las 3 orientaciones (rotaciones). */
            for(Rotacion = 0; Rotacion < NUM_LADOS; Rotacion++){
                rotar_triangulo(triangulo_entrante[i], Rotacion, &t_rotado); // Genera la rotación actual.
                
                // **Verificación de Emparejamiento:**
                // Condición 1: El primer triángulo (posicion == 0) puede ser cualquiera.
                // Condición 2: El Lado Derecho (lados[2]) del anterior DEBE ser igual al Lado Izquierdo (lados[1]) del actual.
                if(posicion == 0 || hexagono_formado[posicion - 1].lados[2] == t_rotado.lados[1]){
                    
                    // **Acción (Selección):** El triángulo encaja.
                    triangulo_usado[i] = 1;                     // Marca como USADO.
                    hexagono_formado[posicion] = t_rotado;      // Lo COLOCA en el hexágono.
                    
                    // **Llamada Recursiva:** Avanza al siguiente triángulo.
                    buscar_max_puntuacion(posicion + 1, triangulo_entrante, hexagono_formado, triangulo_usado, max_puntuacion);
                    
                    // **BACKTRACKING (Retorno):** Deshace la elección.
                    triangulo_usado[i] = 0; // Marca como NO USADO, permitiendo que sea elegido en otra rama del árbol.
                }
            }
        }
    }
}