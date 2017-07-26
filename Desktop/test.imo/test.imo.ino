// Robotics with the BOE Shield - RoamingWithWhiskers
// Go forward.  Back up and turn if whiskers indicate BOE Shield bot bumped
// into something.

#include <Servo.h>                           // Include servo library
 
Servo servoLeft;                             // Declare left and right servos
Servo servoRight;
 
void setup()                                 // Built-in initialization block
{
  pinMode(7, INPUT);                         // Set right whisker pin to input
  pinMode(5, INPUT);                         // Set left whisker pin to input  

  Serial.begin(9600);  
  
  delay(1000);   
  
  servoLeft.attach(7);                      // Attach left signal to pin 13
  servoRight.attach(5);// Attach right signal to pin 12
  
  forward(2000); 
  
  disableServos();                           // Stay still indefinitely

  
}  
 
void loop()                                  // Main loop auto-repeats
{
  byte wLeft = digitalRead(5);               // Copy left result to wLeft  
  byte wRight = digitalRead(7);              // Copy right result to wRight

  Serial.print(wLeft);                       // Display left whisker state 
  Serial.println(wRight);                    // Display right whisker state

  delay(50);                                    // Pause for 50 ms

  if((wLeft == 0) && (wRight == 0))          // If both whiskers contact
  {
    backward(1000);                          // Back up 1 second
    turnLeft(800);                           // Turn left about 120 degrees
  }
  else if(wLeft == 0)                        // If only left whisker contact
  {
    backward(1000);                          // Back up 1 second
    turnRight(400);                          // Turn right about 60 degrees
  }
  else if(wRight == 0)                       // If only right whisker contact
  {
    backward(1000);                          // Back up 1 second
    turnLeft(400);                           // Turn left about 60 degrees
 }
  else                                       // Otherwise, no whisker contact
  {
    forward (2000);                         
  }
}

void forward(int time)                       // Forward function
{
  servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
  servoRight.writeMicroseconds(1700);        // Right wheel clockwise
  delay(time);                               // Maneuver for time ms
}

void turnLeft(int time)                      // Left turn function
{
  servoLeft.writeMicroseconds(1300);         // Left wheel clockwise
  servoRight.writeMicroseconds(1300);        // Right wheel clockwise
  delay(time);                               // Maneuver for time ms
}

void turnRight(int time)                     // Right turn function
{
  servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
  servoRight.writeMicroseconds(1700);        // Right wheel counterclockwise
  delay(time);                               // Maneuver for time ms
}

void backward(int time)                      // Backward function
{
  servoLeft.writeMicroseconds(1300);         // Left wheel clockwise
  servoRight.writeMicroseconds(1700);        // Right wheel counterclockwise
  delay(time);                               // Maneuver for time ms
 
}

void disableServos()                         // Halt servo signals
{                                            
  servoLeft.detach();                        // Stop sending servo signals
  servoRight.detach(); 
}
