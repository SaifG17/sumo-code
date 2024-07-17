// Motor Right
int ENA = 19;
int MotorRPin1 = 18;
int MotorRPin2 = 5;

// Motor Left
int MotorLPin1 = 25;
int MotorLPin2 = 26;
int ENB = 27;

// Ultrasonic sensor
const int TrigPinR = 12;
const int EchoPinR = 14;
const int TrigPinL = 33;
const int EchoPinL = 32;

// Line sensor
const int LineR = 4;
const int LineL = 15;
int inputLineR = 0;
int inputLineL = 0;

// Setting PWM properties
const int freq = 30000;
const int pwmChannelR = 0;
const int pwmChannelL = 0;
const int resolution = 8;
int dutyCycle = 200;

//Ultrasonic variables
long durationR;
long durationL;
float distanceR;
float distanceL;


void setup() {
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
  // Ultrasonic sensor Right
  pinMode(TrigPinR, OUTPUT);  // Sets the trigPin as an Output
  pinMode(EchoPinR, INPUT);   // Sets the echoPin as an Input
  // Ultrasonic sensor Left
  pinMode(TrigPinL, OUTPUT);  // Sets the trigPin as an Output
  pinMode(EchoPinL, INPUT);   // Sets the echoPin as an Input
  // Line Sensor
  pinMode(LineR, INPUT);  // Sets Right Line Sensor
  pinMode(LineL, INPUT);  // Sets Left Line Sensor
  Serial.begin(115200);
  Serial.print("Testing DC Motor...");
}

void loop() {

  // // Right Motor
  // digitalWrite(MotorRPin1, LOW);  // Right Forward
  // digitalWrite(MotorRPin2, HIGH);
  // ledcWrite(pwmChannelR, dutyCycle);
  // Serial.println("Right Motor Forward");
  // delay(5000);
  // digitalWrite(MotorRPin1, LOW);  // Right Stop
  // digitalWrite(MotorRPin2, LOW);
  // Serial.println("Right Motor Stop");
  // delay(2000);
  // digitalWrite(MotorRPin1, HIGH);  // Right Reverse
  // digitalWrite(MotorRPin2, LOW);
  // ledcWrite(pwmChannelR, dutyCycle);
  // Serial.println("Right Motor Reverse");
  // delay(5000);
  // digitalWrite(MotorRPin1, LOW);  // Right Stop
  // digitalWrite(MotorRPin2, LOW);
  // Serial.println("Right Motor Stop");
  // delay(2000);

  // // Left Motor
  // digitalWrite(MotorLPin1, LOW);  //  Left Forward
  // digitalWrite(MotorLPin2, HIGH);
  // ledcWrite(pwmChannelL, dutyCycle);
  // Serial.println("Motor Left Forward");
  // delay(5000);
  // digitalWrite(MotorLPin1, LOW);  // Left Stop
  // digitalWrite(MotorLPin2, LOW);
  // delay(2000);
  // digitalWrite(MotorLPin1, HIGH);  // Left Reverse
  // digitalWrite(MotorLPin2, LOW);
  // ledcWrite(pwmChannelL, dutyCycle);
  // Serial.println("Motor Left Reverse");
  // delay(5000);
  // digitalWrite(MotorLPin1, LOW);  // Left Stop
  // digitalWrite(MotorLPin2, LOW);
  // delay(2000);

  // //Both Motor Forward
  // digitalWrite(MotorRPin1, LOW);  // Right Forward
  // digitalWrite(MotorRPin2, HIGH);
  // digitalWrite(MotorLPin1, LOW);  // Left Forward
  // digitalWrite(MotorLPin2, HIGH);
  // ledcWrite(pwmChannelR, dutyCycle);
  // ledcWrite(pwmChannelL, dutyCycle);
  // Serial.println("Both Motor Forward");
  // delay(5000);
  // digitalWrite(MotorRPin1, LOW);  // Right Stop
  // digitalWrite(MotorRPin2, LOW);
  // digitalWrite(MotorLPin1, LOW);  // Left Stop
  // digitalWrite(MotorLPin2, LOW);
  // Serial.println("Both Motor Stop");
  // delay(2000);
  // digitalWrite(MotorRPin1, HIGH);  // Right Reverse
  // digitalWrite(MotorRPin2, LOW);
  // digitalWrite(MotorLPin1, HIGH);  // Left Reverse
  // digitalWrite(MotorLPin2, LOW);
  // ledcWrite(pwmChannelR, dutyCycle);
  // ledcWrite(pwmChannelL, dutyCycle);
  // Serial.println("Both Motor Reverse");
  // delay(5000);
  // digitalWrite(MotorRPin1, LOW);  // Right Stop
  // digitalWrite(MotorRPin2, LOW);
  // digitalWrite(MotorLPin1, LOW);  // Left Stop
  // digitalWrite(MotorLPin2, LOW);
  // Serial.println("Both Motor Stop");
  // delay(2000);

  // // Reading Right Line Sensor
  // if (analogRead(LineR) >= 3000)  //Check the sensor output
  // {
  //   inputLineR = 1;  // Black
  // } else {
  //   inputLineR = 0;  // White
  // }
  // Serial.println(analogRead(LineR));
  // Serial.println(inputLineR);

  // // Reading Left Line Sensor
  // if (analogRead(LineL) >= 3000)  //Check the sensor output
  // {
  //   inputLineL = 1;  // Black
  // } else {
  //   inputLineL = 0;  // White
  // }
  // Serial.println(analogRead(LineL));
  // Serial.println(inputLineL);
  // delay(1000);

  // Reading Distance Right
  // digitalWrite(TrigPinR, LOW);
  // delayMicroseconds(2);
  // digitalWrite(TrigPinR, HIGH);  // Sets the trigPin on HIGH state for 10 micro seconds
  // delayMicroseconds(10);
  // digitalWrite(TrigPinR, LOW);  // Reads the echoPin, returns the sound wave travel time in microseconds
  // durationR = pulseIn(EchoPinR, HIGH);
  // distanceR = (durationR / 2) / 29.1;  // Calculate the distance
  // Serial.print("Distance Right Sensor: ");
  // Serial.println(distanceR);

  // Reading Distance Left
  // digitalWrite(TrigPinL, LOW);
  // delayMicroseconds(2);
  // digitalWrite(TrigPinL, HIGH);  // Sets the trigPin on HIGH state for 10 micro seconds
  // delayMicroseconds(10);
  // digitalWrite(TrigPinL, LOW);  // Reads the echoPin, returns the sound wave travel time in microseconds
  // durationL = pulseIn(EchoPinL, HIGH);
  // distanceL = (durationL / 2) / 29.1;  // Calculate the distance
  // Serial.print("Distance Left Sensor: ");

  // standby();
  // attack();
  // delay(5000);
  // whiteLine(1); // Right Line sensor Detected
  // whiteLine(2); // Left Line sensor Detected
  digitalWrite(MotorRPin1, LOW);  // Right Stop
  digitalWrite(MotorRPin2, LOW);
  digitalWrite(MotorLPin1, LOW);  // Left Stop
  digitalWrite(MotorLPin2, LOW);
  Serial.println("Both Motor Stop");
  delay(2000);
}

