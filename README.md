# CoreX IoT Platform

Pustaka ini digunakan untuk menghubungkan perangkat ke platform CoreX menggunakan protokol MQTT berdasarkan [arduino-mqtt](https://github.com/256dpi/arduino-mqtt/)

Pustaka ini mengimplementasikan "**L**ight **W**eight **MQTT**" [lwmqtt](https://github.com/256dpi/lwmqtt) MQTT 3.1.1 dimana pustaka ini dioptimalkan untuk digunakan pada perangkat tertanam (embedded device).

Unduh versi terbaru dari [rilis](https://github.com/nusabot-iot/dashboard-arduino/releases) atau juga lebih baik jika unduh dan install melalui Library Manager pada Arduino IDE. Cari dengan nama **CoreX IoT**.

## Contoh

Pustaka menyertakan contoh kode program. Lihat Berkas -> Contoh -> CoreX (File -> Example -> CoreX) pada Arduino IDE.

Contoh berikut menggunakan ESP32/ESP8266 Development Board:
```c++
#include <CoreX.h>

// Ubah nilai auth_token dan device anda.
const char* AUTH_TOKEN = "..........";
const char* DEVICE_ID = "..........";

WiFiClient net;
CoreX corex;
CoreXTimer timer;                   // Gunakan timer agar dapat mengeksekusi perintah setiap sekian milidetik tanpa blocking.

// Ubah nilai berikut sesuai jaringan Anda.
const char ssid[] = "..........";
const char pass[] = "..........";


void setupCoreX() {
  Serial.println("CoreX IoT by Nusabot");
  Serial.println("Menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nTerhubung ke WiFi!");
  Serial.print("Menghubungkan ke server/broker");
  while (!corex.connect()) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nTerhubung ke server!");
}

void receive(String &topic, String &message) {
  Serial.println("data masuk: \n" + topic + " - " + message);
}

void send() {
  corex.send("hello", "world");     // send ke topik "hello" dengan pesan "world".
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  corex.begin(net);

  corex.onMessage(receive);       // Lakukan receive pada fungsi receive().
  timer.setInterval(1000, send);     // Lakukan send setiap 1000 milidetik.

  setupCoreX();
}

void loop() {
  corex.loop();
  timer.run();                          // Jalankan timer.
  //delay(10);                          // Hapus komentar untuk memberikan delay 10 milidetik jika terjadi kendala pada stabilitas WiFi.

  // Periksa apakah perangkat masih terhubung.
  if (!corex.connected()) {
    setupCoreX();
  }

  //==LETAKAN KODE PROGRAM DISINI UNTUK DILAKUKAN PROSES==//
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
