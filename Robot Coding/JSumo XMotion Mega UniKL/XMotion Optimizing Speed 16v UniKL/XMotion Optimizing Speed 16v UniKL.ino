#include <xmotion.h>  // Max power for timeless control is 255 (RED WHEEL)

// Ultrasonic sensor
#define TrigPinR 4
#define EchoPinR 2
#define TrigPinL 1
#define EchoPinL 0

#define DipSwitch1 5  // Dipswitch 1 tied to Digital 5
#define DipSwitch2 6  // Dipswitch 2 tied to Digital 6
#define DipSwitch3 7  // Dipswitch 3 tied to Digital 7
#define start 10      // Button tied to Digital 10
int fight = 0;
long lastMsg = 0;

//Ultrasonic variables
long durationR;
long durationL;
float distanceR;
float distanceL;

// Line sensor
const int LeftLine = 750;
const int RightLine = 780;
const int LineR = A4;
const int LineL = A5;
int inputLineR = 0;
int inputLineL = 0;

void setup() {
  // Ultrasonic sensor Right
  pinMode(TrigPinR, OUTPUT);  // Sets the trigPin as an Output
  pinMode(EchoPinR, INPUT);   // Sets the echoPin as an Input
  // Ultrasonic sensor Left
  pinMode(TrigPinL, OUTPUT);     // Sets the trigPin as an Output
  pinMode(EchoPinL, INPUT);      // Sets the echoPin as an Input
  pinMode(start, INPUT_PULLUP);  //Button Declared as Input innitially 1, clicked turn to 0

  pinMode(DipSwitch1, INPUT);  //Dipswitch 1 Declared as Input
  pinMode(DipSwitch2, INPUT);  //Dipswitch 2 Declared as Input
  pinMode(DipSwitch3, INPUT);  //Dipswitch 3 Declared as Input

  digitalWrite(DipSwitch1, HIGH);  // Dipswitch Inputs are High (Pull-up made)
  digitalWrite(DipSwitch2, HIGH);
  digitalWrite(DipSwitch3, HIGH);
  Serial.begin(9600);
}

void loop() {

  int buttonState = digitalRead(start);
  // Serial.println(buttonState);
  if (buttonState == 0) {
    // Serial.println("Starting");
    if (fight == 0 && digitalRead(DipSwitch3) == 1 && digitalRead(DipSwitch2) == 1 && digitalRead(DipSwitch1) == 1) {
      // Serial.println("Starting 1");
      delay(5500);
      starting1();
      routine();
      fight = 1;
    } else if (fight == 0 && digitalRead(DipSwitch3) == 0 && digitalRead(DipSwitch2) == 1 && digitalRead(DipSwitch1) == 1) {
      // Serial.println("Starting 2");
      delay(5500);
      starting2();
      routine();
      fight = 1;
    } else if (fight == 0 && digitalRead(DipSwitch3) == 1 && digitalRead(DipSwitch2) == 0 && digitalRead(DipSwitch1) == 1) {
      // Serial.println("Starting 3");
      delay(5500);
      starting3();
      routine();
      fight = 1;
    } else if (fight == 0 && digitalRead(DipSwitch3) == 1 && digitalRead(DipSwitch2) == 1 && digitalRead(DipSwitch1) == 0) {
      // Serial.println("Starting 4");
      delay(5500);
      starting4();
      routine();
      fight = 1;
    } else if (fight == 0 && digitalRead(DipSwitch3) == 1 && digitalRead(DipSwitch2) == 0 && digitalRead(DipSwitch1) == 0) {
      // Serial.println("Starting 5");
    } else if (fight == 0 && digitalRead(DipSwitch3) == 0 && digitalRead(DipSwitch2) == 0 && digitalRead(DipSwitch1) == 0) {
      // Serial.println("Starting 6");
    } else {
      // Serial.println("Out");
      xmotion.MotorControl(0, 0);
      fight = 0;
      delay(1000);
    }
  } else if (fight == 1) {
    routine();
  }
}

void starting1() {
  xmotion.Right0(100, 80);        // Speed, Duration (Right Motor Backward, Left Forward)
  xmotion.ArcTurn(40, 100, 600);  // Left speed, Right speed, Duration in percent
  xmotion.Left0(100, 120);        // Speed, Duration (Right Motor Backward, Left Forward)
  xmotion.MotorControl(255, 255);
  delay(200);
}

