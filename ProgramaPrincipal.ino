//LIBRERIAS: 
#include <Arduino_LSM9DS1.h> // The library for 9-axis IMU, install "Arduino_LSM9DS1", docs https://www.arduino.cc/en/Reference/ArduinoLSM9DS1
#include <Arduino_LPS22HB.h> // The library to read Pressure, install "Arduino_LPS22HB", docs https://www.arduino.cc/en/Reference/ArduinoLPS22HB
#include <Arduino_HTS221.h> // The library to read Temperature and Humidity, install "Arduino_HTS221", docs https://www.arduino.cc/en/Reference/ArduinoHTS221
#include <Arduino_APDS9960.h> // Include library for colour, proximity and gesture recognition, install "Arduino_APDS9960", docs 



int incomingByte = 0; // for incoming serial data

//Definición de las variables de sensores:  
float accel_x, accel_y, accel_z;
float gyro_x, gyro_y, gyro_z;
float mag_x, mag_y, mag_z;
float Pressure;
int Proximity;

void setup() 
{
  
  Serial.begin(115200); // opens serial port, sets data rate to 9600 bps  
  Serial1.begin(115200);

  // Apagar luces LED
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

  // Para calcular el tiempo en movimiento
  unsigned long t_principio=0;
  unsigned long t_final=0;

  // Órdenes que le enviaremos al motor
  int speed=0;  // velocidad
  int steer=0;  // dirección

  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();   // Lectura de órdenes 
    
    if (incomingByte == 'f') {      // ADELANTE -->  añadido en lugar de 8
    t_principio=millis()  ;  
    for (int i=0; i<=3000; i++){    // Movimiento hacia adelante durante 3 segundos
    digitalWrite(23,LOW);           // Encender luz verde
    steer=0 ;                       // Asignación de dirección
    speed=200 ;                     // Asignación de velocidad       
    Comunication(steer,speed);      // Mandar órdenes al motor
    if (i % 100==0){
      Measure();                    // Adquisición de datos
    }
    delay(1);
    Serial.println("i");
    Serial.println(i);
    }      
    digitalWrite(23,HIGH);          //Apagar luz verde
    t_final=millis();
    Serial.println("tiempo en movimiento="); 
    Serial.println(t_final-t_principio);        
    }
    
    if (incomingByte == 'b') {      // ATRÁS -->  añadido en lugar de 2
    t_principio=millis()  ;  
    for (int i=0; i<=3000; i++){    // Movimiento hacia adelante durante 3 segundos
    digitalWrite(22,LOW);           // Encender luz roja
    steer=0;                        // Asignación de dirección 
    speed=-200;                     // Asignación de velocidad
    Comunication(steer,speed);      // Mandar órdenes al motor
    if (i % 100==0){
      Measure();                      // Adquisición de datos
    }
    delay(1);
    }    
    digitalWrite(22,HIGH);          // Apagar luz roja
    t_final=millis();
    Serial.println("tiempo en movimiento="); 
    Serial.println(t_final-t_principio);
    }

    if (incomingByte == 'r') {      // DERECHA --> añadido en lugar de 6
    t_principio=millis()  ;  
    for (int i=0; i<=3000; i++){    // Movimiento hacia derecha durante 3 segundos
    steer=1000;                     // Asignación de dirección
    speed=200;                      // Asignación de velocidad
    Comunication(steer,speed);      // Mandar órdenes al motor
    if (i % 100==0){
    Measure();                      // Adquisición de datos
    }
    if ((i>=0 && i<=750)||(i>=1500 && i<=2250) ){     //Luz intermitente azul
      digitalWrite(24, LOW);
    }    
    digitalWrite(24, HIGH);
    delay(1);
    }
    t_final=millis();
    Serial.println("tiempo en movimiento="); 
    Serial.println(t_final-t_principio);    
    }

    if (incomingByte == 'l') {    // IZQUIERDA --> añadido en lugar de 4
    t_principio=millis()  ;  
    for (int i=0; i<=3000; i++){  // Movimiento hacia izquierda durante 3 segundos
    steer=-1000;                  // Asignación de dirección
    speed=200;                    // Asignación de velocidad
    Comunication(steer,speed);    // Mandar órdenes al motor
    if (i % 100==0){
    Measure();                    // Adquisición de datos 
    }
    if ((i>=0 && i<=750)||(i>=1500 && i<=2250) ){    //Luz intermitente azul
      digitalWrite(24, LOW);
    }    
    digitalWrite(24, HIGH);             
    delay(1);
    }
    t_final=millis();
    Serial.println("tiempo en movimiento="); 
    Serial.println(t_final-t_principio); 
    }

  }  

  // Apagar luces LED
  digitalWrite(22, HIGH); 
  digitalWrite(23, HIGH); 
  digitalWrite(24, HIGH); 

  }

void Comunication(int steer,int speed){  // Manda órdenes al motor
Serial1.write(steer^speed); 
}   
  
void Measure(){     // Mide e imprime los valores adquiridos por los sensores
  Serial.print(millis());                                 
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