#include <SoftwareSerial.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Bluetooth HC-05
SoftwareSerial BT(2, 3); // RX, TX

// LCD 20x4
LiquidCrystal_I2C lcd(0x27, 20, 4);

// LEDs
const int cuarto1 = 11;
const int cuarto2 = 10;
const int cuarto3 = 9;
const int cuarto4 = 6;
const int cuarto5 = 5;

// Ventilador (Motor DC)
const int ventilador = 4;

// Servo puerta
Servo servoPuerta;
bool puertaAbierta = false;

// Variables modo fiesta
int modo = 0;
unsigned long tiempoAnterior = 0;
bool estadoFiesta = false;

void setup() {

  Serial.begin(9600);
  BT.begin(9600);

  pinMode(cuarto1, OUTPUT);
  pinMode(cuarto2, OUTPUT);
  pinMode(cuarto3, OUTPUT);
  pinMode(cuarto4, OUTPUT);
  pinMode(cuarto5, OUTPUT);

  pinMode(ventilador, OUTPUT);

  servoPuerta.attach(7);
  servoPuerta.write(0);

  lcd.init();
  lcd.backlight();

  apagarTodo();

  Serial.println("SMART HOME INICIADO");
}

void loop() {

  if (BT.available()) {

    char comando = BT.read();

    Serial.print("Comando recibido: ");
    Serial.println(comando);

    switch (comando) {

      case 'F':
        modoFiesta();
        break;

      case 'R':
        modoRelajado();
        break;

      case 'N':
        modoNoche();
        break;

      case 'E':
        encenderTodo();
        break;

      case 'A':
        apagarTodo();
        break;

      case 'P':
        togglePuerta();
        break;
    }
  }

  if (modo == 1) {
    fiestaAnimacion();
  }
}

// =======================
// LCD
// =======================

void mostrarLCD(String l1, String l2, String l3, String l4) {

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(l1);

  lcd.setCursor(0, 1);
  lcd.print(l2);

  lcd.setCursor(0, 2);
  lcd.print(l3);

  lcd.setCursor(0, 3);
  lcd.print(l4);
}

// =======================
// PUERTA
// =======================

void togglePuerta() {

  if (puertaAbierta) {

    servoPuerta.write(0);
    puertaAbierta = false;

    Serial.println("Puerta Cerrada");

  } else {

    servoPuerta.write(90);
    puertaAbierta = true;

    Serial.println("Puerta Abierta");
  }
}

// =======================
// MODO FIESTA
// =======================

void modoFiesta() {

  modo = 1;

  digitalWrite(ventilador, HIGH);

  mostrarLCD(
    "Modo Mensaje LCD",
    "Modo: FIESTA",
    "Ventilador: ON",
    "LEDS: Alternandose"
  );

  Serial.println("Modo Fiesta");
}

void fiestaAnimacion() {

  if (millis() - tiempoAnterior >= 300) {

    tiempoAnterior = millis();

    estadoFiesta = !estadoFiesta;

    digitalWrite(cuarto1, estadoFiesta);
    digitalWrite(cuarto2, !estadoFiesta);
    digitalWrite(cuarto3, estadoFiesta);
    digitalWrite(cuarto4, !estadoFiesta);
    digitalWrite(cuarto5, estadoFiesta);
  }
}

// =======================
// MODO RELAJADO
// =======================

void modoRelajado() {

  modo = 2;

  digitalWrite(ventilador, LOW);

  digitalWrite(cuarto1, LOW);
  digitalWrite(cuarto2, LOW);
  digitalWrite(cuarto3, LOW);
  digitalWrite(cuarto4, LOW);
  digitalWrite(cuarto5, LOW);

  mostrarLCD(
    "Modo Mensaje LCD",
    "Modo: RELAJADO",
    "Ventilador: OFF",
    "LEDS: OFF"
  );

  Serial.println("Modo Relajado");
}

// =======================
// MODO NOCHE
// =======================

void modoNoche() {

  modo = 3;

  digitalWrite(ventilador, LOW);

  digitalWrite(cuarto1, LOW);
  digitalWrite(cuarto2, LOW);
  digitalWrite(cuarto3, LOW);
  digitalWrite(cuarto4, LOW);
  digitalWrite(cuarto5, LOW);

  mostrarLCD(
    "Modo Mensaje LCD",
    "Modo: NOCHE",
    "Ventilador: OFF",
    "LEDS: OFF"
  );

  Serial.println("Modo Noche");
}

// =======================
// ENCENDER TODO
// =======================

void encenderTodo() {

  modo = 4;

  digitalWrite(ventilador, HIGH);

  digitalWrite(cuarto1, HIGH);
  digitalWrite(cuarto2, HIGH);
  digitalWrite(cuarto3, HIGH);
  digitalWrite(cuarto4, HIGH);
  digitalWrite(cuarto5, HIGH);

  mostrarLCD(
    "Modo Mensaje LCD",
    "ENCENDER TODO",
    "LEDS: ON",
    "Ventilador: ON"
  );

  Serial.println("Todo Encendido");
}

// =======================
// APAGAR TODO
// =======================

void apagarTodo() {

  modo = 0;

  digitalWrite(ventilador, LOW);

  digitalWrite(cuarto1, LOW);
  digitalWrite(cuarto2, LOW);
  digitalWrite(cuarto3, LOW);
  digitalWrite(cuarto4, LOW);
  digitalWrite(cuarto5, LOW);

  mostrarLCD(
    "Modo Mensaje LCD",
    "APAGAR TODO",
    "LEDS: OFF",
    "Ventilador: OFF"
  );

  Serial.println("Todo Apagado");
}
