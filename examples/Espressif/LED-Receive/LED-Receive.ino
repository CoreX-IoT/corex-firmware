#include <CoreX.h>
#include "Connection.h"

const char* AUTH_TOKEN = "..........";
const char* DEVICE_ID = "..........";

// Ubah nilai berikut sesuai jaringan Anda.
const char ssid[] = "......";
const char pass[] = "......";


void receive(String &topic, String &message) {
  Serial.println("data masuk: \n" + topic + " - " + message);

    if(topic == String(AUTH_TOKEN) + "/led"){
    digitalWrite(BUILTIN_LED, message.toInt());
    
      if(message == "0"){
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

  corex.onMessage(receive);       // Lakukan subscribe pada fungsi subscribe().

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