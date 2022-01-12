#include<SoftwareSerial.h>
#include<ArduinoJson.h>
#include <LiquidCrystal.h>

SoftwareSerial esp(2,3); // RX, TX  

const int rs = 9, en = 8, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600);
  esp.begin(9600);
  delay(5000);
}

void setPinVal(int pin_no, char* sig) {
  if(sig[0] == '1') {
    digitalWrite(pin_no, HIGH);
    Serial.println("This pin is now high: " + pin_no);
  } else {
    digitalWrite(pin_no, LOW);
  }
}

void loop() {
  String message = "";
  boolean newMessage = false;

  while(esp.available()) {
    message = esp.readString();
    newMessage = true;
  }

  if(newMessage) {
    Serial.println("ESP Says:");
    Serial.println(message);

    int str_len = message.length() + 1; 
    char json[str_len];
    message.toCharArray(json, str_len);

    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, json);
  
    // Test if parsing succeeds.
    if (error) {
      Serial.println(error.f_str());
      return;
    }
    
    const char* m = doc["message"];
    const char* btc = doc["BTCPrice"];
    const char* temp = doc["temp"];
    const char* pin10 = doc["pin10"];
    const char* pin11 = doc["pin11"];
    const char* pin12 = doc["pin12"];
    Serial.println(m);
    Serial.println(btc);
    Serial.println(temp);
    Serial.println(pin10);
    Serial.println(pin11);
    Serial.println(pin12);

    setPinVal(10, pin10);
    setPinVal(11, pin11);
    setPinVal(12, pin12);
  }
}
