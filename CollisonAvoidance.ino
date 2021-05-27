int readPing(){

  delay(70);
  int cm = sonar_distancesensor.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

void Ping()
{  
   if ( (pingOn == true)) 
 {
                 // convert the time into a distance
  Ping_distance == readPing(); 
 
    if ( (Ping_distance < 12) )
      {
        Serial1.print("Crash! ");
        Serial1.println(inches);
        MoveBackward();                                        // Quick reverse to Stop quickly
        delay(100);
        MoveStop();   
        currentLine + = "GET/3";                                 // Set bluetooth value to "Stop"
      } 
  
  }       // end if statement
 
} 

void pingToggle()                                         // Turns Collision avoidance on/ off
 {
  if (pingOn == true) {
    pingOn = false;
    Serial.print("Collision Avoidance OFF");
  }
    else if (pingOn == false) {
    pingOn = true;
    Serial.print("Collision Avoidance ON");
  }
  
 }

 
