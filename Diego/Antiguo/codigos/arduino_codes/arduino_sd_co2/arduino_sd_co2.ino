#include <Wire.h>             // Librería necesaria para la comunicación I2C
#include <Adafruit_CCS811.h> 
#include <SPI.h> // Librería necesaria para la comunicación SPI (entre Arduino y SD)
#include <SD.h>  // Librería para manejar la tarjeta SD

 // Librería específica para el sensor CCS811

// -------------------------------------------------------------------
// 1. CREACIÓN DEL OBJETO SENSOR
// -------------------------------------------------------------------
// Creamos una instancia del sensor, con el nombre 'ccs'.
Adafruit_CCS811 ccs;
unsigned long hora = 0;
unsigned long min = 0;
unsigned long seg = 0;
String mensaje = "";
const int chipSelect = 10;
// -------------------------------------------------------------------
// 2. FUNCIÓN SETUP (Se ejecuta una sola vez al inicio)
// -------------------------------------------------------------------
void setup() {
  if (!SD.begin(chipSelect)) {
    Serial.println(" ERROR. Fallo en la inicializacion.");
    Serial.println("Verifique el cableado y que la tarjeta este en formato FAT16 o FAT32.");
    while (true); // Detiene el programa aqui
  }
  Serial.println(" Exitoso.");

  // Inicializa la comunicación serial para mostrar los datos en el Monitor Serie
  Serial.begin(9600);
  Serial.println("--- Inicio de prueba del sensor CJMCU-811 (CCS811) ---");
  Serial.println("Asegurese de que el Monitor Serie este a 9600 baudios.");
  
  // 1. Intenta iniciar el sensor
  if (!ccs.begin()) {
    // Si falla, el programa se detiene aqui.
    // Esto significa que hay un problema de cableado o el sensor no responde.
    Serial.println("!!! FALLO al iniciar el sensor CCS811. Verifique el cableado I2C y alimentacion (VCC a 3.3V) !!!");
    while (1); 
  }

  // 2. Espera a que el sensor esté listo para medir (puede tardar unos segundos)
  Serial.print("Esperando que el sensor este listo...");
  while (!ccs.available()) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println(" Listo!");

  // 3. Opcional: Configura la tasa de medicion (el sensor ya viene configurado
  // para medir cada segundo, pero lo podemos confirmar)
  ccs.setDriveMode(CCS811_DRIVE_MODE_1SEC);
  
  Serial.println("Sensor CCS811 iniciado correctamente. Comenzando lecturas...");
  File sd = SD.open("MENSAJE.TXT", FILE_WRITE);
  sd.print("Nueva lectura \n");
  sd.print("HORA : MINUTOS : SEGUNDOS | Co2(ppm) | TVOC (Compuestos Orgánicos Volátiles Totales)\n");
  sd.close();
}
// -------------------------------------------------------------------
// 3. FUNCIÓN LOOP (Se ejecuta repetidamente)
// -------------------------------------------------------------------
void loop() {
  // 1. Comprueba si hay nuevos datos de medición disponibles en el sensor
  if (ccs.available()) {
    
    // 2. Intenta leer los datos y comprueba si la lectura fue exitosa
    if (!ccs.readData()) {
      File sd = SD.open("MENSAJE.TXT", FILE_WRITE);
      
      mensaje = String(hora) + ":"+ String(min) + ":" + String(seg);

      sd.print(mensaje);
      seg++;
      if(seg == 60){
        min++;
        seg=0;
      }
      if(min == 60){
        hora++;
        min=0;
      }
      if(hora == 24){
        hora=0;
      }

      
      // La lectura fue exitosa: Imprime los valores
      sd.print(" | CO2: ");
      // ccs.geteCO2() devuelve el CO2 equivalente en Partes Por Millón (ppm)
      sd.print(ccs.geteCO2());
      sd.print(" | ppm, \t");
      
      sd.print("TVOC: ");
      // ccs.getTVOC() devuelve los Compuestos Organicos Volatiles en Partes Por Billon (ppb)
      sd.print(ccs.getTVOC());
      sd.println(" ppb");
      sd.close();
    } else {
      // La lectura no fue exitosa (hubo un error de I2C o el sensor no esta en modo de medicion)
      Serial.println("!!! Error al leer los datos del sensor !!!");
    }
  }

  // El sensor CCS811 en modo por defecto mide cada ~1 segundo (1000ms), 
  // asi que un pequeño retraso ayuda a no saturar el puerto serial.
  delay(1000); 
}