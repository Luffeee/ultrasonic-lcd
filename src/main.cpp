#include <Arduino.h>
#include <../headers/Ultrasonic.h>
#include <LiquidCrystal_I2C.h>
#include <string>
#include <WiFi.h>

const char *ssid = "Spider paul";
const char *password = "7500@@85";

UltrasonicSensor ultrasonic(19, 18);
LiquidCrystal_I2C lcd(0x27, 21, 22);
unsigned long pMLCD = 0;
int prevDistance = 0;

void updateLCD(unsigned long currentMillis, unsigned long previousMillis, unsigned long interval)
{
  long distance = ultrasonic.readDistance();
  if (currentMillis - previousMillis >= interval && distance != prevDistance)
  {
    prevDistance = distance;
    pMLCD = currentMillis;
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.print("Distance: ");
    lcd.print(distance);
    lcd.print(" cm");
    lcd.setCursor(0, 1);
    std::string text = ultrasonic.readDist();
    lcd.print(text.c_str());
  }
}

void setup()
{
  pinMode(15, OUTPUT);
  pinMode(4, OUTPUT);
  Serial.begin(115200);
  ultrasonic.initialize();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  delay(1000);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    lcd.clear();
    lcd.print("Initializing...");
    delay(1000);
  }
  lcd.clear();
  lcd.print("Connected 2 WiFi");
  delay(1000);
  lcd.clear();
  lcd.print(WiFi.localIP().toString());
  delay(2000);
}

void loop()
{
  updateLCD(millis(), pMLCD, 500);
}