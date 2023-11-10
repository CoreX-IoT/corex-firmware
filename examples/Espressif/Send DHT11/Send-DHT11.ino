#include <CoreX.h>
#include <DHT.h>
#include "Connection.h"

#define DHTPIN 12                       // GPIO 12 (D6) untuk pin DHT.
// #define DHTTYPE DHT11                   // DHT 11
#define DHTTYPE DHT22                 // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21                 // DHT 21 (AM2301)

const char* AUTH_TOKEN = "..........";
const char* DEVICE_ID = "..........";

DHT dht(DHTPIN, DHTTYPE);
CoreXTimer timer;                   // Gunakan timer agar dapat mengeksekusi perintah setiap sekian milidetik tanpa blocking.

// Ubah nilai berikut sesuai jaringan Anda.
const char ssid[] = "..........";
const char pass[] = "..........";

const char server[] = "nusabotid.cloud.shiftr.io";

void send() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Gagal membaca sensor DHT!"));
    return;
  }

  corex.send("kelembaban", String(h).c_str());     // send data kelembaban ke topic "authProject/kelembaban".
  corex.send("temperatur", String(t).c_str());     // Publish data temperatur ke topic "authProject/temperatur".
}

void setup() {
  dht.begin();
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  corex.begin(server, net);

  timer.setInterval(3000, send);     // Lakukan publish setiap 1000 milidetik.

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