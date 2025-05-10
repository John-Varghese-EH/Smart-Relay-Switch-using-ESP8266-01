# Wiring Diagram

Below is the recommended wiring for the Smart Switch ESP8266 project.  
This setup supports both manual and remote (cloud/voice) control, and status feedback.

![Wiring Diagram](./)

**Legend:**
- **ESP8266-01:** Main WiFi microcontroller.
- **Relay Module:** Switches the load (e.g., camera, appliance).
- **Manual Switch:** Connected to GPIO2 for local toggling.
- **Status LED:** Indicates relay or device state.
- **Power Supplies:** 5V for relay/ESP.

**Connections:**
- GPIO0 → Relay IN
- GPIO2 → Manual switch input/status sensor
- 5V and GND → Power relay and ESP8266-01
- Relay output → Controls AC/DC load (eg; fan, light, etc)

> [!CAUTION]
> Always ensure proper isolation when switching high voltages.

---

## Support My Work ☺️
<p align="left">
  <a href="https://buymeacoffee.com/CyberTrinity">
    <img src="https://img.shields.io/badge/Buy%20Me%20a%20Coffee-ffdd00?style=for-the-badge&logo=buy-me-a-coffee&logoColor=black" />
  </a>
  <a href="https://patreon.com/CyberTrinity">
    <img src="https://img.shields.io/badge/Patreon-F96854?style=for-the-badge&logo=patreon&logoColor=white" />
  </a>
</p>

*Powered By: [J0X](https://github.com/John-Varghese-EH)*
