#include <ESP8266WiFi.h>
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

void subscribe(String &topic, String &message) {
  Serial.println("data masuk: \n" + topic + " - " + message);

  if(topic == authProject + "/data/led"){
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