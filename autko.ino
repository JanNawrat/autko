#include "Wheels.h"

Wheels w;
volatile char cmd;

void setup() {
  // 1 - right wheel forward
  // 2 - right wheel backward
  // 3 - right wheel speed
  // 4 - left wheel forward
  // 5 - left wheel backward
  // 6 - left wheel speed
  // pins 9, 10 shouldn't be used because of complications with I2C
  w.attach(2, 3, 6, 4, 5, 11);
  
  Serial.begin(9600);
  Serial.println("Forward: WAD");
  Serial.println("Back: ZXC");
  Serial.println("Stop: S");

}

void loop() {
  while(Serial.available())
  {
    cmd = Serial.read();
    switch(cmd)
    {
      case 'w': w.forward(); break;
      case 'x': w.back(); break;
      case 'a': w.forwardLeft(); break;
      case 'd': w.forwardRight(); break;
      case 'z': w.backLeft(); break;
      case 'c': w.backRight(); break;
      case 's': w.stop(); break;
      case '1': w.setSpeedLeft(75); break;
      case '2': w.setSpeedLeft(200); break;
      case '9': w.setSpeedRight(75); break;
      case '0': w.setSpeedRight(200); break;
      case '5': w.setSpeed(100); break;
      case 'g' : w.goForward(10); break;
      case 'b' : w.goBack(10); break;
    }
  }
}
