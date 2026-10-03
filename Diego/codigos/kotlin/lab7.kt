import java.io.File

val historialLog = mutableListOf<String>()

fun main() {
  println("=== SISTEMA DE NOTIFICACIONES ===")
  
  while(true) {
    println("\n1. Enviar Email")
    println("2. Enviar SMS")
    println("3. Salir")
    print("Elija opción: ")
    
    val opStr = readln()
    val op = opStr.toIntOrNull() ?: 0
    
    if (op == 1) {
      print("Ingrese destinatario (email): ")
      val destino = readln()
      
      if (!destino.contains("@")) {
        println("ERROR: Email inválido")
        continue
      }
      
      print("Ingrese mensaje: ")
      val mensaje = readln()
      
      val registro = "EMAIL a $destino: $mensaje"
      println("Enviando correo electrónico...")
      println("CONECTANDO AL SERVIDOR SMTP...")
      println("¡Enviado con éxito!")
      
      historialLog.add(registro)
      File("log.txt").appendText("$registro\n")
      
    } else if (op == 2) {
      print("Ingrese número de teléfono: ")
      val destino = readln()
      
      if (destino.length < 9) {
        println("ERROR: Teléfono muy corto")
        continue
      }
      
      print("Ingrese mensaje: ")
      val mensaje = readln()
      
      val registro = "SMS al +56$destino: $mensaje"
      println("Enviando mensaje de texto...")
      println("CONECTANDO A TORRE DE TELEFONÍA...")
      println("¡Enviado con éxito!")
      
      historialLog.add(registro)
      File("log.txt").appendText("$registro\n")
      
    } else if (op == 3) {
      println("Saliendo...")
      break
    } else {
      println("Opción no válida")
    }
  }
}