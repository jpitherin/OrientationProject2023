/*

*/

//Blynk device information
#define BLYNK_TEMPLATE_ID "TMPL40rjfr5vX"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "WYPo72A2q4S_LsaRQdTHxURiCAr4un7V"

//Import libraries
#include <SPI.h>
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>

//Set global variables (constants)
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "4G-Gateway-E6F8";
char pass[] = "EE5NTMT4TGB";
BlynkTimer timer;

//Declare variables to be used
int sensorPin = A0; 
int sensorData;
float analogVoltage;
int analogTemp;

void myTimerEvent() {
  //Send information to Blynk datastreams
  Blynk.virtualWrite(V2,millis() / 1000); //Second counter
  Blynk.virtualWrite(V4,sensorData);  //Raw sensor data
  Blynk.virtualWrite(V3,analogVoltage); //Sensor voltage output
  Blynk.virtualWrite(V5,analogTemp);  //Sensor temperature reading (celsius)
}

void setup() {
  // Connect to Blynk
  Blynk.begin(auth,ssid,pass);

  //Timer runs in 1 second intervals
  timer.setInterval(1000L,myTimerEvent);
}

void loop() {
  //Start the Blynk things
  Blynk.run();
  timer.run();

  //Read raw data from analog temperature sensor
  sensorData = analogRead(sensorPin);

  //Convert raw data into volts
  analogVoltage = (sensorData*3.3/1024);

  //Convert volts into temperature (celcius)
  analogTemp = sensorData*(3.3/1024)*100;
}
