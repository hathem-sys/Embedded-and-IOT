#include <SPI.h>
#include <LoRa.h>

#define LORA_SCK   18
#define LORA_MISO  19
#define LORA_MOSI  23
#define LORA_SS     5
#define LORA_RST   14
#define LORA_DIO0  26

#define LORA_FREQUENCY 433E6

#define DEVICE_NAME "ESP32-1"


void setup() {

  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("==============================");
  Serial.println(DEVICE_NAME);
  Serial.println("LoRa Live Communication");
  Serial.println("==============================");

  SPI.begin(
    LORA_SCK,
    LORA_MISO,
    LORA_MOSI,
    LORA_SS
  );

  LoRa.setPins(
    LORA_SS,
    LORA_RST,
    LORA_DIO0
  );

  if (!LoRa.begin(LORA_FREQUENCY)) {

    Serial.println("LoRa initialization FAILED!");

    while (1) {
      delay(1000);
    }
  }

  Serial.println("LoRa initialization SUCCESS!");
  Serial.println("Ready.");
  Serial.println();
  Serial.println("Type a message and press ENTER.");
  Serial.println();
}


void loop() {

  int packetSize = LoRa.parsePacket();

  if (packetSize) {

    String receivedMessage = "";

    while (LoRa.available()) {
      receivedMessage += (char)LoRa.read();
    }

    Serial.println();
    Serial.println("------------------------------");
    Serial.println("[RECEIVED]");
    Serial.println(receivedMessage);

    Serial.print("RSSI: ");
    Serial.print(LoRa.packetRssi());
    Serial.println(" dBm");

    Serial.print("SNR: ");
    Serial.print(LoRa.packetSnr());
    Serial.println(" dB");

    Serial.println("------------------------------");
    Serial.println("Type message:");
  }


  if (Serial.available()) {

    String message = Serial.readStringUntil('\n');

    message.trim();

    if (message.length() > 0) {

      Serial.print("[SENDING] ");
      Serial.println(message);

      LoRa.beginPacket();

      LoRa.print(DEVICE_NAME);

      LoRa.print(": ");

      LoRa.print(message);
      LoRa.endPacket();

      Serial.println("[SENT]");
      Serial.println();
    }
  }
}