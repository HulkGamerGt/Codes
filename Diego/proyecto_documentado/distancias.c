/* Implementacion de las formulas de distancia geografica. */

#include "distancias.h"
#include <math.h>

/* Convierte un angulo expresado en grados a su equivalente en radianes,
 * unidad requerida por las funciones trigonometricas de math.h. */
double grados_a_radianes(double grados) {
    return grados * (PI_LOCAL / 180.0);
}

/* Proyeccion equirectangular: corrige la longitud por el coseno de la
 * latitud promedio y aplica Pitagoras, escalado por el radio terrestre. */
double distancia_euclidiana_aprox(double lat1, double lon1,
                                   double lat2, double lon2) {
    double lat1_rad = grados_a_radianes(lat1);
    double lon1_rad = grados_a_radianes(lon1);
    double lat2_rad = grados_a_radianes(lat2);
    double lon2_rad = grados_a_radianes(lon2);
    double lat_promedio = (lat1_rad + lat2_rad) / 2.0;

    /* dx: diferencia de longitud corregida por el coseno de la latitud
     * promedio (las longitudes se "acercan" entre si cerca de los polos).
     * dy: diferencia de latitud, sin necesidad de correccion. */
    double dx = (lon2_rad - lon1_rad) * cos(lat_promedio);
    double dy = (lat2_rad - lat1_rad);

    return RADIO_TIERRA_KM * sqrt(dx * dx + dy * dy);
}

/* Formula del haversine: distancia de gran circulo sobre la esfera. */
double distancia_haversine(double lat1, double lon1,
                            double lat2, double lon2) {
    double lat1_rad = grados_a_radianes(lat1);
    double lat2_rad = grados_a_radianes(lat2);
    double d_lat = grados_a_radianes(lat2 - lat1);
    double d_lon = grados_a_radianes(lon2 - lon1);

    double sin_lat_medio = sin(d_lat / 2.0);
    double sin_lon_medio = sin(d_lon / 2.0);

    /* a representa el cuadrado de la mitad de la "cuerda" entre los dos
     * puntos sobre la esfera unitaria, segun la formula de haversine. */
    double a = (sin_lat_medio * sin_lat_medio) +
               cos(lat1_rad) * cos(lat2_rad) * (sin_lon_medio * sin_lon_medio);

    /* Se acota a [0,1] para evitar NaN por errores de redondeo. */
    if (a < 0.0) a = 0.0;
    if (a > 1.0) a = 1.0;

    return 2.0 * RADIO_TIERRA_KM * asin(sqrt(a));
}
