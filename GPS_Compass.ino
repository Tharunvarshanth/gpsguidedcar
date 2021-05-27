void calibrateCompass(){                                               // end of for loop
  
  MoveStop();                             // Set calibration offset
}

void getCompass()                                               // get latest compass value
 { 
  MagnetometerRaw raw = compass.ReadRawAxis();  
  MagnetometerScaled scaled = compass.ReadScaledAxis();
  
  // Values are accessed like so:
  int MilliGauss_OnThe_XAxis = scaled.XAxis;// (or YAxis, or ZAxis)

  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  float heading = atan2(scaled.YAxis, scaled.XAxis);
  float declinationAngle = 0.0457;
  heading += declinationAngle;
  
  // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;
    compass_heading = (int)(heading * 180/M_PI); 
    
  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
   
  // Convert radians to degrees for readability.
  float headingDegrees = heading * 180/M_PI; 

  // Output the data via the serial port.
  Output(raw, scaled, heading, headingDegrees);
  // 

 
  // Calculate heading
 // float heading = atan2(norm.YAxis, norm.XAxis);
 
  if(heading < 0)
     heading += 2 * M_PI;      
  compass_heading = (int)(heading * 180/M_PI);                   // assign compass calculation to variable (compass_heading) and convert to integer to remove decimal places                                                              

 }

 void setHeading()                                                           // This procedure will set the current heading and the Heading(s) of the robot going away and returning using opposing degrees from 0 to 360;
                                                              // for instance, if the car is leaving on a 0 degree path (North), it will return on a 180 degree path (South)
{
   for (int i=0; i <= 5; i++)                                    // Take several readings from the compass to insure accuracy
      { 
        getCompass();                                            // get the current compass heading
      }                                               
    
    desired_heading = compass_heading;                           // set the desired heading to equal the current compass heading
    Heading_A = compass_heading;                                 // Set Heading A to current compass 
    Heading_B = compass_heading + 180;                           // Set Heading B to current compass heading + 180  

      if (Heading_B >= 360)                                      // if the heading is greater than 360 then subtract 360 from it, heading must be between 0 and 360
         {
          Heading_B = Heading_B - 360;
         }
     
    Serial.print("Compass Heading Set: "); 
    Serial.print(compass_heading);   
    Serial.print(" Degrees");

    Serial.print("desired heading");
    Serial.println(desired_heading);
    Serial.print("compass heading");
    Serial.println(compass_heading);

}
 // ************************************************************************************************************************************************* 

void getGPS()                                                 // Get Latest GPS coordinates
{
   // while (Serial2.available() > 0)
     loc = location.getGeoFromWiFi();
} 

// 

void setWaypoint()                                            // Set up to 5 GPS waypoints
{


  if (wpCount >= 0)
  {
    Serial.print("GPS Waypoint ");
    Serial.print(wpCount + 1);
    Serial.print(" Set ");
    getGPS();                                               // get the latest GPS coordinates
    getCompass();                                             // update latest compass heading     
                                               
    Home_LATarray[ac] = loc.lat;                   // store waypoint in an array   
    Home_LONarray[ac] = loc.lon;                   // store waypoint in an array   
                                                              
    Serial.print("Waypoint #1: ");
    Serial.print(Home_LATarray[0],6);
    Serial.print(" ");
    Serial.println(Home_LONarray[0],6);
    Serial.print("Waypoint #2: ");
    Serial.print(Home_LATarray[1],6);
    Serial.print(" ");
    Serial.println(Home_LONarray[1],6);
    Serial.print("Waypoint #3: ");
    Serial.print(Home_LATarray[2],6);
    Serial.print(" ");
    Serial.println(Home_LONarray[2],6);
    Serial.print("Waypoint #4: ");
    Serial.print(Home_LATarray[3],6);
    Serial.print(" ");
    Serial.println(Home_LONarray[3],6);
    Serial.print("Waypoint #5: ");
    Serial.print(Home_LATarray[4],6);
    Serial.print(" ");
    Serial.println(Home_LONarray[4],6);

    wpCount++;                                                  // increment waypoint counter
    ac++;                                                       // increment array counter
        
  }         
  else {serail1.print("Waypoints Full");}*/
}

// ************************************************************************************************************************************************* 

void clearWaypoints()
{
   memset(Home_LATarray, 0, sizeof(Home_LATarray));             // clear the array
   memset(Home_LONarray, 0, sizeof(Home_LONarray));             // clear the array
   wpCount = 0;                                                 // reset increment counter to 0
   ac = 0;
   
   serial1.print("GPS Waypoints Cleared");                      // display waypoints cleared
  
}

void gpsInfo()                                                  // displays Satellite data to user
  {     
       getGPS();
   
        Distance_To_Home = TinyGPSPlus::distanceBetween(loc.lat,loc.lon,Home_LATarray[ac], Home_LONarray[ac]);  //Query Tiny GPS for Distance to Destination    
        Serial.print("Lat:");
        Serial.print(loc.lat,7);
        Serial.print(" Lon:");
        Serial.print(loc.lon,7);
        Serial.print(" ");
       
        Serial.print("Distance to Home ");
        Serial.println(Distance_To_Home);

  
  }
/*
void Output(MagnetometerRaw raw, MagnetometerScaled scaled, float heading, float headingDegrees)
{
   Serial.print("Raw:\t");
   Serial.print(raw.XAxis);
   Serial.print("   ");   
   Serial.print(raw.YAxis);
   Serial.print("   ");   
   Serial.print(raw.ZAxis);
   Serial.print("   \tScaled:\t");
   
   Serial.print(scaled.XAxis);
   Serial.print("   ");   
   Serial.print(scaled.YAxis);
   Serial.print("   ");   
   Serial.print(scaled.ZAxis);

   Serial.print("   \tHeading:\t");
   Serial.print(heading);
   Serial.print(" Radians   \t");
   Serial.print(headingDegrees);
   Serial.println(" Degrees   \t");
}
*/
