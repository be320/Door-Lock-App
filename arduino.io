

#include "ESP8266WiFi.h"
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "xxxxxx.firebaseio.com"
#define FIREBASE_AUTH "mssjdbajdbaldnkklajdjlajd"
#define WIFI_SSID "msalmfs"
#define WIFI_PASSWORD "12345678"



void setup() {
  Serial.begin(115200);
 pinMode(LED_BUILTIN, OUTPUT);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
   digitalWrite(LED_BUILTIN,HIGH);
     delay(1000);
}

int n = 0;

void loop() {
  int response = Firebase.getInt("/door/lock");
  Serial.println(response);

  if(response == 0)
  {
    digitalWrite(LED_BUILTIN,LOW);
    delay(1000);
    }
  else{
    digitalWrite(LED_BUILTIN,HIGH);
     delay(4000);
     Firebase.setInt("/door/lock",0);
    }
  
  delay(1000);


}
