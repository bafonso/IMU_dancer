/**
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"
#include <ESP8266WiFi.h>
// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#include "Wire.h"
#include "MPU9250.h"
#include "quaternionFilters.h"
#include "additionalFunctions.h"

int myLed = 15;
int intPin = 4;
bool newData = false;
bool newMagData = false;

#define SerialDebug true  // set to true to get Serial output for debugging


MPU9250 myIMU;


void setup()
{
  Serial.begin(115200);
  // initialize LED digital pin as an output.
  pinMode(myLed, OUTPUT);

  Wire.begin(0,2); // SDA (0), SCL (2) on ESP8285
 //Wire.begin(12,14); // SDA (12), SCL (14) on ESP8285
 Wire.setClock(400000); // choose 400 kHz I2C rate

 // Set up the interrupt pin, its set as active high, push-pull
 pinMode(intPin, INPUT);
 pinMode(myLed, OUTPUT);

  I2Cscan();// look for I2C devices on the bus


  // Read the WHO_AM_I register, this is a good test of communication
  byte c = myIMU.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);
  Serial.print("MPU9250 "); Serial.print("I AM "); Serial.print(c, HEX);
  Serial.print(" I should be "); Serial.println(0x71, HEX);

  myIMU.initMPU9250();

  float selfTestDeviation;            // holds results of gyro and accelerometer self test

  myIMU.MPU9250SelfTest(& selfTestDeviation);
  Serial.print("Serial point deviation is: ");
  Serial.println(selfTestDeviation);

  uint32_t freeheap = ESP.getFreeHeap();
  Serial.print("Free Heap Size = "); Serial.println(freeheap);
  uint32_t chipID = ESP.getChipId();
  Serial.print("ESP8285 chip ID = "); Serial.println(chipID);
  uint32_t flashChipID = ESP.getFlashChipId();
  Serial.print("ESP8285 flash chip ID = "); Serial.println(flashChipID);
  uint32_t flashChipSize = ESP.getFlashChipSize();
  Serial.print("ESP8285 flash chip size = "); Serial.print(flashChipSize); Serial.println(" bytes");
  uint32_t flashChipSpeed = ESP.getFlashChipSpeed();
  Serial.print("ESP8285 flash chip speed = "); Serial.print(flashChipSpeed); Serial.println(" Hz");
  uint32_t getVcc = ESP.getVcc();
  Serial.print("ESP8285 supply voltage = "); Serial.print(getVcc); Serial.println(" volts");

}

void loop()
{



  // turn the LED on (HIGH is the voltage level)
  digitalWrite(myLed, HIGH);
  // wait for a second
Serial.println("We turn on");
  delay(1000);
  // turn the LED off by making the voltage LOW
  digitalWrite(myLed, LOW);
  Serial.println("We turn off");

   // wait for a second
  delay(1000);

}
