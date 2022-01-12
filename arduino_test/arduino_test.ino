// Thanks to https://www.youtube.com/watch?v=ji71cHaGW8w&list=PLna0oQMFNc6C2HdLO0PAAxjhlAxQMgn3v&index=12

#include<SoftwareSerial.h>
#include<ArduinoJson.h>

SoftwareSerial esp(2,3); // TX, RX

void setup() {
  Serial.begin(9600);
  esp.begin(9600);
  delay(3000);
}

void loop() {
  String messageFromESP = "";
  boolean strReady = false;
  while(esp.available()) {
    messageFromESP = esp.readString();
    strReady = true;
  }

  if(strReady) {
    Serial.println("Received Str from ESP: ");
    Serial.println(messageFromESP);

    if(messageFromESP.startsWith("{")) {
      Serial.println("I'm in");
      // We have some juicy JSON data to deal with - crazy assumption
      DynamicJsonDocument doc(1024);
      
      int str_len = messageFromESP.length() + 1; 
      char json[str_len];
      messageFromESP.toCharArray(json, str_len);
     
      DeserializationError error = deserializeJson(doc, json);

      if(error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.f_str());
          return;
      }
      
      const char* btc = doc["BTCPrice"];
      const char* message = doc["message"];
      const char* temp = doc["temp"];
      const char* pin8 = doc["pin8"];
      const char* pin9 = doc["pin9"];
      const char* pin10 = doc["pin10"];
      const char* pin11 = doc["pin11"];
      const char* pin12 = doc["pin12"];

      Serial.println(btc);
      Serial.println(message);
      Serial.println(temp);
      Serial.println(pin8);
    }
  }
}
