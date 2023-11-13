#include <CoreX.h>
#include "Connection.h"
#include <Servo.h>

const char* AUTH_TOKEN = "..........";
const char* DEVICE_ID = "..........";

// Ubah nilai berikut sesuai jaringan Anda.
const char ssid[] = "..........";
const char pass[] = "..........";

const int servoPin = 12;
Servo servo;  //Deklarasi  servo global

void receive(String &topic, String &message) {
  if (topic == "servo") {
    servo.write(message.toInt());
  }
}

void setup() {
  Serial.begin(115200);
  servo.attach(servoPin, 500, 2400);
  WiFi.begin(ssid, pass);
  corex.begin(server, net);

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
