/*8-12-2023 buanG MPU6050, TUKAR SENSOR fs80Nk
*/

char str[4];
char buf[11];
String cond;
//-------------------- PIN DEFINITION TENGOK ROBOT DARI TAYAR untuk tau left right
#define RIGHT_IR_SENSOR A3
#define MIDDLE_IR_SENSOR A2 //tukar dari A1
#define LEFT_IR_SENSOR A1
#define TRUERIGHT_IR_SENSOR A0
#define TRUELEFT_IR_SENSOR  4  // tukar dariA4, A4 & A5 for i2c MPU6050
#define RIGHT_EDGE_SENSOR A6
#define LEFT_EDGE_SENSOR A7
#define PIN_START1 7 // 7
#define PIN_START2 12 //8
#define PIN_START3 8 //9
#define PIN_START4 9//12
#define MOTOR_A_RPWM 5
#define MOTOR_A_LPWM 6
#define MOTOR_B_RPWM 10
#define MOTOR_B_LPWM 11


//-------------------- END OFF PIN DEFINITION

#define motorOn 1 //------------------------------ sini kalau nak off motor
#define thold_edge 200
#define thold_turn 160
#define thold_obs 1


const int delayloophit = 10, delayturn = 10, delayBackward = 300, delayloophitonce = 6;
int pwmVal = 90;
const int pwmRev = 60;
const int pwmTurn = 70;
const int pwmTurnFast = 150;// turning to opponent
const int pwmTurnFast2 = 105;
const int pwmHit = 255;

int trueRight, rightIR, middleIR, trueLeft, leftIR, rightEdgeIR, leftEdgeIR ;
int detectOppo = 0;
int toaccel = 1;
int toHit;
float initAngleY, angleY;
const int Strategy = 1;
const int tracerOnly = 0;
const int serialOn = 0;
int state = 0;
int teststate = 0;//test initial method infinitely

void setup() {
  // u8g2.begin();
  if (serialOn == 1) {
    Serial.begin(9600);
  }
  // Configure pin modes
  //Wire.begin();
  //mpu6050.begin();
  // mpu6050.calcGyroOffsets(true);
  pinMode(PIN_START1, INPUT_PULLUP);
  pinMode(PIN_START2, INPUT_PULLUP);
  pinMode(PIN_START3, INPUT_PULLUP);
  pinMode(PIN_START4, INPUT_PULLUP);
  pinMode(RIGHT_IR_SENSOR, INPUT);
  pinMode(MIDDLE_IR_SENSOR, INPUT_PULLUP);
  pinMode(LEFT_IR_SENSOR, INPUT);
  pinMode(RIGHT_EDGE_SENSOR, INPUT);
  pinMode(LEFT_EDGE_SENSOR, INPUT);
  pinMode(TRUERIGHT_IR_SENSOR, INPUT);
  pinMode(TRUELEFT_IR_SENSOR, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(MOTOR_A_RPWM, OUTPUT);
  pinMode(MOTOR_A_LPWM, OUTPUT);
  pinMode(MOTOR_B_RPWM, OUTPUT);
  pinMode(MOTOR_B_LPWM, OUTPUT);

  for (int i = 0; i < 5; i++) { //Blinking to show it is ready to start
    digitalWrite(13, HIGH); delay(50);
    digitalWrite(13, LOW); delay(50);
  }
  testinit();

}
void testinit() {

  while (state == 0) {
    if (digitalRead(PIN_START1) == 0) {
      delaytime(3);// how many seconds
      if (serialOn == 1) {
        Serial.println("No1");
      }
      //turnLeft(255); delay(100);
      state = 0;
      break;
    }
    else if (digitalRead(PIN_START2) == 0) {
      if (serialOn == 1) {
        Serial.println("No2");
      }
      delaytime(3);// how many seconds
      turnLeft(255); delay(200);
      state = 0;
      break;
    }

    else if (digitalRead(PIN_START3) == 0) {
      if (serialOn == 1) {
        Serial.println("No3");
      }

      delaytime(3);// how many seconds
      turnLeft(255); delay(200);

      state = 0;
      break;
    }

    else if (digitalRead(PIN_START4) == 0) {
      if (serialOn == 1) {
        Serial.println("No4");
      }
      delaytime(3);// how many seconds
      state = 0;
      break;
    }
    //delay(10);
  }
}
void delaytime(int cycle) {
  for (int xstart = 0; xstart < cycle; xstart++)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500); //competition rules 3 second//competition rules 3 second IIUMRC
  }
}
void loop() {
  if (teststate == 1) {
    //state = 0;
    Stop();
    testinit();
  }
  else {
    loopActualBattle();  // actual battle
    //loop2(); //check motion
    //loop3(); //sensorsonly
  }
}

