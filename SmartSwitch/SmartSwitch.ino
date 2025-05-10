/**********************************************************************************
 *  TITLE: Arduino IoT Cloud Smart Relay Switch using ESP01
 *  Author: John Varghese (@Cyber__Trinity)
 *  Version: 2.0
 *
 *  Description:
 *  ESP8266-based smart relay switch with manual/cloud control and status reporting.
 *  Features watchdog timer, always-on mode, and cloud message handling.
 *
 *  Requirements:
 *  - ESP8266 board package
 *  - ArduinoIoTCloud library
 *  - Ticker library
 *  - Thing variables:
 *      CloudContactSensor switchStatus;
 *      CloudSwitch switch1;
 *      String messages;
 **********************************************************************************/

#include "thingProperties.h"
#include <ESP8266WiFi.h>
#include <Ticker.h>

// GPIO pin definitions
#define RELAY_PIN 0    // GPIO0 controls relay
#define STATUS_PIN 2   // GPIO2 reads manual switch state

// Watchdog Timer
Ticker watchdogTicker;
volatile int watchdogCount = 0;
const int WATCHDOG_TIMEOUT = 4; // 4 intervals * 5s = 20s timeout

// AlwaysOn mode control
bool alwaysOnMode = false;
unsigned long lastSwitchToggle = 0;
const unsigned long debounceTime = 1000; // ms debounce

// State management
bool currentRelayState = false;
bool currentSwitchState = false;

void ISRwatchdog() {
  watchdogCount++;
  if (watchdogCount >= WATCHDOG_TIMEOUT) {
    Serial.println("Watchdog timeout! Rebooting...");
    ESP.restart();
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);

  // Initialize GPIO
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Relay OFF
  currentRelayState = false;
  pinMode(STATUS_PIN, INPUT_PULLUP);

  // WiFi Connection
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASS);
  WiFi.setAutoReconnect(true);
  
  Serial.print("Connecting to WiFi");
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 40) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nWiFi failed! Rebooting...");
    ESP.restart();
  }

  // Arduino IoT Cloud
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  // Initial states
  switch1 = false;
  watchdogTicker.attach(5, ISRwatchdog);
  Serial.println("System ready");
}

void loop() {
  ArduinoCloud.update();
  watchdogCount = 0; // Reset watchdog

  bool switchState = (digitalRead(STATUS_PIN) == LOW);
  bool relayState = (digitalRead(RELAY_PIN) == LOW);
  unsigned long now = millis();

  // AlwaysOn logic
  if (alwaysOnMode) {
    if (!switchState && (now - lastSwitchToggle >= debounceTime)) {
      digitalWrite(RELAY_PIN, !relayState);
      currentRelayState = !relayState;
      switch1 = currentRelayState;
      lastSwitchToggle = now;
      messages = "[AlwaysOn] Toggling relay";
      ArduinoCloud.update();
    }
  }

  // State change detection
  if (!alwaysOnMode && switchState != currentSwitchState) {
    currentSwitchState = switchState;
    switchStatus = switchState;
    messages = "Switch: " + String(switchState ? "ON" : "OFF");
    ArduinoCloud.update();
  }

  ArduinoCloud.update();
}

void onSwitch1Change() {
  if (!alwaysOnMode) {
    if (switch1 != currentRelayState) {
      currentRelayState = switch1;
      digitalWrite(RELAY_PIN, switch1 ? LOW : HIGH);
      messages = "Relay " + String(switch1 ? "ON" : "OFF") + " (Cloud)";
      ArduinoCloud.update();
    }
  } else {
    messages = "Manual control disabled (AlwaysOn)";
    switch1 = currentRelayState;
    ArduinoCloud.update();
  }
}

void onMessagesChange() {
  String response;

  if (messages.equalsIgnoreCase("Relay On")) {
    alwaysOnMode = false;
    digitalWrite(RELAY_PIN, LOW);
    switch1 = true;
    response = "Relay ON by command";
  } else if (messages.equalsIgnoreCase("Relay Off")) {
    alwaysOnMode = false;
    digitalWrite(RELAY_PIN, HIGH);
    switch1 = false;
    response = "Relay OFF by command";
  } else if (messages.equalsIgnoreCase("alwaysOn")) {
    alwaysOnMode = true;
    response = "AlwaysOn Enabled";
  } else if (messages.equalsIgnoreCase("alwaysOff")) {
    alwaysOnMode = false;
    response = "AlwaysOn Disabled";
  } else {
    response = "IoT Cam Relay v2.0 \nby John Varghese (@Cyber__Trinity)\n | Valid Commands: Relay on/off, AlwaysOn/AlwaysOff, help/about\n | Status auto-synced";
  }

  messages = response;
  ArduinoCloud.update();
}
