# Plant-whisperer---Iot
Plant Whisperer - In a nutshell it is a plant monitoring system, that displays data in real time.

# Plant Whisperer - IoT Smart Plant Monitoring System

## Sensors Used
- DHT11 Temperature and Humidity Sensor  
- Soil Moisture Sensor  
- Light Sensor (optional)  
- ESP32 Microcontroller

## Hardware Connections
- DHT11 Data Pin -> GPIO 4 on ESP32  
- Soil Moisture Sensor Analog Pin -> GPIO 36 (VP)  
- Light Sensor -> GPIO XX  

## Software Overview
The Arduino code reads sensor values and sends them via WiFi to ThingSpeak using the ESP32's WiFi capabilities.

## ThingSpeak Integration
- Created a ThingSpeak channel and obtained an API Write Key.  
- The ESP32 posts sensor data periodically to ThingSpeak.  
- Real-time data is visualized on the ThingSpeak dashboard.

## How to Run
- Upload the Arduino sketch to the ESP32.  
- Make sure WiFi credentials and ThingSpeak API key are set in the code.  
- Monitor data on your ThingSpeak channel.

---


