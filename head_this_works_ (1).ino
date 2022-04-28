/*
 * This is the code for the Head arduino
 */
#include <Servo.h>
int pos = 0;            //Declare and initialize the position variable
int servoPin = 5;       

#define echoPinL 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPinL 3 //attach pin D3 Arduino to pin Trig of HC-SR04

//DC motor
const int speedPin = 11; //L293D pin 1
const int dirPin1 = 12;  //L293D pin 2
const int dirPin2 = 10;  //L293D pin 7
//buzzer
const int buzzer = 9; //buzzer to arduino pin 9
//LED
const int ledPin = 7; //LED to arduino pin 7
//Servo
Servo testServo; //Create a servo object called testServo

// defines variables
long durationL; // variable for the duration of sound wave travel
int distanceL; // variable for the distance measurement

// Time
long startTime = 0;
// Reset time
long resetTime = 20000;
// Wake status
int wakeVal;
// Variable for difference in current time and last time a sensor was triggered. This acts as a timer.
long timeDifference = 0;

void setup() {
  //ultrasonic sensor setup
  pinMode(trigPinL, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPinL, INPUT); // Sets the echoPin as an INPUT
  //buzzer setup
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  //LED setup
  pinMode(ledPin, OUTPUT);
  //DC motor setup
  pinMode(speedPin, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  
  Serial.begin(9600); // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");

    Serial.begin(9600);
  testServo.attach(servoPin);  //tell servo object which pin controls it
  Serial.println();
}

void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPinL, LOW);
  delayMicroseconds(20);
  
  // Sets the trigPin HIGH (ACTIVE) for 100 microseconds
  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPinL, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationL = pulseIn(echoPinL, HIGH);
  
  // Calculating the distance
  distanceL = durationL * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  analogWrite(speedPin, 0);
  analogWrite(ledPin, 0); //turns LED off

    Serial.println(distanceL);
    if (distanceL < 15) {
      for (int i = 0; i < 3; i++) {
        analogWrite(ledPin, 255); //turns LED on
        tone(buzzer, 1000); // Send 1KHz sound signal...
        delay(1000);        // ...for 1 sec
        analogWrite(ledPin, 0); //turns LED off
        noTone(buzzer);     // Stop sound...
        delay(1000);        // ...for 1 sec
        Serial.println("1 buzzer");
      }
      digitalWrite( dirPin1, HIGH );
      digitalWrite( dirPin2, LOW);
      Serial.println("motor 1");
      analogWrite(speedPin, 200);
      delay(5000);
      for(int i = 0; i < 90; i++){
        testServo.write(i);
        delay(5);
      }
      for(int i = 90; i > 0; i--){
        testServo.write(i);
        delay(10);
      }
      Serial.println("servo 1");
      for (int i = 0; i < 3; i++) {
        analogWrite(ledPin, 255); //turns LED on
        tone(buzzer, 1000); // Send 1KHz sound signal...
        delay(1000);        // ...for 1 sec
        analogWrite(ledPin, 0); //turns LED off
        noTone(buzzer);     // Stop sound...
        delay(1000);        // ...for 1 sec
        Serial.println("1 buzzer");
      }
    }
    else if (distanceL < 38) {
      for (int i = 0; i < 3; i++) {
        analogWrite(ledPin, 255); //turns LED on
        tone(buzzer, 1000); // Send 1KHz sound signal...
        delay(1000);        // ...for 1 sec
        analogWrite(ledPin, 0); //turns LED off
        noTone(buzzer);     // Stop sound...
        delay(1000);        // ...for 1 sec
        Serial.println("2 buzzer");
      }
      digitalWrite( dirPin1, HIGH );
      digitalWrite( dirPin2, LOW);
      analogWrite(speedPin, 0);
      Serial.println("motor 2");
      for(int i = 0; i < 90; i++){
        testServo.write(i);
        delay(5);
      }
      for(int i = 90; i > 0; i--){
        testServo.write(i);
        delay(10);
      }
      Serial.println("servo 2");
      for (int i = 0; i < 3; i++) {
        analogWrite(ledPin, 255); //turns LED on
        tone(buzzer, 1000); // Send 1KHz sound signal...
        delay(1000);        // ...for 1 sec
        analogWrite(ledPin, 0); //turns LED off
        noTone(buzzer);     // Stop sound...
        delay(1000);        // ...for 1 sec
        Serial.println("2 buzzer");
      }
    }
    else if (distanceL < 50) {
      for (int i = 0; i < 3; i++) {
        analogWrite(ledPin, 255); //turns LED on
        tone(buzzer, 1000); // Send 1KHz sound signal...
        delay(1000);        // ...for 1 sec
        analogWrite(ledPin, 0); //turns LED off
        noTone(buzzer);     // Stop sound...
        delay(1000);        // ...for 1 sec
        Serial.println("3 buzzer");
      }
      analogWrite(speedPin, 200);
      digitalWrite( dirPin1, LOW );
      digitalWrite( dirPin2, HIGH);
      delay(5000);
      Serial.println("motor 3");
      for(int i = 0; i < 90; i++){
        testServo.write(i);
        delay(5);
      }
      for(int i = 90; i > 0; i--){
        testServo.write(i);
        delay(10);
      }
      Serial.println("servo 3");
    }
  else {
    digitalWrite(dirPin1, HIGH );
    digitalWrite(dirPin2, LOW);
    analogWrite(speedPin, 0);
    testServo.write(0); 
    analogWrite(ledPin, 0); //turns LED off
  } 
}
