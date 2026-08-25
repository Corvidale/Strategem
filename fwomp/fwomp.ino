#include "Arduino.h"

//////////////// Varaibles
String code = "";
int count = 0;
bool on = false;
bool locked = false;

const int rightButton = 3;
const int rightLed = rightButton-1;
int rightPrevState = LOW;
const int leftButton = 9;
const int leftLed = leftButton-1;
int leftPrevState = LOW;
const int upButton = 5;
const int upLed = upButton-1;
int upPrevState = LOW;
const int downButton = 7;
const int downLed = downButton-1;
int downPrevState = LOW;

const int onButton = A1;
const int onLed = A0;
int onPrevState = LOW;


//////////////// Initate buttons and lights
void setup() {
  pinMode(rightButton, INPUT);
  pinMode(leftButton, INPUT);
  pinMode(upButton, INPUT);
  pinMode(downButton, INPUT);

  pinMode(rightLed, OUTPUT);
  pinMode(leftLed, OUTPUT);
  pinMode(upLed, OUTPUT);
  pinMode(downLed, OUTPUT);

  pinMode(onButton, INPUT);
  pinMode(onLed, OUTPUT);

  Serial.begin(9600);

  digitalWrite(rightLed, LOW);
  digitalWrite(leftLed, LOW);
  digitalWrite(upLed, LOW);
  digitalWrite(downLed, LOW);
  digitalWrite(onLed, LOW);
}

//////////////// the main thingy that runs over and over
void loop() {
  int upState = digitalRead(upButton);
  int downState = digitalRead(downButton);    // getting the state of the button aka if it is pressed down or not
  int rightState = digitalRead(rightButton);
  int leftState = digitalRead(leftButton);
  int onState = digitalRead(onButton);
  bool left = false;
  bool right = false;   // this is for the lights to help keep track of which should be on and which shouldn't
  bool up = false;
  bool down = false;



  if (onState == HIGH && onPrevState == LOW) { // checks if the button was pressed this frame (actually checks if we let go of the button, but it doenst matter really :p )
    on = !on;
  }
  if (on) {
    digitalWrite(onLed, HIGH);
    if (!locked) {  // just makes sure you can only press the button when no code has been activated
      if (upState == HIGH && upPrevState == LOW) {
      up = true;
      code += "s";
      count++;
      }
      if (downState == HIGH && downPrevState == LOW) {
        down = true;
        code += "w";
        count++;
      }
      if (leftState == HIGH && leftPrevState == LOW) {
        left = true;
        code += "a";
        count++;
      }
      if (rightState == HIGH && rightPrevState == LOW) {
        right = true;
        code += "d";
        count++;
      }
    }
    
  } else {
    digitalWrite(onLed, LOW);
    up = false;
    down = false;   // resets stuff when the powerbutton on the box is turned off
    left = false;
    right = false;
    count = 0;
    code = "";
    locked = false;
  }
  if(code == "wdsss" || code == "wssws"|| code == "adwsd"|| code == "wwssd"|| code == "sssss"|| code == "wwwww"|| code == "wwssadad"|| code == "sads"|| code == "dwssw" ||code == "adad"||code == "dad"||code == "wasdwasdwasdwasdwasdwasdwasdwasdwasdwasdwasdwasdwasd" ||code == "dsdsdsds")  {
    locked = true;  // the bread and butter, it checks if an active code has been typed and then turns on the lights and locks the input exept power button.
    up = true;
    down = true;
    left = true;
    right = true;
  } 
  if (up) {
    digitalWrite(upLed,HIGH);   //the functional parts of the lights
  } else {
    digitalWrite(upLed,LOW);
  }
  if (down) {
    digitalWrite(downLed,HIGH);
  } else {
    digitalWrite(downLed,LOW);
  }
  if (left) {
    digitalWrite(leftLed,HIGH);
  } else {
    digitalWrite(leftLed,LOW);
  }
  if (right) {
    digitalWrite(rightLed,HIGH);
  } else {
    digitalWrite(rightLed,LOW);
  }
  Serial.print(code + "\n");
  onPrevState = onState;
  upPrevState = upState;      // sets the previous states so they are ready for next frame
  downPrevState = downState;
  leftPrevState = leftState;
  rightPrevState = rightState;
}