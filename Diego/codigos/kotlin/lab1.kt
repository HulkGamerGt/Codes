import kotlin.random.Random

fun main() {

    val jugadas = listOf("Piedra", "Papel" , "Tijeras")

    println("Hoy jugaremos al Piedra(1), Papel(2) o Tijera(3)")
    var jugada: Int
    do{
        print("Para salir del juego ingrese 0, ")
        print("Ingrese su jugada: ")
        jugada = readln().toInt()

        val computadora = Random.nextInt(1, 4)
        if(jugada !=0){
            if(jugada == computadora){
                println("Empate")
            }else if((jugada == 1 && computadora == 3) || (jugada == 2 && computadora == 1) || (jugada == 3 && computadora == 2)){
                println("Ganaste")
            }else{
                println("Perdiste")
            }
            if(jugada != 0){
                println("La computadora eligió: ${jugadas[computadora-1]}")
            }
        }
    }while(jugada != 0)

    println("Nos vemos")
    
}
