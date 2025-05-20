# Germinator
Germinator is an ESP32-based smart agriculture project designed to monitor and display environmental conditions critical for plant growth. It integrates sensors for temperature, humidity, and soil moisture, displays information on an OLED screen, and sends data to Google Sheets via a web API. It also supports IR remote interaction.

## Features
- Wi-Fi connectivity using ESP32
- Air temperature & humidity readings via DHT11
- Soil moisture monitoring via analog sensor
- Soil temperature using DS18B20
- OLED display (128x64) for real-time info
- Data logging to Google Sheets
- Week number fetch via WorldTimeAPI
- IR remote control support for different modes

## Hardware
- ESP32 microcontroller
- DHT11 sensor
- DS18B20 temperature sensor
- Soil moisture sensor
- OLED Display (SSD1306)
- IR Receiver (TSOP)
- Jumper wires, breadboard

## Library Dependencies
Make sure to install the following Arduino libraries:
- WiFi.h
- HTTPClient.h
- DHT.h
- Wire.h
- Adafruit_GFX.h
- Adafruit_SSD1306.h
- OneWire.h
- DallasTemperature.h
- IRremote.h

## Getting Started
1. Clone this repository or download the .ino file.
2. Open the project in the Arduino IDE.
3. Install all required libraries via the Library Manager.
4. Replace the placeholders:
    - const char* ssid = "YOUR_WIFI_SSID";
    - const char* password = "YOUR_WIFI_PASSWORD";
    - const String GOOGLE_ID = "YOUR_GOOGLE_SCRIPT_ID";
5. Upload the code to your ESP32 board.
6. Use an IR remote to navigate modes.

## Google Sheets Integration
This project logs data using Google Apps Script:
- Create a Google Sheet.
- Open the Extensions > Apps Script.
- Paste the .gs script that accepts GET requests and logs parameters.
- Deploy as a web app (publicly accessible).
- Use the Script ID in your code.

## Remote Control Commands
- `0` → Show instructions
- `1` → Get flower options

## Code Overview
- `setup()` initializes Wi-Fi, sensors, display, and IR receiver.
- `loop()` listens for IR commands and triggers functions.
- `phaseZero()` shows welcome text.
- `phaseOne()` collects sensor data and logs it online.
- `sendData()` sends and displays logged data from Google Sheets.
- `fetchWeekNumber()` retrieves the current week number.

## License
This project is open source under the MIT License.
