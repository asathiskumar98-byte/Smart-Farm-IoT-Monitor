#include <ESP8266WiFi.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// DHT Sensor
#define DHTPIN D3
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Sensor Pins
#define SOIL_PIN A0
#define RAIN_PIN D5
#define LDR_PIN D6
#define MQ2_PIN D7

// Wi-Fi & ThingSpeak
const char* ssid = "SaThis JeeVa";
const char* password = "ABCDEFGH";
String apiKey = "4QQPQ7N1UJJLGKP4";
const char* server = "api.thingspeak.com";

WiFiClient client;

void setup() {
  Serial.begin(115200);
  dht.begin();

  // OLED setup
  Wire.begin(D1, D2);  // SDA, SCL
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 25);
  display.println("Connecting WiFi...");
  display.display();

  // Wi-Fi connection
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  Serial.println(WiFi.localIP());

  display.clearDisplay();
  display.setCursor(0, 10);
  display.println("WiFi Connected!");
  display.println(WiFi.localIP());
  display.display();
  delay(2000);
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int soil = analogRead(SOIL_PIN);
  int rain = digitalRead(RAIN_PIN);
  int ldr = digitalRead(LDR_PIN);
  int gas = digitalRead(MQ2_PIN);

  Serial.println("----- Sensor Data -----");
  Serial.print("Temperature: "); Serial.println(temp);
  Serial.print("Humidity: "); Serial.println(hum);
  Serial.print("Soil Moisture: "); Serial.println(soil);
  Serial.print("Rain Sensor: "); Serial.println(rain);
  Serial.print("LDR Light: "); Serial.println(ldr);
  Serial.print("MQ2 Gas: "); Serial.println(gas);

  // OLED display update
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(10, 0);
  display.println("Smart Farm Monitor");

  display.setCursor(0, 10);
  display.print("Tem:"); display.print(temp, 1); display.print("C  ");
  display.print("Hum:"); display.print(hum, 0); display.println("%");

  display.setCursor(0, 20);
  display.print("Soil:");
  if (soil < 400) display.print("Wet ");
  else if (soil < 700) display.print("Moist ");
  else display.print("Dry  ");
  display.print("("); display.print(soil); display.println(")");

  display.setCursor(0, 30);
  display.print("Light:");
  display.print(ldr ? "Dark " : "Bright");

  display.setCursor(0, 40);
  display.print("Gas:");
  display.print(gas == HIGH ? "Safe" : "Alert");

  display.setCursor(0, 50);
  display.print("Rain:");
  display.print(rain == LOW ? "Raining" : "Clear ");
  display.print("  WiFi:");
  display.print(WiFi.status() == WL_CONNECTED ? "OK" : "Err");

  display.display();


  // Send to ThingSpeak
  if (client.connect(server, 80)) {
    String postStr = apiKey;
    postStr += "&field1=" + String(temp);
    postStr += "&field2=" + String(hum);
    postStr += "&field3=" + String(soil);
    postStr += "&field4=" + String(rain);
    postStr += "&field5=" + String(ldr);
    postStr += "&field6=" + String(gas);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
  }

  client.stop();
  Serial.println("Data sent to ThingSpeak");
  delay(1000); // Update every 1 seconds
}
