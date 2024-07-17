#include <xmotion.h>
// max power for timeless control is 255

// Ultrasonic sensor
#define TrigPinR 4
#define EchoPinR 2
#define TrigPinL 1
#define EchoPinL 0

#define start 10  // Button tied to Digital 10
int status = 1;
int fight = 0;

//Ultrasonic variables
long durationR;
long durationL;
float distanceR;
float distanceL;

// Line sensor
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
  Serial.begin(9600);
}

void loop() {

  int buttonState = digitalRead(start);
  Serial.println(buttonState);
  if (buttonState == 0) {
    fight = 1;
    Serial.println("In");
    if (status == 1) {
      // Serial.println("Starting");
      delay(5000);
      starting();
    }
    // Reading Right Line Sensor
    inputLineR = analogRead(LineR);
    inputLineL = analogRead(LineL);
    // Serial.println(inputLineR);
    // Serial.println(inputLineL);

    // Reverse when white detected
    if (inputLineR <= 800 || inputLineL <= 800) {  //Check the sensor output
      if (inputLineR <= 800) {
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
      if (distanceR > 30 && distanceL > 30) {  //if both sensors read more than 25 cm, brake both motors
        standby();
        // Serial.println("Robot Standby");
      } else {
        stalking();
      }
    }
    status = 0;
  }
  Serial.println("Out");
  xmotion.MotorControl(0, 0);
  delay(3000)
    status = 1;
}

void starting() {
  // Serial.println("Moving Forward");
  xmotion.Forward(50, 900);
  delay(900);
  // Serial.println("Turn Left");
  xmotion.Left0(50, 500);
  // Serial.println("Moving Forward");
  xmotion.Forward(50, 400);
}

void standby() {  // Standby search opponent
  xmotion.MotorControl(-200, 200);
}

void stalking() {
  if (distanceR < 10 || distanceL < 10) {
    xmotion.MotorControl(255, 255);
  } else if (distanceR < 30 && distanceL < 30) {  //if both sensors less than than 25 cm, go forward
    xmotion.MotorControl(200, 200);
    // Serial.println("Both Motor Forward");
  } else if (distanceR > 30 && distanceL < 30) {  //if only something is in front of the left ultrasonic sensor, turn left
    xmotion.MotorControl(-200, 200);
    // Serial.println("Turn Left");
  } else if (distanceR < 30 && distanceL > 30) {  //if only something is in front of the right ultrasonic sensor, turn right
    xmotion.MotorControl(200, -200);
    // Serial.println("Turn Right");
  }
}

void whiteLine(int sensor) {
  if (sensor == 1) {  //Right sensor Detected
    // Serial.println("Moving Backward");
    xmotion.Backward(70, 450);  // %70 Speed, both motor backward 1000mS.
  } else {                      //Left sensor Detected
    // Serial.println("Moving Backward");
    xmotion.Backward(70, 450);  // %70 Speed, both motor backward 1000mS.
  }
  xmotion.MotorControl(-200, 200);  //Timeless -150/255 Left Motor Backward Speed, 190/255 Right Motor Speed
}