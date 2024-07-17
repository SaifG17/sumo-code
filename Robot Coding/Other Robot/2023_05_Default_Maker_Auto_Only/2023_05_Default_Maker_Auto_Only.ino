
int pin_ed_L = A0;
int pin_ed_R = A1;
// set edge sensor

int threshold_L = 300;
int threshold_R = 300;
//edge sensor threshold

const int dirl = 4;
const int pwml = 3;
const int dirr = 10;
const int pwmr = 11;

int pin_L = 12;
int pin_FL = 5;
int pin_FC = 6;
int pin_FR = 7;
int pin_R = 13;

int pin_mode = A6;

int p_button1 = 2;
int button1 = 0;

int speed_normal = 60;
int speed_new;
float speed_inc = 2;
float speed_inc_2 = 4;
int speed_mode = 0;


void read_button() {
  button1 = digitalRead(p_button1);
}


int ed_L, ed_R = 0;
void read_edge() {
  int adc_ed_L = analogRead(pin_ed_L);
  int adc_ed_R = analogRead(pin_ed_R);

  if (adc_ed_L < threshold_L) {
    ed_L = 0;
  } else {
    ed_L = 1;
  }

  if (adc_ed_R < threshold_R) {
    ed_R = 0;
  } else {
    ed_R = 1;
  }
}



void motorsteer(char *robotdirection, int power) {
  if (robotdirection == "forward") {
    digitalWrite(dirl, HIGH);
    analogWrite(pwml, power);
    digitalWrite(dirr, LOW);
    analogWrite(pwmr, power);
  } else if (robotdirection == "backward") {
    digitalWrite(dirl, LOW);
    analogWrite(pwml, power);
    // digitalWrite(dirr, HIGH);
    // analogWrite(pwmr, power);
  } else if (robotdirection == "right") {
    digitalWrite(dirl, HIGH);
    analogWrite(pwml, power);
    digitalWrite(dirr, LOW);
    analogWrite(pwmr, power / 3);
  } else if (robotdirection == "rightatC") {
    digitalWrite(dirl, HIGH);
    analogWrite(pwml, power);
    digitalWrite(dirr, HIGH);
    analogWrite(pwmr, power);
  } else if (robotdirection == "left") {
    digitalWrite(dirl, HIGH);
    analogWrite(pwml, power / 3);
    digitalWrite(dirr, LOW);
    analogWrite(pwmr, power);
  } else if (robotdirection == "leftatC") {
    digitalWrite(dirl, LOW);
    analogWrite(pwml, power);
    digitalWrite(dirr, LOW);
    analogWrite(pwmr, power);
  } else if (robotdirection == "stop") {
    digitalWrite(dirl, HIGH);
    analogWrite(pwml, 0);
    digitalWrite(dirr, HIGH);
    analogWrite(pwmr, 0);
  } else {
    digitalWrite(dirl, HIGH);
    analogWrite(pwml, 0);
    digitalWrite(dirr, LOW);
    analogWrite(pwmr, 0);
  }
}


void motordrive(char *directionL, int powerL, char *directionR, int powerR) {
  if (directionL == "forward") {
    digitalWrite(dirl, HIGH);
  } else if (directionL == "backward") {
    digitalWrite(dirl, LOW);
  }
  if (directionR == "forward") {
    digitalWrite(dirr, LOW);
  } else if (directionR == "backward") {
    digitalWrite(dirr, HIGH);
  }
  analogWrite(pwml, powerL);
  analogWrite(pwmr, powerR);
}



int read_dip_mode(void) {
  int adc = analogRead(pin_mode);
  if (adc > 933) return 0;
  if (adc > 773) return 1;
  if (adc > 658) return 2;
  if (adc > 563) return 3;
  if (adc > 487) return 4;
  if (adc > 440) return 5;
  if (adc > 400) return 6;
  return 7;
}


void setup() {

  Serial.begin(9600);

  pinMode(A4, OUTPUT);

  pinMode(dirl, OUTPUT);
  pinMode(dirr, OUTPUT);
  pinMode(pwml, OUTPUT);
  pinMode(pwmr, OUTPUT);

  pinMode(pin_L, INPUT_PULLUP);
  pinMode(pin_FL, INPUT_PULLUP);
  pinMode(pin_FC, INPUT_PULLUP);
  pinMode(pin_FR, INPUT_PULLUP);
  pinMode(pin_R, INPUT_PULLUP);


  pinMode(p_button1, INPUT_PULLUP);


  digitalWrite(A4, HIGH);
  delay(1000);
  digitalWrite(A4, LOW);

  speed_new = speed_normal;
}

void loop() {

  Serial.print(read_dip_mode());
  Serial.print("\t");
  Serial.print(analogRead(pin_ed_L));
  Serial.print("\t");
  Serial.println(analogRead(pin_ed_R));

  read_button();


  if (button1 == 0)  //untuk button on-board=0
  {
    digitalWrite(A4, HIGH);
    // Jangan lupa..Peraturan kne start button kemudian 5 saat selepas tu baru bergerak
    delay(5000);
    digitalWrite(A4, LOW);

    run_starting_move();
    //motorsteer("forward", 0); delay(2000);


    run_auto_sumo();

  } else {
    motorsteer("forward", 0);
  }
}
