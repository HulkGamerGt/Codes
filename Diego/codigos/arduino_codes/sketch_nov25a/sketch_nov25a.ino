// =======================================================
// === 1. DEFINICIÓN DE PINES ===
// =======================================================

// Pines del Sensor Ultrasónico HC-SR04
const int PIN_TRIG = 13; // Pin de Emisión (Salida)
const int PIN_ECHO = 12; // Pin de Recepción (Entrada)

// =======================================================
// === 2. CONSTANTES Y VARIABLES ===
// =======================================================

// Velocidad del sonido en el aire (cm/µs) a 20°C
const float VELOCIDAD_SONIDO_CMS_US = 0.0343;

long duracion_us;   // Duración del pulso de sonido ida y vuelta (en microsegundos)
float distancia_cm; // Distancia calculada (en centímetros)

// =======================================================
// === 3. FUNCIÓN DE MEDICIÓN ===
// =======================================================

// Función para medir la distancia
float medirDistanciaCM() {
  // 1. Limpiar el Pin TRIG (asegura que esté en LOW antes de enviar el pulso)
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);

  // 2. Enviar pulso HIGH de 10µs por el Pin TRIG (Inicia la medición)
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  // 3. Medir la duración del Pin ECHO (Tiempo que tarda el sonido en ir y volver)
  // La función pulseIn() es bloqueante: espera hasta recibir el eco.
  duracion_us = pulseIn(PIN_ECHO, HIGH, 30000); // El tercer parámetro es un timeout (30ms)

  // 4. Calcular la distancia en cm
  // Distancia = (Duración * Velocidad del Sonido) / 2 (porque mide ida y vuelta)
  distancia_cm = (duracion_us * VELOCIDAD_SONIDO_CMS_US) / 2.0;

  // Manejar casos de error o fuera de rango (si duracion_us es 0 o muy alta)
  if (duracion_us == 0) {
      return -1.0; // Retorna -1.0 para indicar que no hubo eco (fuera de rango)
  }
  
  return distancia_cm;
}

// =======================================================
// === 4. SETUP ===
// =======================================================

void setup() {
  Serial.begin(115200);
  
  // Configurar Pines del Sensor Ultrasónico
  pinMode(PIN_TRIG, OUTPUT); // TRIG como Salida
  pinMode(PIN_ECHO, INPUT);  // ECHO como Entrada
  
  Serial.println("Solo Sensor Ultrasónico HC-SR04 Iniciado.");
  Serial.println("------------------------------------");
}

// =======================================================
// === 5. LOOP PRINCIPAL ===
// =======================================================

void loop() {
  // Medir la distancia
  float distancia = medirDistanciaCM();

  // Imprimir el resultado en el Monitor Serial
  Serial.print("Distancia: ");
  
  if (distancia == -1.0) {
      Serial.println("Fuera de Rango ( > 400 cm )");
  } else {
      Serial.print(distancia);
      Serial.println(" cm");
  }

  // Esperar un momento antes de la siguiente medición para estabilizar
  delay(500); // 500 ms de espera entre mediciones
}