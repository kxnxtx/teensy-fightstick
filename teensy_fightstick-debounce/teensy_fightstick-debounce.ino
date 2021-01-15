#include <Bounce.h>
#include "XInput.h"

#define MILLIDEBOUNCE 3  //Debounce time in milliseconds
#define NUMBUTTONS 12  //Number of all buttons
#define LED_DISABLED 0 //disable led, change to 1 to enable led

#define pinA 0
#define pinB 1
#define pinX 2
#define pinY 3
#define pinLB 4
#define pinRB 5
#define pinSE 6
#define pinST 7
#define pinU 10
#define pinD 11
#define pinL 12
#define pinR 14

//Position of a button in the button status array
#define POSA 0
#define POSB 1
#define POSX 2
#define POSY 3
#define POSLB 4
#define POSRB 5
#define POSSE 6
#define POSST 7
#define POSU 8
#define POSD 9
#define POSL 10
#define POSR 11

byte buttonStatus[NUMBUTTONS];  //array Holds a "Snapshot" of the button status to parse and manipulate

Bounce joystickUP = Bounce(pinU, MILLIDEBOUNCE);
Bounce joystickDOWN = Bounce(pinD, MILLIDEBOUNCE);
Bounce joystickLEFT = Bounce(pinL, MILLIDEBOUNCE);
Bounce joystickRIGHT = Bounce(pinR, MILLIDEBOUNCE);
Bounce button1 = Bounce(pinA, MILLIDEBOUNCE);
Bounce button2 = Bounce(pinB, MILLIDEBOUNCE);
Bounce button3 = Bounce(pinX, MILLIDEBOUNCE);
Bounce button4 = Bounce(pinY, MILLIDEBOUNCE);
Bounce button5 = Bounce(pinLB, MILLIDEBOUNCE);
Bounce button6 = Bounce(pinRB, MILLIDEBOUNCE);
Bounce buttonSTART = Bounce(pinST, MILLIDEBOUNCE);
Bounce buttonSELECT = Bounce(pinSE, MILLIDEBOUNCE);

void setupPins()
{
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
    pinMode(pinX, INPUT_PULLUP);
    pinMode(pinY, INPUT_PULLUP);
    pinMode(pinLB, INPUT_PULLUP);
    pinMode(pinRB, INPUT_PULLUP);
    pinMode(pinSE, INPUT_PULLUP);
    pinMode(pinST, INPUT_PULLUP);
    pinMode(pinU, INPUT_PULLUP);
    pinMode(pinD, INPUT_PULLUP);
    pinMode(pinL, INPUT_PULLUP);
    pinMode(pinR, INPUT_PULLUP);
}

void buttonRead()
{
  if (joystickUP.update()) {buttonStatus[POSU] = joystickUP.fallingEdge();}
  if (joystickDOWN.update()) {buttonStatus[POSD] = joystickDOWN.fallingEdge();}
  if (joystickLEFT.update()) {buttonStatus[POSL] = joystickLEFT.fallingEdge();}
  if (joystickRIGHT.update()) {buttonStatus[POSR] = joystickRIGHT.fallingEdge();}
  if (button1.update()) {buttonStatus[POSA] = button1.fallingEdge();}
  if (button2.update()) {buttonStatus[POSB] = button2.fallingEdge();}
  if (button3.update()) {buttonStatus[POSX] = button3.fallingEdge();}
  if (button4.update()) {buttonStatus[POSY] = button4.fallingEdge();}
  if (button5.update()) {buttonStatus[POSLB] = button5.fallingEdge();}
  if (button6.update()) {buttonStatus[POSRB] = button6.fallingEdge();}
  if (buttonSTART.update()) {buttonStatus[POSST] = buttonSTART.fallingEdge();}
  if (buttonSELECT.update()) {buttonStatus[POSSE] = buttonSELECT.fallingEdge();}
}

void processInputs()
{
  XInput.setDpad(buttonStatus[POSU], buttonStatus[POSD], buttonStatus[POSL], buttonStatus[POSR]);
  
  //Buttons
  if (buttonStatus[POSA]) {XInput.setButton(BUTTON_A, 1);} 
  else {XInput.setButton(BUTTON_A, 0);}
  if (buttonStatus[POSB]) {XInput.setButton(BUTTON_B, 1);} 
  else {XInput.setButton(BUTTON_B, 0);}
  if (buttonStatus[POSX]) {XInput.setButton(BUTTON_X, 1);} 
  else {XInput.setButton(BUTTON_X, 0);}
  if (buttonStatus[POSY]) {XInput.setButton(BUTTON_Y, 1);} 
  else {XInput.setButton(BUTTON_Y, 0);}
  if (buttonStatus[POSLB]) {XInput.setButton(BUTTON_LB, 1);} 
  else  {XInput.setButton(BUTTON_LB, 0);}
  if (buttonStatus[POSRB]) {XInput.setButton(BUTTON_RB, 1);} 
  else {XInput.setButton(BUTTON_RB, 0);}
    if (buttonStatus[POSST]) {XInput.setButton(BUTTON_START, 1);} 
  else  {XInput.setButton(BUTTON_START, 0);}
  if (buttonStatus[POSSE]) {XInput.setButton(BUTTON_BACK, 1);} 
  else {XInput.setButton(BUTTON_BACK, 0);}
}

void setup() {
  setupPins();
	XInput.setAutoSend(false);  // Wait for all controls before sending
	XInput.begin();
}

void loop() {
  buttonRead();
  processInputs();
	XInput.send();
}
