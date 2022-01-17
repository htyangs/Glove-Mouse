#include <Wire.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM9DS0.h>


SoftwareSerial BTSerial(10, 11); // RX | TX for AT mode

Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0(1000);  // Use I2C, ID #1000
/*
To change hardware operation of LSM9DS0, go to Adafruit_LSM9DS0.cpp
1. restrict reading of accelerometer/gyrometer/magnometer/temperature: goto line 220, comment out readAccel() or readGyro() etc..
2. To set min/max reading of gyro: goto line 708, hard-code min/max into function
*/

#define LSM9DS0_XM_CS 10
#define LSM9DS0_GYRO_CS 9
#define LSM9DS0_SCLK 13
#define LSM9DS0_MISO 12
#define LSM9DS0_MOSI 11


// Measure the voltage at 5V and the actual resistance of your
// 47k resistor, and enter them below:
const int FLEX_PIN = A2; // Pin connected to voltage divider output
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 47000.0; // Measured resistance of 3.3k resistor

// Upload the code, then try to adjust these values to more
// accurately calculate bend degree.
const float STRAIGHT_RESISTANCE = 37000.0; // resistance when straight
const float BEND_RESISTANCE = 90000.0; // resistance at 90 deg


void displaySensorDetails(void)
{
  sensor_t accel, mag, gyro, temp;
  lsm.getSensor(&accel, &mag, &gyro, &temp);
  
  Serial.println(F("------------------------------------"));
  Serial.print  (F("Sensor:       ")); Serial.println(accel.name);
  Serial.print  (F("Driver Ver:   ")); Serial.println(accel.version);
  Serial.print  (F("Unique ID:    ")); Serial.println(accel.sensor_id);
  Serial.print  (F("Max Value:    ")); Serial.print(accel.max_value); Serial.println(F(" m/s^2"));
  Serial.print  (F("Min Value:    ")); Serial.print(accel.min_value); Serial.println(F(" m/s^2"));
  Serial.print  (F("Resolution:   ")); Serial.print(accel.resolution); Serial.println(F(" m/s^2"));  
  Serial.println(F("------------------------------------"));
  Serial.println(F(""));

  Serial.println(F("------------------------------------"));
  Serial.print  (F("Sensor:       ")); Serial.println(mag.name);
  Serial.print  (F("Driver Ver:   ")); Serial.println(mag.version);
  Serial.print  (F("Unique ID:    ")); Serial.println(mag.sensor_id);
  Serial.print  (F("Max Value:    ")); Serial.print(mag.max_value); Serial.println(F(" uT"));
  Serial.print  (F("Min Value:    ")); Serial.print(mag.min_value); Serial.println(F(" uT"));
  Serial.print  (F("Resolution:   ")); Serial.print(mag.resolution); Serial.println(F(" uT"));  
  Serial.println(F("------------------------------------"));
  Serial.println(F(""));

  Serial.println(F("------------------------------------"));
  Serial.print  (F("Sensor:       ")); Serial.println(gyro.name);
  Serial.print  (F("Driver Ver:   ")); Serial.println(gyro.version);
  Serial.print  (F("Unique ID:    ")); Serial.println(gyro.sensor_id);
  Serial.print  (F("Max Value:    ")); Serial.print(gyro.max_value); Serial.println(F(" rad/s"));
  Serial.print  (F("Min Value:    ")); Serial.print(gyro.min_value); Serial.println(F(" rad/s"));
  Serial.print  (F("Resolution:   ")); Serial.print(gyro.resolution); Serial.println(F(" rad/s"));  
  Serial.println(F("------------------------------------"));
  Serial.println(F(""));
  
  delay(500);
}

// Configures the gain and integration time for the TSL2561
void configureSensor(void) 
{
  // 1.) Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_2G); // lsm.LSM9DS0_ACCELRANGE_2G, 4G, 6G, 8G, 16G
  
  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS0_MAGGAIN_2GAUSS); // lsm.LSM9DS0_MAGGAIN_2GAUSS, 4GAUSS. 8GAUSS, 12GAUSS

  // 3.) Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_245DPS); // lsm.LSM9DS0_GYROSCALE_245DPS, 500DPS, 2000DPS
}



void setup()
{
 Serial.begin(9600);  //baud rate of Arduino can go up to 115200, 9600 by default. Does not affect sample rate of analogRead
 //Serial.println("Enter commands:");
 BTSerial.begin(38400); // initialise HC-05, has a max baudrate of 38400
 pinMode(FLEX_PIN, INPUT); //FLEX_PIN = A2

// initialising LSM9DS0
  Serial.println(F("LSM9DS0 9DOF Sensor Test")); Serial.println("");
  
  /* Initialise the sensor */
  if(!lsm.begin())
  {
    /* There was a problem detecting the LSM9DS0 ... check your connections */
    Serial.print(F("Ooops, no LSM9DS0 detected ... Check your wiring or I2C ADDR!"));
    while(1);
  }
  
  Serial.println(F("Found LSM9DS0 9DOF"));

  /* Setup the sensor gain and integration time */
  configureSensor();
  
  /* Display some basic information on this sensor */
  displaySensorDetails();
  
  /* We're ready to go! */
  Serial.println("Sensor is ready");
}


 
void loop()
{ 

    
    // read LSM9DS0 
   sensors_event_t accel, mag, gyro, temp;
   lsm.getEvent(NULL, NULL, &gyro, NULL); 

  //long t0, t;
  //t0 = micros();
  
  
  
  if(BTSerial.available()){
    Serial.println(BTSerial.readString());
  }
  //if(Serial.available()){
    //
    long  value = accel.acceleration.x * 7.0 + 127.5; // as accel is [-20, 20]?, we shift/normalise this value to be [0, 255]
    long  valueX = gyro.gyro.x * 7.0 + 127.5;         // as gyro is [-20, 20]?, we shift/normalise this value to be [0, 255]
    long  valueY = gyro.gyro.y * 7.0 + 127.5;
    long  valueZ = gyro.gyro.z * 7.0 + 127.5;
    int fsr_value = analogRead(A3)/4; // 讀取FSR [0,1023]
    int fsr_value2 = analogRead(A1)/4; 
    int bend = 0;
    int flexADC = analogRead(FLEX_PIN); // reads a value in [0, 1023]
    float flexV = flexADC * VCC / 1023.0; // conversion to Voltage
    float flexR = R_DIV * (VCC / flexV - 1.0); // conversion to resistance of flex resistor
    //Serial.println("Resistance: " + String(flexR) + " ohms");
  
    // Use the calculated resistance to estimate the sensor's
    // bend angle:
    //float angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE, 0, 90.0); // conversion to flex angle
    //Serial.println("Bend: " + String(angle) + " degrees");
    //Serial.println();

    /*
    Serial.println(fsr_value);
    Serial.println(fsr_value2);
    Serial.println(valueZ);
    Serial.println(valueY);
    Serial.println("------------------------------------------------");*/
    /*
    Serial.println(value);
    Serial.println(valueX);
    Serial.println(valueY);
    Serial.println(valueZ);
    Serial.println();
    */
      
    BTSerial.write(valueZ);
    BTSerial.write(valueY);
    BTSerial.write(valueX);
    BTSerial.write(fsr_value);
    BTSerial.write(fsr_value2);
    BTSerial.write(flexV*50);
    
    /*if (flexR<30000){
      bend = 1;
      BTSerial.write(bend);
    }
    else{
      bend = 0;
      BTSerial.write(bend);
    }
    */
    BTSerial.println();
  //}

  
  
  //t = micros();
  //Serial.print("1000 Samples+send took (us): "); Serial.println(t-t0);
  
}
