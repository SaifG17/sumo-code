// Ultrasonic sensor
#define TrigPinR 4
#define EchoPinR 2
#define TrigPinL 1
#define EchoPinL 0

//Ultrasonic variables
long durationR;
long durationL; 
float distanceR;
float distanceL;

void setup() {
  // Ultrasonic sensor Right
  pinMode(TrigPinR, OUTPUT);  // Sets the trigPin as an Output
  pinMode(EchoPinR, INPUT);   // Sets the echoPin as an Input
  // Ultrasonic sensor Left
  pinMode(TrigPinL, OUTPUT);  // Sets the trigPin as an Output
  pinMode(EchoPinL, INPUT);   // Sets the echoPin as an Input
  Serial.begin(9600);
}

void loop() {
  // Reading Distance Right
  digitalWrite(TrigPinR, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPinR, HIGH);  // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(TrigPinR, LOW);  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationR = pulseIn(EchoPinR, HIGH);
  distanceR = (durationR / 2) / 29.1;  // Calculate the distance
  Serial.print("Distance Right Sensor: ");
  Serial.print(distanceR);

  // Reading Distance Left
  digitalWrite(TrigPinL, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPinL, HIGH);  // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(TrigPinL, LOW);  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationL = pulseIn(EchoPinL, HIGH);
  distanceL = (durationL / 2) / 29.1;  // Calculate the distance
  Serial.print("   Distance Left Sensor: ");
  Serial.println(distanceL);

  delay(100);  // delay in between reads for stability
}
