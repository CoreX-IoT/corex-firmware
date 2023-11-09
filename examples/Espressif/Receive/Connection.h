WiFiClient net;
CoreX corex;

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