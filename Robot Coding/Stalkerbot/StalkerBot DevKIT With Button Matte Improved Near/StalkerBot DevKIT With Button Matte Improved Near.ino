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

// Button
const int BUTTON_PIN = 22;  // the number of the pushbutton pin
int status = 1;
int att = 1;

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
  pinMode(ENA, OUTPUT);
  ledcSetup(pwmChannelR, freq, resolution);  // configure LED PWM functionalitites
  ledcAttachPin(ENA, pwmChannelR);           // attach the channel to the GPIO to be controlled
  // Left Motor
  pinMode(MotorLPin1, OUTPUT);
  pinMode(MotorLPin2, OUTPUT);
  pinMode(ENB, OUTPUT);
  ledcSetup(pwmChannelL, freq, resolution);  // configure LED PWM functionalitites
  ledcAttachPin(ENB, pwmChannelL);           // attach the channel to the GPIO to be controlled
  // Button
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);

  while (buttonState == HIGH) {
    if (status == 1) {
      Serial.println("Starting");
      delay(5000);
      starting();
    }
    // Reading Right Line Sensor
    inputLineR = analogRead(LineR);
    inputLineL = analogRead(LineL);
    // Serial.println(inputLineR);
    // Serial.println(inputLineL);

    // Reverse when white detected
    if ((inputLineR <= 2800 || inputLineL <= 3000) && att == 1) {  //Check the sensor output
      if (inputLineR <= 2800) {
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
      if ((distanceR > 30 && distanceL > 30) || (distanceR < 1200 && distanceL < 1200)) {  //if both sensors read more than 25 cm, brake both motors
        standby();
        // Serial.println("Robot Standby");
        att = 1;
      } else {
        att = 0;
        stalking();
      }
    }
    status = 0;
    buttonState = digitalRead(BUTTON_PIN);  // read the state of the button again
  }
  digitalWrite(MotorRPin1, LOW);  // Right Stop
  digitalWrite(MotorRPin2, LOW);
  digitalWrite(MotorLPin1, LOW);  // Left Stop
  digitalWrite(MotorLPin2, LOW);
  status = 1;
}

void starting() {
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
  delay(450);
  digitalWrite(MotorRPin1, LOW);  // Right Forward
  digitalWrite(MotorRPin2, HIGH);
  digitalWrite(MotorLPin1, LOW);  // Left Forward
  digitalWrite(MotorLPin2, HIGH);
  ledcWrite(pwmChannelR, dutyCycleHigh);
  ledcWrite(pwmChannelL, dutyCycleHigh);
  delay(400);
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
  if (distanceR < 5 || distanceL < 5) {
    digitalWrite(MotorRPin1, LOW);  // Right Forward
    digitalWrite(MotorRPin2, HIGH);
    digitalWrite(MotorLPin1, LOW);  // Left Forward
    digitalWrite(MotorLPin2, HIGH);
    ledcWrite(pwmChannelR, dutyCycleHigh);
    ledcWrite(pwmChannelL, dutyCycleHigh);
  } else if (distanceR > 1200 || distanceL > 1200) {
    digitalWrite(MotorRPin1, HIGH);  // Right Reverse
    digitalWrite(MotorRPin2, LOW);
    digitalWrite(MotorLPin1, HIGH);  // Left Reverse
    digitalWrite(MotorLPin2, LOW);
    ledcWrite(pwmChannelR, dutyCycleHigh);
    ledcWrite(pwmChannelL, dutyCycleHigh);
    delay(200);
    digitalWrite(MotorRPin1, LOW);  // Right Forward
    digitalWrite(MotorRPin2, HIGH);
    digitalWrite(MotorLPin1, LOW);  // Left Forward
    digitalWrite(MotorLPin2, HIGH);
    ledcWrite(pwmChannelR, dutyCycleHigh);
    ledcWrite(pwmChannelL, dutyCycleHigh);
  } else if ((distanceR < 30 && distanceL < 30) || (distanceR > 1200 && distanceL > 1200)) {  //if both sensors less than than 25 cm, go forward
    digitalWrite(MotorRPin1, LOW);                                                            // Right Forward
    digitalWrite(MotorRPin2, HIGH);
    digitalWrite(MotorLPin1, LOW);  // Left Forward
    digitalWrite(MotorLPin2, HIGH);
    ledcWrite(pwmChannelR, dutyCycleHigh);
    ledcWrite(pwmChannelL, dutyCycleHigh);
    // Serial.println("Both Motor Forward");
  } else if ((distanceR > 30 && distanceL < 30) || (distanceR > 30 && distanceL > 1200)) {  //if only something is in front of the left ultrasonic sensor, turn left
    digitalWrite(MotorRPin1, LOW);                                                          // Right Forward
    digitalWrite(MotorRPin2, HIGH);
    digitalWrite(MotorLPin1, LOW);  // Left Stop
    digitalWrite(MotorLPin2, LOW);
    ledcWrite(pwmChannelR, dutyCycleLow);
    ledcWrite(pwmChannelL, dutyCycleLow);
    // Serial.println("Turn Left");
  } else if ((distanceR < 30 && distanceL > 30) || (distanceR > 1200 && distanceL > 30)) {  //if only something is in front of the right ultrasonic sensor, turn right
    digitalWrite(MotorRPin1, LOW);                                                          // Right Stop
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
    delay(650);
  } else {                           //Left sensor Detected
    digitalWrite(MotorRPin1, HIGH);  // Right Reverse
    digitalWrite(MotorRPin2, LOW);
    digitalWrite(MotorLPin1, HIGH);  // Left Reverse
    digitalWrite(MotorLPin2, LOW);
    ledcWrite(pwmChannelR, dutyCycleMid);
    ledcWrite(pwmChannelL, dutyCycleMid);
    delay(650);
  }
  digitalWrite(MotorRPin1, LOW);  // Right Forward
  digitalWrite(MotorRPin2, HIGH);
  digitalWrite(MotorLPin1, HIGH);  // Left Reverse
  digitalWrite(MotorLPin2, LOW);
  ledcWrite(pwmChannelR, dutyCycleLow);
  ledcWrite(pwmChannelL, dutyCycleLow);
}
