#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char DEVICE_LOGIN_NAME[]  = ""; // Enter DEVICE ID
const char SSID[]               = ""; // WiFi SSID
const char PASS[]               = ""; // WiFi Password
const char DEVICE_KEY[]         = ""; // Secret device key

void onSwitch1Change();
void onMessagesChange();

// Cloud variables
CloudSwitch switch1;
CloudContactSensor switchStatus;
String messages;

void initProperties() {
  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  
  ArduinoCloud.addProperty(switch1, READWRITE, ON_CHANGE, onSwitch1Change);
  ArduinoCloud.addProperty(switchStatus, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(messages, READWRITE, ON_CHANGE, onMessagesChange);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