void loopActualBattle() {
  readSensors();

  // Edge detection ---- IF VALUE LESS then 100 (value is higher if detect white line (if near) OR no obstacle(far from floor))
  if ((rightEdgeIR < thold_edge) && (leftEdgeIR > thold_edge)) {//&& (middleIR == 0)
    // Move backward
    toaccel = 1; //ready to accelerate
    cond = "White line 1!";
    printSerial();
    Stop(); delay(30);
    reverse(pwmRev); delay(350);
    turnLeft(pwmTurnFast2); delay(160);

  }

  else if ((leftEdgeIR < thold_edge) && (rightEdgeIR > thold_edge)) {//&& (middleIR == 0)
    // Move backward
    toaccel = 1; //ready to accelerate
    cond = "White line 2!";
    printSerial();
    Stop(); delay(30);
    reverse(pwmRev); delay(350);
    turnRight(pwmTurnFast2); delay(190);
  }

  if ((rightEdgeIR < thold_edge) && (leftEdgeIR < thold_edge)) {//&& (middleIR == 0)
    // Move backward
    toaccel = 1; //ready to accelerate
    cond = "White line 3!";
    printSerial();

    reverse(pwmRev); delay(350);
    turnLeft(pwmTurn); delay(350);

  }

  //   Ende of EDGE DETECTION----------------------------------------

  // enemy on Right, turn Right
  if (((trueRight == 1) || (rightIR  == 1)) && (middleIR == 0) && (rightEdgeIR > thold_edge) && (leftEdgeIR > thold_edge)) {
    cond = "Turn Right";
    printSerial();
    turnRight(pwmTurnFast);
    delay(delayturn);
    toaccel = 1;
    //Stop();
  }
  // got enemy infront, move forward
  else if ((middleIR == 1) && ((rightEdgeIR > thold_edge) && (leftEdgeIR > thold_edge))) { // && (rightEdgeIR > thold_edge) && (leftEdgeIR > thold_edge)
    cond = "Attack!!";
    printSerial();
    if (tracerOnly == 0) {
      //Stop();//moveForward(pwmHit);

      AccelForward(pwmHit);
      //toHit=0;
    }
  }

  //enemy on left, turn left
  else if (((trueLeft == 1) || (leftIR == 1)) && (middleIR == 0) && (rightEdgeIR > thold_turn) && (leftEdgeIR > thold_edge)) {
    cond = "Turn left";
    printSerial();
    turnLeft(pwmTurnFast);
    delay(delayturn);
    toaccel = 1;
    //Stop();
  }

  else if ( (tracerOnly == 0) && (rightIR == 0) && (middleIR == 0) && (leftIR == 0) && (rightEdgeIR > thold_edge) && (leftEdgeIR > thold_edge)) {
    //Strategy 1 moveforward while searching and destroy
    //Strategy 2 tornado
    //Strategy 3 movefor
    cond = "strategy ";
    printSerial();
    if (tracerOnly == 0) {
      switch (Strategy) {
        case 1:
          moveForward(pwmVal); delay(10);
          break;
        case 2:
          turnRight(pwmTurnFast); delay(20);
          break;
        case 3:
          // statements
          break;
        default:
          // statements
          break;
      }
      toaccel = 1;
    }

    //Stop(); delay(50);
  }
  else {
    if (tracerOnly == 1) {
      Stop();
      cond = "stop";
      printSerial();
      toaccel = 1;
    }
  }
} //end loop 1

