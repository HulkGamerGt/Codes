#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Inicializamos el LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop() {
  String texto1 = "LIMPIEZA OK?! ";
  String texto2 = "FILA 2: SE SUPONE QUE FUNCIONA? ";
  
  // Mostrar texto desplazándose
  for (int posicion = 0; posicion < texto1.length() + 16; posicion++) {
    lcd.clear();
    
    // Primera línea - texto desplazante
    lcd.setCursor(0, 0);
    for (int i = 0; i < 16; i++) {
      int indice = (posicion + i) % (texto1.length() + 5); // +5 para espacio extra
      if (indice < texto1.length()) {
        lcd.print(texto1[indice]);
      } else {
        lcd.print(" ");
      }
    }
    
    // Segunda línea - texto desplazante
    lcd.setCursor(0, 1);
    for (int i = 0; i < 16; i++) {
      int indice = (posicion + i) % (texto2.length() + 5); // +5 para espacio extra
      if (indice < texto2.length()) {
        lcd.print(texto2[indice]);
      } else {
        lcd.print(" ");
      }
    }
    
    delay(400); // Ajusta este valor para cambiar la velocidad (mayor = más lento)
  }
}