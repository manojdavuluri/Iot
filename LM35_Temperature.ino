const int groundpin = A0; //Pin-3
const int powerpin = A2;  //Pin-1
int tempPin = A1;   //Pin-2

float tempC;
float reading;

void setup() {
  Serial.begin(9600);
  pinMode(groundpin, OUTPUT);
  pinMode(powerpin, OUTPUT);
  digitalWrite(groundpin, LOW);
  digitalWrite(powerpin, HIGH);
  analogReference(INTERNAL);
}
void loop() {
  reading = analogRead(tempPin);
  tempC = reading / 9.31;
  Serial.print("Temperature: ");
  Serial.println(tempC);
  delay(1000);
  }
