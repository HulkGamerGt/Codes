// =======================================================
// === 1. LIBRERÍA Y DEFINICIONES DE PINES ===
// =======================================================

#include <TM1637Display.h> // Necesario para el display de 4 dígitos

// Pines del display TM1637 (Configuración solicitada)
#define CLK 22 
#define DIO 21
TM1637Display display(CLK, DIO);

// Pines del Semáforo KS0413
const int PIN_ROJO = 18;
const int PIN_AMARILLO = 19;
const int PIN_VERDE = 23;

// >>> DEFINICIONES DEL TONO (DIGITALWRITE - BLOQUEANTE) <<<
const int PIN_ALTAVOZ = 13;       // Pin para el altavoz/buzzer
const int FRECUENCIA_TONO = 800;  // Frecuencia del tono en Hz (800 Hz)

// Cálculo del medio período para generar 800 Hz
const int MEDIO_PERIODO_US = (1000000 / FRECUENCIA_TONO) / 2; 

// Variables de estado
enum EstadoSemaforo { ROJO, VERDE, AMARILLO };
EstadoSemaforo estadoActual = ROJO;

// Variables de Temporización (en milisegundos)
const long DURACION_ROJO_MS = 5000;  
const long DURACION_VERDE_MS = 7000; 
const long DURACION_AMARILLO_MS = 2000; // Duración igual al tono bloqueante

unsigned long tiempoCambio = 0;      // Almacena el tiempo del último cambio de estado
unsigned long ultimoSegundo = 0;     // Para temporizar el conteo de segundos
int segundosRestantes = 0;           // Segundos que faltan para el cambio

// =======================================================
// === 2. FUNCIONES AUXILIARES ===
// =======================================================

// Controla el estado de los LEDs del semáforo
void configurarSemaforo(int r, int a, int v) {
  digitalWrite(PIN_ROJO, r);
  digitalWrite(PIN_AMARILLO, a);
  digitalWrite(PIN_VERDE, v);
}

// ⚠️ FUNCIÓN BLOQUEANTE PARA EL TONO ⚠️
// Genera una onda cuadrada manual en el pin del altavoz por el tiempo especificado.
void tonoBloqueante(long duracion_ms) {
  // Calcula el número total de ciclos necesarios para la duración
  long ciclos = (duracion_ms * 1000) / (MEDIO_PERIODO_US * 2);

  for (long i = 0; i < ciclos; i++) {
    digitalWrite(PIN_ALTAVOZ, HIGH);
    delayMicroseconds(MEDIO_PERIODO_US);
    digitalWrite(PIN_ALTAVOZ, LOW);
    delayMicroseconds(MEDIO_PERIODO_US);
  }
}

// Función para actualizar el display TM1637
void actualizarDisplay(int segundos) {
  if (segundos > 0) {
    display.showNumberDec(segundos, false); // Muestra el número, sin ceros a la izquierda
  } else {
    display.clear(); // Apaga el display cuando llega a 0
  }
}

// =======================================================
// === 3. SETUP ===
// =======================================================

void setup() {
  Serial.begin(115200);
  
  // Configurar pines de Salida para el semáforo y altavoz
  pinMode(PIN_ROJO, OUTPUT);
  pinMode(PIN_AMARILLO, OUTPUT);
  pinMode(PIN_VERDE, OUTPUT);
  pinMode(PIN_ALTAVOZ, OUTPUT); 

  // Inicializar display TM1637
  display.setBrightness(0x02); // Brillo medio-bajo
  display.clear(); 

  // Inicializar semáforo en ROJO
  configurarSemaforo(HIGH, LOW, LOW); 
  tiempoCambio = millis();
  segundosRestantes = DURACION_ROJO_MS / 1000; // 5 segundos
  actualizarDisplay(segundosRestantes); 
  
  Serial.println("Sistema Inicializado.");
}

// =======================================================
// === 4. LOOP PRINCIPAL ===
// =======================================================

void loop() {
  unsigned long tiempoActual = millis();

  // --- Lógica de Cuenta Regresiva No Bloqueante ---
  // Se ejecuta y actualiza el display cada 1000 ms (1 segundo)
  if (tiempoActual - ultimoSegundo >= 1000) {
    if (segundosRestantes > 0) {
      segundosRestantes--;
      actualizarDisplay(segundosRestantes);
      Serial.print("Tiempo restante: ");
      Serial.println(segundosRestantes);
    }
    ultimoSegundo = tiempoActual;
  }
  
  // --- Lógica principal de la secuencia del semáforo ---
  switch (estadoActual) {
    case ROJO:
      if (tiempoActual - tiempoCambio >= DURACION_ROJO_MS) {
        // ROJO -> VERDE
        estadoActual = VERDE;
        configurarSemaforo(LOW, LOW, HIGH);
        tiempoCambio = tiempoActual;
        segundosRestantes = DURACION_VERDE_MS / 1000; // 7 segundos
        actualizarDisplay(segundosRestantes); 
        Serial.println("Cambio a VERDE.");
      }
      break;
      
    case VERDE:
      if (tiempoActual - tiempoCambio >= DURACION_VERDE_MS) {
        // VERDE -> AMARILLO (Transición)
        estadoActual = AMARILLO;
        
        // Antes de que el código se bloquee, reiniciamos el tiempo.
        tiempoCambio = millis(); 
        segundosRestantes = DURACION_AMARILLO_MS / 1000; // 2 segundos
        actualizarDisplay(segundosRestantes); // Muestra '2'
        
        configurarSemaforo(LOW, HIGH, LOW); // Enciende la luz AMARILLA
        Serial.println("Cambio a AMARILLO. Tono BLOQUEANTE ON.");
        
        // ¡El código se detiene aquí por 2000 milisegundos!
        tonoBloqueante(DURACION_AMARILLO_MS); 
        
        // AMARILLO -> ROJO
        estadoActual = ROJO;
        configurarSemaforo(HIGH, LOW, LOW);
        segundosRestantes = DURACION_ROJO_MS / 1000; 
        actualizarDisplay(segundosRestantes);
        Serial.println("Cambio a ROJO.");
      }
      break;
      
    case AMARILLO:
      // El código no se queda aquí, la transición ocurre dentro del CASE VERDE
      break;
  }
}