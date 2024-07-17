// Line sensor               
const int LineR = A4;
const int LineL = A5;
int inputLineR = 0;
int inputLineL = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Reading Line Sensor
  inputLineR = analogRead(LineR);
  inputLineL = analogRead(LineL);
  Serial.print(inputLineR);
  Serial.print(", ");
  Serial.println(inputLineL);

  delay(100);  // delay in between reads for stability
}
