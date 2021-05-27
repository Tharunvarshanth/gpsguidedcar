//**************************************************************************************************************************************************
// This procedure reads the serial port - Serial1 - for bluetooth commands being sent from the Android device

void wifimodule()
{
  WiFiClient client = server.available();
 if (client)  {                                  // Read bluetooth commands over Serial1 // Warning: If an error with Serial1 occurs, make sure Arduino Mega 2560 is Selected
     serial.println("new client");
     currentLine ="";
     while(client.connected(){
         if(client.available()){
            char c = client.read();
            if(c=='\n'){
               if(currentLine.length()==0){
                  client.println("HTTP\1.1 200 OK");
                  client.println("Content-type:text/html");
                  client.println();
                  client.print("valua  at A0 is");
                  client.print(analogRead(A0));
                  client.print("<br>");
                  //The HTTP Response ends with another blank line:
                  client.println();
            // break out of the while loop
                  break;
               }else{
                currentLine = "";
                }
           }else if(c!=='\r') {       
               currentLine + = c;
               }
           
             // Actions started
           // Check to see if the client request was "GET /H" or "GET /L":
              if(currentLine.endsWith("GET/1")){
                    setWaypoint();
               }
              if(currentLine.endsWith("GET/2"){
                     goWaypoint();
               } 
               if(currentLine.endsWith("GET/3"){
                     MoveStop();
               }
               if(currentLine.endsWith("GET/4"){
                     gpsInfo();
               }
               if(currentLine.endsWith("GET/5"){
                     pingToggle();
               }
               if(currentLine.endsWith("GET/6"){
                 clearWaypoints();
               }
               if(currentLine.endsWith("GET/7"){
                  // finish with waypoints
                      ac = 0;
                      Serial.print("Waypoints Complete");
               }
               if(currentLine.endsWith("GET/8"){
                 MoveForward()
               }
               if(currentLine.endsWith("GET/9"){
                 MoveBackward();
               }
               if(currentLine.endsWith("GET/10"){
                 TurnRight();
               }
               if(currentLine.endsWith("GET/11"){
                 TurnLeft();
               }
               
           
        }  //if(client.available()) 

           
       }//while loop ended
                    //CLOSE THE CONNECTION
                   client.stop();
                   serial.println("client disconnect");
  } //client end  
  else{
    Serial.println("Client Not Available");
  }
    
                         

// **************************************************************************************************************************************************
/*
 switch (currentLine.endsWith("GET/H").toInt()) 
 {
      case 1:                                
        Serial1.println("Forward");
        Forward();
        break;

      case 2:                 
        Serial1.println("Reverse");
        Reverse();
        break;

      case 3:         
        Serial1.println("Left");
        LeftTurn();
        StopCar();
        break;
        
      case 4:                     
        Serial1.println("Right");
        RightTurn();
        StopCar();
        break;
        
      case 5:                                            
        Serial1.println("Stop Car ");
        StopCar();
        break; 

      case 6:                 
        setWaypoint();
        break;
      
      case 7:        
        goWaypoint();
        break;  
      
      case 8:        
        Serial1.println("Turn Around");
        turnAround();
        break;
      
      case 9:        
         Serial1.println("Compass Forward");
        setHeading();
        Compass_Forward();
        break;
      
      case 10:
        setHeading();
        break; 

      case 11:
         gpsInfo();
        break;
      
      case 12:  
        Serial1.println("Compass Turn Right");
        CompassTurnRight();
        break;
      
      case 13:  
        Serial1.println("Compass Turn Left");
        CompassTurnLeft();
        break;
        
      case 14:  
        Serial1.println("Calibrate Compass");
        calibrateCompass();
        break;

      case 15:  
        pingToggle();
        break;  

      case 16:
        clearWaypoints();
        break;  

      case 17:                    // finish with waypoints
        ac = 0;
        Serial1.print("Waypoints Complete");
        break;
      

 } 
*/
// **************************************************************************************************************************************************  
// Slider Value for Speed
/*
if (blueToothVal)                                    
  {    
   //Serial.println(blueToothVal);
  if (blueToothVal >= 1000)
{
    Serial1.print("Speed set To:  ");
    Serial1.println(blueToothVal - 1000);
    turn_Speed = (blueToothVal - 1000); 
    Serial.println();
    Serial.print("Turn Speed ");
    Serial.println(turn_Speed);
 } 
  }  
*/
/*

// **************************************************************************************************************************************************
// Detect for Mines - Sweep Not Used

 else if (blueToothVal== 15)                                   
  {    
    Serial1.println("Detecting");
    sweep();
  }

// **************************************************************************************************************************************************  
*/
  
} // end of bluetooth procedure
