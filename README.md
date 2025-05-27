# Plant Whisperer - IoT Project

## Overview
Plant Whisperer is an IoT-based smart plant monitoring system using an ESP32 microcontroller. It measures environmental parameters like soil moisture, temperature, humidity, and light intensity using various sensors and sends this data to the ThingSpeak platform for real-time remote monitoring.

---

## Sensors Used and Connections

| Sensor               | Purpose                     | ESP32 Connection Details              |
|----------------------|-----------------------------|-------------------------------------|
| **DHT22 (AM2302)**    | Measures temperature & humidity | Data pin connected to GPIO 4        |
| **TSL2591 Light Sensor** | Measures ambient light intensity | Connected via I2C (SDA, SCL pins, default ESP32 pins) |
| **Soil Moisture Sensor** | Measures soil moisture level    | Analog output connected to GPIO 34  |

### Additional Notes:
- All sensors share a common ground (GND) with ESP32.
- Power sensors using 3.3V or 5V as per their requirements.
- The TSL2591 sensor uses I2C communication handled by the Wire library.

---

## WiFi and ThingSpeak Setup

- **WiFi Credentials:**  
  - SSID: Your WiFi network name  
  - Password: Your WiFi password

- **ThingSpeak Configuration:**  
  - Create a ThingSpeak account at [thingspeak.com](https://thingspeak.com).
  - Create a new channel for your project.
  - Obtain your **Write API Key** from the channel.
  - Replace `"your API key"` in the code with your actual ThingSpeak Write API key.

---

## How It Works (Code Workflow)

1. **Initialize sensors**: DHT22, TSL2591 light sensor, and soil moisture sensor.
2. **Connect to WiFi**: ESP32 attempts to connect to the specified network.
3. **Read sensor data**:
   - Temperature and humidity from DHT22.
   - Light intensity from TSL2591.
   - Soil moisture value from the analog sensor.
4. **Send data to ThingSpeak**:
   - Constructs a URL with the sensor readings.
   - Uses HTTP GET request to send data to ThingSpeak API.
5. **Monitor data online**: View your sensor readings on your ThingSpeak channel dashboard in real-time.

---

## Important Tips

- **API Keys & Credentials**  
  - **Never** commit real WiFi passwords or API keys to public GitHub repositories.  
  - Use placeholder strings in your code like:  
    ```cpp
    const char* ssid = "your_network_name";
    const char* password = "your_password";
    String apiKey = "your_api_key";
    ```  
  - Keep credentials in a separate file (e.g., `config.h`) and add it to `.gitignore`.

- **Power Supply**  
  - Ensure sensors and ESP32 are powered correctly (3.3V recommended for ESP32 pins).

- **I2C Pins on ESP32**  
  - Default SDA and SCL pins for ESP32 are GPIO 21 and GPIO 22, respectively, used by the TSL2591 sensor.

---

## Should ThingSpeak Code Be Committed?

- **Yes**, commit your ESP32 source code that interacts with ThingSpeak.
- **No**, do **not** commit your WiFi passwords or API keys.
- Use `.gitignore` to exclude sensitive files containing keys.

---

## How to Use

1. Wire your sensors to ESP32 as described.
2. Replace placeholders for WiFi and ThingSpeak API keys in the code.
3. Upload the code to your ESP32 device.
4. Power on the device.
5. Monitor live sensor data on your ThingSpeak channel dashboard.

---