void delay10withupdate(int cycle) {
  for (int i = 0; i < cycle; i++) {
    delay(10);
    //mpu6050.update();
  }

}
void AccelForward(int valspeed) {
  if (motorOn == 1) {
    if (toaccel == 1) { //prevent flipping when hitting
      int xled = 0;
      for (int aspeed = 0; aspeed <= (valspeed ); aspeed = aspeed + 5) {
        xled++;
        if ( (xled % 2) == 1) {
          digitalWrite(LED_BUILTIN, LOW);
        }
        else {
          digitalWrite(LED_BUILTIN, HIGH);
        }
        analogWrite(MOTOR_A_LPWM, 0);// delay(1);
        analogWrite(MOTOR_A_RPWM, aspeed); //delay(1);
        analogWrite(MOTOR_B_LPWM, 0); //delay(1);
        analogWrite(MOTOR_B_RPWM, aspeed); //delay(1);
        readSensors();
        delay(delayloophit);
        if ((middleIR == 0) || ((rightEdgeIR < thold_edge) || (leftEdgeIR < thold_edge))) {
          Stop();
          break;
        }

        // jika middle ir <thold = tak detect opponent, rightedge<thold = detect line putin

        //Serial.println("Accelerate");
      }

    }
    else {//
      digitalWrite(LED_BUILTIN, HIGH);
      analogWrite(MOTOR_A_LPWM, 0);// delay(1);
      analogWrite(MOTOR_A_RPWM, valspeed); //delay(1);
      analogWrite(MOTOR_B_LPWM, 0); //delay(1);
      analogWrite(MOTOR_B_RPWM, valspeed); //delay(1);
    }
  }
  toaccel = 0;// flush value to prevent reaccelarate for continous hitting//
  //Serial.println("AccelForward");
  // may lose grip if attempt to accelerate from 0
}

void readSensors() {
  rightIR = !digitalRead(RIGHT_IR_SENSOR);
  trueRight = !digitalRead(TRUERIGHT_IR_SENSOR);//
  middleIR = !digitalRead(MIDDLE_IR_SENSOR); //
  //middleIR = !middleIR;
  leftIR = !digitalRead(LEFT_IR_SENSOR); //
  trueLeft = !digitalRead(TRUELEFT_IR_SENSOR); //
  rightEdgeIR = analogRead(RIGHT_EDGE_SENSOR); //
  leftEdgeIR = analogRead(LEFT_EDGE_SENSOR);//
  //angleY = mpu6050.getAngleY();
  if ((rightIR > thold_turn) || (middleIR == 1) || (leftIR > thold_turn)) {
    detectOppo = 0;// to reset whether opponnent is detected using any obstacle IR sensor

  }
  if (middleIR == 0) {
    toHit = 1;
  }
  if (serialOn == 1) {
    loopSerial();// printserial if serialmode is on
  }
}


// Motor control functions
void moveForward(int valspeed) {
  if (motorOn == 1) {
    toaccel = 1;
    analogWrite(MOTOR_A_LPWM, 0);// delay(1);
    analogWrite(MOTOR_A_RPWM, valspeed); //delay(1);
    analogWrite(MOTOR_B_LPWM, 0); //delay(1);
    analogWrite(MOTOR_B_RPWM, valspeed); //delay(1);
    //Serial.println("moveForward");
  }
}

void moveForwardLeft(int valspeed) {
  if (motorOn == 1) {
    toaccel = 1;
    analogWrite(MOTOR_A_LPWM, 0);// delay(1);
    analogWrite(MOTOR_A_RPWM, valspeed); //delay(1);
    analogWrite(MOTOR_B_LPWM, 0); //delay(1);
    analogWrite(MOTOR_B_RPWM, valspeed / 2); //delay(1);
    //Serial.println("moveForward");
  }
}
void moveBackward(int valpwm) {
  if (motorOn == 1) {
    toaccel = 1;
    analogWrite(MOTOR_A_RPWM, 0);
    analogWrite(MOTOR_A_LPWM, valpwm);
    analogWrite(MOTOR_B_RPWM, 0);
    analogWrite(MOTOR_B_LPWM, valpwm);
  }
  //Serial.print("moveBackward");
}

void turnRight(int valpwm) {
  if ( motorOn == 1) {
    toaccel = 1;
    analogWrite(MOTOR_A_RPWM, 0);
    analogWrite(MOTOR_A_LPWM, valpwm);
    analogWrite(MOTOR_B_LPWM, 0);
    analogWrite(MOTOR_B_RPWM, valpwm);

  }
  //Serial.print("turnRight");
}

void curveRight(int valpwm, int valpwm2) {
  if ( motorOn == 1) {
    toaccel = 1;
    analogWrite(MOTOR_A_RPWM,  valpwm2);
    analogWrite(MOTOR_A_LPWM, 0);
    analogWrite(MOTOR_B_LPWM, 0);
    analogWrite(MOTOR_B_RPWM, valpwm);

  }
  //Serial.print("turnRight");
}

void turnLeft(int valpwm) {
  if (motorOn == 1) {
    toaccel = 1;
    analogWrite(MOTOR_A_LPWM, 0);
    analogWrite(MOTOR_A_RPWM, valpwm);
    analogWrite(MOTOR_B_RPWM, 0);
    analogWrite(MOTOR_B_LPWM, valpwm);
  }
  //Serial.print("turnLeft");
}

