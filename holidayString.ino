void holidayString (int pixel){

  if(pixel%pixPerFlake == 5){pixels.setPixelColor( pixel, maxBri, 0, 0);}                     //red
  else if(pixel%pixPerFlake == 4){pixels.setPixelColor( pixel, 0, maxBri, 0);}                //green
  else if(pixel%pixPerFlake == 3){pixels.setPixelColor( pixel, (4*maxBri)/5, maxBri/5, 0);}   //orange
  else if(pixel%pixPerFlake == 2){pixels.setPixelColor( pixel, maxBri/2, 0, maxBri/2);}       //purple
  else if(pixel%pixPerFlake == 1){pixels.setPixelColor( pixel, (2*maxBri)/3, maxBri/3, 0);}   //yellow
  else if(pixel%pixPerFlake == 0){pixels.setPixelColor( pixel, 0, 0, maxBri);}                //blue
  
  pixels.show();
}
