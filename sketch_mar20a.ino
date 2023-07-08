#include <LiquidCrystal.h>

const int rs = 11, en = 12, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String pin = "12X94R";

void setup() {
  lcd.begin(16,2);
  lcd.print("Ingrese el PIN: ");
  Serial.begin(9600);
}

void loop() {
  bool pin_correcto = false;
  
  while (!pin_correcto) {
    if (Serial.available()) {
      String input = Serial.readStringUntil('\n'); 
      input.trim(); 
      if (input == pin) {
        lcd.clear();
        lcd.print("Contraseña");
        lcd.setCursor(0, 1);
        lcd.print("Correcta");
        delay(1000);
        pin_correcto = true;
      } else {
        lcd.clear();
        lcd.print("Contraseña");
        lcd.setCursor(0, 1);
        lcd.print("Incorrecta");
        delay(1000);
      }
      lcd.clear();
      lcd.print("Ingrese el PIN: ");
    }
  }
}
