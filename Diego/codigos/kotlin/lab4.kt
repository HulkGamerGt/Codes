class CuentaBancaria {

    var nombre: String = ""
    private var saldo: Double = 0.0

    constructor(nombre: String, saldo: Double = 0.0) {
        this.nombre = nombre
        this.saldo = saldo
    }

    init {
        require(nombre.isEmpty()) { "Nombre No vacio" }
    }

    fun getSaldo(): Double {
        return saldo
    }

    fun depositar(monto: Double) {
        if (monto > 0) {
            saldo += monto
        }
    }

    fun retirar(monto: Double): Boolean {
        return if (monto > 0 && saldo >= monto) {
            saldo -= monto
            true
        } else {
            println("Error: Fondos insuficientes o monto invalido")
            false
        }
    }

    fun mostrarResumen() {
        println("=== RESUMEN DE CUENTA ===")
        println("Titular: $nombre")
        println("Saldo: $${getSaldo()}")
        println("=========================")
    }
}

fun main() {
    val cuenta = CuentaBancaria("Bruno", 500.0)
    
    cuenta.depositar(200.0)
    cuenta.retirar(100.0)
    cuenta.mostrarResumen()
}
/*

class CuentaBancaria {

    var nombre: String = ""
    private var saldo: Double = 0.0

    constructor(nombre: String, saldo: Double = 0.0) {
        this.nombre = nombre
        this.saldo = saldo
    }

    init {
        require(nombre.isNotBlank()) { "Nombre No vacio" }
    }

    fun getSaldo(): Double {
        return saldo
    }

    fun depositar(monto: Double) {
        if (monto > 0) {
            saldo += monto
        }
    }

    fun retirar(monto: Double): Boolean {
        return if (monto > 0 && saldo >= monto) {
            saldo -= monto
            true
        } else {
            println("Error: Fondos insuficientes o monto invalido")
            false
        }
    }

    fun mostrarResumen() {
        println("=== RESUMEN DE CUENTA ===")
        println("Titular: $nombre")
        println("Saldo: $${getSaldo()}")
        println("=========================")
    }
}

class Banco {

    fun transferir(monto: Double, cuentaOrigen: CuentaBancaria, cuentaDestino: CuentaBancaria) {
        if (cuentaOrigen.retirar(monto)) {
            cuentaDestino.depositar(monto)
            println("Transferencia exitosa: $monto de ${cuentaOrigen.nombre} a ${cuentaDestino.nombre}")
        } else {
            println("Transferencia fallida de ${cuentaOrigen.nombre} a ${cuentaDestino.nombre}")
        }
    }
}

fun main() {
    val cuenta1 = CuentaBancaria("Carlos", 1000.0)
    val cuenta2 = CuentaBancaria("Ana", 500.0)
    val miBanco = Banco()

    cuenta1.mostrarResumen()
    cuenta2.mostrarResumen()

    miBanco.transferir(300.0, cuenta1, cuenta2)

    cuenta1.mostrarResumen()
    cuenta2.mostrarResumen()

    miBanco.transferir(1500.0, cuenta1, cuenta2)
}


*/