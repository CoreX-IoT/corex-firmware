// MEMBUTUHKAN pustaka Arduino berikut:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library

#include <ESP8266WiFi.h>
#include <Dashboard.h>
#include <DHT.h>
#include "Connection.h"

#define DHTPIN 12                       // GPIO 12 (D6) untuk pin DHT.
#define DHTTYPE DHT11                   // DHT 11
//#define DHTTYPE DHT22                 // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21                 // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);
DashboardTimer timer;                   // Gunakan timer agar dapat mengeksekusi perintah setiap sekian milidetik tanpa blocking.

// Ubah nilai berikut sesuai jaringan Anda.
const char ssid[] = "......";
const char pass[] = "......";
const char server[] = "broker.emqx.io";
const String authProject = "......";
// Atur Client ID dengan nomor acak. Anda bisa menggantinya dengan Client ID apapun.
// String CleintId = "YourClientId";
const String clientId = "Nusabot-" + String(random(0xffff), HEX);

void publish() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Gagal membaca sensor DHT!"));
    return;
  }

  dashboard.publish(authProject, "kelembaban", String(h));     // Publish data kelembaban ke topic "authProject/kelembaban".
  dashboard.publish(authProject, "temperatur", String(t));     // Publish data temperatur ke topic "authProject/temperatur".
}

void setup() {
  dht.begin();
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  dashboard.begin(server, net);

  timer.setInterval(1000, publish);     // Lakukan publish setiap 1000 milidetik.

  setupDashboard(authProject, clientId);
}

void loop() {
  dashboard.loop();
  //delay(10);                          // Hapus komentar untuk memberikan delay 10 milidetik jika terjadi kendala pada stabilitas WiFi.
  timer.run();                          // Jalankan timer.

  // Periksa apakah perangkat masih terhubung.
  if (!dashboard.connected()) {
    setupDashboard(authProject, clientId);
  }

  //==LETAKAN KODE PROGRAM DISINI UNTUK DILAKUKAN PROSES==//
}