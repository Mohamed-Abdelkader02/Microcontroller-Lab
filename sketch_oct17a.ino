//to access the simulation please open this link :https://www.tinkercad.com/things/9MGnGD1RVbP-magnificent-fulffy/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard
int redLight = 13;
int yellowLight = 12;
int greenLight = 11;
int pedRedLight = 10;
int pedGreenLight = 9;
int buttonPin = 8;
int flag = 0;  
int buttonState = 0;
int buttonPressed = 0;  

void setup() {
  pinMode(redLight, OUTPUT);
  pinMode(yellowLight, OUTPUT);
  pinMode(greenLight, OUTPUT);
  pinMode(pedRedLight, OUTPUT);
  pinMode(pedGreenLight, OUTPUT);
  pinMode(buttonPin, INPUT); 
}

void loop() {
  
  buttonState = digitalRead(buttonPin);

  
  if (buttonState == HIGH && buttonPressed == 0) {
    buttonPressed = 1; 
  }

  switch (flag) {
    case 0: 
      digitalWrite(redLight, HIGH);
      digitalWrite(yellowLight, LOW);
      digitalWrite(greenLight, LOW);
      digitalWrite(pedRedLight, HIGH);
      digitalWrite(pedGreenLight, LOW);
      delay(5000); 
      flag = 1;
      break;

    case 1: 
      digitalWrite(redLight, LOW);
      digitalWrite(yellowLight, HIGH);
      digitalWrite(greenLight, LOW);
      delay(2000); 
      flag = 2;
      break;

    case 2: 
      digitalWrite(redLight, LOW);
      digitalWrite(yellowLight, LOW);
      digitalWrite(greenLight, HIGH);
      digitalWrite(pedRedLight, HIGH); 
      digitalWrite(pedGreenLight, LOW);
      delay(10000); 
      if (buttonPressed == 1) {
        flag = 3;  
      } else {
        flag = 3;  
      }
      break;

    case 3: 
      digitalWrite(redLight, LOW);
      digitalWrite(yellowLight, HIGH);
      digitalWrite(greenLight, LOW);
      delay(5000); 
      if (buttonPressed == 1) {
        flag = 4;  
      } else {
        flag = 0;  
      }
      break;

    case 4:
      digitalWrite(redLight, HIGH); 
      digitalWrite(yellowLight, LOW);
      digitalWrite(greenLight, LOW);
      digitalWrite(pedRedLight, LOW);
      digitalWrite(pedGreenLight, HIGH); 
      delay(5000); 
      flag = 5; 
      break;

    case 5: 
      digitalWrite(pedGreenLight, LOW); 
      digitalWrite(pedRedLight, HIGH);
      delay(2000); 
      buttonPressed = 0; 
      flag = 0;
      break;
  }
}



