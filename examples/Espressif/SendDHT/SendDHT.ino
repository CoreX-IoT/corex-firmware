#include <CoreX.h>
#include <DHT.h>
#include "Connection.h"

#define DHTPIN 12                       // GPIO 12 untuk pin DHT.
#define DHTTYPE DHT11                   // DHT 11
//#define DHTTYPE DHT22                 // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21                 // DHT 21 (AM2301)

// Ubah nilai auth_token dan device anda.
const char* AUTH_TOKEN = "..........";
const char* DEVICE_ID = "..........";

DHT dht(DHTPIN, DHTTYPE);
CoreXTimer timer;                   // Gunakan timer agar dapat mengeksekusi perintah setiap sekian milidetik tanpa blocking.

// Ubah nilai berikut sesuai jaringan Anda.
const char ssid[] = "..........";
const char pass[] = "..........";

void send() {
  float humid = dht.readHumidity();
  float temp = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Gagal membaca sensor DHT!"));
    return;
  }

  corex.send("kelembaban", humid);     // send data kelembaban ke topic "kelembaban".
  corex.send("temperatur", temp);     // send data temperatur ke topic "temperatur".
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  corex.begin(net);
  dht.begin();

  timer.setInterval(3000, send);     // Lakukan send setiap 3000 milidetik.

  setupCorex();
}

void loop() {
  timer.run();                          // Jalankan timer.
  //delay(10);                          // Hapus komentar untuk memberikan delay 10 milidetik jika terjadi kendala pada stabilitas WiFi.

  // Periksa apakah perangkat masih terhubung.
  if (!corex.connected()) {
    setupCorex();
  }

  //==LETAKAN KODE PROGRAM DISINI UNTUK DILAKUKAN PROSES==//
}