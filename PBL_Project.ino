
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3B-5X3vYD"
#define BLYNK_TEMPLATE_NAME "Home Automatioon"
#define BLYNK_AUTH_TOKEN "62mDaEvW-AFF5Y1jm669QJUTUs5oZv-H"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
//#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "cdot-L";
char pass[] = "kartik1409";

//DHT dht(D4, DHT11); //(sensor pin,sensor type)
BlynkTimer timer;
bool pirbutton = 0;

#define Buzzer D6
#define MQ2 A0
#define flame D2

BLYNK_WRITE(V0) {
  pirbutton = param.asInt();
}

void setup() {
  
  Serial.begin(9600);
  pinMode(Buzzer, OUTPUT);
  pinMode(flame, INPUT);

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100L, gassensor);
  
  timer.setInterval(100L, flamesensor);
  
}

void gassensor() {
  int value = analogRead(MQ2);
  
  value = map(value, 0, 1024, 0, 100);
  Serial.println(value);
  if (value <= 16) {
    digitalWrite(Buzzer, LOW);
  } else if (value > 16) {
    Serial.println("gas leak detected");
    Blynk.logEvent("gas_leak", "Warning! Gas leak has been detected");
    digitalWrite(Buzzer, HIGH);
  }
  Blynk.virtualWrite(V1, value);
  
}
void flamesensor() {
  bool value = digitalRead(flame );
  if (value == 1) {
    digitalWrite(Buzzer, HIGH);
    Serial.println("Flame detected");
    Blynk.logEvent("fire_alert", "Warning! Fire was detected");
  } else {
    Serial.println("No flame detected");
    digitalWrite(Buzzer, LOW);
  }
}


void loop() {

  Blynk.run();
  timer.run();
}