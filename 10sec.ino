//LIBRERIAS: 
#include <Arduino_LSM9DS1.h> // The library for 9-axis IMU, install "Arduino_LSM9DS1", docs https://www.arduino.cc/en/Reference/ArduinoLSM9DS1
#include <Arduino_LPS22HB.h> // The library to read Pressure, install "Arduino_LPS22HB", docs https://www.arduino.cc/en/Reference/ArduinoLPS22HB
#include <Arduino_HTS221.h> // The library to read Temperature and Humidity, install "Arduino_HTS221", docs https://www.arduino.cc/en/Reference/ArduinoHTS221
#include <Arduino_APDS9960.h> // Include library for colour, proximity and gesture recognition, install "Arduino_APDS9960", docs https://www.arduino.cc/en/Reference/ArduinoAPDS9960


unsigned long hasieraf=0;
unsigned long bukaeraf=0;
unsigned long hasierab=0;
unsigned long bukaerab=0;
unsigned long hasierar=0;
unsigned long bukaerar=0;
unsigned long hasieral=0;
unsigned long bukaeral=0;
int incomingByte = 0; // for incoming serial data

//Sensoren bariablek definittu: 
float accel_x, accel_y, accel_z;
float gyro_x, gyro_y, gyro_z;
float mag_x, mag_y, mag_z;
float Pressure;
int Proximity;

void setup() 
{
  Serial.begin(115200); // opens serial port, sets data rate to 9600 bps  

  // LED-a itzali
   digitalWrite(22, HIGH); // añadido
   digitalWrite(23, HIGH); // añadido
   digitalWrite(24, HIGH); // añadido
  
  while (!Serial) {
    ; // wait for serial port to connect
  }
  
  if (!IMU.begin()) { // Initialize IMU sensor 
   Serial.println("Failed to initialize IMU!");
   while (1);
  }

  if (!BARO.begin()) { //Initialize Pressure Sensor 
   Serial.println("Failed to initialize Pressure Sensor!");
   while (1);
  }

  if (!APDS.begin()) { // Initialize Colour, Proximity and Gesture sensor 
    Serial.println("Failed to initialize Colour, Proximity and Gesture Sensor!");
    while (1);
  }

 
}

void loop() 
{
  // Motorrai bialikoizkion aginduk
  int speed=0;
  int steer=0;

   if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read(); //Bialitako komandoa letukou
   

    if (incomingByte == 'f') {  // añadido en lugar de 8
    // Aurrera
    Serial.println("aurrera");
    hasieraf=millis()  ;  
      for (int i=0; i<=10000; i++){   //4 segungo aurrea
      digitalWrite(23,LOW);
      steer=0 ;
      speed=200 ;
   //   Comunication(steer,speed);
     if (i % 100==0){
      Measure();     
     }      
      delay(1);
      }      
      digitalWrite(23,HIGH);
    bukaeraf=millis();
    Serial.println("denbora="); 
    Serial.println(bukaeraf-hasieraf);        
    }
    
    if (incomingByte == 'b') {  // añadido en lugar de 2
    // Atzera
     Serial.println("atzera");
    hasierab=millis()  ;  

    for (int i=0; i<=10000; i++){   //4 segungo atzea
    digitalWrite(22,LOW);
    steer=0;
    speed=-200;
    //  Comunication(steer,speed);
    if (i % 100==0){
      Measure();     
     }   
    delay(1);
    }    
    digitalWrite(22,HIGH);   
    
    bukaerab=millis();
    Serial.println("denbora="); 
    Serial.println(bukaerab-hasierab);

    }

    if (incomingByte == 'r') {  // añadido en lugar de 6
    // Eskuina
    Serial.println("eskuinera");
    hasierar=millis()  ;  

    for (int i=0; i<=10000; i++){   //4 segungo eskuinea intermitentekin
    steer=1000;
    speed=200;
  //  Comunication(steer,speed);
    if (i % 100==0){
      Measure();     
     }     
      if ((i>=0 && i<=1000)||(i>=2000 && i<=3000)||(i>=4000 && i<=5000)||(i>=6000 && i<=7000)||(i>=8000 && i<=9000) ){

      digitalWrite(24, LOW);
      }    
      digitalWrite(24, HIGH);
    delay(1);
    }

    bukaerar=millis();
    Serial.println("denbora="); 
    Serial.println(bukaerar-hasierar);    
    }

    if (incomingByte == 'l') {  //
    Serial.println("ezkerrera");
    // Ezkerra
    hasieral=millis()  ;  

    for (int i=0; i<=10000; i++){   //4 segungo ezkerrea intermitentekin
    steer=-1000;
    speed=200;
  //  Comunication(steer,speed);
    if (i % 100==0){
      Measure();     
     }   
      
     if ((i>=0 && i<=1000)||(i>=2000 && i<=3000)||(i>=4000 && i<=5000)||(i>=6000 && i<=7000)||(i>=8000 && i<=9000)){

      digitalWrite(24, LOW);
      }    
      digitalWrite(24, HIGH);             
      delay(1);
    }
    bukaeral=millis();
    Serial.println("denbora="); 
    Serial.println(bukaeral-hasieral); 
    }


  }  

  digitalWrite(22, HIGH); // añadido
  digitalWrite(23, HIGH); // añadido
  digitalWrite(24, HIGH); // añadido

  }

//void Comunication(int steer,int speed){

//Serial1.write=(steer^speed);

//}   
  
void Measure(){
  Serial.print(millis());
  Serial.print(", ");
  // Accelerometer values 
    if (IMU.accelerationAvailable()) {
      IMU.readAcceleration(accel_x, accel_y, accel_z);
      Serial.print(accel_x);
      Serial.print(", ");
      Serial.print(accel_y);
      Serial.print(", ");
      Serial.print(accel_z);
    }

    // Gyroscope values 
    if (IMU.gyroscopeAvailable()) {
      IMU.readGyroscope(gyro_x, gyro_y, gyro_z);
      Serial.print(", ");
      Serial.print(gyro_x);
      Serial.print(", ");
      Serial.print(gyro_y);
      Serial.print(", ");
      Serial.print(gyro_z);
      }

  // Magnetometer values 
    if (IMU.magneticFieldAvailable()) {
      IMU.readMagneticField(mag_x, mag_y, mag_z);
      Serial.print(", ");
      Serial.print(mag_x);
      Serial.print(", ");
      Serial.print(mag_y);
      Serial.print(", ");
      Serial.print(mag_z);
      }

  // Read Pressure value
    Pressure = BARO.readPressure();
    Serial.print(", ");
    Serial.print(Pressure);

  Serial.println(""); 
  
     
}

  
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