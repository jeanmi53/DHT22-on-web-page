//
//  ESP8266 and the Arduino IDE Part 10: Environment monitor station
//  ESP8266-10_sketch04_IOT_Website
//  http://www.martyncurrey.com/esp8266-and-the-arduino-ide-part-10b-iot-website-enhancing-the-website/
/*
|* 
|*           ------
|*          /      \
|*         ---------
|*         |        |
|*         |        |
|*         |        |
|*         |        |
|*         ---------
|*          | | | |
 * DHT pin  1 2 3 4
 *          + D   -
 */
#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
 
WiFiServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

//char ssid[] = "mySSID"; // See webPass.h
//char pass[]= "myPassword";


#include <DHT.h>  // Adafruit DHT lib
#define DHTPIN SDA     
#define DHTTYPE DHT22   
DHT dht(DHTPIN, DHTTYPE);

byte const pinLED = LED_BUILTIN;  // D4 GPIO02 pin 2
byte const pinLDR = A0;
byte moy;
float moyC;
float moyH;
float humidity = 0;       
float tempC = 0;
float tempF = 0;
float temp[20];
float hum[20];

boolean DHTreadingsOK = false;
boolean updateWebpage = false;

long sensorUpdateFrequency = 5000;
long timeNow = 0;
long timePrev = 0;


#include "webpage.h"
#include "webPass.h"
#include "sensor.h"
#include "webEvent.h"
 
void setup()
{
  pinMode(pinLED, OUTPUT); digitalWrite(pinLED, LOW); 
  dht.begin();
  
  Serial.begin(115200);
  //while (!Serial) {;}
  Serial.println();
  Serial.println("Serial started at 115200");
  Serial.println();
 
  // Connect to a WiFi network
  Serial.print("Connecting to ");  Serial.println(ssid); 
  
  // try to connect to the network
  WiFi.begin(ssid,password);
  
  // connection with timeout
  int count = 0; 
  digitalWrite(pinLED, HIGH); 
  while ( (WiFi.status() != WL_CONNECTED) && count < 17) 
  {
      Serial.print(".");    count++;     delay(500);
  }
 digitalWrite(pinLED, LOW);
 
  if (WiFi.status() != WL_CONNECTED)
  { 
     Serial.println("");  Serial.print("Failed to connect to ");  Serial.println(ssid);
     while(1);
  }
 
  Serial.println("");
  Serial.print("Connected. IP address = ");   Serial.println(WiFi.localIP());  

 
  // start a server
  server.begin();
  Serial.println("Server started");

  // start the websocket
  webSocket.begin();
  Serial.println("websocket started");

  Serial.println("");
  Serial.println("");

  // webSocketEvent is the function to call when there is a websocket event
  webSocket.onEvent(webSocketEvent); 
}
 
 
void loop()
{
    // check the websocket status.
    webSocket.loop();

    // Check if a client has connected
    WiFiClient client = server.available();     

    // if a client has connected send the webpage
    if (client)  
    {  
        client.flush();
        client.print( header );
        client.print( html_1 ); 
        Serial.println("New page served");
        Serial.println("");
        updateSensors();
    }

    // see if it is time to update the sensor values on the website
    timeNow = millis();
    if (timeNow - timePrev >= sensorUpdateFrequency) 
    { 
      timePrev = timeNow;

      // if it is time, call the updateSensors() function 
      updateSensors(); 
    }

}  // void loop()