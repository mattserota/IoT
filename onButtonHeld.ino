


// duration reports back how long it has been since the button was originally pressed.
// repeatCount tells us how many times this function has been called by this button.

void onButtonHeld(Button& btn, uint16_t duration, uint16_t repeatCount){

        button1HeldFlag = true;
        
        Serial.print("button has been held for ");
        Serial.print(duration);
        Serial.print(" ms; this event has been fired ");
        Serial.print(repeatCount);
        Serial.println(" times");
        
}//END onButtonHeld
