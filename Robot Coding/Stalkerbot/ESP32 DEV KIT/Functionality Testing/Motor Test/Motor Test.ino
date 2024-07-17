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
int dutyCycleR = 200;
int dutyCycleL = 200;

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

  //Both Motor Forward
  digitalWrite(MotorRPin1, LOW);  // Right Forward
  digitalWrite(MotorRPin2, HIGH);
  digitalWrite(MotorLPin1, LOW);  // Left Forward
  digitalWrite(MotorLPin2, HIGH);
  ledcWrite(pwmChannelR, dutyCycleR);
  ledcWrite(pwmChannelL, dutyCycleL);
  Serial.println("Both Motor Forward");
  delay(3000);
  digitalWrite(MotorRPin1, LOW);  // Right Stop
  digitalWrite(MotorRPin2, LOW);
  digitalWrite(MotorLPin1, LOW);  // Left Stop
  digitalWrite(MotorLPin2, LOW);
  Serial.println("Both Motor Stop");
  delay(1000);
  digitalWrite(MotorRPin1, HIGH);  // Right Reverse
  digitalWrite(MotorRPin2, LOW);
  digitalWrite(MotorLPin1, HIGH);  // Left Reverse
  digitalWrite(MotorLPin2, LOW);
  ledcWrite(pwmChannelR, dutyCycleR);
  ledcWrite(pwmChannelL, dutyCycleL);
  Serial.println("Both Motor Reverse");
  delay(3000);
  digitalWrite(MotorRPin1, LOW);  // Right Stop
  digitalWrite(MotorRPin2, LOW);
  digitalWrite(MotorLPin1, LOW);  // Left Stop
  digitalWrite(MotorLPin2, LOW);
  Serial.println("Both Motor Stop");
  delay(1000);
}
