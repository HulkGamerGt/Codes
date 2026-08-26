import kotlin.collections.List
import kotlin.collections.Set

data class Sala(val id: String, val cap: Int, val eq: Set<String>)
data class Sol(val idSol: String, val hr: String, val asis: Int, val eqReq: Set<String>)

data class Asig(val idSol: String, val idSala: String, val hr: String)
data class Rchz(val idSol: String, val mtv: String)

data class Est(val asigs: List<Asig> = emptyList(), val rchzs: List<Rchz> = emptyList())

fun main() {
    val catSalas = listOf(
        Sala("S1", 30, setOf("Proyector", "Pizarra")),
        Sala("S2", 15, setOf("TV")),
        Sala("S3", 50, setOf("Proyector", "Pizarra", "Audio"))
    )
    
    val flujoSols = listOf(
        Sol("Req1", "10:00", 20, setOf("Proyector")),
        Sol("Req2", "10:00", 10, setOf("TV")),
        Sol("Req3", "10:00", 40, setOf("MacBook"))
    )
    
    val resFinal = procFlujo(flujoSols, catSalas)
    
    println("Asignaciones Aceptadas:")
    resFinal.asigs.forEach { println(" -> Solicitud ${it.idSol} en Sala ${it.idSala} a las ${it.hr}") }
    
    println("\nSolicitudes Rechazadas:")
    resFinal.rchzs.forEach { println(" -> Solicitud ${it.idSol} rechazada. Motivo: ${it.mtv}") }
}

fun procFlujo(sols: List<Sol>, cat: List<Sala>): Est {
    // PUNTO 1 (Clausura): La clausura pasada a 'fold' captura 'cat' del entorno externo.
    // Esto permite consultar el catálogo iterativamente sin depender de un estado nombrado global.
    return sols.fold(Est()) { estAct, solAct -> 
        
        // PUNTO 2 (Clausura): La clausura en 'firstOrNull' captura 'solAct' y 'estAct'.
        // Evalúa las restricciones inyectando el contexto actual sin mutar variables.
        val salaOpt = cat.firstOrNull { sl -> 
            cumpleReq(sl, solAct) && isDisp(sl, solAct.hr, estAct.asigs) 
        }
        
        if (salaOpt != null) {
            val nvaAsig = Asig(solAct.idSol, salaOpt.id, solAct.hr)
            Est(estAct.asigs + nvaAsig, estAct.rchzs)
        } else {
            val nvoRchz = Rchz(solAct.idSol, "Capacidad o equipamiento insuficiente.")
            Est(estAct.asigs, estAct.rchzs + nvoRchz)
        }
    }
}

fun cumpleReq(sl: Sala, sol: Sol): Boolean {
    // PUNTO 3 (Clausura): La clausura en 'all' captura 'sl.eq'.
    // Aísla la verificación de subconjuntos manteniendo la pureza y determinismo de la función.
    return sl.cap >= sol.asis && sol.eqReq.all { req -> sl.eq.contains(req) }
}

fun isDisp(sl: Sala, hr: String, asigs: List<Asig>): Boolean {
    // Verifica disponibilidad filtrando colisiones de horario.
    return asigs.none { asig -> asig.idSala == sl.id && asig.hr == hr }
}