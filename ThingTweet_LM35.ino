#include<stdlib.h>
const int groundpin = A0;
const int powerpin = A2;
const int receiver = 0;
float tempC;
int reading;
int tempPin = A1;
int led=13; int con=0;
String apiKey = "7OHUO9B4DNWTW8XS";

String Tweet_Message(float temp){
        //Tweet message
        String tempMessage;
        tempMessage="Abnormal Temperature Noted in the room " + String(temp) +" degrees Celsius.";
        return tempMessage;
    }

void setup() {
  
  Serial.begin(115200);
  pinMode(groundpin, OUTPUT);
  pinMode(powerpin, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(groundpin, LOW);
  digitalWrite(powerpin, HIGH);
  analogReference(INTERNAL);
  // reset ESP8266
  Serial.println("AT+RST");
  Serial.println("AT+CIPMUX=0");

}

void loop() {
  
  reading = analogRead(tempPin);
  tempC = reading / 9.31;
  // convert to string
  char buf[16];
  String strTemp = dtostrf(tempC, 5, 2, buf);
  Serial.println(tempC);
  
  if(tempC>35||tempC<15)
  {  
        // TCP connection
        String cmd = "AT+CIPSTART=\"TCP\",\"";
        cmd += "api.thingspeak.com"; // api.thingspeak.com
        cmd += "\",80";
        Serial.println(cmd);
        if(Serial.find("Error"))
        {
          Serial.println("AT+CIPSTART error");
          return;
        }
        // prepare GET string
        String getStr= "GET https://api.thingspeak.com/apps/thingtweet/1/statuses/update?api_key=";
        getStr += apiKey;
        getStr +="&status=";
        getStr += Tweet_Message(tempC);
        getStr += "\r\n\r\n";
        // send data length
        cmd = "AT+CIPSEND=";
        cmd += String(getStr.length());
        Serial.println(cmd);
        if(Serial.find(">"))
        {
          Serial.print(getStr);
        }
        else
        {
           Serial.println("AT+CIPCLOSE");     // alert user
        }
  }
  // thingspeak needs 5 sec delay between updates
  delay(5000);  
}
