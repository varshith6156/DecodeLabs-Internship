#define BLYNK_TEMPLATE_ID "TMPL3UmYovt23"
#define BLYNK_TEMPLATE_NAME "smart irrigation"
#define BLYNK_AUTH_TOKEN "8oOAxjUfOCGBrxj3TUzcwRacBQWGOUrQ"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// -------------------- WiFi --------------------
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

// -------------------- Pins --------------------
#define SOIL_PIN 34
#define RELAY_PIN 26
#define LED_PIN 2

// -------------------- OLED --------------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

// -------------------- Moisture limits --------------------
const int ON_THRESHOLD = 30;
const int OFF_THRESHOLD = 45;

bool pumpState = false;

// -------------------- Blynk --------------------
BlynkTimer timer;

// V1 = manual pump switch
BLYNK_WRITE(V1)
{
  int value = param.asInt();

  pumpState = (value == 1);

  digitalWrite(RELAY_PIN, pumpState ? HIGH : LOW);
  digitalWrite(LED_PIN, pumpState ? HIGH : LOW);

  Serial.print("Manual Pump: ");
  Serial.println(pumpState ? "ON" : "OFF");
}

// -------------------- Soil reading --------------------
void readSoilMoisture()
{
  int rawValue = analogRead(SOIL_PIN);

  // ESP32 ADC: 0 = wet, 4095 = dry
  int moisture = map(rawValue, 4095, 0, 0, 100);

  moisture = constrain(moisture, 0, 100);

  // Automatic pump control
  if (!pumpState && moisture < ON_THRESHOLD)
  {
    pumpState = true;
  }
  else if (pumpState && moisture > OFF_THRESHOLD)
  {
    pumpState = false;
  }

  // Relay + LED
  digitalWrite(RELAY_PIN, pumpState ? HIGH : LOW);
  digitalWrite(LED_PIN, pumpState ? HIGH : LOW);

  // Send values to Blynk
  Blynk.virtualWrite(V0, rawValue);
  Blynk.virtualWrite(V2, moisture);
  Blynk.virtualWrite(V1, pumpState ? 1 : 0);
  // Serial monitor
  Serial.print("Soil raw value: ");
  Serial.println(rawValue);

  Serial.print("Soil moisture: ");
  Serial.print(moisture);
  Serial.println("%");

  Serial.print("Pump: ");
  Serial.println(pumpState ? "ON" : "OFF");

  // ---------------- OLED ----------------
  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("SMART IRRIGATION");

  display.setCursor(0, 15);
  display.print("Raw: ");
  display.println(rawValue);

  display.setCursor(0, 28);
  display.print("Moisture: ");
  display.print(moisture);
  display.println("%");

  display.setCursor(0, 41);
  display.print("Pump: ");
  display.println(pumpState ? "ON" : "OFF");

  display.setCursor(0, 54);
  display.print("Blynk: ");
  display.println(Blynk.connected() ? "ONLINE" : "OFFLINE");

  display.display();
}

// -------------------- SETUP --------------------
void setup()
{
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  analogReadResolution(12);

  // OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("OLED Failed!");
    while (1)
    {
      delay(100);
    }
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  display.setCursor(0, 0);
  display.println("SMART IRRIGATION");

  display.setCursor(0, 18);
  display.println("Connecting WiFi...");

  display.display();

  // WiFi
  WiFi.begin(ssid, pass);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected!");

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Blynk
  display.clearDisplay();

  display.setCursor(0, 0);
  display.println("SMART IRRIGATION");

  display.setCursor(0, 18);
  display.println("Connecting Blynk...");

  display.display();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.println("Blynk connected!");

  // First reading
  readSoilMoisture();

  // Read every 2 seconds
  timer.setInterval(2000L, readSoilMoisture);
}

// -------------------- LOOP --------------------
void loop()
{
  Blynk.run();
  timer.run();
}
