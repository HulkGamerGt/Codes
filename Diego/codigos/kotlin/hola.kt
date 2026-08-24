// 1. Definimos la clase (el molde)
class Perro(val nombre: String, var edad: Int) {
    
    // Comportamiento (función/método)
    fun ladrar() {
        println("$nombre dice: ¡Guau, guau!")
    }
}

fun main() {
    // 2. Creamos los objetos usando el molde (no se usa la palabra 'new')
    val miPerro = Perro("Firulais", 3)
    val otroPerro = Perro("Luna", 5)

    // 3. Accedemos a sus propiedades y funciones
    println(miPerro.nombre) // Imprime: Firulais
    miPerro.ladrar()        // Imprime: Firulais dice: ¡Guau, guau!
    
    // Modificamos una propiedad mutable (var)
    otroPerro.edad = 6
    println("La nueva edad de ${otroPerro.nombre} es ${otroPerro.edad}")
}
