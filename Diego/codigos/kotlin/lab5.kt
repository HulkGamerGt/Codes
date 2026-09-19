package cl.ucm.lab4.modelos

import java.io.File
import java.io.IOException

// 1. Modificación de CuentaBancaria para arrojar errores personalizados
class CuentaBancaria(var titular: String, private var saldo: Double) {

    constructor(titular: String) : this(titular = titular, saldo = 0.0)

    init {
        require(titular.isNotBlank()) { "El titular no puede estar vacio" }
    }

    fun getSaldo(): Double = saldo

    fun depositar(monto: Double): Double {
        if (monto <= 0) {
            throw MontoInvalidoException("El monto a depositar ($monto) debe ser mayor a cero.")
        }
        saldo += monto
        return saldo
    }

    fun retirar(monto: Double): Boolean {
        // Validacion de monto invalido
        if (monto <= 0) {
            throw MontoInvalidoException("El monto a retirar ($monto) debe ser mayor a cero.")
        }
        // Validacion de fondos insuficientes usando el error personalizado
        if (monto > saldo) {
            throw SaldoInsuficienteException("Fondos insuficientes. Intenta retirar \$$monto pero tu saldo actual es de \$$saldo.")
        }
        saldo -= monto
        return true
    }

    fun mostrarResumen() {
        println("╔══════════════════════════════╗")
        println("║      RESUMEN DE CUCTA       ║")
        println("╠══════════════════════════════╣")
        println("║ Titular: $titular")
        println("║ Saldo: \$$saldo") 
        println("╚══════════════════════════════╝")
    }
}

class Banco {
    val cuentasRegistradas: MutableList<CuentaBancaria> = mutableListOf()

    // 2. Modificación del método transferir() para arrojar un error personalizado y registrar en CSV
    fun transferir(monto: Double, cuentaOrigen: CuentaBancaria, cuentaDestino: CuentaBancaria) {
        if (monto <= 0) {
            throw MontoInvalidoException("El monto de transferencia ($monto) debe ser mayor a cero.")
        }
        
        // El metodo retirar() arrojara SaldoInsuficienteException si no hay dinero.
        // Al no capturarlo aqui con un try-catch, el error se propaga hacia el main().
        cuentaOrigen.retirar(monto)
        cuentaDestino.depositar(monto)
        println("Transferencia exitosa. Se enviaron \$$monto desde la cuenta de ${cuentaOrigen.titular} a la de ${cuentaDestino.titular}.")

        // i. Crear una instancia de Transaccion
        val transaccion = Transaccion(monto, cuentaOrigen.titular, cuentaDestino.titular)

        // ii. Usar el método toCSVLine() para generar una String
        val lineaCSV = transaccion.toCSVLine()

        // iii. Añadirla al final de un archivo historial.csv
        try {
            val archivo = File("historial.csv")
            archivo.appendText(lineaCSV + "\n")
            println("Transaccion persistida en historial.csv correctamente.")
        } catch (e: IOException) {
            println("ERROR AL GUARDAR: No se pudo escribir en el archivo historial.csv: ${e.message}")
        }
    }

    fun registrarCuenta(cuenta: CuentaBancaria) {
        if (!cuentasRegistradas.contains(cuenta)) {
            cuentasRegistradas.add(cuenta)
        }
    }
}

// Clases de soporte proporcionadas en tu código original
data class Transaccion(var monto: Double, var emisor: String, var destinatario: String) {
    // Paso 3.1: Añadir método toCSVLine() a la clase Transaccion
    fun toCSVLine(): String {
        return "$monto,$emisor,$destinatario"
    }
}

class SaldoInsuficienteException(mensaje: String) : Exception(mensaje)
class MontoInvalidoException(mensaje: String) : Exception(mensaje)


// 3. Capturar los errores en el main() y mostrar mensajes amigables
fun main() {
    val banco = Banco()
    
    val cuentajoakolover = CuentaBancaria("joakolover lover", 50000.0)
    val cuentaBruno = CuentaBancaria("Bruno Faundez", 10000.0)
    
    banco.registrarCuenta(cuentajoakolover)
    banco.registrarCuenta(cuentaBruno)

    println("--- Simulando operaciones bancarias ---")

    // Caso 1: Intento de retiro con fondos insuficientes
    try {
        println("\n[Intentando retirar \$60,000 de la cuenta de joakolover...]")
        cuentajoakolover.retirar(60000.0)
    } catch (e: SaldoInsuficienteException) {
        println("ERROR: Lo sentimos, no pudimos procesar el retiro. ${e.message}")
    } catch (e: MontoInvalidoException) {
        println("ERROR: ${e.message}")
    }

    // Caso 2: Intento de transferencia con monto inválido o negativo
    try {
        println("\n[Intentando transferir \$-5,000 desde Bruno a joakolover...]")
        banco.transferir(-5000.0, cuentaBruno, cuentajoakolover)
    } catch (e: SaldoInsuficienteException) {
        println("ERROR: La transferencia fallo debido a problemas de fondos. ${e.message}")
    } catch (e: MontoInvalidoException) {
        println("ERROR: Operacion rechazada. ${e.message}")
    }

    // Caso 3: Transferencia válida y exitosa
    try {
        println("\n[Intentando transferir \$15,000 desde joakolover a Bruno...]")
        banco.transferir(15000.0, cuentajoakolover, cuentaBruno)
    } catch (e: Exception) {
        println("ERROR INESPERADO: ${e.message}")
    }

    // Mostrar estado final de las cuentas
    println("\n--- Resumen Final ---")
    cuentajoakolover.mostrarResumen()
    cuentaBruno.mostrarResumen()
}



/*import cl.ucm.lab4.modelos.CuentaBancaria
import cl.ucm.lab4.modelos.Banco

fun main() {
  // Paso 1 y 2 
  var cuenta1 = CuentaBancaria("Usuario 1")
  println("Titular: ${cuenta1.titular}")
  println("Saldo inicial: ${cuenta1.getSaldo()}")

  cuenta1.depositar(1000.0)
  println("Saldo después del depósito: ${cuenta1.getSaldo()}")

  cuenta1.retirar(250.0)
  println("Saldo después del retiro: ${cuenta1.getSaldo()}")

  cuenta1.mostrarResumen()

  // Paso 3
  var cuenta2 = CuentaBancaria("Usuario 2")
  cuenta2.depositar(3000.0)

  var banco = Banco()
  println("Resúmenes de cuentas antes de la transferencia:")
  cuenta1.mostrarResumen()
  cuenta2.mostrarResumen()
  banco.transferir(monto = 1500.0, cuentaOrigen = cuenta2, cuentaDestino = cuenta1)

  println("Resúmenes de cuentas después de la transferencia:")
  cuenta1.mostrarResumen()
  cuenta2.mostrarResumen()

  // Paso 4
  // Mostrar saldo total
  banco.registrarCuenta(cuenta1)
  banco.registrarCuenta(cuenta2)

  // Esto debe mostrar que la cuenta1 ya existe
  banco.registrarCuenta(cuenta1)

  // Se obtiene el saldo total
  println("\n=== SALDO TOTAL DEL BANCO ===")
  println("Saldo total: $${banco.getSaldoTotal()}")
} */