#include <WiFi.h>
#include <WebServer.h>

// WiFi credentials
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// LED pin (connected to GPIO 23)
const int LED_PIN = 23;

WebServer server(80);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n\nStarting ESP32...");
  
  // Initialize LED pin
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  // Connect to WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  Serial.print("Connecting to WiFi");
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 30) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    
    // Setup web server routes
    server.on("/", handleRoot);
    server.on("/notify", handleNotification);
    
    server.begin();
    Serial.println("Web server started!");
  } else {
    Serial.println("\nWiFi connection failed");
  }
}

void handleRoot() {
  server.send(200, "text/html", 
    "<h1>GlowBox - Notification Light</h1>"
    "<p>Send a request to /notify to trigger the LED</p>"
    "<button onclick=\"fetch('/notify')\">Test Notification</button>");
}

void handleNotification() {
  Serial.println("Notification received!");
  
  // Flash LED 3 times
  for(int i = 0; i < 3; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  }
  
  server.send(200, "text/plain", "OK");
}

void loop() {
  server.handleClient();
  delay(1);
}
