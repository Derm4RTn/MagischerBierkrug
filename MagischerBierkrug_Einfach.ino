/*
Das ganze soll den neuen Bierschoff-Stab steuern.

Über 2 Schalter soll sich der Bierkrug der auf den Stab geschraubt ist öffnen und schließen lassen.

Als Schalter fungieren zwei Reed schalter (Magnetschalter) die jeh nach Reinfolge der Aktivierung Befehl 1 oder Befehl 2 ausführen.

Der Bierkrug wird per Servo geöffnet und soll sich nach 30 Sekunden wieder schließen.

Wenn der Bierkrug geöffnet ist soll eine LED leuchten und sich nach 30 Sekunden wieder ausschalten.

Aktivierungen des Schalters sollen nach 5 Sekunden (oder so) wieder zurückgesetzt werden um mit nicht eindeutigen Befehlen umzugehen.

*/

// Definiere Pins für Schalter, LED und Servo
const int schalterPin1 = 2;
const int schalterPin2 = 3;
const int ledPin = 4;
const int servoPin = 5;

// Erstelle ein Servo- und LED-Objekt
Servo servo;
int servoPosition = 0;
bool servoInBewegung = false;
bool ledAn = false;
unsigned long letzteAktivitaet = 0;

void setup() {
  // Initialisiere die Pins
  pinMode(schalterPin1, INPUT_PULLUP);
  pinMode(schalterPin2, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  servo.attach(servoPin);
}

void loop() {
  // Überprüfe, ob der erste Schalter aktiviert wurde
  if (digitalRead(schalterPin1) == LOW) {
    // Warte auf die Aktivierung des zweiten Schalters innerhalb von 5 Sekunden
    unsigned long startZeit = millis();
    while (millis() - startZeit < 5000) {
      if (digitalRead(schalterPin2) == LOW) {
        // Befehl A ausführen
        servoInBewegung = true;
        servo.write(90);
        servoPosition = 90;
        letzteAktivitaet = millis();
        break;
      }
    }
  }

  // Überprüfe, ob der zweite Schalter aktiviert wurde
  if (digitalRead(schalterPin2) == LOW) {
    // Warte auf die Aktivierung des ersten Schalters innerhalb von 5 Sekunden
    unsigned long startZeit = millis();
    while (millis() - startZeit < 5000) {
      if (digitalRead(schalterPin1) == LOW) {
        // Befehl B ausführen
        digitalWrite(ledPin, HIGH);
        ledAn = true;
        letzteAktivitaet = millis();
        break;
      }
    }
  }

  // Überprüfe, ob das Licht ausgeschaltet werden muss
  if (ledAn && millis() - letzteAktivitaet > 30000) {
    digitalWrite(ledPin, LOW);
    ledAn = false;
  }

  // Überprüfe, ob der Servo in die Standardposition zurückkehren muss
  if (servoInBewegung && millis() - letzteAktivitaet > 30000) {
    servo.write(0);
    servoPosition = 0;
    servoInBewegung = false;
  }
}
