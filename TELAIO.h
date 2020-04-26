#include <ESP8266WiFi.h>
#include <time.h>
#include <LiquidCrystal_I2C.h>  // display library
#include <Wire.h>               // I2C library


#define SECRET_SSID "..."        // SSID
#define SECRET_PASS "..."              // WiFi password


#define DISPLAY_CHARS 16     // number of characters on a line
#define DISPLAY_LINES 2      // number of display lines
#define DISPLAY_ADDR 0x27    // display address on I2C bus
LiquidCrystal_I2C lcd(DISPLAY_ADDR, DISPLAY_CHARS, DISPLAY_LINES);

  
void checkwifi(){
  char ssid[] = SECRET_SSID;   // your network SSID (name) 
  char pass[] = SECRET_PASS;   // your network password
  if(WiFi.status() != WL_CONNECTED){
      Serial.print("Connecting to SSID: ");
      Serial.println(SECRET_SSID);
      //WiFi.config(ip, dns, gateway, subnet);   // by default network is configured using DHCP
      WiFi.begin(ssid, pass);
      while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
      } 
      Serial.println("\nWi-Fi Connected!"); 
    }
}

void checklcd(){
  Serial.println("\n\nCheck LCD connection...");
  Wire.begin();
  Wire.beginTransmission(DISPLAY_ADDR);
  byte error = Wire.endTransmission();

  if (error == 0) {
    Serial.println("LCD found.");
    lcd.begin(DISPLAY_CHARS, 2);   // initialize the lcd

  } else {
    Serial.print("LCD not found. Error ");
    Serial.println(error);
    Serial.println("Check connections and configuration. Reset to try again!");
    while (true);
  }
  Serial.println("\n\nSetup completed.\n\n");
  lcd.setBacklight(255);
}

void settime(){
  configTime(2 * 3600, 0, "pool.ntp.org", "time.nist.gov");
  Serial.println("\nWaiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
}

void initSetup(){
  WiFiClient  client;
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  checkwifi();
  checklcd();
  settime();
}
