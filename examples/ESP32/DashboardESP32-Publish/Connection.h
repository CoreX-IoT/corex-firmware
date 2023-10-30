WiFiClient net;
Dashboard dashboard;

void setupDashboard(String authProject, String clientId) {
  Serial.println("Dashboard IoT by Nusabot");
  Serial.println("Menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nTerhubung ke WiFi!");
  Serial.print("Menghubungkan ke server/broker");
  while (!dashboard.connect(clientId.c_str())) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nTerhubung ke server!");
}