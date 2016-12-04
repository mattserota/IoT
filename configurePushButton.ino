

// Use this function to configure the internal Bounce object to suit you. See the documentation at: https://github.com/thomasfredericks/Bounce2/wiki
// This function can be left out if the defaults are acceptable - just don't call configureButton

void configurePushButton(Bounce& bouncedButton){
    
        // Set the debounce interval to 15ms - default is 10ms
        bouncedButton.interval(debounceInterval);
        
}//END configurePushButton()
