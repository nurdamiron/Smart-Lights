#include <Tlc5940.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP";
const char* password = "12345678";

// Create an instance of the WebServer class
WebServer server(80);

// Define the number of TLC5940 chips in the chain
#define NUM_TLC 1

// Define the number of MOSFETs connected to each TLC5940 chip
#define NUM_MOSFETS 12

// Define the initial brightness of the LED strips (0-100)
int brightness = 50;




// Define the number of stairs and the duration of shine time
int numStairs = 12;
int shineDuration = 500;

// Define whether motion sensing is enabled or disabled
bool motionSensingEnabled = true;

// Define the TLC5940 pins (SIN, SCLK, XLAT, BLANK, GSCLK)
int tlcPins[] = {23, 18, 5, 4, 19};

// Define the MOSFET pins for each LED strip
int mosfetPins[NUM_TLC][NUM_MOSFETS] = {
  {27, 26, 25, 33, 32, 35, 34, 39, 36, 21, 19, 22}
};

void setup() {
  // Initialize the serial communication
  Serial.begin(115200);

  // Initialize the TLC5940 library
  Tlc.init();

  // Set the maximum brightness value for the TLC5940 library
  Tlc.setPWMResolution(8);

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
  server.on("/stairs", handleStairs);
  server.on("/duration", handleDuration);
  server.on("/motion", handleMotion);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Listen for incoming client requests
  server.handleClient();

  // Check if motion sensing is enabled and the ultrasonic sensor detects motion
  if (motionSensingEnabled && detectMotion()) {
    // Turn on the LED strips for the specified duration
    for (int i = 0; i < numStairs; i++) {
      digitalWrite(mosfetPins[0][i], HIGH);
    }
    delay(shineDuration);
    for (int i = 0; i < numStairs; i++) {
      digitalWrite(mosfetPins[0][i], LOW);
    }
  }

  // Update the brightness of the LED strips
  for (int i = 0; i < NUM_TLC; i++) {
    for (int j = 0; j < NUM_MOSFETS; j++) {
      // Calculate the PWM value based on the brightness level
      int pwmValue = map(brightness, 0, 100, 0, 255);

      // Set the PWM value for the current MOSFET
      int channel = i * NUM_MOSFETS + j;
      Tlc.set(channel, pwmValue);
      }

// Update the TLC5940 output
Tlc.update();
}

// Function to handle the root URL ("/")
void handleRoot() {
// Set the content type and send the HTML page to the client
  server.send(200, "text/html", "<html><head><title>ESP32 LED Control</title></head><body><h1>ESP32 LED Control</h1><p>Brightness: " + String(brightness) + "</p><p>Number of stairs: " + String(numStairs) + "</p><p>Shine duration: " + String(shineDuration) + " ms</p><p>Motion sensing: " + (motionSensingEnabled ? "Enabled" : "Disabled") + "</p><form method='POST' action='/brightness'><input type='range' name='brightness' min='0' max='100' value='" + String(brightness) + "'><input type='submit' value='Set'></form><form method='POST' action='/stairs'><input type='number' name='stairs' min='1' max='12' value='" + String(numStairs) + "'><input type='submit' value='Set'></form><form method='POST' action='/duration'><input type='number' name='duration' min='100' max='5000' step='100' value='" + String(shineDuration) + "'><input type='submit' value='Set'></form><form method='POST' action='/motion'><input type='checkbox' name='motion' " + (motionSensingEnabled ? "checked" : "") + "><input type='submit' value='Set'></form></body></html>");
}

// Function to handle the "/brightness" URL
void handleBrightness() {
// Get the new brightness value from the POST data
  brightness = server.arg("brightness").toInt();

// Redirect the client back to the root URL
  server.sendHeader("Location", "/");
  server.send(302);
}

// Function to handle the "/stairs" URL
void handleStairs() {
// Get the new number of stairs from the POST data
  numStairs = server.arg("stairs").toInt();

  // Redirect the client back to the root URL 
  server.sendHeader("Location", "/");
  server.send(302);
}

// Function to handle the "/duration" URL
void handleDuration() {
  // Get the new duration value from the POST data
  shineDuration = server.arg("duration").toInt();

// Redirect the client back to the root URL
  server.sendHeader("Location", "/");
  server.send(302);
}

// Function to handle the "/motion" URL
void handleMotion() {
// Toggle the motion sensing state
  motionSensingEnabled = !motionSensingEnabled;

// Redirect the client back to the root URL
  server.sendHeader("Location", "/");
  server.send(302);
}

// Function to detect motion using an ultrasonic sensor
bool detectMotion() {
// Define the ultrasonic sensor pins (TRIG, ECHO)
  int trigPin = 14;
  int echoPin = 12;

  // Generate a 10 microsecond pulse on the TRIG pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

// Read the pulse duration on the ECHO pin
  long duration = pulseIn(echoPin, HIGH);

// Calculate the distance based on the pulse duration
  float distance = duration * 0.034 / 2;

// Return true if the distance
// is less than 50 cm (indicating motion detected), otherwise false
  return (distance < 50);
}

