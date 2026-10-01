import.java.io.File

open class GeneradorBase{

    open fun generar(){
        return "Soy un String de ejemplo xd lol"
    }

    fun generarN(n: Int): list<String>{
        var lista = mutablelistof<String>()
        for(i in 0..n){
            var elemento : String = generar()
            lista.add(elemento)
        }
        return lista
    }

    fun generarNArchivo(n: Int, archivo: String) {
        require(n > 0) { "El valor de n debe ser positivo" }
        val valores = generarN(n)
        File(archivo).writeLines(valores) 
    }
}

class GeneradorRango : GeneradorBase() {
    private val rangos = listOf("Bronce", "Plata", "Oro", "Platino", "Diamante", "Campeón", "Gran Campeón", "Leyenda Supersonica")
    
    override fun generar(): String {
        return rangos.random()
    }
}

class GeneradorAuto : GeneradorBase() {
    private val autos = listOf("Octane", "Fennec", "Dominus", "Breakout", "Batmobile", "Mantis")
    
    override fun generar(): String {
        return autos.random()
    }
}

class GeneradorArena : GeneradorBase() {
    private val arenas = listOf("DFH Stadium", "Mannfield", "Champions Field", "Neo Tokyo", "Utopia Coliseum", "Farmstead")
    
    override fun generar(): String {
        return arenas.random()
    }
}