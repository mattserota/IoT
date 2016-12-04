

// btn is a reference to the button that fired the event. That means you can use the same event handler for many buttons

void onButtonPressed(Button& btn){

        if(btn.is(button1))
        {
          Serial.print("Button 1 Pressed ");
          button1PressedFlag = true;
        }
        
        else
        {
           Serial.print("Hmmm, no button was");
        }

}//END onButtonPressed()
