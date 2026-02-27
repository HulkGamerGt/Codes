#include <stdio.h>

#define FILAS 3
#define COLUMNAS 3
#define MAX_MOV 15
#define MAX_ESTADOS 10000

/* Estructura que representa el tablero del 8-puzzle */
typedef struct {
    int celdas[FILAS][COLUMNAS];
} TABLERO;

/* Estructura que almacena la solución del puzzle */
typedef struct {
    TABLERO pasos[MAX_MOV + 1];  /* Secuencia de estados del tablero */
    int movimientos[MAX_MOV];    /* Direcciones de los movimientos */
    int numeros[MAX_MOV];        /* Números que se movieron */
    int total_pasos;             /* Cantidad total de pasos */
} SOLUCION;

void copiar_tablero(TABLERO *, TABLERO *); /* Copia el contenido de un tablero a otro */
int mismos_tableros(TABLERO *, TABLERO *); /* Compara dos tableros y devuelve 1 si son iguales, 0 en caso contrario */
void intercambiar(int *, int *); /* Intercambia los valores de dos variables enteras */
void encontrar_vacio(TABLERO *, int *, int *); /* Encuentra la posición del espacio vacío (0) en el tablero */
int resolver_puzzle(TABLERO *, TABLERO *, SOLUCION *); /* Resuelve el puzzle usando búsqueda en amplitud  */
void leer_tablero(TABLERO *); /* Lee el tablero inicial desde la entrada estándar */
void mostrar_tablero(TABLERO *); /* Muestra el tablero en formato gráfico */

/* Vectores de movimiento: ARRIBA, IZQUIERDA, ABAJO, DERECHA */
int mov_fila[] = {1, 0, -1, 0};
int mov_col[] = {0, 1, 0, -1}; 
char *nombres_dir[] = {"ARRIBA", "IZQUIERDA", "ABAJO", "DERECHA"};

/* Función principal del programa */
int main(){
    TABLERO inicio;
    TABLERO objetivo = {{{1,2,3}, {4,5,6}, {7,8,0}}};
    SOLUCION sol;
    int resultado;
    int i;
    
    printf("Programa resolvedor de puzzle (no todos)\n");
    printf("\n\n");
    
    leer_tablero(&inicio);
    
    printf("\nEstado inicial:\n");
    mostrar_tablero(&inicio);
    
    printf("\nObjetivo:\n");
    mostrar_tablero(&objetivo);
    
    printf("\nBuscando solucion...\n");
    
    resultado = resolver_puzzle(&inicio, &objetivo, &sol);

    /* Mostrar resultados */
    if(resultado){
        printf("SOLUCION ENCONTRADA\n");
        printf("Movimientos: %d\n\n", sol.total_pasos - 1);
        
        /* Mostrar cada paso de la solución */
        for(i = 1; i < sol.total_pasos; i++){
            printf("Paso %d: Mover %d hacia %s\n", i, sol.numeros[i-1], nombres_dir[sol.movimientos[i-1]]);
            mostrar_tablero(&sol.pasos[i]);
            printf("\n");
        }
    }else{
        printf("NO SE ENCONTRO SOLUCION\n");
    }
    
    return 0;
}

/* Copia el contenido de un tablero a otro */
void copiar_tablero(TABLERO *dest, TABLERO *orig){
    int i, j;
    for(i = 0; i < FILAS; i++){
        for(j = 0; j < COLUMNAS; j++){
            dest->celdas[i][j] = orig->celdas[i][j];
        }
    }
}

/* Compara dos tableros y devuelve 1 si son iguales, 0 en caso contrario */
int mismos_tableros(TABLERO *t1, TABLERO *t2){
    int i, j;
    for(i = 0; i < FILAS; i++){
        for(j = 0; j < COLUMNAS; j++){
            if(t1->celdas[i][j] != t2->celdas[i][j]) return 0;
        }
    }
    return 1;
}

