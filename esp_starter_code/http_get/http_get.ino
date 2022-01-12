//http://api.weatherstack.com/current?access_key=0a474fb20c2dec4b814bc739544e7652&query=London
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


const char* ssid = "Saicourt204";
const char* password = "00576201s";

void setup () {

  Serial.begin(74880);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.print("Connecting..");

  }

  //pinMode(LED_BUILTIN, OUTPUT);

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    Serial.print("Connected");
    HTTPClient http;  //Declare an object of class HTTPClient
    WiFiClient cli;

    http.begin(cli,"http://api.weatherstack.com/current?access_key=0a474fb20c2dec4b814bc739544e7652&query=London");  //Specify request destination
    int httpCode = http.GET();                                  //Send the request

    Serial.println("\nHTTP Code:");
    Serial.println(httpCode);
    if (httpCode > 0) { //Check the returning code

      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);             //Print the response payload
//      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//      delay(1000);                       // wait for a second
//      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    }

    //http.end();   //Close connection

  }

//  delay(30000);    //Send a request every 30 seconds

}

void loop() {

  
}
