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

// Line sensor
const int LineR = 4;
const int LineL = 15;
int inputLineR = 0;
int inputLineL = 0;

// Motor Right
int MotorRPin1 = 25;  // Actual pin is 26
int MotorRPin2 = 26;  // Actual pin is 25
int ENB = 33;

// Motor Left
int ENA = 5;
int MotorLPin1 = 16;
int MotorLPin2 = 17;

// Setting PWM properties
const int freq = 30000;
const int pwmChannelR = 0;
const int pwmChannelL = 0;
const int resolution = 8;
const int dutyCycleLow = 180;
const int dutyCycleMid = 200;
const int dutyCycleHigh = 230;
;

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
  // Reading Line Sensor
  inputLineR = analogRead(LineR);
  inputLineL = analogRead(LineL);
  Serial.println(inputLineR);
  Serial.println(inputLineL);
  delay(1000);

  // Reading Distance Right
  digitalWrite(TrigPinR, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPinR, HIGH);  // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(TrigPinR, LOW);  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationR = pulseIn(EchoPinR, HIGH);
  distanceR = durationR * SOUND_SPEED / 2;  // Calculate the distance
  Serial.print("Distance Right Sensor: ");
  Serial.println(distanceR);
  // Reading Distance Right
  digitalWrite(TrigPinL, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPinL, HIGH);  // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(TrigPinL, LOW);  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationL = pulseIn(EchoPinL, HIGH);
  distanceL = durationL * SOUND_SPEED / 2;  // Calculate the distance
  Serial.print("Distance Left Sensor: ");
  Serial.println(distanceL);

  // Right Motor Testing
  digitalWrite(MotorRPin1, LOW);  // Right Forward
  digitalWrite(MotorRPin2, HIGH);
  ledcWrite(pwmChannelR, dutyCycleLow);
  Serial.println("Right Motor Forward");
  delay(3000);
  digitalWrite(MotorRPin1, LOW);  // Right Stop
  digitalWrite(MotorRPin2, LOW);
  Serial.println("Right Motor Stop");
  delay(1000);
  digitalWrite(MotorRPin1, HIGH);  // Right Reverse
  digitalWrite(MotorRPin2, LOW);
  ledcWrite(pwmChannelR, dutyCycleHigh);
  Serial.println("Right Motor Reverse");
  delay(3000);
  digitalWrite(MotorRPin1, LOW);  // Right Stop
  digitalWrite(MotorRPin2, LOW);
  Serial.println("Right Motor Stop");
  // Left Motor Testing
  digitalWrite(MotorLPin1, LOW);  // Left Forward
  digitalWrite(MotorLPin2, HIGH);
  ledcWrite(pwmChannelL, dutyCycleLow);
  Serial.println("Left Motor Forward");
  delay(3000);
  digitalWrite(MotorLPin1, LOW);  // Left Stop
  digitalWrite(MotorLPin2, LOW);
  Serial.println("Left Motor Stop");
  delay(1000);
  digitalWrite(MotorLPin1, HIGH);  // Left Reverse
  digitalWrite(MotorLPin2, LOW);
  ledcWrite(pwmChannelL, dutyCycleHigh);
  Serial.println("Left Motor Reverse");
  delay(3000);
  digitalWrite(MotorLPin1, LOW);  // Left Stop
  digitalWrite(MotorLPin2, LOW);
  Serial.println("Left Motor Stop");
}
