#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "SmartBin"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <HTTPClient.h>

char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";

#define TRIG_PIN 5
#define ECHO_PIN 18
String binId = "BIN_001";

const char* serverURL = "http://your-server-ip:5000/api/bins";

BlynkTimer timer;

float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2;
  return distance;
}

void sendData() {
  float distance = getDistance(); // in cm
  float fillLevel = 100 - (distance / 30.0 * 100); // assuming bin height = 30cm
  fillLevel = constrain(fillLevel, 0, 100);

  Serial.print("Fill Level: ");
  Serial.println(fillLevel);

  Blynk.virtualWrite(V0, fillLevel); // send to Blynk dashboard

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");

    String jsonData = "{\"binId\":\"" + binId + "\",\"fillLevel\":" + String(fillLevel, 2) + ",\"weight\":0,\"timestamp\":\"" + String(millis()) + "\"}";
    int httpResponseCode = http.POST(jsonData);
    Serial.print("POST Response Code: ");
    Serial.println(httpResponseCode);
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(10000L, sendData); // every 10 seconds
}

void loop() {
  Blynk.run();
  timer.run();
}
