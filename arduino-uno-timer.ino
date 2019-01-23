/************************************************************************************************************
 * 
 * Authors: Julia Owsen
 * Date: 31 May 2017
 * Title: Arduino Uno Timer
 * Code for the Arduino Uno board. This program uses a four-digit seven segment diplay to show the time 
 * passed (in seconds). Counts down from 30 seconds. If the button is ever pressed, the timer will reset to
 * 30. Once the timer counts down to zero, the active buzzer plays a tone. 
 * 
 ************************************************************************************************************
 */

#include <SevSeg.h> //library for the seven segment component

SevSeg sevseg; //initiallizing seven segment

//lowercase letter variables below represent the segment pins - one for each of seven segments:
byte a = 11;
byte b = 7; 
byte c = 4;
byte d = 2;
byte e = 1;
byte f = 10;
byte g = 5;

//the four variables below represent each of the four digits (the digit pins):
byte D1 = 12;
byte D2 = 9;
byte D3 = 8;
byte D4 = 6; 

unsigned long millisVal = 0; //value that will display on the seven segment after time has passed
int buzzer = A0; //buzzer pin
int buttonPin = A1; //button pin
int buttonState = 0; //variable to keep track of whether or not button has been pushed
int startCount = 30; //start the timer at 30 seconds
boolean playBuzzer = true; //indicates when to play buzzzer

void setup() {
  byte numDigits = 4;
  byte digitPins[] = {D1, D2, D3, D4};
  byte segmentPins[] = {a, b, c, d, e, f, g};
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins); //start seven segment with values given
  sevseg.setBrightness(90);
  pinMode(buzzer, OUTPUT); //initiallize buzzer
  pinMode(buttonPin, INPUT); //initiallize button
}

void loop() {
     buttonState = digitalRead(buttonPin); //keep track of whether button has been pressed
     millisVal = startCount - millis()/1000; //get current value for timer based on milliseconds passed
     if(buttonState == HIGH) { //if button has been pressed
        startCount = 30 + (millis()/1000);
        millisVal = startCount - millis()/1000; //restart timer count
        playBuzzer = true; //allow the buzzer to play
     }
     if (millisVal <= -1) { //once the timer hits zero
        sevseg.setNumber(0000, 3);
        sevseg.refreshDisplay();
        if (playBuzzer == true) { //play the buzzer once
          tone(buzzer, 1000);
          delay(600);
          noTone(buzzer);
          playBuzzer = false;
          sevseg.setNumber(0000, 3);
          sevseg.refreshDisplay();
        } 
      } else { //if the timer is not yet at zero, display current value
        sevseg.setNumber(millisVal, 3);
        sevseg.refreshDisplay();
      }
}
