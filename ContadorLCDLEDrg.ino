#include<LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 4, 5, 6, 7);

const int green_led = 10, red_led = 8, push = 3;

int push_status = 0;
int count = 0; // variable para contar pulsaciones

void setup() {
  pinMode(green_led, OUTPUT);
  pinMode(red_led, OUTPUT);
  pinMode(push, INPUT);
  lcd.begin(16,2);
  lcd.print("Cantidad => ");
}



void loop() {
  
  lcd.setCursor(12,0); // mover cursor a la posición 7,0
  //lcd.print(count); // mostrar el contador

  push_status = digitalRead(push);
  if(push_status == HIGH){
    digitalWrite(green_led, HIGH);
    count = count + 1; // incrementar el contador
    delay(200); // delay para evitar múltiples conteos por una sola pulsación
    digitalWrite(green_led, LOW);
  }
  
  lcd.print(count);

  if(count == 20){
    digitalWrite(green_led, LOW);
    maxblink();
  }
 
}

void maxblink(){
    lcd.clear();
    delay(400);
    lcd.print("Cantidad Maxima!");
    delay(400);

    while(digitalRead(push) == LOW){
    digitalWrite(red_led, HIGH);
    delay(400);
    digitalWrite(red_led, LOW);
    delay(400);
}


    // Esperar a que el botón sea presionado nuevamente
    while(digitalRead(push) == LOW){
      // Esperar
    }
    
    // Restablecer el contador y mostrar el mensaje del setup()
    count = 0;
    lcd.clear();
    lcd.print("Cantidad => ");
}

