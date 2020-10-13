#include "ThingSpeak.h" // her inkluderes det libary som der får Thingspeak til at read og write fra Cloud
#include <ESP8266WiFi.h> // her inkluderes det libary som der får WiFi til at fungere på NodeMcu

//WI-FI settings
const char ssid[] = "IOTtestOA"; //WI-Fi navn
const char pass[] = "Oliver1234"; //password
WiFiClient client;

//Channel detaljer
unsigned long counterChannelNumber = 1184878;            // Channel ID
const char * myCounterReadAPIKey = "AKG0Y9LIPL4PQZLU"; // Read API Key
const char * myWriteAPIKey = "DUTTUWHN1R5B3CGN";    // Write API Key
const int fieldNumberOne = 1;  // Det field som vi læser fra i Thingspeak




void setup() {
  // put your setup code here, to run once:

Serial.begin(115200);
  WiFi.mode(WIFI_STA); //her startes WiFi Mode for NodeMcu
  ThingSpeak.begin(client); //Thingspeak libary starter WiFi client


}

void loop() {
  // put your main code here, to run repeatedly:
 
 //Tilslutter til WiFi ved brug af tidligere defineret variabler SSID og pass
    if (WiFi.status() != WL_CONNECTED)
    {
      Serial.print("Connecting to ");
      Serial.print(ssid);
      Serial.println(" ....");
      while (WiFi.status() != WL_CONNECTED)
      {
        WiFi.begin(ssid, pass);
        delay(5000);
      }
      Serial.println("Connected to Wi-Fi Succesfully.");
    }
    //--------- Slut på tilslutning til WiFi--------//



}
