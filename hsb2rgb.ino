void hsb2rgb(uint16_t hue_HSB, uint8_t sat_HSB, uint8_t bri_HSB, uint8_t rgbArray[3]) {
/*
https://blog.adafruit.com/2012/03/14/constant-brightness-hsb-to-rgb-algorithm/
accepts hue, saturation and brightness values and outputs three 8-bit color values in an array (color[])
saturation (sat_HSB) and brightness (bri_HSB) are 8-bit values.
hue (hue_HSB) is a value between 0 and 767
hue values out of range are rendered as 0.

*/
      uint16_t r_temp, g_temp, b_temp;
      uint8_t hue_mod_HSB;
      uint8_t inverse_sat_HSB = (sat_HSB ^ 255);
    
      hue_HSB = hue_HSB % 768;
      hue_mod_HSB = hue_HSB % 256;
    
      if (hue_HSB < 256)
      {
        r_temp = hue_mod_HSB ^ 255;
        g_temp = hue_mod_HSB;
        b_temp = 0;
      }
    
      else if (hue_HSB < 512)
      {
        r_temp = 0;
        g_temp = hue_mod_HSB ^ 255;
        b_temp = hue_mod_HSB;
      }
    
      else if ( hue_HSB < 768)
      {
        r_temp = hue_mod_HSB;
        g_temp = 0;
        b_temp = hue_mod_HSB ^ 255;
      }
    
      else
      {
        r_temp = 0;
        g_temp = 0;
        b_temp = 0;
      }
    
      r_temp = ((r_temp * sat_HSB) / 255) + inverse_sat_HSB;
      g_temp = ((g_temp * sat_HSB) / 255) + inverse_sat_HSB;
      b_temp = ((b_temp * sat_HSB) / 255) + inverse_sat_HSB;
    
      r_temp = (r_temp * bri_HSB) / 255;
      g_temp = (g_temp * bri_HSB) / 255;
      b_temp = (b_temp * bri_HSB) / 255;
    
      rgbArray[0]  = (uint8_t)r_temp;
      rgbArray[1]  = (uint8_t)g_temp;
      rgbArray[2] = (uint8_t)b_temp;
      
}//END hsb2rgb()
