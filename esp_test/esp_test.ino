// Setup the ESP-01 such that it repeatedly queries REST API at https://esp8266-01-rohan.herokuapp.com/data

//Thanks to https://techtutorialsx.com/2016/07/17/esp8266-http-get-requests/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Wifi credentials
const char* ssid = "Saicourt204";
const char* password = "00576201s";

void setup() {
  Serial.begin(9600);

  // Connect to Wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
//    Serial.println("Connecting..");
  }
}

void loop() {
  // If Connected
  if (WiFi.status() == WL_CONNECTED) { // Check WiFi connection status
//    Serial.println("Connected");
    HTTPClient http;  //Declare an object of class HTTPClient
//    WiFiClient cli;

    http.begin("http://esp8266-01-rohan.herokuapp.com/data");  //Specify request url
    int httpCode = http.GET();                                      //Send the request

//    Serial.println("\nHTTP Code:");
//    Serial.println(httpCode);
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);             //Print the response payload
    }
    http.end();   //Close connection
  }
    delay(10000);
//  Serial.println("Hello From ESP!");
}
