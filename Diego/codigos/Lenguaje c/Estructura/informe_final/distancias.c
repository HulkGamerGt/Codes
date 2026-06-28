#include <math.h>
#include "distancias.h"

#define PI_LOCAL 3.14159265358979323846
#define RADIO_TIERRA_KM 6372.8  /* R indicado en el enunciado */

double grados_a_radianes(double grados) {
    return grados * PI_LOCAL / 180.0;
}

double distancia_euclidiana_aprox(double lat1, double lon1, double lat2, double lon2) {
    /* Proyeccion equirectangular: convierte diferencias de lat/lon a km
     * y luego aplica el teorema de Pitagoras (distancia euclidiana). */
    double lat1r = grados_a_radianes(lat1);
    double lat2r = grados_a_radianes(lat2);
    double dLat = grados_a_radianes(lat2 - lat1);
    double dLon = grados_a_radianes(lon2 - lon1);
    double x = dLon * cos((lat1r + lat2r) / 2.0);
    double y = dLat;
    return RADIO_TIERRA_KM * sqrt(x * x + y * y);
}

double distancia_haversine(double lat1, double lon1, double lat2, double lon2) {
    double dLat = grados_a_radianes(lat2 - lat1);
    double dLon = grados_a_radianes(lon2 - lon1);
    double lat1r = grados_a_radianes(lat1);
    double lat2r = grados_a_radianes(lat2);

    double a = sin(dLat / 2.0) * sin(dLat / 2.0)
             + cos(lat1r) * cos(lat2r) * sin(dLon / 2.0) * sin(dLon / 2.0);

    return 2.0 * RADIO_TIERRA_KM * asin(sqrt(a));
}
