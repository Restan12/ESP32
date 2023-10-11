//Copy this file on your Arduino IDE
//author: Restan V. Requina
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
//#include <ESPAsyncWebSrv.h> // do not include this on Arduino IDE
//This is used on WokWi Only

//setup ssid,pass of your router
//not recommended for multiple wifi
//use wifi manager instead
const char* ssid = "Wokwi-GUEST"; // Replace with your network name
const char* password = ""; // Replace with your network password
//Uncomment this if you are using AP
/*const char* ssid = "ESP32-AP"; // Replace with your network name
const char* password = ""; // Replace with your network password
*/
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
<h1>ESP32 Web Server</h1>
<button onclick=\"toggleLED()\">Toggle LED</button>
<script>
function toggleLED() {
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/toggle", true);
      xhr.send();
    }
</script>
</body>
</html>
)rawliteral";

int ledPin = 2;

void setup() {
  
  Serial.begin(115200); 
  pinMode(ledPin, OUTPUT);
  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  //Wifi.mode(WIFI_AP);
  //WiFi.softAP(ssid, password);
  /*
  Serial.println("Access Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());*/ 
  Serial.print("Connecting to: ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
  digitalWrite(ledPin, LOW);
  Serial.println("Type IP this on your Web Browser Search bar");
  Serial.println(WiFi.localIP());
  // Route for root URL
  //Displays on the clients request
  //EX: 192.168.4.1/ - notice the URL '/'
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html",index_html );
  });
  //when the user request on /ledon it turn on the led
  //EX: 192.168.4.1/toggle - it will send a text on your web browser of
  // LED Toggled
   server.on("/toggle", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, !digitalRead(ledPin));
    request->send(200, "text/plain", "LED Toggled");
  });
  // Start server
  server.begin();
}

void loop() {
  // Nothing to do here
}
