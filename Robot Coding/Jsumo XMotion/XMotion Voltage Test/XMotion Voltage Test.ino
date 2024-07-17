#include <xmotion.h>  // Max power for timeless control is 255
void setup() {
  // put your setup code here, to run once:
}

void loop() {
  xmotion.Forward(100, 5000);  // Speed, Duration

  xmotion.MotorControl(255, 255);
  delay(5000);
  xmotion.MotorControl(0, 0);
  delay(3000);
}
