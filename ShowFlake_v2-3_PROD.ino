/***************************************************************************************************************************************************
 * ShowFlake Workshop
 * by Matt Garfield / NextFab
 * 12/3/2016
 * 
 * Hardware:
 * --------
 *    - ShowFlake v1.2 PCB
 *    - Arduino Nano
 *    - WS2812 "Smart" RGB LEDs (a.k.a. NeoPixels)
 *    - Additional Components Kit
 * 
 * Description:
 * -----------
 * ShowFlake is a a snowflake shaped PCB with a customizable, winter-themed lightshow. ShowFlake includes (6) "Smart" RGB LEDs and comes
 * with a variety of pre-programmed lightshows such as "SnowFall", "HolidayString", "Candle", "Christmas", "Hanukkah", "CandyCane", and "Off".
 * ShowFlake is expandable, allowing for additional lightshows to be added using the Arduino IDE.
 * 
 * Operating Instructions:
 * ----------------------
 *    - Power ShowFlake by either:
 *          - 5V USB Mini-B Cable plugged directly into Arduino Nano
 *          - 7 to 12 V DC Barrel Jack 
 *    
 *    - ShowFlake will being playing a lightshow automatically     
 *    
 *    - Short-Press the button to cyle through lightshows
 *    
 *    - Press-and-Hold the button to enter Setup Mode
 *        - While in Setup Mode, ShowFlake will display the number of ShowFlakes selected in the chain
 *        - Short-Press the button to increment the number of ShowFlakes in the chain
 *        - You can chain up to 6 ShowFlakes
 *        - Press-and-Hold the Button to save the number of ShowFlakes selected and return to the lightshow
 *        
 *    - ShowFlake will remember the settings you selected (lightshow and number of ShowFlakes) even after Power is removed
 *    
*************************************************************************************************************************************************/

/* *********************************
********** Libraries ***************
*************************************/

//Pixel Library
#include <Adafruit_NeoPixel.h>

//Button Libraries
//https://github.com/r89m/Button
#include <Button.h>
#include <ButtonEventCallback.h>
#include <PushButton.h>
#include <Bounce2.h>    // https://github.com/thomasfredericks/Bounce-Arduino-Wiring

//Memory Library
#include <EEPROM.h>

/* *********************************
******** Global Defines **********
*************************************/
#define BTN1_PIN        2
#define PIXEL_PIN       7
#define LED_PIN         13

/* *********************************
******** Global Variables **********
*************************************/

//Pixel Variables
int numShowFlakes = 1;
int pixPerFlake = 6;
int numPixels = pixPerFlake*numShowFlakes;
int maxNumShowFlakes = 6;
int maxNumPixels = pixPerFlake*maxNumShowFlakes;

int maxBri = 180;           //able to set limit of maximum brightness value
int pixelIndex = -1;       //index of pixel in array of pixels, initialized to -1 for first run

unsigned int showScene = 1;
unsigned int totalScenes = 6;

//Array of values to hold max number of pixel data (6*6 = 36)
int hueArray[36];            //range from 0 (red) to 767 (back to red)
byte satArray[36]; 
byte briArray[36];

byte rgbByteArray[3];       //Array to hold RGB color values set by hsb2rgb()

//Button Variables
boolean button1PressedFlag = false;
boolean button1HeldFlag = false;
boolean button1ReleasedFlag = false;
unsigned int debounceInterval = 15; //ms
unsigned int buttonHoldThreshold = 2000; //ms

unsigned long timeSnap = 0;
boolean toggle = true;

//Memory Variables
int addr_numShowFlakes = 0;
int addr_showScene = 2;

/****************************************
******* Object Initialization ***********
****************************************/

// Create an instance of PushButton reading digital pin 2
PushButton button1 = PushButton(BTN1_PIN, ENABLE_INTERNAL_PULLUP);

