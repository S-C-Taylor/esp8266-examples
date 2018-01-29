#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

ESP8266WebServer server(80); //Start webserver

const char *ssid = "Telstra3ADA";
const char *password = "2638455370";

int flag = 0;

void setup() {
  pinMode(D5, OUTPUT);
  Serial.begin ( 115200 ); //Open serial communication at 115200 Baud Rate
  WiFi.begin ( ssid, password ); //Turn on wifi
  Serial.println ( "" );

  // Wait for connection to wifi
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 ); //Sleep for half a second
    Serial.print ( "." ); //Status printing
  }

  //Print our IP Address
  Serial.println ( "" );
  Serial.print ( "Connected to " );
  Serial.println ( ssid );
  Serial.print ( "IP address: " );
  Serial.println ( WiFi.localIP() );

  //Start the multicast DNS
  if ( MDNS.begin ( "esp8266" ) ) {
    Serial.println ( "MDNS responder started" );
  }

  //Create endpoint for LED
  server.on("/led", doLed);

  //Start the server
  server.begin();
}

void doLed(){
  if (flag){ //If the LED is ON turn it off
    digitalWrite(D5, LOW);
    server.send(200, "text/plain", "LED OFF");
    flag = 0;
  }else{ //If the LED is OFF turn it on
    digitalWrite(D5, HIGH);
    server.send(200, "text/plain", "LED ON");
    flag = 1;
  }
}

void loop() {
  // Handle connected clients
  server.handleClient();
}
