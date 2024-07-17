// Line sensor
const int LineR = 4;
const int LineL = 15;
int inputLineR = 0;
int inputLineL = 0;

void setup() {
  // Line Sensor
  pinMode(LineR, INPUT);  // Sets Right Line Sensor
  pinMode(LineL, INPUT);  // Sets Left Line Sensor
  Serial.begin(115200);
  Serial.print("Testing DC Motor...");
}

void loop() {

  // Reading Line Sensor
  inputLineR = analogRead(LineR);
  inputLineL = analogRead(LineL);
  Serial.println(inputLineR);
  Serial.println(inputLineL);
  delay(1000);
}
