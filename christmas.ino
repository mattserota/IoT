void christmas(int pixel){

    int hueVal = 0;   //red
    int satVal;
    
    // periodically flip candyCaneToggle
    if(millis() - timeSnap > 500){
      timeSnap = millis();
      toggle = !toggle;                                         
    }
     
    if(toggle){                                             // if toggle is true, and
      if (pixel%3 == 0){satVal = 255; hueVal = 0;}          // if pixel is 3, red
      else if (pixel%3 == 1) {satVal = 255; hueVal = 256;}  // if pixel is 2, green
      else {satVal = 0;}                                    // else white
    }
    else {                                                  // if toggle is false,
      if (pixel%3 == 0) {satVal = 0;}                       // if pixel is 3, white
      else if (pixel%3 == 1) {satVal = 255; hueVal = 0;}    // if pixel is 2, red
      else {satVal = 255; hueVal = 256;}                    // else green
    }

    hsb2rgb(hueVal, satVal, maxBri, rgbByteArray);
    pixels.setPixelColor( pixel, rgbByteArray[0], rgbByteArray[1], rgbByteArray[2] );   // use RGB bytes to set pixel colors
    pixels.show();
}