void curveLeft(int valpwm, int valpwm2 ) {
  if (motorOn == 1) {
    toaccel = 1;
    analogWrite(MOTOR_A_LPWM, 0);
    analogWrite(MOTOR_A_RPWM, valpwm);
    analogWrite(MOTOR_B_RPWM, valpwm2);
    analogWrite(MOTOR_B_LPWM, 0);
  }
}
void reverseLeft() {
  if (motorOn == 1) {
    toaccel = 1;
    analogWrite(MOTOR_A_RPWM, 0);
    analogWrite(MOTOR_A_LPWM, pwmRev);
    analogWrite(MOTOR_B_LPWM, pwmRev - (pwmRev / 3));
    analogWrite(MOTOR_B_RPWM, 0);
  }
  //Serial.print("turnLeft");
}

void reverse(int valpwm) {
  if (motorOn == 1) {
    toaccel = 1;
    analogWrite(MOTOR_A_RPWM, 0);
    analogWrite(MOTOR_A_LPWM, valpwm);
    analogWrite(MOTOR_B_LPWM, valpwm);
    analogWrite(MOTOR_B_RPWM, 0);
  }
  //Serial.print("turnLeft");
}
void reverseRight(int valpwm) {
  if (motorOn == 1) {
    toaccel = 1;
    analogWrite(MOTOR_A_LPWM, 0);
    analogWrite(MOTOR_A_RPWM, valpwm);
    analogWrite(MOTOR_B_RPWM, valpwm - (valpwm / 3));
    analogWrite(MOTOR_B_LPWM, 0);
  }
  //Serial.print("turnLeft");
}

void Stop() {
  toaccel = 1;
  analogWrite(MOTOR_A_RPWM, 0);
  analogWrite(MOTOR_A_LPWM, 0);
  analogWrite(MOTOR_B_RPWM, 0);
  analogWrite(MOTOR_B_LPWM, 0);
  //Serial.print("STOP");
}


void loopSerial() {
  //mpu6050.update();
  Serial.print("TR:"); print3digit(trueRight);//Serial.print(trueRight);
  Serial.print(", R:"); print3digit(rightIR);//Serial.print(rightIR);
  Serial.print(", Mid: "); print3digit(middleIR);//Serial.print(middleIR);
  Serial.print(", L: "); print3digit(leftIR);//Serial.print(leftIR);
  Serial.print(", TL: "); print3digit(trueLeft);//Serial.print(trueLeft);
  Serial.print(", R edge: "); print3digit(rightEdgeIR);//Serial.print(rightEdgeIR);
  Serial.print(", L-edge: "); print3digit(leftEdgeIR);//Serial.print(leftEdgeIR);
  Serial.print(", Angle: "); print3digit(angleY);//Serial.print(angleY);
  Serial.print(", toaccel:");
  Serial.print(toaccel);
  Serial.print(", detectOppo:");
  Serial.println(detectOppo);
  //Serial.println();
}
void print3digit(int vale) {
  if (vale < 10) {
    Serial.print("  ");
    Serial.print(vale);
  }
  else if (vale < 100) {
    Serial.print(" ");
    Serial.print(vale);
  }
  else if (vale < 1000) {
    Serial.print(vale);
  }
}

void loop3() {
  readSensors();
  loopSerial();
  delay(50);

  //loop4();
}

void AccelForwardOnce(int valspeed) {

  for (int aspeed = 0; aspeed <= (valspeed ); aspeed = aspeed + 5) {

    analogWrite(MOTOR_A_LPWM, 0);// delay(1);
    analogWrite(MOTOR_A_RPWM, aspeed); //delay(1);
    analogWrite(MOTOR_B_LPWM, 0); //delay(1);
    analogWrite(MOTOR_B_RPWM, aspeed); //delay(1);
    delay(delayloophitonce);
  }
}

void loop2() {
  moveForward(pwmVal); delay(1000);
  Stop(); delay(1000);
  moveBackward(pwmRev); delay(1000);
  Stop(); delay(1000);
  turnRight(pwmTurn); delay(1000);
  Stop(); delay(1000);
  turnLeft(pwmTurn); delay(1000);
  Stop(); delay(3000);
}
void printSerial() {
  if (serialOn == 1) {
    Serial.print(cond);
    Serial.print("  ");
  }
}
