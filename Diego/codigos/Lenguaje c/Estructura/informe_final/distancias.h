#ifndef DISTANCIAS_H
#define DISTANCIAS_H

double grados_a_radianes(double grados);

/* Distancia euclidiana APROXIMADA entre dos coordenadas geograficas (en km),
 * usando proyeccion equirectangular simple. Se usa en el Ejercicio 1 (MST). */
double distancia_euclidiana_aprox(double lat1, double lon1, double lat2, double lon2);

/* Distancia de Haversine (en km), segun formula exacta del enunciado.
 * Se usa en el Ejercicio 2 (TSP / GRASP). */
double distancia_haversine(double lat1, double lon1, double lat2, double lon2);

#endif
