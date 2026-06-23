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

int main() {
    ListaEnlazada listaAgendados;
    Cola colaEspera;
    Pila historial;
    Pila anulados;   /* Pila separada para clientes anulados */

    inicializarLista(&listaAgendados);
    inicializarCola(&colaEspera);
    inicializarPila(&historial);
    inicializarPila(&anulados);

    /* Archivo de log */
    FILE *logFile = fopen("log_operaciones.txt", "w");
    if (!logFile) {
        printf("Error al crear log_operaciones.txt\n");
        return 1;
    }
    fprintf(logFile, "--- Inicio de operaciones ---\n");

    /* Carga inicial */
    int c1 = cargarClientesAgendados("clientes_agendados.txt", &listaAgendados,
                                     &colaEspera, &historial, logFile);

    int c2 = cargarClientesLlegada("clientes_llegada.txt", &colaEspera,
                                   &listaAgendados, &historial, logFile);
    total_cargados_inicial = c1 + c2;
    fprintf(logFile, "Cargados inicialmente: %d (agendados: %d, llegada: %d)\n\n",
            total_cargados_inicial, c1, c2);

    /* Procesar operaciones */
    procesarOperaciones("operaciones.txt", &listaAgendados, &colaEspera,
                        &historial, &anulados, logFile);

    fprintf(logFile, "\n--- Fin de operaciones ---\n");
    fclose(logFile);

    /* Generar reportes */
    generarReporteFinal("reporte_final.txt", &listaAgendados, &colaEspera,
                        &historial, &anulados);
    generarEstadisticas("estadisticas.txt", &listaAgendados, &colaEspera,
                        &historial, total_cargados_inicial,
                        total_agendados_acum, total_cola_acum);

    /* Liberar memoria */
    liberarLista(&listaAgendados);
    liberarCola(&colaEspera);
    liberarPila(&historial);
    liberarPila(&anulados);

    printf("Simulación completada. Archivos generados.\n");
    return 0;
}