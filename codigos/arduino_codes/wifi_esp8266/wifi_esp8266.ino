#include <Servo.h>

Servo miServo;          // Objeto para controlar el servo
int sensorPin = A0;     // Pin de señal del sensor de agua
int sensorValue = 0;    // Variable para la lectura
int umbral = 150;       // Si el valor es mayor a esto, hay agua

void setup() {
  miServo.attach(9);    // Pin de señal del servo
  
  // POSICIÓN INICIAL AL ENCENDER
  miServo.write(45);    
  delay(1000);          
  
  Serial.begin(9600);   
  Serial.println("Sistema iniciado. Esperando agua para activar...");
}

void loop() {
  sensorValue = analogRead(sensorPin); // Leer nivel de agua en tiempo real
  
  Serial.print("Nivel: ");
  Serial.println(sensorValue);

  if (sensorValue >= umbral) {
    // MIENTRAS detecte agua, se queda en 150 grados
    miServo.write(150); 
    Serial.println("Estado: AGUA DETECTADA - Posición: 130°");
  } 
  else {
    // Cuando el valor baja del umbral (YA NO hay agua), vuelve a 45 grados
    miServo.write(45);
    Serial.println("Estado: SECO - Posición: 45°");
  }
  
  delay(100); // Pequeña pausa para que las lecturas sean estables
}