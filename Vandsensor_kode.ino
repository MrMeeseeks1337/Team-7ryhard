void setup(){
Serial.begin(115200);     // Communication started with 9600 baud
}
void loop(){
int sensor=analogRead(A1); // Incoming analog signal read and appointed sensor
Serial.println(sensor);   //Wrote serial port
}
