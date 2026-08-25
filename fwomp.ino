#include "Arduino.h"



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

void loop() {
  int upState = digitalRead(upButton);
  int downState = digitalRead(downButton);
  int rightState = digitalRead(rightButton);
  int leftState = digitalRead(leftButton);
  int onState = digitalRead(onButton);
  bool left = false;
  bool right = false;
  bool up = false;
  bool down = false;



  if (onState == HIGH && onPrevState == LOW) {
    on = !on;
  }
  if (on) {
    digitalWrite(onLed, HIGH);
    if (!locked) {
      if (upState == HIGH && upPrevState == LOW) {
      up = true;
      code += "w";
      count++;
      }
      if (downState == HIGH && downPrevState == LOW) {
        down = true;
        code += "s";
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
    down = false;
    left = false;
    right = false;
    count = 0;
    code = "";
    locked = false;
  }
  if(code == "wdsss" || code == "wssws"|| code == "adwsd"|| code == "wwssd"|| code == "sssss"|| code == "wwwww"|| code == "wwssadad"|| code == "sads"|| code == "dwssw")  {
    locked = true;
    up = true;
    down = true;
    left = true;
    right = true;
  } 
  if (up) {
    digitalWrite(upLed,HIGH);
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
  onPrevState = onState;
  upPrevState = upState;
  downPrevState = downState;
  leftPrevState = leftState;
  rightPrevState = rightState;
}