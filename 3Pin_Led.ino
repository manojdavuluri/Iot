#define RED 4
#define GREEN 7
#define BLUE 8
#define delayTime 500
int state = 0;
void setup() {
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(RED, OUTPUT);
  Serial.begin(9600);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
  digitalWrite(RED, HIGH);
}

void loop() {
  
  if(Serial.available()>0) {
    state = Serial.read();
  }
 if(state=='1') {
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, LOW);
    digitalWrite(RED, LOW);
    Serial.println("BLUE: ON");
  } else if(state=='2') {
    digitalWrite(RED, HIGH);
    digitalWrite(BLUE, LOW);
    digitalWrite(GREEN, LOW);
    Serial.println("RED: ON");
  } else if(state=='3') {
    digitalWrite(BLUE, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, LOW);
    Serial.println("GREEN: ON");
  }

  delay(delayTime);

}
