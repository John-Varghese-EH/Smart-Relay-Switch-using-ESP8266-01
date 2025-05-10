# Wiring Diagram

Below is the recommended wiring for the Smart Switch ESP8266 project.  
This setup supports both manual and remote (cloud/voice) control, and status feedback.

![Wiring Diagram](Indoor-CAM-Relay-Connection-with-Status.jpg)

**Legend:**
- **ESP8266-01:** Main WiFi microcontroller.
- **Relay Module:** Switches the load (e.g., camera, appliance).
- **Manual Switch:** Connected to GPIO2 for local toggling.
- **Status LED:** Indicates relay or device state.
- **Power Supplies:** 5V for relay/ESP, 12V for the load (e.g., camera).

**Connections:**
- GPIO0 → Relay IN
- GPIO2 → Manual switch input/status sensor
- 5V and GND → Power relay and ESP8266-01
- Relay output → Controls AC/DC load (e.g., camera, light)

> **Caution:** Always ensure proper isolation when switching high voltages.
