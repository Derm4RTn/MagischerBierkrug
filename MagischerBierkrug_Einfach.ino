/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(2);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  for (pos = 20; pos <= 130; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(0);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 130; pos >= 20; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(100);                       // waits 15 ms for the servo to reach the position
  }
}
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
