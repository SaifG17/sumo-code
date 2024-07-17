//MOTOR CONTROL
int RPwm = 10;
int RDir = 13;
int LPwm = 9;
int LDir = 5;

//LED & BUZZER
int Speaker = A0;
int Led = A3;


// DIPSWITCH & BUTTON
int Button = 11;  // Can be used as start pin too.
int DS1 = 6;
int DS2 = 7;
int DS3 = 8;

void setup() {
  pinMode(Speaker, OUTPUT);  // Speaker Declared as Output
  pinMode(Led, OUTPUT);      // Led Declared as Output
  pinMode(Button, INPUT);    // Button Declared as Input

  pinMode(RPwm, OUTPUT);  // 2 PWM Channel Declared as Output
  pinMode(RDir, OUTPUT);
  pinMode(LPwm, OUTPUT);
  pinMode(LDir, OUTPUT);

  digitalWrite(Speaker, LOW);  // Speaker Pin Made Low for Silence
  digitalWrite(Led, LOW);      // Arduino Mode Led Made Low
  digitalWrite(DS1, HIGH);     // 3 Dipswitch Pin Pullups Made
  digitalWrite(DS2, HIGH);
  digitalWrite(DS3, HIGH);



  Serial.begin(9600);
  tone(Speaker, 523, 300);
  delay(300);
  noTone(Speaker);
  digitalWrite(RPwm, LOW);
  digitalWrite(LPwm, LOW);
}

//Motor Control Function
void Set_Motor(float Lval, float Rval, int timex) {
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
void loop() {
  digitalWrite(Led, LOW);
  Serial.println("Stop");
  Set_Motor(0, 0, 2000);

  digitalWrite(Led, HIGH);
  Serial.println("Forward");
  Set_Motor(50, 50, 1000);

  digitalWrite(Led, LOW);
  Serial.println("Stop");
  Set_Motor(0, 0, 2000);

  digitalWrite(Led, HIGH);
  Serial.println("Backward");
  Set_Motor(-50, -50, 1000);
}
