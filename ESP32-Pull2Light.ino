#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi Credentials
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

#define RELAY_PIN 23 // GPIO pin connected to the Relay

WebServer server(80);
bool lightState = false; 

// Embedded Web Dashboard (HTML + CSS + JS)
const char HTML_PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Smart Lamp Control</title>
  <style>
    body {
      background-color: #121212;
      display: flex;
      flex-direction: column;
      align-items: center;
      justify-content: center;
      height: 100vh;
      margin: 0;
      font-family: Arial, sans-serif;
      color: white;
    }
    .lamp-container {
      position: relative;
      width: 200px;
      height: 300px;
      display: flex;
      flex-direction: column;
      align-items: center;
    }
    .shade {
      width: 140px;
      height: 90px;
      background: #444;
      clip-path: polygon(20% 0%, 80% 0%, 100% 100%, 0% 100%);
      transition: background 0.3s;
      z-index: 2;
    }
    .beam {
      width: 0;
      height: 0;
      border-left: 90px solid transparent;
      border-right: 90px solid transparent;
      border-bottom: 180px solid rgba(255, 235, 59, 0.5);
      position: absolute;
      top: 90px;
      opacity: 0;
      transition: opacity 0.3s;
      z-index: 1;
    }
    .stand {
      width: 8px;
      height: 120px;
      background: #888;
      z-index: 2;
    }
    .base {
      width: 100px;
      height: 12px;
      background: #666;
      border-radius: 6px;
      z-index: 2;
    }
    .chain-container {
      position: absolute;
      top: 85px;
      right: 55px;
      z-index: 3;
      cursor: pointer;
      user-select: none;
    }
    .string {
      width: 3px;
      height: 50px;
      background: #aaa;
      margin: 0 auto;
      transition: height 0.1s;
    }
    .handle {
      width: 16px;
      height: 24px;
      background: #ffd700;
      border-radius: 8px;
      box-shadow: 0 0 5px rgba(0,0,0,0.5);
    }
    .on .shade {
      background: #fdd835;
      box-shadow: 0 -10px 30px #fdd835;
    }
    .on .beam {
      opacity: 1;
    }
  </style>
</head>
<body>

  <h2>Pull to Control Light</h2>

  <div class="lamp-container" id="lamp">
    <div class="shade"></div>
    <div class="beam"></div>
    <div class="stand"></div>
    <div class="base"></div>
    
    <div class="chain-container" id="chain" onclick="toggleLight()">
      <div class="string" id="string"></div>
      <div class="handle"></div>
    </div>
  </div>

  <script>
    let isON = false;

    function toggleLight() {
      const string = document.getElementById('string');
      string.style.height = '75px';
      setTimeout(() => {
        string.style.height = '50px';
      }, 150);

      fetch('/toggle')
        .then(response => response.text())
        .then(state => {
          isON = (state === "1");
          updateUI();
        });
    }

    function updateUI() {
      const lamp = document.getElementById('lamp');
      if (isON) {
        lamp.classList.add('on');
      } else {
        lamp.classList.remove('on');
      }
    }

    fetch('/state')
      .then(response => response.text())
      .then(state => {
        isON = (state === "1");
        updateUI();
      });
  </script>
</body>
</html>
)rawliteral";

void handleRoot() {
  server.send(200, "text/html", HTML_PAGE);
}

void handleToggle() {
  lightState = !lightState;
  digitalWrite(RELAY_PIN, lightState ? LOW : HIGH); 
  server.send(200, "text/plain", lightState ? "1" : "0");
}

void handleState() {
  server.send(200, "text/plain", lightState ? "1" : "0");
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.on("/state", handleState);

  server.begin();
  Serial.println("HTTP Server Started");
}

void loop() {
  server.handleClient();
}
