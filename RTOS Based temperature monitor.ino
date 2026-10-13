#include <DHT.h>
#define DHT_PIN 4
#define BUZZER_PIN 18
#define TEMP_LIMIT 30

DHT dht(DHT_PIN, DHT11);
float temp = 0;
float hum = 0;
void senseTask(void *p) {
  while (1) {
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    if (!isnan(t) && !isnan(h)) {
      temp = t;
      hum = h;
    }
    delay(1000);
  }
}
void publishTask(void *p) {   
  while (1) {
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print(" C  Humidity: ");
    Serial.print(hum);
    Serial.println(" %");
    delay(500);
  }
}
void alertTask(void *p) {
  while (1) {
    if (temp > TEMP_LIMIT) {
      digitalWrite(BUZZER_PIN, HIGH);
    } else {
      digitalWrite(BUZZER_PIN, LOW);
    }
    delay(200);
  }
}
void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(BUZZER_PIN, OUTPUT);
  xTaskCreate(senseTask, "Sense", 2048, NULL, 3, NULL);
  xTaskCreate(publishTask, "Publish", 2048, NULL, 2, NULL);
  xTaskCreate(alertTask, "Alert", 2048, NULL, 1, NULL);
}
void loop() {
  delay(1000);
}
