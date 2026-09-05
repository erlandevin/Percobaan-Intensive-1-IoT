#include <ESP32Servo.h>

// =====================
// SERVO
// =====================
Servo servoRain;
Servo servoUltra;

// =====================
// PIN
// =====================
const int servoRainPin = 26;
const int servoUltraPin = 25;

const int rainSensorPin = 33;

const int trigPin = 14;
const int echoPin = 27;

const int ledPin = 2;

// =====================
// SETPOINT
// =====================
int rainThreshold = 3500;
int setpointUltra = 10;

// =====================
// BACA ULTRASONIC
// =====================
long readUltrasonicDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  // Tambahkan timeout 30000 microsecond
  long duration = pulseIn(echoPin, HIGH, 30000);

  // Jika tidak ada pantulan
  if (duration == 0) {
    return 999;
  }

  long distance = duration * 0.034 / 2;

  return distance;
}

void setup() {

  Serial.begin(9600);

  // Setup Servo
  servoRain.attach(servoRainPin);
  servoUltra.attach(servoUltraPin);

  // Setup pin
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(ledPin, OUTPUT);

  // Posisi awal
  servoRain.write(90);
  servoUltra.write(0);

  delay(1000);
}

void loop() {

  // =====================
  // SENSOR HUJAN
  // =====================
  int rainValue = analogRead(rainSensorPin);

  Serial.print("Rain Value : ");
  Serial.println(rainValue);

  // Servo hujan langsung respon
  if (rainValue < rainThreshold) {

    servoRain.write(0);

    Serial.println("HUJAN -> Servo Tertutup");
  }
  else {

    servoRain.write(90);

    Serial.println("TIDAK HUJAN -> Servo Terbuka");
  }

  // =====================
  // ULTRASONIC
  // =====================
  long distance = readUltrasonicDistance();

  Serial.print("Distance : ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < setpointUltra) {

    servoUltra.write(90);

    digitalWrite(ledPin, HIGH);
    Serial.println("Objek dekat");
  }
  else {

    servoUltra.write(0);


    digitalWrite(ledPin, LOW);

    Serial.println("Objek jauh");
  }

  Serial.println("====================");

  delay(2000);
}