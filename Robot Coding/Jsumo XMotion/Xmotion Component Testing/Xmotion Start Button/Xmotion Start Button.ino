#define DipSwitch1 5  // Dipswitch 1 tied to Digital 5
#define DipSwitch2 6  // Dipswitch 2 tied to Digital 6
#define DipSwitch3 7  // Dipswitch 3 tied to Digital 7
#define start 10      // Button tied to Digital 10

void setup() {
  // put your setup code here, to run once:
  pinMode(DipSwitch1, INPUT);    //Dipswitch 1 Declared as Input
  pinMode(DipSwitch2, INPUT);    //Dipswitch 2 Declared as Input
  pinMode(DipSwitch3, INPUT);    //Dipswitch 3 Declared as Input
  pinMode(start, INPUT_PULLUP);  //Button Declared as Input innitially 1, clicked turn to 0
  
  digitalWrite(DipSwitch1, HIGH);  // Dipswitch Inputs are High (Pull-up made)
  digitalWrite(DipSwitch2, HIGH);
  digitalWrite(DipSwitch3, HIGH);
  Serial.begin(9600);  //Serial Interface started with 9600 bits per sec.
}

void loop() {
  Serial.print("Button State:");     //We are writing this statement to serial Monitor
  Serial.print(digitalRead(start));  //digital reading of button
  Serial.print("Dipswitch Inputs:");
  Serial.print(digitalRead(DipSwitch1));  // digital reading of dipswitches
  Serial.print(digitalRead(DipSwitch2));
  Serial.println(digitalRead(DipSwitch3));
  delay(500);
}
