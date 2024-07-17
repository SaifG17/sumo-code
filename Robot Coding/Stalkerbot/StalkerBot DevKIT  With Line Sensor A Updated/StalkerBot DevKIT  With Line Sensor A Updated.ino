// Ultrasonic sensor
const int TrigPinR = 13;
const int EchoPinR = 12;
const int TrigPinL = 14;
const int EchoPinL = 27;

//Ultrasonic variables
long durationR;
long durationL;
float distanceR;
float distanceL;

// Motor Right
int ENA = 33;
int MotorRPin1 = 25;
int MotorRPin2 = 26;

// Motor Left
int MotorLPin1 = 16;
int MotorLPin2 = 17;
int ENB = 5;

// Setting PWM properties
const int freq = 30000;
const int pwmChannelR = 0;
const int pwmChannelL = 0;
const int resolution = 8;
const int dutyCycleLow = 180;
const int dutyCycleMid = 200;
const int dutyCycleHigh = 230;

// Line sensor
const int LineR = 4;
const int LineL = 15;
int inputLineR = 0;
int inputLineL = 0;

void setup() {

  // Ultrasonic sensor Right
  pinMode(TrigPinR, OUTPUT);  // Sets the trigPin as an Output
  pinMode(EchoPinR, INPUT);   // Sets the echoPin as an Input
  // Ultrasonic sensor Left
  pinMode(TrigPinL, OUTPUT);  // Sets the trigPin as an Output
  pinMode(EchoPinL, INPUT);   // Sets the echoPin as an Input

  // Right Motor
  pinMode(MotorRPin1, OUTPUT);
  pinMode(MotorRPin2, OUTPUT);
  pinMode(ENB, OUTPUT);
  ledcSetup(pwmChannelR, freq, resolution);  // configure LED PWM functionalitites
  ledcAttachPin(ENB, pwmChannelR);           // attach the channel to the GPIO to be controlled
  // Left Motor
  pinMode(MotorLPin1, OUTPUT);
  pinMode(MotorLPin2, OUTPUT);
  pinMode(ENA, OUTPUT);
  ledcSetup(pwmChannelL, freq, resolution);  // configure LED PWM functionalitites
  ledcAttachPin(ENA, pwmChannelL);           // attach the channel to the GPIO to be controlled

  // Line Sensor
  pinMode(LineR, INPUT);  // Sets Right Line Sensor
  pinMode(LineL, INPUT);  // Sets Left Line Sensor

  Serial.begin(115200);
  delay(4500);
  digitalWrite(MotorRPin1, LOW);  // Right Forward
  digitalWrite(MotorRPin2, HIGH);
  digitalWrite(MotorLPin1, LOW);  // Left Forward
  digitalWrite(MotorLPin2, HIGH);
  ledcWrite(pwmChannelR, dutyCycleHigh);
  ledcWrite(pwmChannelL, dutyCycleHigh);
  delay(900);
  digitalWrite(MotorRPin1, LOW);  // Right Forward
  digitalWrite(MotorRPin2, HIGH);
  digitalWrite(MotorLPin1, HIGH);  // Left Reverse
  digitalWrite(MotorLPin2, LOW);
  ledcWrite(pwmChannelR, dutyCycleLow);
  ledcWrite(pwmChannelL, dutyCycleLow);
  delay(500);
  digitalWrite(MotorRPin1, LOW);  // Right Forward
  digitalWrite(MotorRPin2, HIGH);
  digitalWrite(MotorLPin1, LOW);  // Left Forward
  digitalWrite(MotorLPin2, HIGH);
  ledcWrite(pwmChannelR, dutyCycleHigh);
  ledcWrite(pwmChannelL, dutyCycleHigh);
  delay(400);
  // Serial.print("Testing StalkerBot...");
}

void loop() {
  // Reading Line Sensor
  inputLineR = analogRead(LineR);
  inputLineL = analogRead(LineL);
  // Serial.println(inputLineR);
  // Serial.println(inputLineL);

  // Reverse when white detected
  if (inputLineR <= 3000 || inputLineL <= 3000) {  //Check the sensor output
    if (inputLineR <= 3800) {
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
}

void standby() {                  // Standby search opponent
  digitalWrite(MotorRPin1, LOW);  // Right Forward
  digitalWrite(MotorRPin2, HIGH);
  digitalWrite(MotorLPin1, HIGH);  // Left Reverse
  digitalWrite(MotorLPin2, LOW);
  ledcWrite(pwmChannelR, dutyCycleLow);
  ledcWrite(pwmChannelL, dutyCycleLow);
}

void stalking() {
  if (distanceR < 30 && distanceL < 30) {  //if both sensors less than than 25 cm, go forward
    digitalWrite(MotorRPin1, LOW);         // Right Forward
    digitalWrite(MotorRPin2, HIGH);
    digitalWrite(MotorLPin1, LOW);  // Left Forward
    digitalWrite(MotorLPin2, HIGH);
    ledcWrite(pwmChannelR, dutyCycleHigh);
    ledcWrite(pwmChannelL, dutyCycleHigh);
    // Serial.println("Both Motor Forward");
  }

  if (distanceR > 30 && distanceL < 30) {  //if only something is in front of the left ultrasonic sensor, turn left
    digitalWrite(MotorRPin1, LOW);         // Right Forward
    digitalWrite(MotorRPin2, HIGH);
    digitalWrite(MotorLPin1, LOW);  // Left Stop
    digitalWrite(MotorLPin2, LOW);
    ledcWrite(pwmChannelR, dutyCycleLow);
    ledcWrite(pwmChannelL, dutyCycleLow);
    // Serial.println("Turn Left");
  }

  if (distanceR < 30 && distanceL > 30) {  //if only something is in front of the right ultrasonic sensor, turn right
    digitalWrite(MotorRPin1, LOW);         // Right Stop
    digitalWrite(MotorRPin2, LOW);
    digitalWrite(MotorLPin1, LOW);  // Left Forward
    digitalWrite(MotorLPin2, HIGH);
    ledcWrite(pwmChannelR, dutyCycleLow);
    ledcWrite(pwmChannelL, dutyCycleLow);
    // Serial.println("Turn Right");
  }
}

void whiteLine(int sensor) {
  if (sensor == 1) {                 //Right sensor Detected
    digitalWrite(MotorRPin1, HIGH);  // Right Reverse
    digitalWrite(MotorRPin2, LOW);
    digitalWrite(MotorLPin1, HIGH);  // Left Reverse
    digitalWrite(MotorLPin2, LOW);
    ledcWrite(pwmChannelR, dutyCycleMid);
    ledcWrite(pwmChannelL, dutyCycleMid);
    delay(800);
  } else {                           //Left sensor Detected
    digitalWrite(MotorRPin1, HIGH);  // Right Reverse
    digitalWrite(MotorRPin2, LOW);
    digitalWrite(MotorLPin1, HIGH);  // Left Reverse
    digitalWrite(MotorLPin2, LOW);
    ledcWrite(pwmChannelR, dutyCycleMid);
    ledcWrite(pwmChannelL, dutyCycleMid);
    delay(800);
  }
  digitalWrite(MotorRPin1, LOW);  // Right Forward
  digitalWrite(MotorRPin2, HIGH);
  digitalWrite(MotorLPin1, HIGH);  // Left Reverse
  digitalWrite(MotorLPin2, LOW);
  ledcWrite(pwmChannelR, dutyCycleLow);
  ledcWrite(pwmChannelL, dutyCycleLow);
}
