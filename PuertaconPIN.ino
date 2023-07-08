//Llamado de Librerias
#include<Servo.h>
#include<Keypad.h>

//Declaracion de Variables
const int buzzer = 12;
const int gLED = 11, rLED = 10;
const int  Filas = 4;
const int  Columnas = 3;
//Creacion del Servo
Servo SG90;

String Password = "290604";
String unlock   = "#00000";
String lock     = "*0000*";

//Asignacion de teclas a la matriz 4x3 del Keypad
char keys [Filas][Columnas] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte pinsFilas[Filas] = {8,7,6,5};
byte pinsColumn[Columnas] = {4,3,2};

Keypad keypad = Keypad(makeKeymap(keys), pinsFilas, pinsColumn, Filas, Columnas);


void beep(){
tone(buzzer, 200);
delay(55);
noTone(buzzer);
}

void setup() {
  // put your setup code here, to run once:

  pinMode(gLED, OUTPUT);
  pinMode(rLED, OUTPUT);


  //Locked Initialized DOOR

  digitalWrite(rLED, HIGH);
  


  //Servo 
  SG90.attach(13);

  //Buzzer Start
  tone(buzzer, 1300);
  delay(300);
  noTone(buzzer);

  //Serial Monitor
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  static String input = ""; // Variable para almacenar los dígitos introducidos

  char key = keypad.getKey();
  digitalWrite(rLED, HIGH);

  if (key) {
    tone(buzzer, 200);
    delay(100);
    noTone(buzzer);
    Serial.print(key);
    input += key; // Agregar el dígito introducido a la variable input

    if(input.length() == 6 && input == Password){
      Serial.println("    >> CONTRASEÑA CORRECTA");
      tone(buzzer, 500);
      delay(100);
      noTone(buzzer);
      digitalWrite(rLED, LOW);

      //Apertura y cierre del porton
      digitalWrite(gLED, HIGH);
      for(int i = 0; i<=90; i++){
        SG90.write(i);
        delay(70);
        beep();
        
      }
      digitalWrite(gLED, LOW);

      input="";

    }else if(input.length()==6 && input == unlock){
      Serial.println("    >> SEGURIDAD DESACTIVADA! ");
      digitalWrite(gLED, HIGH);
      digitalWrite(rLED, HIGH);
      SG90.write(20);

      input="";
    }else if(input.length()==6 && input == lock){
      Serial.println("    >> SEGURIDAD ACTIVA! ");
      digitalWrite(gLED, LOW);
      digitalWrite(rLED, HIGH);
      SG90.write(90);


      input="";      
    }
  }
}
