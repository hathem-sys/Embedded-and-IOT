# Embedded and IoT

A collection of ESP32 projects built with the Arduino framework, covering sensing, alerts, web dashboards, cloud messaging, and long-range radio.

## Projects

| Sketch | What it does |
| --- | --- |
| `RTOS based temp Monitoring.ino` | Reads a DHT11 sensor using FreeRTOS tasks: one samples temperature and humidity, one prints readings over serial, one sounds a buzzer above 30 °C. |
| `Gyro Sensor based alarm .inoin Embedded system` | Reads an MPU6050 gyroscope and sounds a buzzer when rotation on any axis exceeds a threshold. The alarm stays on for about 1 second after motion stops. |
| `Web dashboard using localhost.ino` | Runs a web server on the ESP32 that serves a dashboard to control an LED and show live temperature, refreshed every 2 seconds. |
| `adafruit mqtt communication.ino` | Publishes DHT11 temperature and humidity to Adafruit IO feeds every 10 seconds, with a local buzzer alert above 30 °C. |
| `loracommunication.ino` | Two-way text messaging between ESP32 nodes over LoRa (433 MHz). Type in the Serial Monitor to send; received messages show RSSI and SNR. |
| `voice based control buzzer.ino` | Subscribes to an Adafruit IO `light` feed and switches a relay on or off from `ON`/`OFF` (or `1`/`0`) messages, so any service that writes to the feed (for example a voice assistant integration) can control it. |

## Hardware

- ESP32 development board
- DHT11 temperature and humidity sensor
- MPU6050 gyroscope and accelerometer
- Active buzzer
- LED
- Relay module (the sketch assumes active-LOW)
- LoRa module (SX127x, 433 MHz)

### Pin reference

| Component | Pin(s) |
| --- | --- |
| DHT11 data | GPIO 4 |
| Buzzer | GPIO 18 |
| LED (built-in) | GPIO 2 |
| Relay | GPIO 23 |
| MPU6050 | SDA 21, SCL 22 |
| LoRa | SCK 18, MISO 19, MOSI 23, SS 5, RST 14, DIO0 26 |

Some sketches reuse the same pins (for example GPIO 18 and 23 appear in both the LoRa and buzzer/relay sketches), so rewire if you combine them.

## Software requirements

- [Arduino IDE](https://www.arduino.cc/en/software) with the ESP32 board package installed
- Libraries (install from the Library Manager):
  - `DHT sensor library` (Adafruit)
  - `Adafruit MPU6050` and `Adafruit Unified Sensor`
  - `Adafruit IO Arduino` and its dependencies
  - `LoRa` (Sandeep Mistry)
- Built-in with the ESP32 core: `WiFi`, `WebServer`, `Wire`, `SPI`

## Getting started

1. Clone the repository:
   ```bash
   git clone https://github.com/hathem-sys/Embedded-and-IOT.git
   ```
2. Open the sketch you want in the Arduino IDE. Sketches are single files, so copy each into its own folder with a matching name if the IDE asks.
3. Select your ESP32 board and port under **Tools**.
4. For sketches that use Wi-Fi or Adafruit IO, fill in your own credentials (see below).
5. Upload, then open the Serial Monitor at **115200 baud**.

## Configuration

Sketches that connect to Wi-Fi or Adafruit IO need placeholders replaced with your own values:

```cpp
#define WIFI_SSID     "YOUR_WIFI_NAME"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
#define IO_USERNAME   "YOUR_ADAFRUIT_IO_USERNAME"
#define IO_KEY        "YOUR_ADAFRUIT_IO_KEY"
```

Adafruit IO feeds used: `temperature`, `humidity`, `light`.

> **Never commit real credentials.** Keep Wi-Fi passwords and API keys in a separate untracked header file (for example `secrets.h`, listed in `.gitignore`).

## Using the web dashboard

After upload, the Serial Monitor prints the ESP32's IP address. Open that address in a browser on the same network. The ESP32 serves three routes: `/` (the dashboard), `/led?state=ON|OFF`, and `/temperature`.

## Notes

- The DHT11 is accurate to roughly ±2 °C; the 30 °C alert threshold is defined at the top of each sketch and easy to change.
- LoRa range depends on antenna, environment, and regional regulations. Check the legal frequency band for your country before transmitting.
- Run the LoRa sketch on two boards to test two-way communication.

## License

No license specified yet. Consider adding one (for example MIT) if you want others to reuse this code.
