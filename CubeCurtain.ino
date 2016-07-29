
/*Cubical Curtain Code from Arrow Electronics
******Thanks for making with us!********

This code should work on any Arduino board - tested on the Uno.

Two momentary buttons are used to indicate whether we want the stepper
motor to spin clockwise or counterclockwise.  The spool attached to the motor
shaft collects or releases thread based on the spin direction.

The motor seemed to get stuck between steps and would draw maximum current between
button presses, which causes the driver to get very hot.  We fixed this issue by sending
all four control lines low after each step.  

We used a 64oz.in. motor powered with 6VDC.  It was more than powerful enough to raise 
the curtain.  

*/


#include <Stepper.h>

const int stepsToTake = 100;  //Spin motor this  many steps.  Ours had 200 steps/rotation, so this was 180 degrees.
int buttonone = 0;            //Clockwise control
int buttontwo = 0;            //Counterclockwise control
// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);


void setup() {
  //int button = 0;
  pinMode(4, OUTPUT);         //set high for buttons
  digitalWrite(4, HIGH);
  digitalWrite(7, LOW);
  pinMode(7, INPUT);          //read this to see if button is pressed
  pinMode(6, INPUT);          //other button
  myStepper.setSpeed(60);     // set the speed at 60 rpm
  Serial.begin(9600);         // initialize the serial port for debugging
}

void loop() {
  //Read and print whether each button is pressed (1) or not pressed (0)
  buttonone = digitalRead(7);
  Serial.println(buttonone);
  buttontwo = digitalRead(6);
  Serial.println(buttontwo);
  delay(100);

  if (buttonone == 1){
    myStepper.step(stepsToTake);   //Spin half a rotation clockwise
    Serial.println("SPIN FORWARD");
  }
  if (buttontwo == 1){
  myStepper.step(-stepsToTake);   //Spin half a rotation counterclockwise
  Serial.println("SPIN BACKWARD");
  }

//Set all motor control Pins low again to stop the current suck thing where it gets stuck between steps.
digitalWrite(8, LOW);
digitalWrite(9, LOW);
digitalWrite(10, LOW);
digitalWrite(11,LOW);

//The end!

}