/* Intercambia los valores de dos variables enteras */
void intercambiar(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Encuentra la posición del espacio vacío (0) en el tablero */
void encontrar_vacio(TABLERO *t, int *fila, int *col){
    int i, j;
    for(i = 0; i < FILAS; i++){
        for(j = 0; j < COLUMNAS; j++){
            if(t->celdas[i][j] == 0){
                *fila = i;
                *col = j;
                return;
            }
        }
    }
    *fila = -1;
    *col = -1;
}

/* Resuelve el puzzle usando búsqueda en amplitud */
int resolver_puzzle(TABLERO *inicio, TABLERO *objetivo, SOLUCION *solucion){
    TABLERO cola[MAX_ESTADOS];        /* Cola para la búsqueda */
    int padre[MAX_ESTADOS];           /* Array de padres para reconstruir camino */
    int direccion_mov[MAX_ESTADOS];   /* Dirección del movimiento */
    int numero_movido[MAX_ESTADOS];   /* Número que se movió */
    int frente = 0, final = 0;        /* Índices para la cola */
    
    TABLERO visitados[MAX_ESTADOS];   /* Estados ya visitados */
    int num_visitados = 0;
    int fila_vacia, col_vacia;        /* Posición del espacio vacío */
    int d, nueva_fila, nueva_col;     /* Variables para movimientos */
    int numero, ya_visitado, v;
    int camino[MAX_MOV + 1];          /* Camino reconstruido */
    int pasos = 0;
    int indice, i;
    TABLERO actual, nuevo;
    
    /* Inicializar con el estado inicial */
    copiar_tablero(&cola[final], inicio);
    padre[final] = -1;
    direccion_mov[final] = -1;
    numero_movido[final] = -1;
    final++;
    
    copiar_tablero(&visitados[num_visitados], inicio);
    num_visitados++;

    /* Búsqueda en amplitud */
    while(frente < final && final < MAX_ESTADOS){
        actual = cola[frente];
        
        /* Verificar si se alcanzó el estado objetivo */
        if(mismos_tableros(&actual, objetivo)){
            indice = frente;
            pasos = 0;

            /* Reconstruir el camino desde el objetivo hasta el inicio */
            while(indice != -1){
                camino[pasos] = indice;
                pasos++;
                indice = padre[indice];
            }
            
            solucion->total_pasos = pasos;

            /* Almacenar los pasos de la solución en orden correcto */
            for(i = 0; i < pasos; i++){
                indice = camino[pasos - 1 - i];
                copiar_tablero(&solucion->pasos[i], &cola[indice]);
                /* Guardar información del movimiento (excepto para el estado inicial) */
                if(i > 0){
                    solucion->movimientos[i-1] = direccion_mov[indice];
                    solucion->numeros[i-1] = numero_movido[indice];
                }
            }
            return 1;  /* Solución encontrada */
        }
        
        /* Encontrar posición del espacio vacío */
        encontrar_vacio(&actual, &fila_vacia, &col_vacia);

        /* Generar todos los movimientos posibles */
        for(d = 0; d < 4; d++){
            nueva_fila = fila_vacia + mov_fila[d];
            nueva_col = col_vacia + mov_col[d];

            /* Verificar si el movimiento es válido (dentro del tablero) */
            if(nueva_fila >= 0 && nueva_fila < FILAS && nueva_col >= 0 && nueva_col < COLUMNAS){
                copiar_tablero(&nuevo, &actual);
                numero = nuevo.celdas[nueva_fila][nueva_col];
                
                /* Realizar el movimiento intercambiando con el espacio vacío */
                intercambiar(&nuevo.celdas[fila_vacia][col_vacia], &nuevo.celdas[nueva_fila][nueva_col]);
                
                /* Verificar si este estado ya fue visitado */
                ya_visitado = 0;
                for(v = 0; v < num_visitados; v++){
                    if(mismos_tableros(&nuevo, &visitados[v])){
                        ya_visitado = 1;
                        break;
                    }
                }

                /* Si es un estado nuevo, agregarlo a la cola */
                if(!ya_visitado){
                    copiar_tablero(&cola[final], &nuevo);
                    padre[final] = frente;
                    direccion_mov[final] = d;
                    numero_movido[final] = numero;
                    final++;
                    
                    copiar_tablero(&visitados[num_visitados], &nuevo);
                    num_visitados++;
                }
            }
        }
        
        frente++;  /* Pasar al siguiente estado en la cola */
    }
    
    return 0;  /* No se encontró solución */
}

/* Lee el tablero inicial desde la entrada estándar */
void leer_tablero(TABLERO *t){
    int temp[9];
    int valido = 0;
    int leidos;
    int indice, i, j;

    while(!valido){
        printf("Ingrese el puzzle (ej: 1-2-3-4-5-6-7-8-0): ");
        
        leidos = scanf("%d-%d-%d-%d-%d-%d-%d-%d-%d", &temp[0], &temp[1], &temp[2], &temp[3], &temp[4], &temp[5], &temp[6], &temp[7], &temp[8]);
            
        if(leidos == 9){
            indice = 0;
            /* Convertir el array lineal a matriz 3x3 */
            for(i = 0; i < FILAS; i++){
                for(j = 0; j < COLUMNAS; j++){
                    t->celdas[i][j] = temp[indice];
                    indice++;
                }
            }
            valido = 1;
        }else{
            printf("Formato incorrecto. Use: 1-2-3-4-5-6-7-8-0\n");
            printf("Use la tecla 'ENTER' para continuar\n");
            /* Limpiar buffer de entrada */
            while(getchar() != '\n');
        }
    }
}

/* Muestra el tablero en formato gráfico */
void mostrar_tablero(TABLERO *t){
    int i, j;
    printf("+---+---+---+\n");
    for(i = 0; i < FILAS; i++){
        printf("|");
        for(j = 0; j < COLUMNAS; j++){
            if(t->celdas[i][j] == 0) 
                printf("   |");
            else 
                printf(" %d |", t->celdas[i][j]);
        }
        printf("\n+---+---+---+\n");
    }
}