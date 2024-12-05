#include <Wire.h>

// Pin definitions for pedestrian light
const int pedRedLight = 7;
const int pedGreenLight = 6;

volatile bool startPedestrianCycle = false;  // Flag set by I2C event
bool pedestrianCycleComplete = false;  // Tracks if the cycle is complete

void setup() {
  Wire.begin(8); // Join I2C bus as Slave with address 8
  Serial.begin(9600); // Initialize serial communication

  Wire.onReceive(receiveEvent);  // Register event for receiving data
  Wire.onRequest(requestEvent);  // Register event for responding to master requests

  pinMode(pedRedLight, OUTPUT);
  pinMode(pedGreenLight, OUTPUT);

  // Initialize pedestrian light to red
  digitalWrite(pedRedLight, HIGH);
  digitalWrite(pedGreenLight, LOW);
}

void loop() {
  // Check if the pedestrian cycle should start
  if (startPedestrianCycle) {
    Serial.println("Starting pedestrian cycle...");
    runPedestrianCycle();  // Run the pedestrian cycle
    pedestrianCycleComplete = true;  // Mark the cycle as complete
    startPedestrianCycle = false;    // Reset the flag
  }
}

// Function to handle incoming data from Master
void receiveEvent(int bytes) {
  while (Wire.available()) {
    char command = Wire.read();  // Read incoming byte as command
    Serial.print("Received command: ");
    Serial.println(command);

    if (command == 'G') {  // Command to turn pedestrian light green
      startPedestrianCycle = true;  // Set the flag to start the cycle
    }
  }
}

// Function to execute the pedestrian light cycle
void runPedestrianCycle() {
  // Turn pedestrian light green
  digitalWrite(pedRedLight, LOW);
  digitalWrite(pedGreenLight, HIGH);
  delay(5000);  // Keep green for 5 seconds

  // Transition back to red for pedestrian
  digitalWrite(pedGreenLight, LOW);
  digitalWrite(pedRedLight, HIGH);
  delay(2000);

  Serial.println("Pedestrian cycle complete.");
}

// Function to respond to Master requests
void requestEvent() {
  if (pedestrianCycleComplete) {
    Wire.write("R");  // Send "resume" signal
    pedestrianCycleComplete = false;  // Reset the flag after response
  } else {
    Wire.write("N");  // Send "no action" signal if cycle not complete
  }
}
