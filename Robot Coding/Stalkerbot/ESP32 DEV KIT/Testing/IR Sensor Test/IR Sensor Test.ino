// Motor Left
int ENA = 14;
int MotorLPin1 = 27;
int MotorLPin2 = 26;

// Motor Right
int MotorRPin1 = 19;
int MotorRPin2 = 18;
int ENB = 5;

// Ultrasonic sensor
const int TrigPinR = 33;
const int EchoPinR = 32;
const int TrigPinL = 13;
const int EchoPinL = 12;

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
#define SOUND_SPEED 0.034
long duration;
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
  pinMode(LineL, INPUT);
  Serial.begin(115200);
  Serial.print("Testing DC Motor...");
}

void loop() {

  // Reading Line Sensor
  if (analogRead(LineL) >= 2000)  //Check the sensor output
  {
    inputLineL = 1; // Black
  } else {
    inputLineL = 0;  // White
  }
  Serial.println(inputLineL);

  // // Reading Distance Right
  // digitalWrite(TrigPinR, LOW);
  // delayMicroseconds(2);
  // digitalWrite(TrigPinR, HIGH);  // Sets the trigPin on HIGH state for 10 micro seconds
  // delayMicroseconds(10);
  // digitalWrite(TrigPinR, LOW);  // Reads the echoPin, returns the sound wave travel time in microseconds
  // durationR = pulseIn(EchoPinR, HIGH);
  // distanceR = durationR * SOUND_SPEED / 2;  // Calculate the distance
  // Serial.print("Distance Right Sensor: ");
  // Serial.println(distanceR);
  // // Reading Distance Right
  // digitalWrite(TrigPinL, LOW);
  // delayMicroseconds(2);
  // digitalWrite(TrigPinL, HIGH);  // Sets the trigPin on HIGH state for 10 micro seconds
  // delayMicroseconds(10);
  // digitalWrite(TrigPinL, LOW);  // Reads the echoPin, returns the sound wave travel time in microseconds
  // durationL = pulseIn(EchoPinL, HIGH);
  // distanceL = durationL * SOUND_SPEED / 2;  // Calculate the distance
  // Serial.print("Distance Left Sensor: ");
  // Serial.println(distanceL);
}


