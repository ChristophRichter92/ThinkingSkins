#include <Servo.h>
#include "tsServoDriver.h"

Servo servoVert;
Servo servoHori;

int VERT_MIN = 70;
int HORI_MIN = 85;
int VERT_MID = 75;
int HORI_MID = 130;
int VERT_MAX = 125;
int HORI_MAX = 180;

// global offset variable
Coord offset(HORI_MID, VERT_MID);
int up = 1;
int left = 1;

void setup() 
{ 
  servoVert.attach(9);  // attaches the servo on pin 9 to the servo object
  servoHori.attach(10);  // attaches the servo on pin 10 to the servo object
} 

void loop() 
{ 
  /*
  // This moves the plate from open to closed in every cycle.
  if (up == 1){
    up = 0;
    offset.setTo(HORI_MAX, VERT_MID);
  } else {
    up = 1;
    offset.setTo(HORI_MID, VERT_MID);
  }
  */
  ///*
  // This moves the plate like an old windows screensaver.
  if(offset.getY() >= VERT_MAX) up = 0;
  if(offset.getX() >= HORI_MAX) left = 0;
  if(offset.getY() <= VERT_MIN) up = 1;
  if(offset.getX() <= HORI_MIN) left = 1;
  
  if(up == 1){
    offset.incY();
  } else offset.decY();
  
  if(left == 1){
    offset.incX();
  } else offset.decX();
  //*/
  // do this every loop
  setServos(offset);
  delay(45);
}

void setServos(Coord newPos)
{
  servoVert.write(newPos.getY());
  servoHori.write(newPos.getX());
}

