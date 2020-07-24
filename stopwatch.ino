#include <LiquidCrystal.h> //the liquid cyrstal library
#include <math.h>

//for the stopwatch
int stopWatchMilli = 0; //milliseconds
int stopWatchSecond = 0;//seconds
int stopWatchMinute = 0;//minutes

// I had 4 buttons, one for Starting the stopwatch
int switchStartPin = 4; 
int switchStateStart = 0;

//Stopping the stopwatch
int switchStopPin = 5;
int switchStateStop = 0;

//Reseting the stopwatch
int switchResetPin = 6;
int switchStateReset = 0;

//Lapping it, a extra function that I wanted to add :)
int switchLapPin = 7;
int switchStateLap = 0;


//define the pins for the liquid crystal display
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);


//setup the pins and the liquid crystal display
void setup() {
  lcd.begin(16, 2);
  //don't want to do INPUT, instead, a press of the buttons are defined as INPUT_PULLUP
  pinMode(switchStartPin, INPUT_PULLUP);
  pinMode(switchStopPin, INPUT_PULLUP);
  pinMode(switchResetPin, INPUT_PULLUP);
  pinMode(switchLapPin, INPUT_PULLUP);
  lcd.setCursor(0, 0);
  //telling whoever is using this device that it is turned on
  lcd.print("StopWatch-");
  delay(2000);
  lcd.clear();
}

void loop() {

  //checking for the voltage from the buttons pins and putting the values into the switchStates
  switchStateStop = digitalRead(switchStopPin);
  switchStateReset = digitalRead(switchResetPin);
  switchStateLap = digitalRead(switchLapPin);
  switchStateStart = digitalRead(switchStartPin);

  //first, letting the liquid crystal display the 0:0:0s
  lcd.setCursor(0, 0);
  // put an "Elasped" in the front so it indicates that the timer is in stopwatch mode
  lcd.print("Elasped ");
  lcd.print(stopWatchMinute);
  lcd.print(":");
  lcd.print(stopWatchSecond);
  lcd.print(":");
  lcd.print(stopWatchMilli);

  //if the Start button is NOT pressed, do the things below(nothing)
  if (switchStateStart == HIGH) {
    stopWatchMilli = 0;
    stopWatchSecond = 0;
    stopWatchMinute = 0;
  }
  //if it is pressed - 
  else {
    //we are going to use a "for" loop, and the for loop is going to make the "stopWatchMilli" go from 0 to 100, cause no stopwatch as it going 0 to 1000
    for (stopWatchMilli = 0; stopWatchMilli <= 100; stopWatchMilli++) {
      //the delay 5 is just for the time it waits to change the current number on the "stopWatchMilli" value and waits for the arduino to finish the for loop
      delay(5);
      //switch back to 0 if the "milli" reaches 100
      if (stopWatchMilli == 100) {
        stopWatchMilli = 0;
        //and the "seconds" digit should add one
        stopWatchSecond += 1;

        //update the display by printing out the newest values
        lcd.setCursor(0, 0);
        lcd.print("Elasped ");
        lcd.print(stopWatchMinute);
        lcd.print(":");
        lcd.print(stopWatchSecond);
        lcd.print(":");
        lcd.print(stopWatchMilli);
      }
      //if the "seconds" value is 60, change it to 0 andd add one to the "minutes" value
      if (stopWatchSecond == 60) {
        lcd.clear();
        stopWatchSecond = 0;
        stopWatchMilli = 0;
        stopWatchMinute += 1;
        //update the liquid crystal with printing out the updated values
        lcd.setCursor(0, 0);
        lcd.print("Elasped ");
        lcd.print(stopWatchMinute);
        lcd.print(":");
        lcd.print(stopWatchSecond);
        lcd.print(":");
        lcd.print(stopWatchMilli);
      }

      lcd.setCursor(0, 0);
      lcd.print("Elasped ");
      lcd.print(stopWatchMinute);
      lcd.print(":");
      lcd.print(stopWatchSecond);
      lcd.print(":");
      lcd.print(stopWatchMilli);

      //now for the stop, reset and lap functions we have to check for the voltage again because we are NOT coming out of this "for" loop
      switchStateStop = digitalRead(switchStopPin);
      switchStateReset = digitalRead(switchResetPin);
      switchStateLap = digitalRead(switchLapPin);

      //stop function, just stops it until the switchStateStart is LOW again and gets out of the while loop
      if (switchStateStop == LOW) {
        while(switchStateStop == LOW){
          switchStateStart = digitalRead(switchStartPin);
          //updates the current values to the newest without any FURTHER changes
          lcd.setCursor(0, 0);
          lcd.print("Elasped ");
          lcd.print(stopWatchMinute);
          lcd.print(":");
          lcd.print(stopWatchSecond);
          lcd.print(":");
          lcd.print(stopWatchMilli);
          if (switchStateStart == LOW) {
            lcd.clear();
            //break out of the "while" loop because you can't just break out of the "if" statement, because it's not a loop
            break;
          }
        }
      }

      //the lap function was surprising simple, I though it was going to be hard, LOL
      //check for the voltage on the "lap" pin
      switchStateLap = digitalRead(switchLapPin);
      if(switchStateLap == LOW){
          //put th value on the bottom line
          //update the current numbers
          lcd.setCursor(0, 1);
          lcd.print("Lapped ");
          lcd.print(stopWatchMinute);
          lcd.print(":");
          lcd.print(stopWatchSecond);
          lcd.print(":");
          lcd.print(stopWatchMilli);
      }
      

      //reset is basically setting the "Elasped" time to 0
      //if I press the button, then it goes back to 0
      switchStateReset = digitalRead(switchResetPin);
      if (switchStateReset == LOW) {
        //and updates the new values to the display
        lcd.setCursor(0, 0);
        lcd.print("Elasped ");
        lcd.print("0");
        lcd.print(":");
        lcd.print("0");
        lcd.print(":");
        lcd.print("0");
        switchStateStart = digitalRead(switchStartPin);
        if (switchStateStart == LOW) {
          stopWatchMinute = 00;
          stopWatchSecond = 00;
          stopWatchMilli = 00;
          lcd.clear();
          break;
        }
      }
    }
  }
}
