#include<WiFi.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>


const char* PARAM_INPUT_1 = "ssid";
const char* PARAM_INPUT_2 = "pass";


const char* ssidPath = "/ssid.txt";
const char* passPath = "/pass.txt";

String ssid;
String pass;
String ip;

AsyncWebServer server(80);

String readFile(const char* path){
  File file = SPIFFS.open(path, "r");
  if(!file){
    Serial.println("Failed to read file");
    return "";
  }
  String data = file.readString();
  file.close();
  return data;
}
void writeFile(const char* path, const char* data) {
  File file = SPIFFS.open(path, "w");
  if (!file) {
    Serial.println("Failed to write file");
    return;
  }
  file.print(data);
  file.close();
}


bool initWiFi() {
   ssid = readFile(ssidPath);
  pass = readFile(passPath);
  if (wifi_ssid == "") {
    Serial.println("Undefined SSID or IP address.");
    return false;
  }
  WiFi.setHostname(hostname.c_str());
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), pass.c_str());
  Serial.println("Connecting to WiFi...");
  
  unsigned long currentMillis = millis();
  previousMillis = currentMillis;
  while (WiFi.status() != WL_CONNECTED) {
   currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      Serial.println("Failed to connect.");
      return false;
    }
  }
  IPAddress dnsServer(8, 8, 8, 8);
  WiFi.config(WiFi.localIP(), WiFi.gatewayIP(), WiFi.subnetMask(), dnsServer);
  Serial.println(WiFi.localIP());
  
  return true;
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  /*Baud rate for serial communication*/
  if(!SPIFFS.begin(true)){
    Serial.println("An error occurred while mounting SPIFFS");
    return;
  }
  if (!initWiFi()) { 
    Serial.println("Setting AP (Access Point)");

    WiFi.softAP("ESP-WIFI-MANAGER", NULL);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
      request->send(200, "text/plain", "test. Post Data only");
    });
      server.on("/wifi/save", HTTP_POST, [](AsyncWebServerRequest * request) {
      int params = request->params();
      String configData;
      DynamicJsonDocument doc(500);

      for (int i = 0; i < params; i++) {
        AsyncWebParameter* p = request->getParam(i);
        if (p->isPost()) {
          // HTTP POST ssid value
          Serial.print(p->name());
          Serial.print(": ");
          Serial.println(p->value());
          if (p->name() == PARAM_INPUT_1) {
            ssid = p->value().c_str();
            Serial.print("SSID set to: ");
            Serial.println(ssid);
            // Write FileSpiffs to save value
            doc["wifi_ssid"] = ssid;
            writeFile(ssidPath, ssid.c_str());
          }
          // HTTP POST pass value
          if (p->name() == PARAM_INPUT_2) {
            pass = p->value().c_str();
            doc["wifi_pass"] = pass;
            Serial.print("Password set to: ");
            Serial.println(pass);
            // Write FileSpiffsSpiffs to save value
            writeFile(passPath, pass.c_str());
        
          }
            Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
        }
      }
      //      serializeJson(doc, configData);
      //      writeFileSpiffs("/config.json", configData.c_str());
      request->send(200, "text/html", "Done. ESP will restart, connect to your router and go to IP address: " + ip + "\n <a href=\"www.google.com\" > Google <a>");
     delay(3000);
      ESP.restart();
    });
      // Start server
  server.begin();
   }
  //Your code

 
}

void loop() {
  // put your main code here, to run repeatedly:
}
