# Dashboard untuk Arduino IDE

Pustaka ini digunakan Arduino IDE untuk menghubungkan perangkat ke platform Dashboard menggunakan protokol MQTT berdasarkan [arduino-mqtt](https://github.com/256dpi/arduino-mqtt/)

Pustaka ini mengimplementasikan "**L**ight **W**eight **MQTT**" [lwmqtt](https://github.com/256dpi/lwmqtt) MQTT 3.1.1 dimana pustaka ini dioptimalkan untuk digunakan pada perangkat tertanam (embedded device).

Unduh versi terbaru dari [rilis](https://github.com/nusabot-iot/dashboard-arduino/releases) atau juga lebih baik jika unduh dan install melalui Library Manager pada Arduino IDE. Cari dengan nama **Dashboard IoT**.

## Contoh

Pustaka menyertakan contoh kode program. Lihat Berkas -> Contoh -> Dashboard (File -> Example -> Dashboard) pada Arduino IDE.

Contoh berikut menggunakan ESP32 Development Board dan terhubung dengan broker EMQX:
```c++
#include <WiFi.h>
#include <Dashboard.h>
#include "Connection.h"

WiFiClient net;
Dashboard dashboard;
DashboardTimer timer;                   // Gunakan timer agar dapat mengeksekusi perintah setiap sekian milidetik tanpa blocking.

// Ubah nilai berikut sesuai jaringan Anda.
const char ssid[] = "ssid";
const char pass[] = "pass";
const char server[] = "broker.emqx.io";
const String authProject = "YOUR_DASHBOARD_AUTH_PROJECT";
// Atur Client ID dengan nomor acak. Anda bisa menggantinya dengan Client ID apapun.
// String CleintId = "YourClientId";
const String clientId = "Nusabot-" + String(random(0xffff), HEX);

void setupDashboard() {
  Serial.println("Menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nMenghubungkan ke server/broker");
  while (!dashboard.connect(clientId.c_str())) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nTerhubung ke server!");

  dashboard.subscribe(authProject+"/data/#");
}

void subscribe(String &topic, String &message) {
  Serial.println("data masuk: \n" + topic + " - " + message);
}

void publish() {
  dashboard.publish(authProject, "data/hello", "world");     // Publish ke topik "authproject/data/hello" dengan pesan "world".
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  dashboard.begin(server, net);

  dashboard.onMessage(subscribe);       // Lakukan subscribe pada fungsi subscribe().
  timer.setInterval(1000, publish);     // Lakukan publish setiap 1000 milidetik.

  setupDashboard();
}

void loop() {
  dashboard.loop();
  timer.run();                          // Jalankan timer.

  // Periksa apakah perangkat masih terhubung.
  if (!dashboard.connected()) {
    setupDashboard();
  }
}
```

## Perangkat Yang Didukung

Pustaka menggunakan API Arduino Ethernet Client untuk berinteraksi dengan perangkat keras jaringan. Artinya pustaka ini dapat digunakan pada perangkat keras apapun yang memiliki interaktifitas API tersebut termasuk papan dan shield seperti:

 - ESP8266 Development Board
 - ESP32 Development Board
 - Arduino Ethernet
 - Arduino Ethernet Shield
 - Arduino YUN & YUN-Shield
 - Arduino WiFi Shield
 - Arduino/Genuino WiFi101 Shield
 - Arduino MKR GSM 1400
 - Intel Galileo/Edison

## Lisensi

Kode program dilisensikan dibawah GNU GENERAL PUBLIC LICENSE
