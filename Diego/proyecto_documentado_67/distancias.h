/* Calculo de distancias geograficas entre coordenadas (lat, lon). */

#ifndef DISTANCIAS_H
#define DISTANCIAS_H

#define PI_LOCAL 3.14159265358979323846
#define RADIO_TIERRA_KM 6372.8

/* Convierte un angulo de grados a radianes. */
double grados_a_radianes(double grados);

/* Distancia aproximada (proyeccion equirectangular), en km. */
double distancia_euclidiana_aprox(double lat1, double lon1,
                                   double lat2, double lon2);

/* Distancia de haversine (considera curvatura terrestre), en km. */
double distancia_haversine(double lat1, double lon1,
                            double lat2, double lon2);

#endif /* DISTANCIAS_H */
