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

  Serial.begin(115200);
  Serial.print("Testing DC Motor...");
}

void loop() {
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
