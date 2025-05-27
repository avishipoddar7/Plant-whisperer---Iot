#include <WiFi.h>              //Includes the WiFi library to enable ESP32 to connect to a wireless network.
#include <HTTPClient.h>        //Allows HTTP requests like GET and POST for sending data online.
#include <Wire.h>              //Used for I2C communication between ESP32 and sensors.
#include <Adafruit_Sensor.h>   //Base class for all Adafruit sensor libraries.
#include <Adafruit_TSL2591.h>  //Library for the TSL2591 light sensor.
#include <DHT.h>               //Includes support for the DHT temperature and humidity sensor.

// Temperature and humidity sensor pinmode and intiallization
#define DHTPIN 4           //Defines the GPIO pin 4 as the data pin for the DHT22 sensor.
#define DHTTYPE DHT22      //Specifies the sensor model being used as DHT 22 (AM2302).
DHT dht(DHTPIN, DHTTYPE);  //Initializes the DHT sensor with the defined pin and type.

// Light intensity sensor intiallization
Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);  //pinmode is predefined in the library

// Soil moisture sensor
const int soil_pin = 34;  //Defines GPIO 34 (pin number 34) for reading analog soil moisture.


// Requirements for  wifi connection
const char* ssid = "network name ";                              //Stores your WiFi SSID (network name).
const char* password = "network password";                      //Stores the WiFi password.
const char* server = "https://api.thingspeak.com/update";  //URL to send sensor data to ThingSpeak.(domain only)
String apiKey = "your API key";                        //Your ThingSpeak write API key for uploading data.

void setup()  //Setup function runs once at boot to initialize everything.
{
  Serial.begin(9600);                     // Starts serial communication at 9600 baud for debugging.
  WiFi.disconnect(true);                  //Disconnects and resets any previous WiFi connections.
  delay(3000);                            //Waits 3 seconds (3000 milli seconds) before starting WiFi connection.
  WiFi.begin(ssid, password);             //Starts connecting to the specified WiFi network/
  Serial.println("connecting to wifi ");  //Prints connection status message.
  while (WiFi.status() != WL_CONNECTED)
    ;  //Keeps looping until the ESP32 is connected to WiFi.
  {
    delay(500);         //Tries connecting to wifi in the time interval of 500 milli seconds.
    Serial.print(".");  //Prints dots and connection status during WiFi attempt.
    Serial.print(WiFi.status());
    Serial.println("connected successfully");  //Confirmation that WiFi is connected.
  }

  pinMode(soil_pin, INPUT);  //Sets soil sensor pin as input for analog readings.


  if (!tsl.begin()) {                                      //Tries to start the light sensor—if it fails, show error.
    Serial.println("❌ TSL2591 not found. Check wiring.");  //If sensor isn’t found, print error and halt the system.
    while (1)
      ;
  }

  Serial.println("✅ TSL2591 sensor initialized.");  //Confirms light sensor is ready.

  // Optional: Set gain and integration time
  tsl.setGain(TSL2591_GAIN_MED);                 // Sets medium gain level for light sensitivity.
  tsl.setTiming(TSL2591_INTEGRATIONTIME_100MS);  // Sets the measurement time of the light sensor to 100 ms, it is good general value.

  dht.begin();  //Starts the DHT22 sensor.
}
void loop()  //Main code that runs repeatedly.
{
  int soil_value = analogRead(soil_pin);  //Reads raw soil moisture data from analog pin.
  Serial.println("Reading soil value");   //Prints soil moisture value to the Serial Monitor.
  Serial.println(soil_value);
  Serial.println("Reading light intensity value");  //Prints that it’s about to read light intensity.
  sensors_event_t event;
  tsl.getEvent(&event);  //Grabs a new light reading from the TSL2591 sensor.

  if (event.light) {
    Serial.print("Light Level: ");
    Serial.print(event.light);
    Serial.println(" lux");  //if the light data is valid, update light_intensity and print it.
  } else {
    Serial.println("⚠ Sensor reading invalid or overflow");  //Handles sensor error or data overflow.
  }
  float temperature = dht.readTemperature();  //Reads current temperature from DHT22.
  float humidity = dht.readHumidity();        //Reads current humidity from DHT22.
  Serial.println("Temperature Level: ");
  Serial.print(temperature);  //Prints the temperature values.

  Serial.println("Humidity Level: ");
  Serial.print(humidity);  //Prints the humidity values.


  if (WiFi.status() == WL_CONNECTED)  //Checks if the device is still connected to WiFi.
  {
    HTTPClient http;  //Creates an HTTP client for making requests.
    //Starts the HTTP request and sends the GET request.
    String url = String(server) + "?api_key=" + apiKey + "&field1=" + String(temperature) + "&field2=" + String(soil_value) + "&field3=" + String(event.light) + "&field4=" + String(humidity);
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode == 200) {
      Serial.println("Data sent succesfully");
      Serial.println(httpCode);
    }  //Checks if data upload was successful or not and prints status.
    else {
      Serial.println("Couldn't send data");
    }
    http.end();  //Ends the HTTP connection.
  } else {
    Serial.println("WiFi was not connected");  //If WiFi failed, print a warning.
  }
}
