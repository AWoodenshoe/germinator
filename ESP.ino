#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <IRremote.h>

// Change to your ssid and passowrd
const char* ssid = "[SSID]";
const char* password = "[PASSWORD]";

// Change to your API Key for Google Cloud
const String GOOGLE_ID = "[API_KEY]";

const char* apiUrl = "http://worldtimeapi.org/api/timezone/America/New_York";

#define WIDTH 128
#define HEIGHT 64
#define RESET -1

Adafruit_SSD1306 display(WIDTH, HEIGHT, &Wire, RESET);

#define DHT_PIN 25
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

#define MOISTURE_PIN 34

#define TEMPERATURE_PIN 13
OneWire oneWire(TEMPERATURE_PIN);
DallasTemperature DS(&oneWire);

#define RECEIVER_PIN 27   
IRrecv receiver(RECEIVER_PIN);
bool buttonPressed = false;  
long lastCommand = 0;        
long lastReceived = 0;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  
  dht.begin();
  DS.begin();
  receiver.enableIRIn(); 
  
  testdrawstyles("Germinator");
  delay(2000);
  testdrawstyles("Press (0) for instructions");
  
  Serial.println("Ready to go");
}

void loop() {
  if (receiver.decode()) {
    long command = receiver.decodedIRData.command;
  
    if (command != lastCommand) {
      switch (command) {
        case 22:
          phaseZero();
          break;
        case 12:
          phaseOne();
          break;
        default:
          Serial.println("Input error.");
          break;
      }
  
      lastCommand = command; 
      lastReceived = millis();  
    }
  
    receiver.resume();  
  } else {
    if (millis() - lastReceived > 500) {  
      lastCommand = 0;  
    }
  }
}

void phaseZero() {
  testdrawstyles("Welcome to Germinator!");
  delay(2000);
  testdrawstyles("(1) for flower options.");
  delay(2000);
  testdrawstyles("(0) for instructions.");

  float airT = dht.readTemperature();
  float airH = dht.readHumidity();
  
  
  int moisture = analogRead(MOISTURE_PIN);
  moisture = map(moisture, 3700, 1800, 0, 100);
  moisture = constrain(moisture, 0, 100);
  
  DS.requestTemperatures();
  int celsius = DS.getTempCByIndex(0);
  
  int weekNum = fetchWeekNumber();
  
  sendData(airT, airH, celsius, moisture, weekNum);
}

void testdrawstyles(String str) {
  display.clearDisplay();
  display.setTextSize(2);      display.setTextColor(SSD1306_WHITE);    display.setCursor(0, 1);     
  display.println(F(str.c_str()));
  display.display();
  delay(2000);
}

void sendData(int value1, int value2, int value3, int value4, int value5) {
  HTTPClient http;
  String url = "https://script.google.com/macros/s/" + SCRIPT_ID + "/exec?";
  url += "action=saveData";
  url += "&value1=" + String(value1);
  url += "&value2=" + String(value2);
  url += "&value3=" + String(value3);
  url += "&value4=" + String(value4);
  url += "&value5=" + String(value5);
  http.begin(url);

  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  http.GET();

  url = "https://script.google.com/macros/s/" + SCRIPT_ID + "/exec?action=fetchData";
  http.begin(url);
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  http.GET();
  testdrawstyles(http.getString());

  HTTPClient http;
  http.begin(apiUrl);                 
  http.GET();  
  
  String payload = http.getString();  
  int index = payload.indexOf("\"week_number\":");

  String weekNum = payload.substring(index + 14, payload.indexOf(",", index));
  return weekNum.toInt();
}
