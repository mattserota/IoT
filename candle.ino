void candle(int pixel){
  
  int flickerRate = 1*numShowFlakes;
  
  if(random(0, 200) < flickerRate){
      int r = 200;
      int g = r-30;
      int b = 70;
      int flicker = random(0,150);
      int r1 = r-flicker;
      int g1 = g-flicker;
      int b1 = b-flicker;
      if(g1<0) g1=0;
      if(r1<0) r1=0;
      if(b1<0) b1=0;
      pixels.setPixelColor(pixel, r1, g1, b1);
      pixels.show();
  }

}
