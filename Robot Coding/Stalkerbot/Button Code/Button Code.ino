const int BUTTON_PIN = 22;  // the number of the pushbutton pin
int status = 1;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize the pushbutton pin as an pull-up input
  // the pull-up input pin will be HIGH when the switch is open and LOW when the switch is closed.
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  // read the state of the switch/button:
  int buttonState = digitalRead(BUTTON_PIN);
  Serial.println(buttonState);

  while (buttonState == High) {  // while the button is pressed
    if (status == 1) {
      Serial.println("Starting");
      delay(5000);
    }
    // do something here
    // this code will run repeatedly while the button is pressed
    Serial.println("On");
    buttonState = digitalRead(BUTTON_PIN);  // read the state of the button again
    status = 0;
  }
  status = 1;
}