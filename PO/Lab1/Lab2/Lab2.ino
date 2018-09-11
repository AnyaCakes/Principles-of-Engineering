/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo_vert;  // create servo object to control a servo
Servo myservo_horz;
int pos_vert = 0;    // variable to store the vertical servo position
int pos_horz = 0;   // variable to store horizontal servo position
void setup() {
  myservo_vert.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo_horz.attach(8);
}

void loop() {
  for (pos_vert = 0; pos_vert <= 180; pos_vert+=10){
    myservo_vert.write(pos_vert);
    delay(500);
    for(pos_horz = 0; pos_horz <= 180; pos_horz+=1){
        myservo_horz.write(pos_horz);
        delay(10);
      }
    for(pos_horz = 180; pos_horz >=0; pos_horz-=1){
        myservo_horz.write(pos_horz);
        delay(10);
      }
    delay(500);
  }
  for (pos_vert = 180; pos_vert >= 0; pos_vert-=10){
    myservo_vert.write(pos_vert);
    delay(500);
    for(pos_horz = 0; pos_horz <= 180; pos_horz+=1){
        myservo_horz.write(pos_horz);
        delay(10);
      }
    for(pos_horz = 180; pos_horz >=0; pos_horz-=1){
        myservo_horz.write(pos_horz);
        delay(10);
      }
    delay(500);
  }
 /* for (pos = 0; pos <= 0; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(100) ;                  // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(100) ;                 // waits 15ms for the servo to reach the position
  }
  */
  
}
