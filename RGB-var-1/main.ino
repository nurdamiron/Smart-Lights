#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Create an instance of the WebServer class
WebServer server(80);

// Define the pins used for the RGB LED strip
#define RED_PIN 12
#define GREEN_PIN 14
#define BLUE_PIN 27

// Define the initial brightness of the LED strip
int brightness = 128;

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);

  // Initialize the pins used for the RGB LED strip
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Set up the web server
  server.on("/", handleRoot);
  server.on("/brightness", handleBrightness);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Listen for incoming client requests
  server.handleClient();
}

// Function to handle the root URL ("/")
void handleRoot() {
  // Set the content type and send the HTML page to the client
  server.send(200, "text/html", "<html><head><title>ESP32 RGB LED Control</title></head><body><h1>ESP32 RGB LED Control</h1><p>Brightness: " + String(brightness) + "</p><form method='POST' action='/brightness'><input type='range' name='brightness' min='0' max='255' value='" + String(brightness) + "'><input type='submit' value='Set'></form></body></html>");
}

// Function to handle the "/brightness" URL
void handleBrightness() {
  // Get the new brightness value from the POST data
  brightness = server.arg("brightness").toInt();

  // Set the brightness of each color channel
  analogWrite(RED_PIN, brightness);
  analogWrite(GREEN_PIN, brightness);
  analogWrite(BLUE_PIN, brightness);

  // Redirect the client back to the root URL
  server.sendHeader("Location", "/");
  server.send(302);
}
