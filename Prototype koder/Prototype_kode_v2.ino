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
float hum;  //Stores humidity value
float temp; //Stores temperature value

int led = D3 ;
int led1 = D4;




void setup() {
  
  // put your setup code here, to run once:
  dht.begin();
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

    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);               // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);               // wait for a second
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println(" ....");
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      delay(5000);
    }
    Serial.println("Connected to Wi-Fi Succesfully.");
    digitalWrite(led, HIGH); // Turn the LED on
    digitalWrite(led1, HIGH);
   
  }


  int sensor = analogRead(A0); // Incoming analog signal read and appointed sensor
  Serial.println(sensor);   //Wrote serial port

  delay(200);
  //Read data and store it to variables hum and temp
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  //Print temp and humidity values to serial monitor
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print(" %, Temp: ");
  Serial.print(temp);
  Serial.println(" Celsius");
  delay(100); //Delay 2 sec.

  if (analogRead(A0) >= 250 ) {
    ThingSpeak.setField(fieldNumberOne, analogRead(A0));
    ThingSpeak.writeFields(counterChannelNumber, myWriteAPIKey);
    delay(20000);
    
  }

  if (dht.readHumidity() >= 80) {
    ThingSpeak.setField(2, dht.readHumidity());
    ThingSpeak.writeFields(counterChannelNumber, myWriteAPIKey);
    
  }
}
