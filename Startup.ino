//Finished
void Startup()
{
    // myservo.detach(); 
     Serial.println("Pause for Startup... ");
             
     for (int i=5; i >= 1; i--)                       // Count down for X seconds
      {         
        Serial.print("Pause for Startup... "); 
        Serial.print(i);
        delay(1000);                                   // Delay for X seconds
      }    
    
  serial1.println("Searching for wifi "); 
  serial.println("Searching for wifi "); 
      
                             
    getGPS();                                         // Update gps data
          
    wifimodule();//connect with mobile app call wifimmodule bluetooth();                                      // Check to see if there are any bluetooth commands being received     

  setWaypoint();                                      // set intial waypoint to current location
  wpCount = 0;                                        // zero waypoint counter
  ac = 0;                                             // zero array counter
  
  
}    
 
