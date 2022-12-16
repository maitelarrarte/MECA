#include <Arduino_LSM9DS1.h> // The library for 9-axis IMU, install "Arduino_LSM9DS1", docs https://www.arduino.cc/en/Reference/ArduinoLSM9DS1
#include <Arduino_LPS22HB.h> // The library to read Pressure, install "Arduino_LPS22HB", docs https://www.arduino.cc/en/Reference/ArduinoLPS22HB
#include <Arduino_HTS221.h> // The library to read Temperature and Humidity, install "Arduino_HTS221", docs https://www.arduino.cc/en/Reference/ArduinoHTS221
#include <Arduino_APDS9960.h> // Include library for colour, proximity and gesture recognition, install "Arduino_APDS9960", docs https://www.arduino.cc/en/Reference/ArduinoAPDS9960

void setup(){
  Serial.begin(9600); //Serial monitor to display all sensor values 
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
  // APDS.setSensitivity(80); takes a value between 1 and 100 is required. Default is 80.
  // Higher values makes the gesture recognition more sensible but less accurate
  // (a wrong gesture may be detected). Lower values makes the gesture recognition
  // more accurate but less sensible (some gestures may be missed).
  // The internal inra-red LED can be increased up to 3 times with APDS.setLEDBoost

 }

float accel_x, accel_y, accel_z;
float gyro_x, gyro_y, gyro_z;
float mag_x, mag_y, mag_z;
float Pressure;
int Proximity;

void loop() {
  // Accelerometer values 
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(accel_x, accel_y, accel_z);
    Serial.print(accel_x);
    Serial.print(", ");
    Serial.print(accel_y);
    Serial.print(", ");
    Serial.print(accel_z);
  }
  // delay (200);

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

  if (true) { // This function also enables the gesture sensor when called for the first time.
    //delay (500); // Por si acaso lo dejamos, Mirara si no hace falta!!

    // TODO: Find out how to correctly wait for gestures
    /*
    int tries = 50;
    while(APDS.gestureAvailable() == 0 && tries > 0) {
      tries--;
      Serial.print(".");
      delay(30);
    }
    Serial.println("");
    int gesture = APDS.readGesture();
    switch (gesture) {
      case GESTURE_UP:
        Serial.println("Detected UP gesture");
        break;
      case GESTURE_DOWN:
        Serial.println("Detected DOWN gesture");
        break;
      case GESTURE_LEFT:
        Serial.println("Detected LEFT gesture");
        break;
      case GESTURE_RIGHT:
        Serial.println("Detected RIGHT gesture");
        break;
      case GESTURE_NONE:
        Serial.println("Detected NONE gesture");
        break;        
      default:
        break;
    }
    */
  }

  // Proximity value
  if (true)
  {
    delay(500);
    int tries= 50;
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
    Serial.print(", ");
    Serial.print("Prox = Not Found");
    //Serial.print(0); 
  }
  
  if (true) 
  { // This function also enables the color sensor when called for the first time.
    delay (500);
    int tries = 50;
    while(APDS.colorAvailable() == 0 && tries > 0) {
      tries--;
      delay(30);
    }
    int r, g, b, c;
    // read the color and clear light intensity
    APDS.readColor(r, g, b, c);
    Serial.print(", ");
    Serial.print(r);
    Serial.print(",");
    Serial.print(g);
    Serial.print(",");
    Serial.print(b);
    Serial.print(", ");
    Serial.print(c);
    // Note: ambient light information can be used to control display color temperature and backlight.
  }

  Serial.println(""); 
  delay(1000);
}
