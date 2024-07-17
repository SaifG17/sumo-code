//Set motor configuration Left motor, Right motor in percent, delay

// Ultrasonic sensor
#define TrigPinR 12
#define EchoPinR 4
#define TrigPinL 0
#define EchoPinL 1

#define DipSwitch1 8  // Dipswitch 1 tied to Digital 6
#define DipSwitch2 7  // Dipswitch 2 tied to Digital 7
#define DipSwitch3 6  // Dipswitch 3 tied to Digital 8
#define start 11      // Button tied to Digital 11
int fight = 0;
long lastMsg = 0;

//MOTOR CONTROL
int RPwm = 10;
int RDir = 13;
int LPwm = 9;
int LDir = 5;

//Ultrasonic variables
long durationR;
long durationL;
float distanceR;
float distanceL;

// Line sensor
const int RightLine = 700;
const int LeftLine = 770;
const int LineR = A4;
const int LineL = A5;
int inputLineR = 0;
int inputLineL = 0;

void setup() {
  // 2 PWM Channel Declared as Output
  pinMode(RPwm, OUTPUT);
  pinMode(RDir, OUTPUT);
  pinMode(LPwm, OUTPUT);
  pinMode(LDir, OUTPUT);
  pinMode(start, INPUT_PULLUP);  //Button Declared as Input innitially 1, clicked turn to 0

  // Ultrasonic sensor Right
  pinMode(TrigPinR, OUTPUT);  // Sets the trigPin as an Output
  pinMode(EchoPinR, INPUT);   // Sets the echoPin as an Input
  // Ultrasonic sensor Left
  pinMode(TrigPinL, OUTPUT);  // Sets the trigPin as an Output
  pinMode(EchoPinL, INPUT);   // Sets the echoPin as an Input

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
      Set_Motor(0, 0, 2000);
      fight = 0;
      delay(1000);
    }
  } else if (fight == 1) {
    routine();
  }
}

void starting1() {
  Set_Motor(100, -100, 80);   //Right Turn
  Set_Motor(40, 100, 600);    //Arc Turn
  Set_Motor(-100, 100, 100);  //Left Turn
  Set_Motor(100, 100, 200);   //Forward
}

void starting2() {
  Set_Motor(-100, 100, 80);   //Left Turn
  Set_Motor(40, 100, 600);    //Arc Turn
  Set_Motor(-100, 100, 100);  //Left Turn
  Set_Motor(100, 100, 200);   //Forward
}

void starting3() {
  Set_Motor(100, -100, 50);   //Right Turn
  Set_Motor(100, 100, 200);   //Forward
  Set_Motor(-100, 100, 100);  //Left Turn
  Set_Motor(100, 100, 80);    //Forward
}

void starting4() {
  Set_Motor(-100, 100, 100);  //Left Turn
}

void standby() {  // Standby search opponent
  Set_Motor(60, -60, 1);
}

void routine() {
  Serial.println("Routine");
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
    if (distanceR > 40 && distanceL > 40) {  //if both sensors read more than 25 cm, brake both motors
      standby();
      Serial.println("Robot Standby");
    } else {
      stalking();
    }
  }
}

void stalking() {
  if (distanceR < 10 || distanceL < 10) {
    // Serial.println("Both Motor Forward");
    Set_Motor(100, 100, 1);
  } else if (distanceR < 40 && distanceL < 40) {  //if both sensors less than than 25 cm, go forward
    Set_Motor(100, 100, 1);
    // Serial.println("Both Motor Forward");
  } else if (distanceR > 40 && distanceL < 40) {  //if only something is in front of the left ultrasonic sensor, turn left
    Set_Motor(-90, 90, 1);                        //Left Turn
    // Serial.println("Turn Left");
  } else if (distanceR < 40 && distanceL > 40) {  //if only something is in front of the right ultrasonic sensor, turn right
    Set_Motor(90, -90, 1);                        //Right Turn
    // Serial.println("Turn Right");
  }
}

void whiteLine(int sensor) {
  // Reverse Straight
  if (sensor == 1) {  //Right sensor Detected
    // Serial.println("Moving Backward Right");
    Set_Motor(-50, -50, 450);  //Backward
  } else {                     //Left sensor Detected
    // Serial.println("Moving Backward Left");
    Set_Motor(-50, -50, 450);  //Backward
  }
  Set_Motor(60, -60, 1);
}

void Set_Motor(float Lval, float Rval, int timex) {  //Motor Control Function
  Lval = Lval * 2.5;
  Rval = Rval * 2.5;
  if (Lval >= 0) {
    analogWrite(LPwm, Lval);
    digitalWrite(LDir, LOW);
  } else {
    Lval = abs(Lval);
    digitalWrite(LDir, HIGH);
    analogWrite(LPwm, Lval);
  }
  if (Rval >= 0) {
    analogWrite(RPwm, Rval);
    digitalWrite(RDir, HIGH);
  } else {
    Rval = abs(Rval);
    digitalWrite(RDir, LOW);
    analogWrite(RPwm, Rval);
  }
  delay(timex);
}