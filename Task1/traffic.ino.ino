// to access the simulation please open this link :  https://www.tinkercad.com/things/9MGnGD1RVbP/editel?sharecode=FBLZ6-X5p1bIYLAIodzW23DC4s_H9cv04zhVrYhaWCk

int redLight = 13;
int yellowLight = 12;
int greenLight = 11;
int flag = 0; 

void setup() {
  
  pinMode(redLight, OUTPUT);
  pinMode(yellowLight, OUTPUT);
  pinMode(greenLight, OUTPUT);
}

void loop() {
 
  switch (flag) {
    case 0: // Red Light
      digitalWrite(redLight, HIGH);   
      digitalWrite(yellowLight, LOW);  
      digitalWrite(greenLight, LOW);   
      delay(5000);                    
      flag = 1;                       
      break;

    case 1: // Yellow Light (after Red)
      digitalWrite(redLight, LOW);     
      digitalWrite(yellowLight, HIGH);  
      digitalWrite(greenLight, LOW);   
      delay(2000);                    
      flag = 2;                        
      break;

    case 2: // Green Light
      digitalWrite(redLight, LOW);     
      digitalWrite(yellowLight, LOW);  
      digitalWrite(greenLight, HIGH);  
      delay(5000);                   
      flag = 3;                        
      break;

    case 3: // Yellow Light (after Green)
      digitalWrite(redLight, LOW);     
      digitalWrite(yellowLight, HIGH);  
      digitalWrite(greenLight, LOW);   
      delay(2000);                    
      flag = 0;                        
      break;
  }
}
