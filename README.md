# CoreX C++ Library

CoreX adalah platform IoT yang memungkinkan kamu mengirim dan menerima data antar perangkat. Kamu dapat membuat desain web kamu sendiri menggunakan berbagai widget untuk menampilkan data dari sensor ataupun mengendalikan aktuator.

- Dengan CoreX kamu bisa menghubungkan berbagai macam model perangkat IoT (termasuk ESP8266, ESP32, NodeMCU, semua board Arduino, Raspberry Pi, dll).
- Dengan CoreX kamu bisa membuat aplikasi web sendiri tanpa pemrograman sama sekali untuk menampilkan data seperti sensor dan mengendalikan aktuator.
- Dengan CoreX kamu bisa mengintegrasikan proyek yang sudah ada melalui API yang sudah disediakan.

Unduh versi terbaru dari [rilis](https://github.com/CoreX-IoT/corex-firmware/releases) atau juga lebih baik jika unduh dan install melalui Library Manager pada Arduino IDE. Cari dengan nama **CoreX IoT**.

## Contoh

Pustaka menyertakan contoh kode program. Lihat Berkas -> Contoh -> CoreX (File -> Example -> CoreX) pada Arduino IDE.

Contoh berikut menggunakan ESP32/ESP8266 Development Board:
```c++
#include <CoreX.h>

// Ubah nilai auth_token dan device Anda.
const char* AUTH_TOKEN = "..........";
const char* DEVICE_ID = "..........";

WiFiClient net;
CoreX corex;
CoreXTimer timer;                   // Gunakan timer agar dapat mengeksekusi perintah setiap sekian milidetik tanpa blocking.

// Ubah nilai berikut sesuai jaringan Anda.
const char ssid[] = "..........";
const char pass[] = "..........";

void receive(String &bucket, String &data) {    // Terima data
  Serial.println("data masuk: \n" + bucket + " - " + data);
}

void send() {
  corex.send("hello", "world");     // Kirim data "world" ke bucket "hello"
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
 - Seluruh perangkat yang mendukung API Arduino Ethernet Client

## Lisensi

Kode program dilisensikan dibawah GNU GENERAL PUBLIC LICENSE
