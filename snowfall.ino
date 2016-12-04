void snowfall(int pixel){
    float snowFallRate = 0.003;
    float snowFadeRate = 0.03;

    if (briArray[pixel] <= 0){                                                          // if pixel is dark
      if ( float(random(0, maxBri)) < float(maxBri)*snowFallRate){                      // test probability of a new snowflake
        briArray[pixel] = maxBri;                                                       // if yes, generate new snowflake
      }
    }
    else{                                                                               // if pixel has a brightness value > 0
      //briArray[pixel] = byte(float(briArray[pixel]) - (maxBri*snowFadeRate));         // reduce brightness by snowFadeRate
      briArray[pixel] = byte(briArray[pixel] - (briArray[pixel]*snowFadeRate));
    }

    hsb2rgb(0, 0, briArray[pixel], rgbByteArray);                                       // convert HSB values to RGB
    pixels.setPixelColor( pixel, rgbByteArray[0], rgbByteArray[1], rgbByteArray[2] );   // use RGB bytes to set pixel colors
    pixels.show();
}
