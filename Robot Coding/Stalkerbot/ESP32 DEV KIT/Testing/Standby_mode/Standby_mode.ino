// Motor A
int motor1Pin1 = 27;
int motor1Pin2 = 26;
int enable1Pin = 14;

// Motor B
int motor2Pin1 = 19;
int motor2Pin2 = 18;
int enable2Pin = 5;

// Setting LED pins
const int ledGreen = 21;  //const int means the value integer can't be changed in the program
const int ledRed = 22;
const int ledYellow = 23;

//ultrasonic sensor
const int trigPin1 = 12;
const int echoPin1 = 13;
const int trigPin2 = 2;
const int echoPin2 = 15;

// Setting PWM properties
const int freq = 30000;
const int pwm1Channel = 0;
const int pwm2Channel = 0;
const int resolution = 8;
int dutyCycle = 200;

// Setting Robot properties
int Attacking = 0;
int Evading = 0;

void setup() {
  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);

  // configure LED PWM functionalitites
  ledcSetup(pwm1Channel, freq, resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwm1Channel);

  // configure LED PWM functionalitites
  ledcSetup(pwm1Channel, freq, resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable2Pin, pwm2Channel);

  Serial.begin(115200);
  // testing
  Serial.print("Testing DC Motor...");
  //turn 45 deg
  //  Serial.println("Initial: Turn Right");
  //  digitalWrite(motor1Pin1, LOW);
  //  digitalWrite(motor1Pin2, HIGH);
  //  digitalWrite(motor2Pin1, HIGH);
  //  digitalWrite(motor2Pin2, LOW);
  //  delay(1000);

  //move forward
  // Serial.println("Move Forward");
  // digitalWrite(motor1Pin1, LOW);
  // digitalWrite(motor1Pin2, HIGH);
  // digitalWrite(motor2Pin1, LOW);
  // digitalWrite(motor2Pin2, HIGH);
  // delay(1000);
}

void loop() {
  long duration1, distance1;
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1 / 2) / 29.1;
  Serial.print("Distance US1: ");
  Serial.println(distance1);
  delay(200);

  long duration2, distance2;
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2 / 2) / 29.1;
  Serial.print("Distance US2: ");
  Serial.println(distance2);
  delay(200);

  if (distance1 <= 30 && distance2 <= 30) {
    Serial.println("Pause");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
    delay(500);
  } else {
    //Serial.println("Spinning");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
    //delay(500);
    while (dutyCycle <= 255) {
      ledcWrite(pwm1Channel, dutyCycle);
      ledcWrite(pwm2Channel, dutyCycle);
      Serial.print("Spinning with duty cycle: ");
      Serial.println(dutyCycle);
      dutyCycle = dutyCycle + 10;
      delay(100);
    }
    dutyCycle = 200;
  }
  Attacking == 0;
  Evading == 0;
}