void standby() {
  digitalWrite(MotorRPin1, HIGH);  // Right Reverse
  digitalWrite(MotorRPin2, LOW);
  digitalWrite(MotorLPin1, LOW);  // Left Forward
  digitalWrite(MotorLPin2, HIGH);
  ledcWrite(pwmChannelR, dutyCycle);
  ledcWrite(pwmChannelL, dutyCycle);
  Serial.println("Standby");
}

void attack() {
  digitalWrite(MotorRPin1, LOW);  // Right Forward
  digitalWrite(MotorRPin2, HIGH);
  digitalWrite(MotorLPin1, LOW);  // Left Forward
  digitalWrite(MotorLPin2, HIGH);
  ledcWrite(pwmChannelR, dutyCycle);
  ledcWrite(pwmChannelL, dutyCycle);
  Serial.println("Attack");
}

void whiteLine(int sensor) {
  Serial.println("White Line Detected");
  digitalWrite(MotorRPin1, HIGH);  // Right Reverse
  digitalWrite(MotorRPin2, LOW);
  digitalWrite(MotorLPin1, HIGH);  // Left Reverse
  digitalWrite(MotorLPin2, LOW);
  ledcWrite(pwmChannelR, dutyCycle);
  ledcWrite(pwmChannelL, dutyCycle);
  Serial.println("Reverse");
  delay(5000);
  if (sensor == 1) {
    Serial.println("Turn Right");
    digitalWrite(MotorRPin1, HIGH);  // Right Reverse
    digitalWrite(MotorRPin2, LOW);
    digitalWrite(MotorLPin1, LOW);  // Left Forward
    digitalWrite(MotorLPin2, HIGH);
    ledcWrite(pwmChannelR, dutyCycle);
    ledcWrite(pwmChannelL, dutyCycle);
    delay(5000);
  } else {
    Serial.println("Turn Left");
    digitalWrite(MotorRPin1, LOW);  // Right Forward
    digitalWrite(MotorRPin2, HIGH);
    digitalWrite(MotorLPin1, HIGH);  // Left Reverse
    digitalWrite(MotorLPin2, LOW);
    ledcWrite(pwmChannelR, dutyCycle);
    ledcWrite(pwmChannelL, dutyCycle);
    delay(5000);
  }
}
