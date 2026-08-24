package cl.ucm.clima.utils

/**
 * Convierte la temperatura.
 * Si [aFahrenheit] es true, convierte de Celsius a Fahrenheit.
 * Si es false, realiza la conversión inversa (Fahrenheit a Celsius).
 */
fun convertirTemperatura(temperatura: Double, aFahrenheit: Boolean): Double {
    return if (aFahrenheit) {
        (temperatura * 9 / 5) + 32
    } else {
        temperatura 
    }
}
