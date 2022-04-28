/*
 * This is the final code for the working neck raising mechanism. In this code, the photoresistor is utilized that when it receives less light than the threshold, the motor will turn on and lift up the neck.
 * After a certain amount of time, it will lower. This timer will be reset by if the ultrasonic sensors read anything within the threshold to turn the head.
 */

// As usual, we'll create constants to name the pins we're using.
// This will make it easier to follow the code below.

//photoresistor
const int sensorPin = 0;
//dc motor
const int speedPin = 11; //L293D pin 1
const int dirPin1 = 12;  //L293D pin 2
const int dirPin2 = 10;  //L293D pin 7
//Ultrasonic sensor
#define echoPinL 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPinL 3 //attach pin D3 Arduino to pin Trig of HC-SR04
// defines variables
long durationL; // variable for the duration of sound wave travel
long distanceL; // variable for the distance measurement
// We'll also set up some global variables for the light level:
int lightLevel, high = 0, low = 1023;

// Time
long startTime = 0;
// Reset time
long resetTime = 7000;
// Wake status
long wakeVal;

long timeDifference;
void setup()
{
  // We'll set up the LED pin to be an output.
  // (We don't need to do anything special to use the analog input.)
  //ultrasonic sensor setup
  pinMode(trigPinL, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPinL, INPUT); // Sets the echoPin as an INPUT
  
  //DC motor setup
  Serial.begin(9600);
  pinMode(speedPin, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(dirPin2, OUTPUT);
}

void loop() {
  // Ultrasonic sensor
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


  lightLevel = analogRead(sensorPin);
  analogWrite(speedPin, 0);
  
 
  manualTune();  // manually change the range from light to dark


  int timeDifference = abs(millis() - startTime);
  // Wake value
//  if (timeDifference < resetTime) {
//    wakeVal = 1;
//  } 
//  else {
//    wakeVal = 0;
//  }
  // If it's awake
  if (timeDifference < resetTime) {
    Serial.print("AWAKE ");
    // if statement for light levels
    if (lightLevel > 100) {
      //startTime = startTime;
      Serial.print("State: ");
      Serial.print(wakeVal);
      Serial.print(" Millis: ");
      Serial.print(millis());
      Serial.print(" Time: ");
      Serial.print(startTime);
      Serial.print(" Difference ");
      Serial.println(timeDifference);
    } else {
      //startTime = startTime;
      Serial.print("State: ");
      Serial.print(wakeVal);
      Serial.print(" Millis: ");
      Serial.print(millis());
      Serial.print(" Time: ");
      Serial.print(startTime);
      Serial.print(" Difference ");
      Serial.println(timeDifference);
    }
    //if statement for distances
    if (distanceL < 30) {
      startTime = millis();
      // trigger alarm and turn head is head code, not neck code
      /*Serial.print("State: ");
      Serial.print(wakeVal);
      Serial.print(" Millis: ");
      Serial.print(millis());
      Serial.print(" Time: ");
      Serial.println(startTime);*/
    } else {
      //startTime = startTime;
      /*Serial.print("State: ");
      Serial.print(wakeVal);
      Serial.print(" Millis: ");
      Serial.print(millis());
      Serial.print(" Time: ");
      Serial.println(startTime);*/
    }
  } 
  //Moment where it falls alseep
  else if (timeDifference >= startTime - 100 && timeDifference <= startTime + 100) {
    //turn motor on to lower head
    digitalWrite( dirPin1, LOW);
    digitalWrite( dirPin2, HIGH);
    analogWrite(speedPin, 75);
    delay(400);
  }
  
  // If it's alseep
  else {
    Serial.print("SLEEPING ");
    // if statement light level
    if (lightLevel > 100) {
      //startTime = startTime;
      Serial.print("State: ");
      Serial.print(wakeVal);
      Serial.print(" Millis: ");
      Serial.print(millis());
      Serial.print(" Time: ");
      Serial.print(startTime);
      Serial.print(" Difference ");
      Serial.println(timeDifference); 
    } else {
      //turn motor on to raise head
      digitalWrite( dirPin1, HIGH );
      digitalWrite( dirPin2, LOW);
      analogWrite(speedPin, 175);
      delay(1000);
      startTime = millis();
      Serial.print("State: ");
      Serial.print(wakeVal);
      Serial.print(" Millis: ");
      Serial.print(millis());
      Serial.print(" Time: ");
      Serial.print(startTime);
      Serial.print(" Difference ");
      Serial.println(timeDifference);
    }
    // if statement for distances
    if (distanceL < 30) {
      /*Serial.print("State: ");
      Serial.print(wakeVal);
      Serial.print(" Millis: ");
      Serial.print(millis());
      Serial.print(" Time: ");
      Serial.println(startTime);*/
    } else {
      //startTime = startTime;
      /*Serial.print("State: ");
      Serial.print(wakeVal);
      Serial.print(" Millis: ");
      Serial.print(millis());
      Serial.print(" Time: ");
      Serial.println(startTime);*/
    }
      
  }

  /*
  //------------------------------------------------------------------------
  // Photoresistor
  if (lightLevel > 130) {
    analogWrite(speedPin, 0);
    digitalWrite( dirPin1, HIGH );
    digitalWrite( dirPin2, LOW);
    startTime = startTime;
    Serial.print("Light: ");
    Serial.print(lightLevel);
    Serial.print(" Distance: ");
    Serial.print(distanceL);
    Serial.print(" Time: ");
    Serial.print(startTime);
    if (wakeVal = 1) {
      Serial.println(" Awake");
    } else {
      Serial.println(" Sleeping");
    }
  } else {
      if (wakeVal = 1) {
        startTime = startTime;
        Serial.print("Light: ");
        Serial.println(lightLevel);
      }
      else {
        startTime = millis();
        analogWrite(speedPin, 200);
        digitalWrite( dirPin1, HIGH );
        digitalWrite( dirPin2, LOW);
        Serial.print("Light: ");
        Serial.println(lightLevel);
      }
  }
  
  // Ultrasonic sensor
  if (wakeVal = 1) {
    if (distanceL < 30) {
      startTime = millis();
      // insert code for head turning *for the head code, not neck code
    } else {
      startTime = startTime;
    }
  } else {
    Serial.println("Sleep");
  }

  // The above statement will brighten the LED along with the
  // light level. To do the opposite, replace "lightLevel" in the
  // above analogWrite() statement with "255-lightLevel".
  // Now you've created a night-light!
}

*/
}
void manualTune()
{
 

  lightLevel = map(lightLevel, 0, 1023, 0, 255);
  lightLevel = constrain(lightLevel, 0, 255);

} 


void autoTune()
{


  if (lightLevel < low)
  {
    low = lightLevel;
  }



  if (lightLevel > high)
  {
    high = lightLevel;
  }


  lightLevel = map(lightLevel, low+30, high-30, 0, 255);
  lightLevel = constrain(lightLevel, 0, 255);


}
