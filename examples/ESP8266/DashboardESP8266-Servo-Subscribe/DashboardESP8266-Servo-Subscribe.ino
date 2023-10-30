#include <ESP8266WiFi.h>
#include <Servo.h>
#include <Dashboard.h>
#include "Connection.h"

// Ubah nilai berikut sesuai jaringan Anda.
const char ssid[] = "......";
const char pass[] = "......";
const char server[] = "broker.emqx.io";
const String authProject = "......";
// Atur Client ID dengan nomor acak. Anda bisa menggantinya dengan Client ID apapun.
// String CleintId = "YourClientId";
const String clientId = "Nusabot-" + String(random(0xffff), HEX);

Servo myservo;

void subscribe(String &topic, String &message) {
  if(topic == authProject + "/data/servo"){
    myservo.write(message.toInt());
  }
  Serial.println("data masuk: \n" + topic + " - " + message);
}

void setup() {
  myservo.attach(12);                    //  Inisialisasi servo pada GPIO12 (D6)
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  dashboard.begin(server, net);

  dashboard.onMessage(subscribe);       // Lakukan subscribe pada fungsi subscribe().

  setupDashboard(authProject, clientId);
}

void loop() {
  dashboard.loop();
  //delay(10);                          // Hapus komentar untuk memberikan delay 10 milidetik jika terjadi kendala pada stabilitas WiFi.

  // Periksa apakah perangkat masih terhubung.
  if (!dashboard.connected()) {
    setupDashboard(authProject, clientId);
  }

  //==LETAKAN KODE PROGRAM DISINI UNTUK DILAKUKAN PROSES==//
}