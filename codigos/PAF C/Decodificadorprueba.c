#include <stdio.h>
#include <string.h>

/* Prototipos de Funciones */
void inicializa_alfabeto(char *alfabeto);
int buscar_posicion_en_alfabeto(char caracter, char *alfabeto);
char buscar_caracter_por_posicion(int posicion, char *alfabeto);
int lee_codificado(char *mensaje, int *N);
void graba_decodificado(char *mensaje_decodificado);

void decodificar(char *mensaje_codificado_con_clave, char *mensaje_decodificado, char *alfabeto, int N);
void revertir_segunda_etapa_codificador(char *mensaje_codificado_entrada, char *mensaje_salida_intermedio, char *alfabeto, int N);
void revertir_primera_etapa_codificador(char *mensaje_intermedio, char *mensaje_decodificado, char *alfabeto, int N);

/* Función Principal del Decodificador */
int main() {
    char alfabeto[48];
    char codificado[100];
    char decodificado[100];
    int clave_n;
    int lectura_exitosa;

    inicializa_alfabeto(alfabeto);
    lectura_exitosa = lee_codificado(codificado, &clave_n);
    
    if (!lectura_exitosa) {
        printf("No se pudo decodificar el mensaje debido a un error en 'codificado.txt'.\n");
        return 1; 
    }

    decodificar(codificado, decodificado, alfabeto, clave_n);
    graba_decodificado(decodificado);

    return 0; 
}

/* Inicializa el vector del alfabeto con los caracteres definidos */
void inicializa_alfabeto(char *alfabeto) {
    strcpy(alfabeto, "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789!,.:;?-+*/");
}

/* Busca la posición de un carácter dado en el alfabeto. Retorna -1 si no lo encuentra. */
int buscar_posicion_en_alfabeto(char caracter, char *alfabeto) {
    int i;
    for (i = 0; i < strlen(alfabeto); i++) {
        if (alfabeto[i] == caracter) {
            return i;
        }
    }
    return -1;
}

/* Busca el carácter en una posición dada del alfabeto, manejando la circularidad. */
char buscar_caracter_por_posicion(int posicion, char *alfabeto) {
    int tamano = strlen(alfabeto);
    int indice_final = posicion % tamano;
    
    if (indice_final < 0) {
        indice_final += tamano;
    }
    return alfabeto[indice_final];
}

/* Lee el mensaje codificado y la clave N desde "codificado.txt". */
int lee_codificado(char *mensaje_codificado_con_clave, int *clave_N_codificado) {
    FILE *archivo;
    char Linea_completa[100];
    char *Posicion_gato; 
    int  Longitud_linea;

    archivo = fopen("codificado.txt", "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo 'codificado.txt'. Asegurese de que existe.\n");
        return 0;
    }

    if (fgets(Linea_completa, sizeof(Linea_completa), archivo) != NULL) {
        Longitud_linea = strlen(Linea_completa);
        if (Longitud_linea > 0 && Linea_completa[Longitud_linea - 1] == '\n') {
            Linea_completa[Longitud_linea - 1] = '\0';
        }
        Posicion_gato = strchr(Linea_completa, '#'); 

        if (Posicion_gato != NULL) {
            if (Linea_completa[0] >= '0' && Linea_completa[0] <= '9') {
                *clave_N_codificado = Linea_completa[0] - '0';
            } else {
                printf("Error: La clave N en 'codificado.txt' no es un digito valido. Formato incorrecto.\n");
                fclose(archivo);
                return 0;
            }
            strcpy(mensaje_codificado_con_clave, Linea_completa);
            fclose(archivo);
            return 1;
        } else {
            printf("Formato de archivo 'codificado.txt' es incorrecto. Se esperaba clave#mensaje.\n");
            fclose(archivo);
            return 0;
        }
    } else {
        printf("El archivo 'codificado.txt' está vacio o no se pudo leer.\n");
        fclose(archivo);
        return 0;
    }
}

/* Graba el mensaje decodificado en "decodificado.txt". */
void graba_decodificado(char *mensaje_decodificado) {
    FILE *archivo;

    archivo = fopen("decodificado.txt", "w");
    if (archivo == NULL) {
        printf("Error al crear 'decodificado.txt'.\n");
        return;
    }
    fprintf(archivo, "%s", mensaje_decodificado);
    fclose(archivo);
    printf("Mensaje decodificado guardado en 'decodificado.txt'.\n");
}

