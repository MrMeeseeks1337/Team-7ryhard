#include "ThingSpeak.h" // her inkluderes det libary som der får Thingspeak til at read og write fra Cloud
#include <ESP8266WiFi.h> // her inkluderes det libary som der får WiFi til at fungere på NodeMcu
#include <DHT.h>;

//WI-FI settings
const char ssid[] = "IOTtestOA"; //WI-Fi navn
const char pass[] = "Oliver1234"; //password
WiFiClient client;

//Channel detaljer
unsigned long counterChannelNumber = 1184878;            // Channel ID
const char * myCounterReadAPIKey = "AKG0Y9LIPL4PQZLU"; // Read API Key
const char * myWriteAPIKey = "DUTTUWHN1R5B3CGN";    // Write API Key
const int fieldNumberOne = 1;  // Det field som vi læser fra i Thingspeak
const int fieldNumberTwo = 1;


//Konstanter
#define DHTPIN D2    // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor 

//Variabler
int chk;
float hum;  //Gemmer fugtighedssensoren værdi
float temp; //Gemmer temperatur værdi

int led = D3 ; //diode variabel
int led1 = D4;




void setup() {
  
  // put your setup code here, to run once:
  dht.begin(); //starter dht sensor
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); //her startes WiFi Mode for NodeMcu
  ThingSpeak.begin(client); //Thingspeak libary starter WiFi client

  pinMode(led, OUTPUT); // erklære LED som output
  pinMode(led1, OUTPUT);
 


}

void loop() {
  // put your main code here, to run repeatedly:

  //Tilslutter til WiFi ved brug af tidligere defineret variabler SSID og pass
  if (WiFi.status() != WL_CONNECTED)
  {

    digitalWrite(led, HIGH);   
    delay(1000);               
    digitalWrite(led, LOW);    
    delay(1000);               
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println(" ....");
    while (WiFi.status() != WL_CONNECTED) //en while løkke der forsøger at tislutte wifi så længe den ikke er tilsluttet 
    {
      WiFi.begin(ssid, pass);
      delay(5000);
    }
    Serial.println("Connected to Wi-Fi Succesfully.");
    digitalWrite(led, HIGH); // tænder LED, hvis den er tilsluttet 
    digitalWrite(led1, HIGH);
   
  }


  int sensor = analogRead(A0); // variabl der gemmer vandsensensors værdi fra den analog pin 
  Serial.println(sensor);   //skriver værdien i serial monitor 

  delay(200);
  //Gemmer værdier fugtighed og temperaruyr i i de to variabler hum og temp
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  //Print begge værdier i serial monitor
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print(" %, Temp: ");
  Serial.print(temp);
  Serial.println(" Celsius");
  delay(100); //Delay 2 sec.

  if (analogRead(A0) >= 250 ) { /* if statement - der sørger for a der bliver uploadet til thingspeak hvis grænseværiden er lig med eller overstiger 250. 
  hvis den overstiger er det lig med vand  */
    ThingSpeak.setField(fieldNumberOne, analogRead(A0)); // her skrives sensor værdi til thingspeaks field 1
    ThingSpeak.writeFields(counterChannelNumber, myWriteAPIKey); // her uploades der til thingspeak
    delay(20000); // delay for ikke at spamme bruger
    
  }

  if (dht.readHumidity() >= 80) { //  if statement - der sørger for a der bliver uploadet til thingspeak hvis grænseværiden er lig med eller overstiger 80
    ThingSpeak.setField(2, dht.readHumidity()); //her skrives sensor værdi til thingspeaks field 2 med luftfugtigheden
    ThingSpeak.writeFields(counterChannelNumber, myWriteAPIKey); // her uploades der til thingspeak 
    
  }
}
