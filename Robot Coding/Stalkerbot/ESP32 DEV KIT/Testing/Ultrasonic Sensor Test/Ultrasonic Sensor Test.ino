// Motor Left
int ENA = 19;
int MotorLPin1 = 18;
int MotorLPin2 = 5;

// Motor Right
int ENB = 25;
int MotorRPin1 = 26;
int MotorRPin2 = 27;

// Ultrasonic sensor
const int TrigPinR = 12;
const int EchoPinR = 14;
const int TrigPinL = 33;
const int EchoPinL = 32;

// Line sensor
const int LineR = 4;
const int LineL = 15;
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

  // Reading Line Sensor
  if (analogRead(LineL) >= 2000)  //Check the sensor output
  {
    inputLineL = 1;  // Black
  } else {
    inputLineL = 0;  // White
  }
  Serial.println(analogRead(LineL));
  Serial.println(inputLineL);
  delay(1000);

  // Reading Distance Right
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
  distanceL = durationL * SOUND_SPEED / 2;  // Calculate the distance
  Serial.print("Distance Left Sensor: ");
  Serial.println(distanceL);
}

void spinning() {  // Standby to attack (turn around at the same place
  //Serial.println("Spinning");
  digitalWrite(MotorRPin1, LOW);
  digitalWrite(MotorRPin2, HIGH);
  digitalWrite(MotorLPin1, HIGH);
  digitalWrite(MotorLPin2, LOW);
}

void attacking() {  // Move Forward push opponent down
  digitalWrite(MotorRPin1, LOW);
  digitalWrite(MotorRPin2, HIGH);
  digitalWrite(MotorLPin1, LOW);
  digitalWrite(MotorLPin2, HIGH));
}

void linedetect(int sensorside) {  // reverse then turn
  // Reverse
  digitalWrite(MotorRPin1, HIGH);
  digitalWrite(MotorRPin2, LOW);
  digitalWrite(MotorLPin1, HIGH);
  digitalWrite(MotorLPin2, LOW);
  // Turn
  if (sensorside == LEFT) {
    // Rotate left backward.
    digitalWrite(MotorRPin1, LOW);
    digitalWrite(MotorRPin2, LOW);
    digitalWrite(MotorLPin1, LOW);
    digitalWrite(MotorLPin2, HIGH);
  } else {
    // Rotate right backward.
    digitalWrite(MotorRPin1, LOW);
    digitalWrite(MotorRPin2, HIGH);
    digitalWrite(MotorLPin1, LOW;
    digitalWrite(MotorLPin2, LOW);
  }
  delay(600);
}
