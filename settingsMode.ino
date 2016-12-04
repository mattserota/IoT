void settingsMode(){
  Serial.println("Enter Settings Mode");

  // LED's go dark
  pixels.clear();
  pixels.show();

  while(!button1ReleasedFlag){    //wait until button1 released

      button1.update();   // Check the state of button1
      
      // Flash onboard LED
      digitalWrite(LED_PIN, HIGH);
      delay(50);
      digitalWrite(LED_PIN, LOW);
      delay(50);
  }

  // clear button1 Flags
  button1ReleasedFlag = false;
  button1PressedFlag = false;
  button1HeldFlag = false;

  while(!button1HeldFlag){   //while button1 has NOT been held down (again)
    
    button1.update();   // Check the state of button1

    // If button is pressed and released (without being held),
    // Increment Number of ShowFlakes
    if (button1PressedFlag && button1ReleasedFlag && !button1HeldFlag){
        
        button1PressedFlag = false;
        button1ReleasedFlag = false;
        
        if(numShowFlakes < maxNumShowFlakes){
          numShowFlakes++;
        }
        else{
          numShowFlakes = 1;
          pixels.clear();
          pixels.show();
        }

        EEPROM.write(addr_numShowFlakes, numShowFlakes);    // Save to memory

        Serial.print("numShowFlakes: ");
        Serial.println(numShowFlakes);
    }

    // Breathe LED's to indicate numShowFlakes
    
    for(int i=20; i < 70; i++){
      hsb2rgb(0, 0, i, rgbByteArray);
      for(int j=0; j < numShowFlakes; j++){   
          pixels.setPixelColor( j, rgbByteArray[0], rgbByteArray[1], rgbByteArray[2] );  
      }
      button1.update();   // Check the state of button1
      pixels.show();
    }
    
    for(int i=70; i > 20; i--){
      hsb2rgb(0, 0, i, rgbByteArray);
      for(int j=0; j < numShowFlakes; j++){
          pixels.setPixelColor( j, rgbByteArray[0], rgbByteArray[1], rgbByteArray[2] );  
      }
      button1.update();   // Check the state of button1
      pixels.show();
      delay(5);
    }
          
  }// END while()

  pixels.clear();
  pixels.show();
  
  while(!button1ReleasedFlag){    //wait until button1 released

      button1.update();   // Check the state of button1
      
      digitalWrite(LED_PIN, HIGH);
      delay(50);
      digitalWrite(LED_PIN, LOW);
      delay(50);
  }

  // clear button1 Flags
  button1ReleasedFlag = false;    
  button1PressedFlag = false;
  button1HeldFlag = false;

  numPixels = pixPerFlake*numShowFlakes;    // Update numShowFlakes

  Serial.println("Exit Settings Mode");
}
