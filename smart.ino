// Smart Plant & Security Monitor with NodeMCU and Blynk

#define BLYNK_TEMPLATE_ID "TMPL3E5OIEnG-"
#define BLYNK_TEMPLATE_NAME "smart plant"
#define BLYNK_AUTH_TOKEN "WrlL43Cv7r1sFScgGi3Cp_trTJWyrNES"

#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// WiFi Credentials
char ssid[] = "vivo";
char pass[] = "sardar6388";

// Initialize LCD: 0x27 or 0x3F are common I2C addresses
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Sensor Definitions
#define DHTPIN D4
#define DHTTYPE DHT11
#define SOIL_PIN A0
#define PIR_PIN D5

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

int pirState = LOW;

void sendSensorData() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int soil = analogRead(SOIL_PIN);

  // Map soil moisture value to 0–100%
  soil = map(soil, 0, 1024, 0, 100);
  soil = (soil - 100) * -1;

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Send data to Blynk
  Blynk.virtualWrite(V0, temp);
  Blynk.virtualWrite(V1, hum);
  Blynk.virtualWrite(V3, soil);

  // Display on LCD
  lcd.setCursor(0, 0);
  lcd.print("T:"); lcd.print(temp); lcd.print("C ");
  lcd.print("H:"); lcd.print(hum); lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Soil:"); lcd.print(soil); lcd.print("% ");
}

void checkMotion() {
  int motion = digitalRead(PIR_PIN);
  if (motion == HIGH && pirState == LOW) {
    Blynk.logEvent("motion_alert", "Motion Detected!");
    Blynk.virtualWrite(V5, 255);
    pirState = HIGH;
  } else if (motion == LOW && pirState == HIGH) {
    Blynk.virtualWrite(V5, 0);
    pirState = LOW;
  }
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  dht.begin();
  lcd.begin(16, 2);
  lcd.backlight();
  pinMode(PIR_PIN, INPUT);

  lcd.setCursor(0, 0);
  lcd.print("Smart Plant Init");
  delay(2000);
  lcd.clear();

  timer.setInterval(2000L, sendSensorData);
  timer.setInterval(1000L, checkMotion);
}

void loop() {
  Blynk.run();
  timer.run();
}
