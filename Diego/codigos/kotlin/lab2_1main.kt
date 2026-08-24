package cl.ucm.clima

// 3. Importar la función anterior
import cl.ucm.clima.utils.convertirTemperatura

fun main() {
    // Leer la temperatura desde la consola

    println("Convertidor de temperatura desde Fahrenheit a Celcius")

    println("Ingrese el valor de la temperatura: ")
    val inputTemp = readln().toDoubleOrNull() ?: 0.0

    print("Si es Fahrenheit ingrese 'true' :")
    val inputConvertir = readln().toBooleanStrictOrNull() ?: false

    // 3. Llamar a la función usando parámetros nombrados
    val resultado = convertirTemperatura(inputTemp, inputConvertir)

    // Mostrar el resultado de la conversión
    println("La temperatura calculada es: $resultado")
}
