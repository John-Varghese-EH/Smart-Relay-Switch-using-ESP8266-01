/**********************************************************************************
 *  TITLE: Smart Relay Switch using ESP8266-01 and Arduino IoT Cloud
 *  Author: John Varghese (@Cyber__Trinity)
 *  Version: 1.0
 *
 *  Preferences--> Additional boards Manager URLs : 
 *  https://dl.espressif.com/dl/package_esp32_index.json,
 *  http://arduino.esp8266.com/stable/package_esp8266com_index.json
 *  Download Board ESP8266 : https://github.com/esp8266/Arduino
 *  Download the libraries:
 *    - ArduinoIoTCloud Library with all dependencies
 *
 *  Arduino IoT Cloud Variables:
 *    CloudContactSensor switchStatus;
 *    CloudSwitch switch1;
 **********************************************************************************/

#include "thingProperties.h"
#include <ESP8266WiFi.h>

// Define the GPIO connected with Relay and status LED/switch
#define RelayPin 0      // GPIO0 controls relay
#define StatusPin 2     // GPIO2 reads status (input, e.g., manual switch or relay feedback)
bool Status = false;    // Local status variable

void setup() {
  Serial.begin(115200);
  delay(500);

  // Initialize Arduino IoT Cloud properties
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  pinMode(RelayPin, OUTPUT);
  pinMode(StatusPin, INPUT_PULLUP); // Set GPIO2 as input with pull-up resistor

  // At startup, ensure relay is OFF
  digitalWrite(RelayPin, HIGH);
}

bool updateSent = false;

void loop() {
  ArduinoCloud.update();

  bool currentStatus = (digitalRead(StatusPin) == LOW); // LOW = ON (active low)
  if (currentStatus != switchStatus) {
    switchStatus = currentStatus;
    ArduinoCloud.update();
    if (!updateSent) {
      Serial.print("Switch Status updated to: ");
      Serial.println(switchStatus ? "ON" : "OFF");
      updateSent = true;
    }
  } else {
    updateSent = false;
  }
}

// Callback function triggered when switch1 is changed from the cloud
void onSwitch1Change() {
  if (switch1 == 1) {
    digitalWrite(RelayPin, LOW); // Relay ON
    Serial.println("Relay ON");
  } else {
    digitalWrite(RelayPin, HIGH); // Relay OFF
    Serial.println("Relay OFF");
  }
}
