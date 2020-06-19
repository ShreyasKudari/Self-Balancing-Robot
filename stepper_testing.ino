
const int stepPin1=5;
const int dirPin1=6;
const int stepPin2=7;
const int dirPin2=8;
void setup() {
  // put your setup code here, to run once:
 pinMode(stepPin1,OUTPUT); 
  pinMode(dirPin1,OUTPUT);
   pinMode(stepPin2,OUTPUT); 
  pinMode(dirPin2,OUTPUT);
 // digitalWrite(dirPin1, HIGH);
  //digitalWrite(stepPin1, HIGH);
}

void loop() {
  
 digitalWrite(dirPin2,HIGH); // Enables the motor to move in a particular direction
  digitalWrite(dirPin1,HIGH);
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 200; x++) {
    digitalWrite(stepPin2,HIGH); 
    digitalWrite(stepPin1,HIGH);
    delayMicroseconds(500); 
    digitalWrite(stepPin2,LOW); 
    digitalWrite(stepPin1,LOW);
    delayMicroseconds(500); 
  }
  delay(1000); // One second delay
  
  digitalWrite(dirPin2,LOW); //Changes the rotations direction
   digitalWrite(dirPin1,LOW);
  // Makes 400 pulses for making two full cycle rotation
  for(int x = 0; x < 400; x++) {
    digitalWrite(stepPin2,HIGH);
     digitalWrite(stepPin1,HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2,LOW);
     digitalWrite(stepPin1,LOW);
    delayMicroseconds(500);
  }
  delay(1000);
}
