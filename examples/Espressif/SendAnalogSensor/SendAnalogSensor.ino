#include <CoreX.h>
#include "Connection.h"

// Ubah nilai auth_token dan device anda.
const char* AUTH_TOKEN = "..........";
const char* DEVICE_ID = "..........";

#define SENSOR_PIN A0
CoreXTimer timer;     // Gunakan timer agar dapat mengeksekusi perintah setiap sekian milidetik tanpa blocking.

// Ubah nilai berikut sesuai jaringan Anda.
const char ssid[] = "..........";
const char pass[] = "..........";

void send() {
  int sensorValue = analogRead(SENSOR_PIN);
  corex.send("sensor", sensorValue);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  corex.begin(net);

  timer.setInterval(1000, send);     // Lakukan send setiap 1000 milidetik.

  setupCorex();
}

void loop() {
  timer.run();                          // Jalankan timer.
  //delay(10);                          // Hapus komentar untuk memberikan delay 10 milidetik jika terjadi kendala pada stabilitas WiFi.

  // Periksa apakah perangkat masih terhubung.
  if (!corex.connected()) {
    setupCorex();
  }
}