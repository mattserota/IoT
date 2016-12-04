

// duration reports back the total time that the button was held down
void onButtonReleased(Button& btn, uint16_t duration){

        button1ReleasedFlag = true;
        
        Serial.print("button released after ");
        Serial.print(duration);
        Serial.println(" ms");
        
}//END onButtonReleased()
