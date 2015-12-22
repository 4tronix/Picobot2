/*
  Demo All
  Shows a number of features of the PicoBot2 and uses the Mode switch to change Operation
  
  1) Flashing Lights
  2) Line Follower
  3) Light seeker
  4) Obstacle avoider
  5) Constant distance
  
  Purpose: Initial test program for shipping
 
  This example code is licensed under CC-BY-SA https://creativecommons.org/licenses/by-sa/3.0/
 */

#include "Picobot2.h"
Picobot2 pb2;

#define LEVEL 200  // level below which it must be over a line
#define HYSTERESIS 120  // difference in analog readings for LDR to make it turn in light follower

#define FLASH 1
#define LINE 2
#define LIGHT 3
#define AVOIDER 4
#define FOLLOW 5
#define LASTPROG 5

int state = 1;      // initial state is 1) Line Follower
bool lastButton = false;  // Initial state of button is OFF
int bright = 40;    // brightness value for RGB LEDs

int baseLeft=0; // Global variables foe the light sensor readings when first activating the light follow routine
int baseRight=0;

// the setup routine runs once when you press reset:
void setup()
{
  pb2.begin();
  Serial.begin(115200);
  FlashAll(200);  // Sign on with a slow flashing display
}

// the loop routine runs over and over again forever:
// runs one iteration of the relevant program, then checks the mode button
// moves to next state if mode button pressed and flashes LED correct number of times
void loop()
{
  switch (state)
  {
    case FLASH:
      flashLEDs();
      break;
    case LINE:
      lineFollow();
      break;
    case LIGHT:
      lightSeek();
      break;
    case AVOIDER:
      obstacleAvoid();
      break;
    case FOLLOW:
      constDistance();
      break;
  }
  if (getButton()==1)
  {
    pb2.stop(true);
    state++;
    if (state > LASTPROG)
      state = 1;
    flashCount(state);
    //Serial.println("New state: " + String(state));
    if (state == LIGHT)
    {
      baseLeft = pb2.lightRead(true);   // pb2.lightRead(true) gets the initial left light sensor value
      baseRight = pb2.lightRead(false);  // pb2.lightRead(false) gets the initial right light sensor value
    }
  }
}

void flashLEDs()  // State 1 FLASH
{
  FlashAll(30);
}

void lineFollow()  // State 2 LINE
{
  int lval = map(pb2.lineRead(true), 120, 320, 0, 255); // pb2.lineRead(true) gets the left line sensor value and maps the usable range into the full motor speed range
  int rval = map(pb2.lineRead(false), 120, 320, 0, 255); // pb2.lineRead(false) gets the right line sensor value
  pb2.turnForward(lval, rval);
  //Serial.println("Left: " + String(lval) + "  Right: " + String(rval));
  if (rval < lval-50)
    pb2.pixelAllSet(CRGB(bright, 0, 0));
  else if (lval < rval-50)
    pb2.pixelAllSet(CRGB(0, bright, 0));
  else
    pb2.pixelAllSet(CRGB(0, 0, bright));
  delay(50);
}

void lightSeek2()  // State 3 LIGHT
{
  int ldrL = pb2.lightRead(true);   // pb2.lightRead(true) gets the current left light sensor value
  int ldrR = pb2.lightRead(false);  // pb2.lightRead(false) gets the current right light sensor value
  int lval=0, rval=0;
  if (ldrL > ldrR)
    rval = map(ldrL-ldrR, 0, 500, 0, 255);
  else
    lval = map(ldrR-ldrL, 0, 500, 0, 255);
  pb2.turnForward(lval, rval);
  //Serial.println("Left: " + String(lval) + "  Right: " + String(rval));
  delay(50);
}

void lightSeek()  // State 3 LIGHT
{
  int ldrL = pb2.lightRead(true);   // pb2.lightRead(true) gets the current left light sensor value
  int ldrR = pb2.lightRead(false);  // pb2.lightRead(false) gets the current right light sensor value
  int threshMove = 70;
  int threshSpin = 200;
  int changeL = abs(ldrL-baseLeft);
  int changeR = abs(ldrR-baseRight);
  Serial.println(String(baseLeft)+":"+String(ldrL)+"  "+String(baseRight)+":"+String(ldrR)+"  "+String(changeL)+":"+String(changeR)+":"+String(abs(changeL-changeR)));
  if ((ldrL < (baseLeft-threshMove)) && (ldrR < (baseRight-threshMove)) && (abs(changeL-changeR) < threshSpin))
    pb2.forward(150);
  else if (ldrL < (baseLeft-threshMove))
    pb2.spinLeft(150);
  else if (ldrR < (baseRight-threshMove))
    pb2.spinRight(150);
  else
    pb2.stop(false);
  delay(50);
}


void obstacleAvoid() // State 4 AVOIDER
{
  int cm = pb2.distanceRead();
  //Serial.println("Distance: " + String(cm));
  if (cm  < 8)
  {
    pb2.pixelAllSet(CRGB(bright, bright, 0));  // Yellow
    pb2.reverse(200);
    delay(1000);
    pb2.pixelAllSet(CRGB(0, bright, 0));  // Green
    pb2.spinRight(120);
    delay(300);
  }
  else
  {
    pb2.pixelAllSet(CRGB(0, 0, bright));  // Blue
    pb2.forward(200);
    delay(10);
  }
}

void constDistance()  // State 5 FOLLOW
{
  // This routine moves backwards if too close, and forwards if too far away
  // It could be improved by changing the speed to depend on the distance, to give a "softer" start and stop
  int cm = pb2.distanceRead();
  //Serial.println("Distance: " + String(cm));
  if (cm  < 9)
  {
    pb2.pixelAllSet(CRGB(bright, bright, 0));  // Yellow
    pb2.reverse(150);
    delay(10);
  }
  else if (cm > 10)
  {
    pb2.pixelAllSet(CRGB(0, 0, bright));  // Blue
    pb2.forward(150);
    delay(10);
  }
  else
  {
    pb2.pixelAllSet(CRGB(bright, bright, bright));  // White
    pb2.stop(false);  // Coast to halt
    delay(10);
  }
}

void FlashAll(int wait)
{
  pb2.setBlueLED(ON);
  delay(wait);
  pb2.setBlueLED(OFF);
  pb2.pixelAllSet(CRGB(bright, 0, 0));
  delay(wait);
  pb2.setBlueLED(ON);
  delay(wait);
  pb2.setBlueLED(OFF);
  pb2.pixelAllSet(CRGB(0, bright, 0));
  delay(wait);
  pb2.setBlueLED(ON);
  delay(wait);
  pb2.setBlueLED(OFF);
  pb2.pixelAllSet(CRGB(0, 0, bright));
  delay(wait);
  pb2.setBlueLED(ON);
  delay(wait);
  pb2.setBlueLED(OFF);
  pb2.pixelAllSet(CRGB(bright, bright, bright));
  delay(wait);
}

int getButton()
{
  bool newB = pb2.buttonRead();
  //Serial.println("Button = " + String(newB));
  if (!newB && lastButton)
  {
    lastButton = false;
    return 1;
  }
  lastButton = newB;
  return 0;
}

void flashCount(int count)
{
  for (int i=0; i<count; i++)
  {
    pb2.setBlueLED(ON);
    delay(300);
    pb2.setBlueLED(OFF);
    delay(300);
  }
}


