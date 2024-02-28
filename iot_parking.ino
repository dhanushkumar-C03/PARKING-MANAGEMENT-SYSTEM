//parkingmdu
//#include <ESP8266WiFi.h>
#include <Servo.h>
//#include <WiFi.h>
//#include <HttpClient.h>

int servopin = 9;  // create servo object to control a servo
Servo Servo1;

int servopin1 = 10;  // create servo object to control a servo
Servo Servo2;

int val = 0;       // variable to count the entries

// Define the number of IR sensors
const int numSensors = 5;

// Define the array of pin numbers connected to the IR sensors
const int irSensorPins[numSensors] = {2,3, 4, 5,6}; // Adjust these pins based on your wiring

// Entry sensor pin
//const int entrySensorPin = 2; // Adjust this pin based on your wiring
const int redLightPin = 7;    // Adjust this pin based on your wiring
const int greenLightPin = 8;
const int redLightPin1 = 9;    // Adjust this pin based on your wiring
const int greenLightPin1 = 10;  // Adjust this pin based on your wiring
// Parking status
//bool parkingFull = false;

void setup() {
  Serial.begin(9600);
  Servo1.attach(servopin);
  Servo2.attach(servopin1);

  // Set the IR sensor pins as input
  for (int i = 0; i < numSensors; i++) {
    pinMode(irSensorPins[i], INPUT);
  }

  // Set the entry sensor pin as input
 // pinMode(entrySensorPin, INPUT);
}



  

void loop() {
  // Read the state of each IR sensor and print the result
  for (int i = 0; i < numSensors; i++) {
    int irSensorState = digitalRead(irSensorPins[i]);

    // Check if an obstacle is detected
    if (irSensorState == LOW) {
      Serial.print("Sensor ");
      Serial.print(i + 1); // Print sensor number (1-based index)
      Serial.println(": Obstacle detected!");
      // parkingFull = true;  // Uncomment this line if you want parkingFull to be set when any sensor detects an obstacle
    } else {
      Serial.print("Sensor ");
      Serial.print(i + 1); // Print sensor number (1-based index)
      Serial.println(": No obstacle detected.");
    }
  }


  // Check entry sensor
  if (digitalRead(2) == LOW) {
    Serial.println("Entry sensor: Vehicle detected!");
    val = val + 1;
    Servo1.write(90); 

    digitalWrite(redLightPin1, LOW);
    digitalWrite(greenLightPin1, HIGH);
    delay(1000);
    
  }
  else{
    Serial.println("Entry sensor: Vehicle detected!");
  }
      
  if( digitalRead(6)== LOW){
    //int irSensorState1 = digitalRead(irSensorPins[6]);
   //if (irSensorState1 == LOW) {
      Serial.print("Gate sensor "); // Print sensor number (1-based index)
      Serial.println(": vehicle detected!");
      
     
    // Turn off red light
      
      val = val - 1;
       // scale it to use it with the servo (value between 0 and 180)
      Servo1.write(90); 

      digitalWrite(redLightPin, LOW);
      digitalWrite(greenLightPin, HIGH);
      delay(1000);
      Servo1.write(180);
      digitalWrite(greenLightPin, LOW);
      digitalWrite(redLightPin, HIGH);
      // sets the servo position according to the scaled value
                               // waits for the servo to get there
}
  // Check parking status
  if (val >=3 || (digitalRead(irSensorPins[3]) == LOW && digitalRead(irSensorPins[4]) == LOW && digitalRead(irSensorPins[5]) == LOW )) {
    Serial.println("Parking full");
    // Uncomment the next line if you want parkingFull to be set when both sensor 1 and sensor 2 detect obstacles
    // parkingFull = true;
  } else {
    Serial.println("Parking available");

    // Identify which sensor is free
    for (int i = 1; i < 4; i++) {
      if (digitalRead(irSensorPins[i]) == HIGH) {
        Serial.print("Sensor ");
        Serial.print(i + 1); // Print sensor number (1-based index)
        Serial.println(": Free");
      }
    }
  }
   
  delay(1000); // Adjust the delay based on your requirements
}