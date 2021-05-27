#include <NewPing.h>
#include <SoftwareSerial.h>
#include <Servo.h>
// Reference the I2C Library
#include <Wire.h>
// Reference the HMC5883L Compass Library
#include <HMC5883L.h>

//WIFI MODULE
#ifdef ARDUINO_ARCH_SAMD
#include <WiFi101.h>
#elif defined ARDUINO_ARCH_ESP8266
#include <ESP8266WiFi.h>
#elif defined ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#error Wrong platform
#endif 
#include <SoftwareSerial.h>
#include <WifiLocation.h>

const char* googleApiKey = "AIzaSyDfb2Qm5r036yDoKboKZamY2SkhDlkZfIo";
const char* ssid = "Mobitel4G-DB05";
const char* passwd = "THA,run1998";

WifiLocation location(googleApiKey);
SoftwareSerial serial1(2,3); //RX,TX
WiFiServer server(80);
String currentLine ="";

// Store our compass as a variable.
HMC5883L compass;
// Record any errors that may occur in the compass.
int error = 0;
int16_t mx, my, mz;                                                // variables to store x,y,z axis from compass (HMC5883L)
int desired_heading;                                               // initialize variable - stores value for the new desired heading
int compass_heading;                                               // initialize variable - stores value calculated from compass readings
int compass_dev = 5;                                               // the amount of deviation that is allowed in the compass heading - Adjust as Needed
                                                                // setting this variable too low will cause the robot to continuously pivot left and right
                                                                   // setting this variable too high will cause the robot to veer off course

int Heading_A;                                                     // variable to store compass heading
int Heading_B;                                                     // variable to store compass heading in Opposite direction
int pass = 0;                                                      // variable to store which pass the robot is on

//******************************************************************************************************

//Servo motor
Servo myservo;
int servostartpos=95;

//our L298N control pins
const int LeftMotorForward = 8;
const int LeftMotorBackward = 9;
const int RightMotorForward = 10;
const int  RightMotorBackward = 11; 
boolean goesForward = false;

//Ultrosonic sensor
#define trigh_ping A0
#define echo_ping  A1
#define max_distance_from_obstacle 100
NewPing sonar_distancesensor(trigh_ping,echo_ping,max_distance_from_obstacle);
int distance ;
boolean pingOn = true;                                           // Turn Collision detection On or Off
int Ping_distance;
     


 //*****************************************************************************************************
// GPS Locations

unsigned long Distance_To_Home;                                   // variable for storing the distance to destination
int ac =0;                                                         // GPS array counter
int wpCount = 0;                                                   // GPS waypoint counter
double Home_LATarray[50];                                          // variable for storing the destination Latitude - Only Programmed for 5 waypoint
double Home_LONarray[50];                                          // variable for storing the destination Longitude - up to 50 waypoints
location_t loc // get current location
int increment = 0;      
TinyGPSPlus gps;  // variable to store which pass the robot is on
//end


void setup() {
  Serial.begin(9600);
  //Serial1.begin(9600);                                             // Serial 1 is for Wifi communication -
  //Serial2.begin(9600); 
  
  //GPS LOCATION SETUP
  serial1.begin(115200);
    // Connect to WPA/WPA2 network
  #ifdef ARDUINO_ARCH_ESP32
  WiFi.mode(WIFI_MODE_STA);
  #endif
  #ifdef ARDUINO_ARCH_ESP8266
  WiFi.mode(WIFI_STA);
  #endif
  WiFi.begin(ssid, passwd);
    while (WiFi.status() != WL_CONNECTED) {
        serial1.print("Attempting to connect to WPA SSID: ");
        serial1.println(ssid);
        // wait 5 seconds for connection:
        serial1.print("Status = ");
        serial1.println(WiFi.status());
        delay(500);
   }
    loc = location.getGeoFromWiFi();

   serial1.println("Location request data");
   serial1.println(location.getSurroundingWiFiJson());
   serial1.println("Latitude: " + String(loc.lat, 7));
   serial1.println("Longitude: " + String(loc.lon, 7));
   serial1.println("Accuracy: " + String(loc.accuracy));
  //End of wifi gps location*/
  
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  
  //Servo motor 
  myservo.attach(13);
  myservo.write(servostartpos);
  
  //Compass*********************************
  Serial.println("Starting the I2C interface.");
  Wire.begin(); // Start the I2C interface.
  Serial.println("Constructing new HMC5883L");
  compass = HMC5883L(); // Construct a new HMC5883 compass.    
  error = compass.SetScale(1.3);
  // Set the scale of the compass.
  if(error != 0) // If there is an error, print it out.
    Serial.println(compass.GetErrorText(error));  
  Serial.println("Setting measurement mode to continous.");
  error = compass.SetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous
  if(error != 0) // If there is an error, print it out.
    Serial.println(compass.GetErrorText(error));
  //*****************************************
  
  



  Startup();
}


void loop() {

  //Connect with MIT App
   wifimodule();
   getGps();
   getCompass();
   Ping();
   
  
   /*
   int distanceRight = 0;
   int distanceLeft = 0;
   
   delay(50);
   if(distance<=50){
     Serial.println("distance below 50");
     MoveStop();
     delay(500);
     MoveBackward();
     delay(500);
     MoveStop();
     delay(100);
     distanceRight = LookRight();
     delay(300);
     distanceLeft = LookLeft();
     delay(300);

     if(distance >=distanceLeft){
      TurnRight();
      MoveStop();
     }
     else{
      TurnLeft();
      MoveStop();
     }
   }
   else{
    MoveForward();
   }
   distance = readPing();
   Serial.println(distance);
   */
   
}

void printWifiStatus(){
  //print the SSID of the netwrok you're attached to 
  serial1.print("SSID:");
  serial1.println(WIFI.SSID());
  
  //PRINT your WIFI SHIELD IP ADDRESS
  IPAddress ip = WiFi.localIP();
  serial1.print("IP Address: ");
  serial1.println(ip);

  //print the received signal strength:
  logn rssi = WiFi.RSSI();
  serial1.print("signal strnegth(RSSI):");
  serial.print(rssi);
  serial.println("dBm");
}


int LookRight(){
  Serial.println("LookRight");
  myservo.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(0);
  return distance;
}
int LookLeft(){
  Serial.println("LookLeft");
  myservo.write(172);
  delay(500);
  int distance = readPing();  
  delay(100);
   myservo.write(servostartpos);
  return distance;
  delay(100);
}
