/*
    Nombres : Ruben Sanchez, Diego Solis, Benjamin Vasquez, Joaquin Vasquez.
    Docente : Nicolas Reyes Reyes.
    Tema : Informe Estructuras de Datos - Serviexpress
    Fecha : 03/06/2026
    Descripcion : Este programa se implementan las funciones anteriormente mencionadas en los archivos
    serviexpress.h y serviexpress.c. Estas funciones incluyen la inicializacion y liberacion de las estructuras,
    operaciones sobre la lista enlazada, la cola y la pila, verificacion global de duplicados, atencion de clientes, 
    carga de archivos iniciales, procesamiento de operaciones y generacion de reportes finales.
    Cada funcion esta diseñada para cumplir con su respectiva tarea dentro de la gestion de clientes 
    en la oficina de atencion al cliente "Serviexpress".
*/
#include "serviexpress.h"

int main(){
    ListaEnlazada listaAgendados;
    Cola colaEspera;
    Pila historial;

    inicializarLista(&listaAgendados);
    inicializarCola(&colaEspera);
    inicializarPila(&historial);

    /* Carga inicial */
    int c1 = cargarClientesAgendados("clientes_agendados.txt", &listaAgendados, &colaEspera, &historial);
    int c2 = cargarClientesLlegada("clientes_llegada.txt", &colaEspera, &listaAgendados, &historial);
    total_cargados_inicial = c1 + c2; /* Suma total de clientes cargados exitosamente */

    /* Archivo de log */
    FILE *logFile = fopen("log_operaciones.txt", "w");
    if(!logFile){
        printf("Error al crear log_operaciones.txt\n");
        return 1;
    }
    fprintf(logFile, "--- Inicio de operaciones ---\n");
    fprintf(logFile, "Cargados inicialmente: %d (agendados: %d, llegada: %d)\n\n",
            total_cargados_inicial, c1, c2);

    /* Procesar operaciones */
    procesarOperaciones("operaciones.txt", &listaAgendados, &colaEspera, &historial, logFile);

    fprintf(logFile, "\n--- Fin de operaciones ---\n");
    fclose(logFile);

    /* Reportes finales */
    generarReporteFinal("reporte_final.txt", &listaAgendados, &colaEspera, &historial);
    generarEstadisticas("estadisticas.txt", &listaAgendados, &colaEspera, &historial, total_cargados_inicial);

    /* Liberar memoria */
    liberarLista(&listaAgendados);
    liberarCola(&colaEspera);
    liberarPila(&historial);

    printf("Simulaci�n completada. Archivos generados.\n");
    return 0;
}