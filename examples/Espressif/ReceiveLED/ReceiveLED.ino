#include <CoreX.h>
#include "Connection.h"

// Ubah nilai auth_token dan device Anda
const char* AUTH_TOKEN = "..........";
const char* DEVICE_ID = "..........";

// Ubah nilai berikut sesuai jaringan Anda
const char ssid[] = "......";
const char pass[] = "......";

void receive(String &bucket, String &data) {
  if(bucket == "led"){
    digitalWrite(BUILTIN_LED, data.toInt());
  
    if(data == "0"){
      Serial.println("LED ON");
    } else {
      Serial.println("LED OFF");
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  corex.begin(net);

  corex.onMessage(receive);       // Lakukan receive pada fungsi receive().

  setupCoreX();
}

void loop() {
  corex.loop();
  //delay(10);                          // Hapus komentar untuk memberikan delay 10 milidetik jika terjadi kendala pada stabilitas WiFi.

  // Periksa apakah perangkat masih terhubung.
  if (!corex.connected()) {
    setupCoreX();
  }

  //==LETAKAN KODE PROGRAM DISINI UNTUK DILAKUKAN PROSES==//
}