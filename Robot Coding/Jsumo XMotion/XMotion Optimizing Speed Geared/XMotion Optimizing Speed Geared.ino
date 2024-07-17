#include <xmotion.h>  // Max power for timeless control is 255

// Ultrasonic sensor
#define TrigPinR 4
#define EchoPinR 2
#define TrigPinL 1
#define EchoPinL 0

#define DipSwitch3 7  // Dipswitch 3 tied to Digital 7
#define start 10      // Button tied to Digital 10
int fight = 0;

//Ultrasonic variables
long durationR;
long durationL;
float distanceR;
float distanceL;

// Line sensor
const int LeftLine = 800;
const int RightLine = 700;
const int LineR = A1;
const int LineL = A2;
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

  pinMode(DipSwitch3, INPUT);  //Dipswitch 3 Declared as Input
  digitalWrite(DipSwitch3, HIGH);
  Serial.begin(9600);
}

void loop() {

  int buttonState = digitalRead(start);
  // Serial.println(buttonState);
  if (buttonState == 0) {
    Serial.println("Starting");
    if (fight == 0 && digitalRead(DipSwitch3) == 1) {
      Serial.println("Starting 1");
      delay(3000);
      starting1();
      routine();
      fight = 1;
    } else if (fight == 0 && digitalRead(DipSwitch3) == 0) {
      Serial.println("Starting 2");
      delay(3000);
      starting2();
      routine();
      fight = 1;
    } else {
      Serial.println("Out");
      xmotion.MotorControl(0, 0);
      fight = 0;
      delay(5000);
    }
  } else if (fight == 1) {
    routine();
  }
}

void starting1() {
  xmotion.Left0(50, 190);         // Speed, Duration (Right Motor Forward, Left Backward)
  xmotion.ArcTurn(22, 50, 1400);  // Left speed, Right speed, Duration in percent
  xmotion.Left0(50, 240);         // Speed, Duration (Right Motor Forward, Left Backward)
  // xmotion.Forward(100,400); // Speed, Duration
  xmotion.MotorControl(127, 127);
  delay(480);
}

void starting2() {
  xmotion.Right0(50, 190);        // Speed, Duration (Right Motor Backward, Left Forward)
  xmotion.ArcTurn(50, 23, 1400);  // Left speed, Right speed, Duration in percent
  xmotion.Right0(50, 240);        // Speed, Duration (Right Motor Backward, Left Forward)
  // xmotion.Forward(100,400); // Speed, Duration
  xmotion.MotorControl(127, 127);
  delay(480);
}

void standby() {  // Standby search opponentv
  xmotion.MotorControl(100, -100);
}

void routine() {
  // Reading Right Line Sensor
  inputLineR = analogRead(LineR);
  inputLineL = analogRead(LineL);
  Serial.println(inputLineR);
  Serial.println(inputLineL);

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
    Serial.print("Distance Right Sensor: ");
    Serial.println(distanceR);

    // Reading Distance Left
    digitalWrite(TrigPinL, LOW);
    delayMicroseconds(2);
    digitalWrite(TrigPinL, HIGH);  // Sets the trigPin on HIGH state for 10 micro seconds
    delayMicroseconds(10);
    digitalWrite(TrigPinL, LOW);  // Reads the echoPin, returns the sound wave travel time in microseconds
    durationL = pulseIn(EchoPinL, HIGH);
    distanceL = (durationL / 2) / 29.1;  // Calculate the distance
    Serial.print("Distance Left Sensor: ");
    Serial.println(distanceL);
    if (distanceR > 30 && distanceL > 30) {  //if both sensors read more than 25 cm, brake both motors
      standby();
      Serial.println("Robot Standby");
    } else {
      stalking();
    }
  }
}

void stalking() {
  if (distanceR < 10 || distanceL < 10) {
    Serial.println("Both Motor Forward");
    xmotion.MotorControl(255, 255);
  } else if (distanceR < 25 && distanceL < 25) {  //if both sensors less than than 25 cm, go forward
    xmotion.MotorControl(255, 255);
    Serial.println("Both Motor Forward");
  } else if (distanceR > 25 && distanceL < 25) {  //if only something is in front of the left ultrasonic sensor, turn left
    xmotion.MotorControl(100, -100);
    Serial.println("Turn Left");
  } else if (distanceR < 25 && distanceL > 25) {  //if only something is in front of the right ultrasonic sensor, turn right
    xmotion.MotorControl(-100, 100);
    Serial.println("Turn Right");
  }
}

void whiteLine(int sensor) {
  if (sensor == 1) {  //Right sensor Detected
    Serial.println("Moving Backward Right");
    xmotion.Backward(70, 450);  // %70 Speed, both motor backward 1000mS.
  } else {                      //Left sensor Detected
    Serial.println("Moving Backward Left");
    xmotion.Backward(70, 450);  // %70 Speed, both motor backward 1000mS.
  }
  xmotion.MotorControl(100, -100);
}