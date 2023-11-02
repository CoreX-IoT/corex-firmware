#include <ESP8266WiFi.h>
#include <Dashboard.h>
#include "Connection.h"

#define DEVICE_ID "......."

DashboardTimer timer;                   // Gunakan timer agar dapat mengeksekusi perintah setiap sekian milidetik tanpa blocking.

// Ubah nilai berikut sesuai jaringan Anda.
const char ssid[] = "......";
const char pass[] = "......";
const char server[] = "broker.emqx.io";
const String authProject = "......";
// Atur Client ID dengan nomor acak. Anda bisa menggantinya dengan Client ID apapun.
// String CleintId = "YourClientId";
// const String clientId = "Nusabot-" + String(random(0xffff), HEX);

void subscribe(String &topic, String &message) {
  Serial.println("data masuk: \n" + topic + " - " + message);
}

void publish() {
  dashboard.publish(authProject, "data/hello", "world");     // Publish ke topik "authproject/data/hello" dengan pesan/payload "world".
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  dashboard.begin(server, net);

  dashboard.onMessage(subscribe);       // Lakukan subscribe pada fungsi subscribe().
  timer.setInterval(1000, publish);     // Lakukan publish setiap 1000 milidetik.

  setupDashboard(authProject, DEVICE_ID);
}

void loop() {
  dashboard.loop();
  //delay(10);                          // Hapus komentar untuk memberikan delay 10 milidetik jika terjadi kendala pada stabilitas WiFi.
  timer.run();                          // Jalankan timer.

  // Periksa apakah perangkat masih terhubung.
  if (!dashboard.connected()) {
    setupDashboard(authProject, DEVICE_ID);
  }

  //==LETAKAN KODE PROGRAM DISINI UNTUK DILAKUKAN PROSES==//
}