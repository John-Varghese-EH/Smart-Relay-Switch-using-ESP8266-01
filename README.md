# Smart Relay Switch ESP8266-01

A robust, cloud-connected smart relay switch using the ESP8266-01 and Arduino IoT Cloud.  
Control your appliances manually, remotely, or by voice with Google Home and Alexa. Monitor real-time status, enjoy advanced features like watchdog protection and Always-On mode, and integrate seamlessly with your smart home ecosystem.

---

## Table of Contents

- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Wiring Diagram](#wiring-diagram)
- [Installation & Setup](#installation--setup)
- [Arduino IoT Cloud Configuration](#arduino-iot-cloud-configuration)
- [Google Home & Alexa Integration](#google-home--alexa-integration)
- [Usage](#usage)
- [Cloud Commands](#cloud-commands)
- [Troubleshooting](#troubleshooting)
- [Contributing](#contributing)
- [License](#license)

---

## Features

- **Manual & Remote Control:** Toggle relay via physical switch or Arduino IoT Cloud dashboard.
- **Voice Assistant Integration:** Native control via Google Home and Alexa through Arduino IoT Cloud.
- **Real-Time Status Updates:** Appliance status is always synced to the cloud and voice assistants.
- **Cloud Messaging:** Send and receive commands/messages via the IoT Cloud.
- **Always-On Mode:** Automatically ensures your appliance stays ON.
- **Watchdog Timer:** Auto-restarts ESP8266 in case of software hangs.
- **Debounced Input:** Reliable manual switching with software debounce.
- **Extensible:** Easily adapt for smart home, industrial, or educational projects.

---

## Hardware Requirements

- [ESP8266-01 Module](https://www.espressif.com/en/products/socs/esp8266)
- 5V Relay Module (active LOW recommended)
- Pushbutton or toggle switch (for manual control)
- Breadboard & jumper wires
- Power supply (3.3V for ESP8266, 5V for relay)
- [Optional] USB to Serial adapter for programming

---

## Wiring Diagram



> **Note:** Use logic level shifters if your relay requires 5V signals.

---

## Installation & Setup

1. **Clone this repository:**
    ```
    git clone https://github.com/John-Varghese-EH/Smart-Relay-Switch-using-ESP8266-01.git
    ```

2. **Install Arduino IDE prerequisites:**
    - **ESP8266 Board support:**  
      Add `http://arduino.esp8266.com/stable/package_esp8266com_index.json` to *File > Preferences > Additional Boards Manager URLs*.
    - **Libraries:**  
      - ArduinoIoTCloud  
      - Arduino_ConnectionHandler  
      - Ticker

3. **Open the project:**
    - Open `SmartSwitch.ino` in Arduino IDE.

4. **Configure your credentials:**
    - Fill in your WiFi SSID, password, Arduino IoT Cloud Device ID, and Device Key in `thingProperties.h`.

---

## Arduino IoT Cloud Configuration

1. **Create a new Thing** in [Arduino IoT Cloud](https://create.arduino.cc/iot/).
2. **Add these variables:**
    - `switch1` (Type: Switch, Read & Write)
    - `switchStatus` (Type: Contact Sensor, Read Only)
    - `messages` (Type: String, Read & Write)
3. **Download the generated `thingProperties.h`** and replace the existing one or change accordingly.
4. **Associate your device** (ESP8266-01) with the Thing.

---

## Google Home & Alexa Integration

Your Smart Switch can be controlled via **Google Home** and **Alexa** using Arduino IoT Cloud’s official integration.

**To set up:**
1. Open the **Google Home** or **Alexa** app.
2. Add a new device and choose "Works with Google" or "Works with Alexa".
3. Search for "Arduino" and log in with your Arduino Cloud credentials.
4. Your Arduino IoT Cloud devices (e.g., `switch1`) will appear as switches in Google Home/Alexa.
5. Use voice commands like:
    - “Hey Google, turn on switch one.”
    - “Alexa, turn off switch one.”

**Notes:**
- Make sure your Arduino Cloud variables use supported types (e.g., Switch, Light).
- Manual toggling updates the status everywhere (cloud and assistants).

---

## Usage

- **Manual Toggle:**  
  Press the physical button/switch to toggle the relay. The status will update in the cloud and on voice assistants.
- **Remote Control:**  
  Use the Arduino IoT Cloud dashboard, Google Home, Alexa, or their mobile apps to turn the relay ON/OFF.
- **Cloud Messaging:**  
  Send commands via the `messages` widget to control advanced features.

---

## Cloud Commands

Send these messages via the IoT Cloud `messages` widget:

| Command       | Description                    |
|---------------|-------------------------------|
| `relay on`    | Turns relay ON                |
| `relay off`   | Turns relay OFF               |
| `alwayson`    | Enables Always-On mode        |
| `alwaysoff`   | Disables Always-On mode       |
| `help`        | Lists available commands      |

---

## Troubleshooting

- **Device not connecting to WiFi:**  
  Double-check SSID and password in `thingProperties.h`. Ensure 2.4GHz WiFi is used.
- **Relay not switching:**  
  Confirm wiring, relay power, and GPIO pin assignments.
- **Cloud not updating:**  
  Ensure IoT Cloud credentials are correct and device is online.
- **Voice assistant not discovering device:**  
  Check that your Arduino IoT Cloud account is linked and variables use supported types.
- **Frequent resets:**  
  Watchdog timer may trigger if the device hangs; check for infinite loops or blocking code.

---

## Contributing

Contributions are welcome!  
Please open issues for bug reports or feature requests, and submit pull requests for improvements.

1. Fork this repo  
2. Create your feature branch (`git checkout -b feature/your-feature`)  
3. Commit your changes (`git commit -am 'Add new feature'`)  
4. Push to the branch (`git push origin feature/your-feature`)  
5. Open a pull request

---

## License

This project is licensed under the [MIT License](LICENSE).

---

**Made with ❤️ by John Varghese (@Cyber__Trinity).**

---

> *For wiring diagrams, troubleshooting, and advanced usage, see the [docs](docs/) folder.*

---

## Currently a work in progress, but I’d appreciate your support! ☺️
<p align="left">
  <a href="https://buymeacoffee.com/CyberTrinity">
    <img src="https://img.shields.io/badge/Buy%20Me%20a%20Coffee-ffdd00?style=for-the-badge&logo=buy-me-a-coffee&logoColor=black" />
  </a>
  <a href="https://patreon.com/CyberTrinity">
    <img src="https://img.shields.io/badge/Patreon-F96854?style=for-the-badge&logo=patreon&logoColor=white" />
  </a>
</p>
