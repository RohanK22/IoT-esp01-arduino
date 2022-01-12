#include <SoftwareSerial.h>
#define RX 6
#define TX 7
String AP ="Saicourt204"; 
String PASS ="00576201s"; 
String HOST = "api.weatherstack.com";
String PORT = "80";
String field = "error";
int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
SoftwareSerial ESP8266(RX,TX); 
 
String Data ="";
void setup() {
  Serial.begin(9600);
  ESP8266.begin(4800);
  sendCommand("AT",5,"OK",false);
  ESP8266.println("AT+UART_DEF=9600,8,1,0,0");
  delay(1000);
  ESP8266.end();
  ESP8266.begin(9600);
  ConnectToWifi();
}
void loop() {
  
String uri="/current?access_key=0a474fb20c2dec4b814bc739544e7652&query=London";

String getData=
"GET " + uri + " HTTP/1.0\n" +
"Host: " + HOST + "\n" +
"Accept: application/json\n" +
"Content-Type: application/json\n" +
"Connection: Keep-Alive\n" +
"\n";



 sendCommand("AT+CIPMUX=1",5,"OK",false);
 sendCommand("AT+CIPSTART=4,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK",false);
 sendCommand("AT+CIPSEND=4," +String(getData.length()+4),4,">",false);


 sendCommand(getData,20,"OK",true);
 delay(1500);
 countTrueCommand++;
 sendCommand("AT+CIPCLOSE=0",5,"OK",false);
}

bool ConnectToWifi(){
  for (int a=0; a<15; a++)
  {
    sendCommand("AT",5,"OK",false);
    sendCommand("AT+CWMODE=1",5,"OK",false);
    boolean isConnected = sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK",false);
    if(isConnected)
    {
      return true;
    }
  }
}

bool sendCommand(String command, int maxTime, char readReplay[],boolean isGetData) {
  boolean result=false;

  //Test Purpose
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    ESP8266.println(command);
    if(ESP8266.find(readReplay))//ok
    {   
      if(isGetData)
      {      
        if(ESP8266.find(readReplay))
        {
          Serial.println("Success : Request is taken from the server");
        }
        while(ESP8266.available())
        {
            char character = ESP8266.read();
            Data.concat(character); 
            if (character == '\n')
             {
             Serial.print("Received: ");
             Serial.println(Data);
             delay(50);
             Data = "";
        } 
        }         
      }
      result = true;
      break;
    }
    countTimeCommand++;
  }
  
  if(result == true)
  {
    Serial.println("Success");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(result == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
  return result;
 }
