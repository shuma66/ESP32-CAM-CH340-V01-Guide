/*
  BasicWebServer.ino - Minimal ESP32-CAM Web Server
  For: ESP32-S-CAM-CH340 V01 Board
  Configuration: XCLK on GPIO0, custom pins applied.
*/

#include "esp_camera.h"
#include <WiFi.h>

// 1. INCLUDE YOUR CUSTOM PIN FILE
#include "camera_pins_v01.h"

// 2. REPLACE WITH YOUR NETWORK CREDENTIALS
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// 3. DEFINE YOUR BOARD MODEL (This is the key!)
#define CAMERA_MODEL_ESP32S_V01_CH340

// Web server port
WebServer server(80);

void handleRoot() {
  // A very simple HTML page with a link to the stream
  String html = "<html><head><title>ESP32-CAM V01</title></head>";
  html += "<body><h1>ESP32-CAM V01 Basic Server</h1>";
  html += "<p><a href=\"/stream\">View Video Stream</a></p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);

  // Initialize camera with your custom config
  camera_config_t config;
  // ... (Full camera config object - use the same settings from your working sketch)
  // Initialize the camera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("Stream Link: http://");
  Serial.print(WiFi.localIP());
  Serial.println("/stream");

  // Set up web server routes
  server.on("/", handleRoot);
  // ... (Set up the /stream handler for video)
  server.begin();
}

void loop() {
  server.handleClient();
}