void starting2() {
  xmotion.Left0(100, 80);         // Speed, Duration (Right Motor Backward, Left Forward)
  xmotion.ArcTurn(40, 100, 600);  // Left speed, Right speed, Duration in percent
  xmotion.Left0(100, 100);        // Speed, Duration (Right Motor Backward, Left Forward)
  xmotion.MotorControl(255, 255);
  delay(200);
}

void starting3() {
  xmotion.Right0(100, 230);   // Speed, Duration (Right Motor Backward, Left Forward)
  xmotion.Forward(100, 280);  // Speed, Duration
  xmotion.Left0(100, 180);    // Speed, Duration (Right Motor Backward, Left Forward)
  xmotion.MotorControl(255, 255);
  delay(280);
}

void starting4() {
  xmotion.Left0(100, 100);  // Speed, Duration (Right Motor Backward, Left Forward)
}

void standby() {  // Standby search opponentv
  xmotion.MotorControl(155, -155);
}

void routine() {
  // Reading Right Line Sensor
  inputLineR = analogRead(LineR);
  inputLineL = analogRead(LineL);
  // Serial.println(inputLineR);
  // Serial.println(inputLineL);

  if (inputLineR <= RightLine || inputLineL <= LeftLine) {  //Check the sensor output
    if (inputLineR <= RightLine) {
      whiteLine(1);  // Right Line sensor Detected
    } else {
      whiteLine(2);  // Left Line sensor Detected
    }
  } else {  // Reading Distance Right
    digitalWrite(TrigPinR, LOW);
    delayMicroseconds(2);
    digitalWrite(TrigPinR, HIGH);  // Sets the trigPin on HIGH state for 10 micro seconds
    delayMicroseconds(10);
    digitalWrite(TrigPinR, LOW);  // Reads the echoPin, returns the sound wave travel time in microseconds
    durationR = pulseIn(EchoPinR, HIGH);
    distanceR = (durationR / 2) / 29.1;  // Calculate the distance
    // Serial.print("Distance Right Sensor: ");
    // Serial.println(distanceR);

    // Reading Distance Left
    digitalWrite(TrigPinL, LOW);
    delayMicroseconds(2);
    digitalWrite(TrigPinL, HIGH);  // Sets the trigPin on HIGH state for 10 micro seconds
    delayMicroseconds(10);
    digitalWrite(TrigPinL, LOW);  // Reads the echoPin, returns the sound wave travel time in microseconds
    durationL = pulseIn(EchoPinL, HIGH);
    distanceL = (durationL / 2) / 29.1;  // Calculate the distance
    // Serial.print("Distance Left Sensor: ");
    // Serial.println(distanceL);
    if (distanceR > 40 && distanceL > 40) {  //if both sensors read more than 25 cm, brake both motors
      standby();
      // Serial.println("Robot Standby");
    } else {
      stalking();
    }
  }
}

void stalking() {
  if (distanceR < 10 || distanceL < 10) {
    // Serial.println("Both Motor Forward");
    xmotion.MotorControl(255, 255);
  } else if (distanceR < 40 && distanceL < 40) {  //if both sensors less than than 25 cm, go forward
    xmotion.MotorControl(255, 255);
    // Serial.println("Both Motor Forward");
  } else if (distanceR > 40 && distanceL < 40) {  //if only something is in front of the left ultrasonic sensor, turn left
    xmotion.MotorControl(230, -230);
    // Serial.println("Turn Left");
  } else if (distanceR < 40 && distanceL > 40) {  //if only something is in front of the right ultrasonic sensor, turn right
    xmotion.MotorControl(-230, 230);
    // Serial.println("Turn Right");
  }
}

void whiteLine(int sensor) {
  // Reverse Straight
  if (sensor == 1) {  //Right sensor Detected
    // Serial.println("Moving Backward Right");
    xmotion.Backward(100, 500);  // %70 Speed, both motor backward 1000mS.
  } else {                       //Left sensor Detected
    // Serial.println("Moving Backward Left");
    xmotion.Backward(100, 500);  // %70 Speed, both motor backward 1000mS.
  }

  // // Reverse Arc
  // if (sensor == 1) {  //Right sensor Detected
  //   // Serial.println("Moving Backward Right");
  //   xmotion.ArcTurn(-50, -100, 500);  // Left speed, Right speed, Duration in percent
  // } else {                            //Left sensor Detected
  //   // Serial.println("Moving Backward Left");
  //   xmotion.ArcTurn(-50, -100, 500);  // Left speed, Right speed, Duration in percent
  // }
  xmotion.MotorControl(155, -155);
}