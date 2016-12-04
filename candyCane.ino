void candyCane(int pixel){

    int hueVal = 0;   //red
    int satVal;
    
    // periodically flip candyCaneToggle
    if(millis() - timeSnap > 500){
      timeSnap = millis();
      toggle = !toggle;                                         
    }

     
    if(toggle){                        // if toggle is true,
      if(pixel%2 == 0){satVal = 255;}  // and if pixel is even, full color saturation
      else{satVal = 0;}                // if pixel is odd, no color saturation (white)
    }
    else {                             // if toggle is false,
      if(pixel%2 == 0){satVal = 0;}    // and if pixel is even, no color saturation (white)
      else{satVal = 255;}              // if pixel is odd, full color saturation
    }

    hsb2rgb(hueVal, satVal, maxBri, rgbByteArray);
    pixels.setPixelColor( pixel, rgbByteArray[0], rgbByteArray[1], rgbByteArray[2] );   // use RGB bytes to set pixel colors
    pixels.show();
}
