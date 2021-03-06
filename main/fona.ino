#include "Adafruit_FONA.h"

#define FONA_RST 10

Adafruit_FONA fona = Adafruit_FONA(FONA_RST); 

void setupFona() {
//  uncomment the following if you'll use a battery. make sure to remove the jumper connected on the NO BAT pins
//  pinMode(12, OUTPUT);
//  digitalWrite(12, LOW);
//  delay(2000);
//  digitalWrite(12, HIGH);
  Serial1.begin(4800);
  while(!fona.begin(Serial1));
  
  while(!fona.enableGPS(true));
  Serial.println("GPS on");

  fona.setGPRSNetworkSettings(F("http.globe.com.ph")); //change this if you'll use non-globe simcard
  fona.enableGPRS(true);

  Serial.println("Setup Fona done");

  deleteMessages();
}

uint8_t sendSMS(char *number, char *message) {
  if (!fona.sendSMS(number, message)) {
    return 0;
  } else {
    return 1;
  }
}

uint8_t getGPS(float *latitude, float *longitude, float *speed_kph, float *heading, float *altitude) {
  if(!fona.getGPS(latitude, longitude, speed_kph, heading, altitude)){
    return 0;
  } else {
    return 1;
  }
}

void deleteMessages() {
  Serial.println("Deleting all messages");

  int slot = 10;
  while(slot > 0) {  // delete all messages
    if(fona.deleteSMS(slot)) {
      Serial.println(F("Deleted!"));
    }
    slot--;
  }
}

String readSMS(char *number) {
  uint16_t smslen;
  char replybuffer[255];
  char sender[32];
  bool isAuthorized = true;
  
  if(fona.readSMS(1, replybuffer, 250, &smslen)) {  // pass in buffer and max len!
    Serial.println(F("Read SMS!"));
    
    if(fona.getSMSSender(1, sender, 31)) {
      Serial.println(String(sender));
      if(!String(sender).equals(String(number))) {
        Serial.println("Unauthorized text received");
        isAuthorized = false;
      } else {
        Serial.println("Authorized text received");
      }
    }
    
    if(fona.deleteSMS(1)) {
      Serial.println(F("Deleted!"));
    } else {
      Serial.println(F("Couldn't delete"));
    }

    if(isAuthorized) return String(replybuffer);

    return "unauthorized";
  }

  return "";
}
