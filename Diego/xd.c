#include <stdio.h>
 /*Cada celda de la matriz contiene un Struct personalizado que encapsula:
1. Un String con el nombre del juego comunitario.
2. La ruta de la imagen o miniatura de previsualización.
3. Un puntero o enlace directo a la URL del código ejecutable en HTML5.*/

struct {
    char* FrivName;          
    char* rutaMiniatura;   // 2. Ruta de la imagen o miniatura de previsualización
    char* urlHTML5;        // 3. Enlace directo a la URL del código ejecutable en HTML5
};