/* Función principal para la decodificación del mensaje. */
void decodificar(char *mensaje_codificado_con_clave, char *mensaje_decodificado, char *alfabeto, int N) {
    char *Almacenar_gato;
    char Mensaje_solo_codificado[100];
    char Mensaje_intermedio_decodificado[100];

    Almacenar_gato = strchr(mensaje_codificado_con_clave, '#');
    strcpy(Mensaje_solo_codificado, Almacenar_gato + 1);

    // PASO 1: Revertir la SEGUNDA ETAPA del Codificador
    // La segunda etapa del codificador RESTA N solo si la posición *antes de la resta* era múltiplo de 4.
    // Para revertir, tenemos que calcular la posición que *tendría* el caracter en el mensaje intermedio del codificador (antes de la segunda etapa del codificador).
    // Si esa posición (pos_en_intermedio_del_codificador) era múltiplo de 4, entonces le sumamos N para revertir.
    revertir_segunda_etapa_codificador(Mensaje_solo_codificado, Mensaje_intermedio_decodificado, alfabeto, N);

    // PASO 2: Revertir la PRIMERA ETAPA del Codificador
    // La primera etapa del codificador SUMA N a *todos* los caracteres.
    // Para revertir, RESTAMOS N a *todos* los caracteres.
    revertir_primera_etapa_codificador(Mensaje_intermedio_decodificado, mensaje_decodificado, alfabeto, N);
}

/* Revertir la Segunda Etapa del Codificador: Deshace la resta de N si la posición era múltiplo de 4. */
void revertir_segunda_etapa_codificador(char *mensaje_codificado_entrada, char *mensaje_salida_intermedio, char *alfabeto, int N) {
    int i;
    int pos_caracter_actual;
    int tamano_alfabeto = strlen(alfabeto);
    
    strcpy(mensaje_salida_intermedio, mensaje_codificado_entrada);

    for (i = 0; mensaje_salida_intermedio[i] != '\0'; i++) {
        pos_caracter_actual = buscar_posicion_en_alfabeto(mensaje_salida_intermedio[i], alfabeto);

        if (pos_caracter_actual != -1) {
            // Calculamos la posición que este caracter tenía en el mensaje intermedio del codificador.
            // Si el codificador le RESTÓ N, su posición actual es (Pos_intermedia - N).
            // Entonces, Pos_intermedia = Pos_actual + N.
            int pos_en_intermedio_del_codificador = (pos_caracter_actual + N);
            
            // Aseguramos que sea positivo y dentro del rango del alfabeto para el cálculo del módulo.
            // Esto es crucial para que el '%' funcione como "módulo matemático" y no "resto".
            pos_en_intermedio_del_codificador = pos_en_intermedio_del_codificador % tamano_alfabeto;
            if (pos_en_intermedio_del_codificador < 0) {
                pos_en_intermedio_del_codificador += tamano_alfabeto;
            }

            // AHORA sí, si esa "posición intermedia" era múltiplo de 4, el codificador le restó N.
            // Nosotros le sumamos N para revertir.
            if (pos_en_intermedio_del_codificador % 4 == 0) {
                mensaje_salida_intermedio[i] = buscar_caracter_por_posicion(pos_caracter_actual + N, alfabeto);
            }
            // Si no fue afectado por la segunda etapa del codificador, se mantiene igual.
        }
    }
    mensaje_salida_intermedio[i] = '\0';
}

/* Revertir la Primera Etapa del Codificador: Deshace la suma de N a todos los caracteres. */
void revertir_primera_etapa_codificador(char *mensaje_intermedio, char *mensaje_decodificado, char *alfabeto, int N) {
    int i;
    int pos_caracter_actual;
    
    strcpy(mensaje_decodificado, mensaje_intermedio);

    for (i = 0; mensaje_decodificado[i] != '\0'; i++) {
        pos_caracter_actual = buscar_posicion_en_alfabeto(mensaje_decodificado[i], alfabeto);
        
        if (pos_caracter_actual != -1) {
            // La primera etapa del codificador siempre SUMÓ N a cada carácter.
            // Para revertir, siempre RESTAMOS N a cada carácter.
            mensaje_decodificado[i] = buscar_caracter_por_posicion(pos_caracter_actual - N, alfabeto);
        }
    }
    mensaje_decodificado[i] = '\0';
}