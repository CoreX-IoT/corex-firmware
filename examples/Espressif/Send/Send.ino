#include <CoreX.h>
#include "Connection.h"

// Ubah nilai auth_token dan device anda.
const char* AUTH_TOKEN = "..........";
const char* DEVICE_ID = "..........";

CoreXTimer timer;       // Gunakan timer agar dapat mengeksekusi perintah setiap sekian milidetik tanpa blocking.

// Ubah nilai berikut sesuai jaringan Anda.
const char ssid[] = "..........";
const char pass[] = "..........";

const char server[] = "nusabotid.cloud.shiftr.io";


void send() {
  corex.send("hello", "world");     // send ke topik "authproject/data/hello" dengan pesan/payload "world".
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  corex.begin(server, net);

  timer.setInterval(1000, send);     // Lakukan send setiap 1000 milidetik.

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