void gowaypoint(){
  Serial.println("Go to Waypoint");
while (true)  
  {                                                                // Start of Go_Home procedure 
  wifimodule;                                                     // Run the Bluetooth procedure to see if there is any data being sent via BT
  if (currentLine.endswith("GET/3"){break;}                                   // If a 'Stop' Bluetooth command is received then break from the Loop
  getCompass();                                                    // Update Compass heading                                          
  getGPS();                                                        // Tiny GPS function that retrieves GPS data - update GPS location// delay time changed from 100 to 10
  

  Distance_To_Home = TinyGPSPlus::distanceBetween(loc.lat,loc.lon,Home_LATarray[ac], Home_LONarray[ac]);  //Query Tiny GPS for Distance to Destination    
  GPS_Course = TinyGPSPlus::courseTo(loc.lat,loc.lon,Home_LATarray[ac],Home_LONarray[ac]);                               //Query Tiny GPS for Course to Destination   
   
   /*
    if (Home_LATarray[ac] == 0) {
      Serial1.print("End of Waypoints");
      StopCar();      
      break;
      }      
   */ 
    if (Distance_To_Home == 0)                                   // If the Vehicle has reached it's Destination, then Stop
        {
        MoveStop();                                               // Stop the robot after each waypoint is reached
        Serial1.println("You have arrived!");                    // Print to Bluetooth device - "You have arrived"          
        ac++;                                                    // increment counter for next waypoint
        break;                                                   // Break from Go_Home procedure and send control back to the Void Loop 
                                                                 // go to next waypoint
        
        }   
   
   
   if ( abs(GPS_Course - compass_heading) <= 15)                  // If GPS Course and the Compass Heading are within x degrees of each other then go Forward                                                                  
                                                                  // otherwise find the shortest turn radius and turn left or right  
       {
         MoveForward();                                               // Go Forward
       } else 
         {                                                       
            int x = (GPS_Course - 360);                           // x = the GPS desired heading - 360
            int y = (compass_heading - (x));                      // y = the Compass heading - x
            int z = (y - 360);                                    // z = y - 360
            
            if ((z <= 180) && (z >= 0))                           // if z is less than 180 and not a negative value then turn left otherwise turn right
                  { TurnLeft();  }
             else { TurnRight(); }               
        } 
    

  }                                                              // End of While Loop

  
}      
