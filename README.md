# Plant Whisperer - IoT Project

## Overview
Plant Whisperer is a smart plant monitoring system built using ESP32 and various sensors. The system collects environmental data such as soil moisture, temperature, humidity, and light intensity, then uploads it to ThingSpeak IoT platform for remote monitoring and visualization.

---

## Sensors Used

| Sensor               | Purpose                   | Connection to ESP32         |
|----------------------|---------------------------|-----------------------------|
| Soil Moisture Sensor  | Measure soil water level  | Analog pin (e.g., GPIO34)   |
| DHT11/DHT22          | Temperature & Humidity    | Digital pin (e.g., GPIO27)  |
| Light Sensor (LDR)    | Measure ambient light     | Analog pin (e.g., GPIO35)   |
| Water Level Sensor    | Water reservoir level     | Digital/Analog pin (e.g., GPIO32) |

*Note: Adjust GPIO pins according to your actual wiring.*

---

## Hardware Connections

- Connect each sensor's VCC to 3.3V or 5V power supply as required.
- Connect all GND pins to ESP32 ground.
- Connect sensor signal pins to respective ESP32 GPIO pins (see table above).

---

## ThingSpeak Setup

1.
