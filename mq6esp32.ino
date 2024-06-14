#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wifi Choi";
const char* password = "tanpapassword";

const char* serverName = "http://192.168.1.89:8000/api/gas"; 

const int mq6Pin = 34; // Pin analog untuk sensor MQ6

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Terhubung ke WiFi dengan IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int gasValue = analogRead(mq6Pin);

  HTTPClient http;
  http.begin(serverName);
  http.addHeader("Content-Type", "application/json");
  String requestBody = "{\"gas_value\":" + String(gasValue) + "}";
  int httpResponseCode = http.POST(requestBody);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("Respons dari server: " + response);
  } else {
    Serial.println("Gagal mengirim data. Kode respons: " + String(httpResponseCode));
  }

  http.end();
  delay(5000); // Menunggu 5 detik sebelum mengambil data berikutnya
}