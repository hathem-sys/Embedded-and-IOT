#include <WiFi.h>
#include "AdafruitIO_WiFi.h"
#include <DHT.h>

#define WIFI_SSID     "Xiaomi 14"
#define WIFI_PASSWORD "12121212"

#define IO_USERNAME "Abdulla322132"
#define IO_KEY      "aio_qTMx74yt6YO6VoSsq3hEFBfUz9vj"

#define DHT_PIN     4
#define BUZZER_PIN  18
#define DHT_TYPE    DHT11
#define TEMP_LIMIT  30

DHT dht(DHT_PIN, DHT_TYPE);

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY,
                   WIFI_SSID, WIFI_PASSWORD);

AdafruitIO_Feed *temperatureFeed =
    io.feed("temperature");

AdafruitIO_Feed *humidityFeed =
    io.feed("humidity");

float temp = 0.0;
float hum = 0.0;

unsigned long lastRead = 0;
unsigned long lastPublish = 0;
unsigned long lastStatus = 0;

bool sensorValid = false;
bool wasConnected = false;

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  dht.begin();

  Serial.println();
  Serial.println("ESP32 Temperature Monitoring");
  Serial.println("Connecting to Wi-Fi and Adafruit IO...");

  io.connect();
}

void loop() {
  io.run();

  if (millis() - lastStatus >= 3000) {
    lastStatus = millis();

    Serial.print("Wi-Fi: ");
    Serial.println(
      WiFi.status() == WL_CONNECTED ?
      "CONNECTED" : "DISCONNECTED"
    );

    Serial.print("Adafruit IO: ");
    Serial.println(
      io.status() == AIO_CONNECTED ?
      "CONNECTED" : "NOT CONNECTED"
    );
  }

  if (io.status() == AIO_CONNECTED && !wasConnected) {
    wasConnected = true;
    Serial.println("Adafruit IO connected successfully!");
  }

  if (io.status() != AIO_CONNECTED) {
    wasConnected = false;
  }

  if (millis() - lastRead >= 2000) {
    lastRead = millis();

    float t = dht.readTemperature();
    float h = dht.readHumidity();

    if (!isnan(t) && !isnan(h)) {
      temp = t;
      hum = h;
      sensorValid = true;

      Serial.print("Temperature: ");
      Serial.print(temp);
      Serial.print(" C | Humidity: ");
      Serial.print(hum);
      Serial.println(" %");

      digitalWrite(
        BUZZER_PIN,
        temp > TEMP_LIMIT ? HIGH : LOW
      );
    } else {
      sensorValid = false;
      digitalWrite(BUZZER_PIN, LOW);
      Serial.println("DHT11 reading failed!");
    }
  }

  if (io.status() == AIO_CONNECTED &&
      sensorValid &&
      millis() - lastPublish >= 10000) {

    lastPublish = millis();

    temperatureFeed->save(temp);
    humidityFeed->save(hum);

    Serial.println("Temperature and humidity sent to Adafruit IO.");
  }

  delay(1);
}
