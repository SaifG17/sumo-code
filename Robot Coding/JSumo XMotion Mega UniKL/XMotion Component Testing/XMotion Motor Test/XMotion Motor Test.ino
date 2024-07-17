#include <xmotion.h>
// max power for timeless control is 255

void setup() {
  Serial.begin(9600);
  delay(2000);
}

void loop() {
  Serial.println("Moving Forward");
  xmotion.Forward(100, 3000);  // %70 Speed, both motor forward 1000mS.
  xmotion.StopMotors(500);      // Stop Both Motors

  Serial.println("Moving Backward");
  xmotion.Backward(100, 3000);  // %70 Speed, both motor backward 1000mS.
  xmotion.StopMotors(500);       // Stop Both Motors
  delay(1000);

  xmotion.MotorControl(255,255);
  delay(3000);
  xmotion.StopMotors(500);

  // Serial.println("Turn Right");
  // xmotion.Right0(50, 1000);  // %51 Speed, 1 second Right 0 Turn. (Left Motor Forward, Right Backward)
  // xmotion.StopMotors(0);     // Stop Both Motors
  // delay(1500);

  // Serial.println("Turn Left");
  // xmotion.Left0(50, 1000);  // %20 Speed, 3.5 second Left 0 Turn. (Right Motor Forward, Left Backward)
  // xmotion.StopMotors(0);    // Stop Both Motors
  // delay(1500);

  // Serial.println("Left Arc");
  // xmotion.ArcTurn(20, 60, 250);  // 250 millisecond %20 Speed Left, %60Speed Right Motor
  // xmotion.StopMotors(0);         // Stop Both Motors
  // delay(1500);


  // Serial.println("Right Arc");
  // xmotion.ArcTurn(60, 20, 250);  // 250 millisecond %20 Speed Left, %60Speed Right Motor
  // xmotion.StopMotors(0);         // Stop Both Motors
  // delay(1500);

  // // Timeless Control
  // Serial.println("Moving Forward");
  // xmotion.MotorControl(150, 150);
  // delay(1500);
  // xmotion.MotorControl(0, 0);  // Stop Both Motors
  // delay(1500);

  // Serial.println("Moving Backward");
  // xmotion.MotorControl(-150, -150);
  // delay(1500);
  // xmotion.MotorControl(0, 0);  // Stop Both Motors
  // delay(1500);

  // Serial.println("Turn Right");
  // xmotion.MotorControl(150, -150);
  // delay(1500);
  // xmotion.MotorControl(0, 0);  // Stop Both Motors
  // delay(1500);

  // Serial.println("Turn Left");
  // xmotion.MotorControl(-150, 150);
  // delay(1500);
  // xmotion.MotorControl(0, 0);  // Stop Both Motors
  // delay(1500);

  // Serial.println("Left Arc");
  // xmotion.MotorControl(150, 200);
  // delay(1500);
  // xmotion.MotorControl(0, 0);  // Stop Both Motors
  // delay(1500);

  // Serial.println("Right Arc");
  // xmotion.MotorControl(200, 150);
  // delay(1500);
  // xmotion.MotorControl(0, 0);  // Stop Both Motors
  // delay(1500);

  // xmotion.MotorControl(-150, 190);  //Timeless -150/255 Left Motor Backward Speed, 190/255 Right Motor Speed
}
