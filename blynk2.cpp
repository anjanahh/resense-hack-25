#include <HX711.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <HTTPClient.h>

#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "SmartBin"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";

#define TRIG_PIN 5
#define ECHO_PIN 18
#define DOUT 4
#define SCK 2

HX711 scale;

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
  return duration * 0.034 / 2;
}

void sendData() {
  float distance = getDistance();
  float fillLevel = 100 - (distance / 30.0 * 100);
  fillLevel = constrain(fillLevel, 0, 100);

  long rawWeight = scale.read_average(10);
  float weight = scale.get_units(10);
  if (weight < 0) weight = 0;

  Serial.printf("Fill: %.2f%% | Weight: %.2fg\n", fillLevel, weight);

  Blynk.virtualWrite(V0, fillLevel);
  Blynk.virtualWrite(V1, weight);

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");

    String jsonData = "{\"binId\":\"" + binId + "\",\"fillLevel\":" + String(fillLevel, 2) + ",\"weight\":" + String(weight, 2) + ",\"timestamp\":\"" + String(millis()) + "\"}";
    int code = http.POST(jsonData);
    Serial.print("POST Response Code: ");
    Serial.println(code);
    http.end();
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  scale.begin(DOUT, SCK);
  scale.set_scale();       // replace with your calibration factor
  scale.tare();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(10000L, sendData);
}

void loop() {
  Blynk.run();
  timer.run();
}
