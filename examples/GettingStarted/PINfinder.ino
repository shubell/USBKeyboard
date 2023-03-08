/**************************************************************************
 *
 * Original File: GettingStarted.ino
 * Modified File: PINfinder.ino
 * Original Author: Julian Schuler (https://github.com/julianschuler)
 * License: GNU GPLv3, see LICENSE.txt
 * Description: This file is an example from the USBKeyboard library.
 *              It types in a message after pressing a button and shows
 *              the state of Caps Lock with the internal LED.
 *
 **************************************************************************/

#include <USBKeyboard.h>

/* connect a button to this pin and GND */
#define BUTTON_PIN 7

/* currently available layouts: LAYOUT_US, LAYOUT_DE */
#define LAYOUT LAYOUT_US


/* create keyboard object mKeyboard */
USBKeyboard mKeyboard = USBKeyboard();

bool lastButtonState = HIGH;
bool lastCapsLockState;
int cifra = 9999;

void setup() {
	/* USB timing has to be exact, therefore deactivate Timer0 interrupt */
 Serial.begin(57600);
	TIMSK0 = 0;

	/* initialize the keyboard */
	mKeyboard.begin();
	
	/* set the button pin as input and activate the internal pullup resistor */
	pinMode(BUTTON_PIN, INPUT_PULLUP);
	
	/* set the internal LED pin (normally D13) as output */
	pinMode(LED_BUILTIN, OUTPUT);
	
	/* set the internal LED corresponding to the Caps Lock state */
	if (mKeyboard.isCapsLockActivated()) {
		digitalWrite(LED_BUILTIN, HIGH);
		lastCapsLockState = HIGH;
	}
	else {
		digitalWrite(LED_BUILTIN, LOW);
		lastCapsLockState = LOW;
	}
}


void loop() {
	/* call this function at least every 20ms, otherwise an USB timeout will occur */
	mKeyboard.update();
	/* check if button is pressed */
  
	if (digitalRead(BUTTON_PIN) == LOW) {
		
			/* print() and println() can be used to type in chars, Strings
       *      prvi.toCharArray(myString, 4);
			 * and numbers, similar to Serial.print() and Serial.println() */
      String prvi = String(cifra);
      char myString[5];
      prvi.toCharArray(myString, 5);
      Serial.println(prvi);
      for (char element : myString) { // for each element in the array
        if (element == '0'){
          mKeyboard.sendKey(mKeyboard.asciiToKeycode('0'));
          }
        if (element == '1'){
          mKeyboard.sendKey(mKeyboard.asciiToKeycode('1'));
          }
          if (element == '2'){
          mKeyboard.sendKey(mKeyboard.asciiToKeycode('2'));
          }
          if (element == '3'){
          mKeyboard.sendKey(mKeyboard.asciiToKeycode('3'));
          }
          if (element == '4'){
          mKeyboard.sendKey(mKeyboard.asciiToKeycode('4'));
          }
          if (element == '5'){
          mKeyboard.sendKey(mKeyboard.asciiToKeycode('5'));
          }
          if (element == '6'){
          mKeyboard.sendKey(mKeyboard.asciiToKeycode('6'));
          }
          if (element == '7'){
          mKeyboard.sendKey(mKeyboard.asciiToKeycode('7'));
          }
          if (element == '8'){
          mKeyboard.sendKey(mKeyboard.asciiToKeycode('8'));
          }
          if (element == '9'){
          mKeyboard.sendKey(mKeyboard.asciiToKeycode('9'));
          }
         
            
        
      }
      mKeyboard.sendKey( 0x28);
    cifra = cifra -1;
     /* mKeyboard.sendKeys(mKeyboard.asciiToKeycode( myString[0]),mKeyboard.asciiToKeycode(myString[1]),mKeyboard.asciiToKeycode(myString[2]),mKeyboard.asciiToKeycode(myString[3]),0,0,0);*/
      delay(100000);
	}
	else if (lastButtonState == LOW) {
		lastButtonState = HIGH;
	}
			
	/* check if the Caps Lock state has changed */
	if (mKeyboard.isCapsLockActivated() != lastCapsLockState) {
		/* toggle lastCapsLockState */
		lastCapsLockState = !lastCapsLockState;
		
		/* toggle LED state */
		digitalWrite(LED_BUILTIN, lastCapsLockState);
	}
	
	/* due to the deactivation of the Timer0 interrupt, delay()
	 * and millis() won't work, call delayMicroseconds() instead */
	delayMicroseconds(20000);
}
