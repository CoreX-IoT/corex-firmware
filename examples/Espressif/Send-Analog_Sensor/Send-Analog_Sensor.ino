#include <CoreX.h>
#include "Connection.h"

const char* AUTH_TOKEN = "..........";
const char* DEVICE_ID = "..........";

#define SENSOR_PIN 14  // GPIO D5 sesuaikan pin yang ingin Anda gunakan 
CoreXTimer timer;     // Gunakan timer agar dapat mengeksekusi perintah setiap sekian milidetik tanpa blocking.

// Ubah nilai berikut sesuai jaringan Anda.
const char ssid[] = "..........";
const char pass[] = "..........";

const char server[] = "nusabotid.cloud.shiftr.io";

void send() {
  int sensorValue = analogRead(SENSOR_PIN);
  corex.send("sensor", String(sensorValue).c_str());
  }

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  corex.begin(server, net);

  timer.setInterval(1000, send);     // Lakukan publish setiap 1000 milidetik.

  setupCorex();
}

void loop() {
  corex.loop();
  //delay(10);                          // Hapus komentar untuk memberikan delay 10 milidetik jika terjadi kendala pada stabilitas WiFi.
  timer.run();                          // Jalankan timer.

  // Periksa apakah perangkat masih terhubung.
  if (!corex.connected()) {
    setupCorex();
  }

  //==LETAKAN KODE PROGRAM DISINI UNTUK DILAKUKAN PROSES==//
}