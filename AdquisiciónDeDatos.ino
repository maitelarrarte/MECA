#include <Arduino_LSM9DS1.h> // The library for 9-axis IMU, install "Arduino_LSM9DS1", docs https://www.arduino.cc/en/Reference/ArduinoLSM9DS1
#include <Arduino_LPS22HB.h> // The library to read Pressure, install "Arduino_LPS22HB", docs https://www.arduino.cc/en/Reference/ArduinoLPS22HB
#include <Arduino_APDS9960.h> // Include library for colour, proximity and gesture recognition, install "Arduino_APDS9960", docs https://www.arduino.cc/en/Reference/ArduinoAPDS9960

void setup(){
  Serial.begin(9600); //Monitor serie para visualizar todos los valores de los sensores 
  while (!Serial) {
    ; //Esperar a que se conecte el puerto serie
  }
  
  if (!IMU.begin()) { // Inicializar el sensor IMU  
   Serial.println("Failed to initialize IMU!");
   while (1);
  }

  if (!BARO.begin()) { //Inicializar el sensor de presión
   Serial.println("Failed to initialize Pressure Sensor!");
   while (1);
  }

  if (!APDS.begin()) { // Inicializar sensores de Color y Proximidad 
    Serial.println("Failed to initialize Colour, Proximity and Gesture Sensor!");
    while (1);
  }
  // APDS.setSensitivity(80); takes a value between 1 and 100 is required. Default is 80.
  // Higher values makes the gesture recognition more sensible but less accurate
  // (a wrong gesture may be detected). Lower values makes the gesture recognition
  // more accurate but less sensible (some gestures may be missed).
  // The internal inra-red LED can be increased up to 3 times with APDS.setLEDBoost

 }
//Definición de los parámetros de aceleración, giro, campo electromagnético, presión y proximidad
float accel_x, accel_y, accel_z;
float gyro_x, gyro_y, gyro_z;
float mag_x, mag_y, mag_z;
float Pressure;
int Proximity;

void loop() {
  // Valores del acelerometro 
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(accel_x, accel_y, accel_z);
    Serial.print(accel_x);
    Serial.print(", ");
    Serial.print(accel_y);
    Serial.print(", ");
    Serial.print(accel_z);
  }
  // delay (200);

  // Valores del giroscopio 
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(gyro_x, gyro_y, gyro_z);
    Serial.print(", ");
    Serial.print(gyro_x);
    Serial.print(", ");
    Serial.print(gyro_y);
    Serial.print(", ");
    Serial.print(gyro_z);
  }

  // Valores del magnetometro 
  if (IMU.magneticFieldAvailable()) {
    IMU.readMagneticField(mag_x, mag_y, mag_z);
    Serial.print(", ");
    Serial.print(mag_x);
    Serial.print(", ");
    Serial.print(mag_y);
    Serial.print(", ");
    Serial.print(mag_z);
  }

  // leer los valores de presión
  Pressure = BARO.readPressure();
  Serial.print(", ");
  Serial.print(Pressure);

 
  //Valores de proximidad
  if (true)
  {
    delay(500);
    int tries= 50;
    //Repitición hasta obtener algún valor de proximidad
    while(APDS.proximityAvailable() == 0 && tries >0)
    {
      tries--;
      delay(30);
    }
    Proximity = APDS.readProximity();
    Serial.print(", ");
    Serial.print(Proximity); 
  }
  else
  {
    //En el caso de no detectar ningún valor de proximidad
    Serial.print(", ");
    Serial.print("Prox = Not Found");
    //Serial.print(0); 
  }
  
  if (true) 
  { // Esta función también activa el sensor de color cuando se llama por primera vez.
    delay (500);
    int tries = 50;
    while(APDS.colorAvailable() == 0 && tries > 0) {
      tries--;
      delay(30);
    }
    int r, g, b, c;
    // leer el color y la intensidad de la luz clara
    APDS.readColor(r, g, b, c);
    Serial.print(", ");
    Serial.print(r);
    Serial.print(",");
    Serial.print(g);
    Serial.print(",");
    Serial.print(b);
    Serial.print(", ");
    Serial.print(c);
    // Nota: la información sobre la luz ambiental puede utilizarse para controlar la temperatura de color y la retroiluminación de la pantalla.
  }

  Serial.println(""); 
  delay(1000);
}
