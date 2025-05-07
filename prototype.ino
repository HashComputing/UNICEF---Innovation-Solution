#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

// DHT11 settings
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// OLED settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Initialize DHT sensor
  dht.begin(2);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Correct I2C initialization
    Serial.println("OLED display initialization failed!");
    while (true); // Halt execution
  }

  // Display initial message
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("DHT11 & OLED");
  display.println("Initializing...");
  display.display();
  delay(2000); // Wait for sensor to stabilize
}

void loop() {
  delay(2000); // Minimum delay between readings

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Serial output (optional)
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%\tTemperature: ");
  Serial.print(temperature);
  Serial.println("C");

  // Update OLED display
  display.clearDisplay();
  display.setCursor(0, 0);
  if (isnan(humidity) || isnan(temperature)) {
    display.println("Failed to read");
    display.println("from DHT11 sensor!");
  } else {
    display.print("Humidity: ");
    display.print(humidity);
    display.println("%");
    display.print("Temp: ");
    display.print(temperature);
    display.println("C");
  }
  display.display();
}
