#include <CoreX.h>
#include "Connection.h"

// Ubah nilai auth_token dan device Anda.
const char* AUTH_TOKEN = "..........";
const char* DEVICE_ID = "..........";

#define SENSOR_PIN A0
CoreXTimer timer;     // Gunakan timer agar dapat mengeksekusi perintah setiap sekian milidetik tanpa blocking.

// Ubah nilai berikut sesuai jaringan Anda.
const char ssid[] = "..........";
const char pass[] = "..........";

float cm;
float inches;

void send() {
  cm = 0.0344/2 * readDistance(3, 2); // Ubah nomor pin sesuai dengan nomor pin echo dan trig
	inches = (cm / 2.54);

  corex.send("distance-cm", cm);
  corex.send("distance-inch", inches);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  corex.begin(net);

  timer.setInterval(1000, send);     // Lakukan send setiap 1000 milidetik.

  setupCorex();
}

void loop() {
  timer.run();                          // Jalankan timer.
  //delay(10);                          // Hapus komentar untuk memberikan delay 10 milidetik jika terjadi kendala pada stabilitas WiFi.

  // Periksa apakah perangkat masih terhubung.
  if (!corex.connected()) {
    setupCorex();
  }
}

long readDistance(int triggerPin, int echoPin) {
	pinMode(triggerPin, OUTPUT);  // Hapus trigger
	digitalWrite(triggerPin, LOW);
	delayMicroseconds(2);
	// Atur pin trgger ke HIGH selama 10 microsecond
	digitalWrite(triggerPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(triggerPin, LOW);
	pinMode(echoPin, INPUT);
	// Baca pin echo dan mengembalikan gelombang suara yang merambat dalam satuan microsecond
	return pulseIn(echoPin, HIGH);
}