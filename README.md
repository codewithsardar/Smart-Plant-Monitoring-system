The Smart Plant Monitoring System is an IoT-based solution designed to help users monitor their plant's environment in real-time. This system measures key parameters like soil moisture, temperature, humidity, light intensity, and optionally gas levels, and sends the data to a mobile app or dashboard using platforms like Blynk, Thingspeak, or a custom web server.

This is ideal for home gardeners, greenhouse operators, or anyone looking to automate plant care and improve plant health.

⚙️ Features
🌡️ Monitors temperature and humidity using a DHT11/DHT22 sensor

💧 Measures soil moisture levels to detect watering needs

☀️ Detects light intensity using an LDR sensor

💨 Optionally detects air quality or gas levels (e.g., MQ135)

📲 Sends real-time data to Blynk or other cloud platforms

⚠️ Sends alerts when conditions are not optimal

🔋 Low power consumption design for long-term usage

🧰 Hardware Requirements
Component	Description
NodeMCU / ESP32	Main controller with Wi-Fi capability
DHT11 / DHT22	Temperature and humidity sensor
Soil Moisture Sensor	Capacitive or resistive type
LDR (Photoresistor)	Measures ambient light intensity
MQ135 / MQ2	(Optional) Gas/Air quality sensor
OLED / LCD	(Optional) Displays data locally
Power Source	USB / Battery / Solar panel
Wi-Fi	Required for IoT functionality

