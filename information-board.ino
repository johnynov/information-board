#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "FS.h"
#include "class/controller/Controller.cpp"


Controller controller;

AsyncWebServer server(80);

IPAddress localIp(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

void setup() {

    Serial.begin(115200);
    Serial.println();

    WiFi.disconnect(true);
    WiFi.mode(WIFI_AP);

    Serial.print("Setting soft-AP configuration ... ");
    Serial.print(WiFi.softAPConfig(localIp, gateway, subnet) ? "Ready\n" : "Failed!\n");

    Serial.print("Setting soft-AP ... ");
    Serial.print(WiFi.softAP("teest") ? "Ready\n" : "Failed!\n");

    Serial.print("Soft-AP IP address = ");
    Serial.print(WiFi.softAPIP());

    // Initialize SPIFFS
    if (!SPIFFS.begin()) {
        Serial.print("An Error has occurred while mounting SPIFFS\n");
        return;
    }

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html");
        Serial.println("Index.html GET Request");
    });

    server.on("/main.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/main.css");
        Serial.println("main.css Request");
    });

    server.on("/resources.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/resources.js");
        Serial.println("resources.js Request");
    });

    server.on("/main.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/main.js");
        Serial.println("main.js Request");
    });

    // get adverts
    server.on("/adverts", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.println("Adverts GET Request");

        Response *response = controller.get_adverts();
        int status = response->getStatus();
        const std::string &payload = response->getPayload();

        request->send(status, "application/json", payload);
    });

    // add advert
    server.on("/adverts", HTTP_PUT, [](AsyncWebServerRequest *request) {
        Serial.println("Adverts PUT Request");

        if (request->hasParam("password", true) && request->hasParam("title", true) && request->hasParam("body", true)) {
            std::string title = request->getParam("title", true)->value();
            std::string body = request->getParam("body", true)->value();
            std::string password = request->getParam("password", true)->value();

            Response *response = controller.add_advert(title, body, password);
            int status = response->getStatus();
            const std::string &payload = response->getPayload();

            request->send(status, "application/json", payload);
        } else {
            request->send(400);
        }
    });

    // update advert
    server.on("/adverts", HTTP_PATCH, [](AsyncWebServerRequest *request) {
        Serial.println("Adverts PATCH Request");

        if (request->hasParam("id") && request->hasParam("title") && request->hasParam("body") && request->hasParam("password")) {
            std::string id = request->getParam("id")->value();
            std::string title = request->getParam("title")->value();
            std::string body = request->getParam("body")->value();
            std::string password = request->getParam("password")->value();

            Response *response = controller.update_advert(id, title, body, password);
            int status = response->getStatus();
            const std::string &payload = response->getPayload();

            request->send(status, "application/json", payload);
        } else {
            request->send(400);
        }
    });

    // remove advert
    server.on("/adverts", HTTP_DELETE, [](AsyncWebServerRequest *request) {
        Serial.println("Adverts DELETE Request");

        if (request->hasParam("id") && request->hasParam("password")) {
            std::string id = request->getParam("id")->value();
            std::string password = request->getParam("password")->value();

            Response *response = controller.remove_advert(id, password);
            int status = response->getStatus();
            const std::string &payload = response->getPayload();

            request->send(status, "application/json", payload);
        } else {
            request->send(400);
        }
    });

    server.begin();
}

// the loop function runs over and over again forever
void loop() {
}
