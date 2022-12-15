// Motor A connections izquierdo
int enA = 11; // velocidad
int in1 = 12; // aurrera
int in2 = 13; // atzera
// Motor B connections derecho
int enB = 10; // velocidad
int in3 = 8; // aurrera
int in4 = 7; // atzera


int incomingByte = 0; // for incoming serial data


void setup() 
{
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps

  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  
  pinMode(22, OUTPUT); // LED
  pinMode(23, OUTPUT); // LED
  pinMode(24, OUTPUT); // LED

   digitalWrite(22, HIGH); // añadido
   digitalWrite(23, HIGH); // añadido
   digitalWrite(24, HIGH); // añadido
  
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

}



void loop() 
{
   if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    
  // Set motors to maximum speed
  // For PWM maximum possible values are 0 to 255
  analogWrite(enA, 255);
  analogWrite(enB, 255);

  
  if (incomingByte == 'f') {  // añadido en lugar de 8
  // Forward A & B (MECA aurrera)
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  
 
  delay(10);
  digitalWrite(22, LOW);
  
  }  

   if (incomingByte == 'b') {
  // Backwards A & B (MECA atzera)
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
 
  delay(10);
  digitalWrite(23, LOW);
  
  }

   if (incomingByte == 'l') {
  // Left A & B (MECA izquierda)
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  

  delay(10);
  digitalWrite(24, LOW);
  }

  if (incomingByte == 'r') {
  // Right A & B (MECA derecha)
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  

  delay(10);
  digitalWrite(22, LOW);
  digitalWrite(23, LOW);
  
   }
  if (incomingByte == '5') {
  // Turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  }

  if (incomingByte == '6') {
  digitalWrite(22, HIGH); // añadido
  digitalWrite(23, HIGH); // añadido
  digitalWrite(24, HIGH); // añadido
  }
  
}}

  
/*
//UNEDITED
// This function lets you control speed of the motors
void speedControl() {
  // Turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
  // Accelerate from zero to maximum speed
  for (int i = 0; i < 256; i++) {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  }
  
  // Decelerate from maximum speed to zero
  for (int i = 255; i >= 0; --i) {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  }
  
  // Now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}*/
