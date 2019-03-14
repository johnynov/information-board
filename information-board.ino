#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

void setup() {

  WiFi.softAP("Information board");
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "{ 'message': 'Super information board XD'}");
  });
}

// the loop function runs over and over again forever
void loop() {

}
