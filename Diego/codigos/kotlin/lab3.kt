import java.io.File
import kotlin.math.ln

fun calc_rocio(temperatura: Double, humedad: Double): Double {
    val gamma = ((17.27 * temperatura) / (237.7 + temperatura)) + ln(humedad / 100.0)
    return (237.7 * gamma) / (17.27 - gamma)
}

// Función auxiliar para clasificar el punto de rocío
fun clasificarRocio(pr: Double): String {
    return when {
        pr < 0.0 -> "Riesgo de Helada Negra"
        pr >= 0.0 && pr < 3.0 -> "Riesgo de Escarcha"
        else -> "Ambiente seguro"
    }
}

fun main() {
    val archivo = File("datos.csv")

    var lineas : List<String> = archivo.readLines()

    // Se elimina la línea inicial con los encabezados
    lineas = lineas.drop(1)

    // Para cada línea se ejecuta map y se extraen los datos
    val datosLimpios: List<List<Any>> = lineas.map { linea ->
        // Se quitan las comillas del principio y del final de la línea
        val sinComillasExtremas = linea.removeSurrounding("\"")
        // Se separa usando patrón comilla-coma-comilla (",")
        val columnas = sinComillasExtremas.split("\",\"")

        val hora = columnas[0]
        val tempC = columnas[1].replace(",", ".").toDouble()
        val hum = columnas[3].replace(",", ".").toDouble()

        listOf(hora, tempC, hum)
    }

    // Preparar lista de líneas para el reporte CSV
    val lineasReporte = mutableListOf<String>()
    
    // Encabezado del reporte
    lineasReporte.add("Hora,Punto de Rocio (Pr),Clasificacion")

    for (fila in datosLimpios) {
        val hora = fila[0] as String
        val temperatura = fila[1] as Double
        val humedad = fila[2] as Double

        // Cálculo y clasificación
        val pr = calc_rocio(temperatura, humedad)
        val clasificacion = clasificarRocio(pr)

        // Se da formato a la fila del CSV (redondeando Pr a 2 decimales)
        val prFormateado = String.format("%.2f", pr)
        lineasReporte.add("\"$hora\",$prFormateado,\"$clasificacion\"")
    }

    // Crear y almacenar en el archivo punto_rocio.csv
    val archivoSalida = File("punto_rocio.csv")
    archivoSalida.writeText(lineasReporte.joinToString("\n"))

    println("Reporte 'punto_rocio.csv' generado exitosamente.")
}