//nameOflibrary yourPixel nameOflibrary(# of pixels, pin pixel is attached to, order of colors + frequency of bitstream)
Adafruit_NeoPixel pixels = Adafruit_NeoPixel (maxNumPixels, PIXEL_PIN, NEO_RGB + NEO_KHZ800); 
/*
    pixels.show();
        update display color values that have been stored for pixels
    
    pixels.clear( );
        clears all settings for the Object, does not retain previous pixel value
    
    pixels.setPixelColor( [ Pixel Number (16-bit)], [ Red Value (8-bit, 0 - 255) ], [ Green Value (8-bit, 0 - 255) ], [ Blue Value (8-bit, 0 - 255) ] );
        Set the color value for the designated pixel number. Multiple ways to define color value.
    
    pixels.numPixels();
        Returns the number of LEDs declared in the Object, aka Array Size
        
    pixels.setBrightness( [ Brightness Value (8-bit, 0 - 255) ] );
        scales the perceived Brightness of all the pixels in the Object
*/


/*************************
******** Setup ********
**************************/

void setup() {

    pinMode(LED_PIN, OUTPUT);
    
    // Open up the serial port so that we can write to it
        Serial.begin(9600);
    
    //*** Initialize Pixels
        pixels.begin();
        pixels.clear();
        pixels.show();

    //*** Initialize Arrays
        for(int i=0; i < (pixPerFlake * maxNumShowFlakes); i++){
          hueArray[i] = 0;
          satArray[i] = 0;
          briArray[i] = 0;
        }
    
        for(int i=0; i < 3; i++){
          rgbByteArray[i] = 0;
        }

    //*** Setup Button Object Functions
        // Configure the button as you'd like - not necessary if you're happy with the defaults
        button1.configureButton(configurePushButton);
    
        // When the button is first pressed, call the function onButtonPressed (further down the page)
        button1.onPress(onButtonPressed);
    
        // Once the button has been held for 1 second (1000ms) call onButtonHeld. Call it again every 0.5s (500ms) until it is let go
        button1.onHoldRepeat(buttonHoldThreshold, buttonHoldThreshold/2, onButtonHeld);
        
        // When the button is released, call onButtonReleased
        button1.onRelease(onButtonReleased);  
    
    //** Memory Check
        int memCheck_numShowFlakes = EEPROM.read(addr_numShowFlakes);
        Serial.print("memCheck_numShowFlakes: ");
        Serial.println(memCheck_numShowFlakes);
        if(memCheck_numShowFlakes <= maxNumShowFlakes){
          numShowFlakes = memCheck_numShowFlakes;
          numPixels = pixPerFlake*numShowFlakes;
        }

        int memCheck_showScene = EEPROM.read(addr_showScene);
        Serial.print("memCheck_showScene: ");
        Serial.println(memCheck_showScene);
        if(memCheck_showScene <= totalScenes){
          showScene = memCheck_showScene;
        }
    
}//END setup()

/****************************************
**************** Loop *******************
*****************************************/

void loop() {
     
      button1.update();   // Check the state of button1

      // If button is pressed and held (without being released),
      // Go to Settings Mode
      if (button1PressedFlag && button1HeldFlag && !button1ReleasedFlag){
  
          button1PressedFlag = false;
          button1HeldFlag = false;
          
          settingsMode();
      } 
      
      // If button is pressed and released (without being held),
      // Increment ShowScene
      if (button1PressedFlag && button1ReleasedFlag && !button1HeldFlag){
          
          button1PressedFlag = false;
          button1ReleasedFlag = false;
          
          if(showScene < totalScenes){
            showScene++;
          }
          else{showScene = 0;}
          
          EEPROM.write(addr_showScene, showScene);  // Save to memory
          
          Serial.print("showScene: ");
          Serial.println(showScene);
      }
  
     // if pixelIndex is outside the range of available pixels, reset to zero
     if (pixelIndex < 0 || pixelIndex >= numPixels-1){
        pixelIndex = 0;
     }
     // otherwise, increment to the next pixelIndex
     else {
        pixelIndex++;
     }

     // Select Lightshow
     switch (showScene) {
        case 1:
            snowfall(pixelIndex);
            break;
        case 2:
            holidayString(pixelIndex);
            break;
        case 3:
            candle(pixelIndex);
            break;
        case 4:
            christmas(pixelIndex);
            break;
        case 5:
            hanukkah(pixelIndex);
            break;
        case 6:
            candyCane(pixelIndex);
            break;
        default:
            pixels.clear();
            pixels.show();
            break;
     }

} //END Loop()


