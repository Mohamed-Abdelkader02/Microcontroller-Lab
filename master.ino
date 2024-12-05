#include <Wire.h>

// Pin definitions
int redLight = 11;
int yellowLight = 12;
int greenLight = 13;
int buttonPin = 2;

// State variables
volatile int buttonPressed = 0; // Marked as volatile for use in interrupt
int flag = 0;

// State constants for traffic light sequence
const int TRAFFIC_RED = 0;
const int TRAFFIC_YELLOW_AFTER_RED = 1;
const int TRAFFIC_GREEN = 2;
const int TRAFFIC_YELLOW_AFTER_GREEN = 3;
const int WAIT_FOR_PEDESTRIAN = 4;

void setup() {
  Wire.begin();  // Join I2C bus as master
  Serial.begin(9600);
  pinMode(redLight, OUTPUT);
  pinMode(yellowLight, OUTPUT);
  pinMode(greenLight, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // Button input with internal pull-up

  // Attach interrupt to button pin
  attachInterrupt(digitalPinToInterrupt(buttonPin), handleButtonPress, RISING);
}

void loop() {
  
  
  switch (flag) {
    case TRAFFIC_RED: // Red Light (Traffic)
      digitalWrite(redLight, HIGH);
      digitalWrite(yellowLight, LOW);
      digitalWrite(greenLight, LOW);
      delay(5000); // 5 seconds red
      flag = TRAFFIC_YELLOW_AFTER_RED;
      break;

    case TRAFFIC_YELLOW_AFTER_RED: // Yellow Light after Red
      digitalWrite(redLight, LOW);
      digitalWrite(yellowLight, HIGH);
      digitalWrite(greenLight, LOW);
      delay(2000); // 2 seconds yellow
      flag = TRAFFIC_GREEN;
      break;

    case TRAFFIC_GREEN: // Green Light (Traffic)
      digitalWrite(redLight, LOW);
      digitalWrite(yellowLight, LOW);
      digitalWrite(greenLight, HIGH);
      delay(10000); // At least 10 seconds green
      flag = TRAFFIC_YELLOW_AFTER_GREEN;
      break;

    case TRAFFIC_YELLOW_AFTER_GREEN: // Yellow Light after Green
      digitalWrite(yellowLight, HIGH);
      digitalWrite(greenLight, LOW);
      delay(5000); // 5 seconds yellow

      if (buttonPressed == 1) { // If button was pressed
        // Notify Arduino 2 to switch pedestrian light to green
        Serial.println("dost 3ala el zorar");
        Wire.beginTransmission(8);  // Send to Slave with address 8
        Wire.write("G");  // Send signal for pedestrian green
        Wire.endTransmission();
        flag = WAIT_FOR_PEDESTRIAN; // Wait for Arduino 2 response
      } else {
        // Go directly back to TRAFFIC_RED if no button is pressed
        flag = TRAFFIC_RED;
      }
      break;

    case WAIT_FOR_PEDESTRIAN:
      // Pedestrian light is green, wait for Arduino 2 to respond
      digitalWrite(redLight, HIGH);
      digitalWrite(yellowLight, LOW);
      digitalWrite(greenLight, LOW);
      Wire.requestFrom(8, 1);  // Request 1 byte from Slave
      if (Wire.available()) {
        char response = Wire.read();
        if (response == 'R') { // If Arduino 2 signals to resume
          buttonPressed = 0; // Reset button state
          flag = TRAFFIC_RED; // Go back to red light
        }
      }
      break;
  }
}

// Interrupt Service Routine (ISR) for button press
void handleButtonPress() {
  buttonPressed = 1; 
  Serial.println("Button pressed");// Set flag when button is pressed
}
