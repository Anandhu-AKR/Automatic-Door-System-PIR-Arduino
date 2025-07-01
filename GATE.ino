#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int trigPin = 0;
const int echoPin = 1;

Servo myservo;

long duration;
int distanceCm;
bool doorOpen = false; // Track the state of the door

void setup() {
  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(9);
  myservo.write(0); // Initialize door to closed position (0 degrees)
}

void loop() {
  // Measure distance using the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2;

  // Display the distance on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distanceCm);
  lcd.print(" cm      ");
  delay(50);

  // Control the door based on the distance
  if (distanceCm < 50 && !doorOpen) {
    // Open the door (rotate servo to 180 degrees)
    lcd.setCursor(0,1);
    lcd.print("Gate is opening!");
    for (int pos = 0; pos <= 180; pos += 1) {
      myservo.write(pos);
      delay(15);
    }

    doorOpen = true; // Update door state to open
  } else if (distanceCm >= 50 && doorOpen) {
    // Close the door (rotate servo to 0 degrees)
    lcd.setCursor(0,1);
    lcd.print("Gate is closing!");
    for (int pos = 180; pos >= 0; pos -= 1) {
      myservo.write(pos);
      delay(15);
    }
    doorOpen = false; // Update door state to closed
  }

  delay(50);
}