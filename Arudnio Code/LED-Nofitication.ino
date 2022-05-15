//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
// Set these to run example.
//Fire Base Host Will be the link in Realtime database without the http
#define FIREBASE_HOST "thunderbird-7ee2e-default-rtdb.asia-southeast1.firebasedatabase.app"
//Fire Base AUTH will be in Project Settings Service Account in Database Secrets
#define FIREBASE_AUTH "yVroB43eV25v4HuTa9DG8fPVpqGVpmGGkas9lsHM"
// Set Wifi Name and Password
#define WIFI_SSID "WIFI Name"
#define WIFI_PASSWORD "Wifi Password"

void setup() {

  Serial.begin(115200);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  //Lines to Check if It Working
  //Serial.println();
  //Serial.print("connected: ");

  Serial.println(WiFi.localIP());
   pinMode(D1, OUTPUT);
   pinMode(D2, OUTPUT);
   pinMode(D7, OUTPUT);
   pinMode(D8, OUTPUT);
   pinMode(D5, OUTPUT);
   pinMode(D6, OUTPUT);
  
  //Connect to Firebase to check if any Changes
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

//Because my LED will have to differentiate against 3 people
String person1 = "-";
String person2 = "-";
String person3 = "-";


// Delays every 1 second, to check if firebase has changed from - for the three to anything else and if there is anything else high the persons leds 
void loop() {

  
  if(person1 == "-"){
  digitalWrite(D1, LOW);     
  digitalWrite(D2, LOW);

   }
     if(person3 == "-"){
    digitalWrite(D7, LOW);     
  digitalWrite(D8, LOW);
 
   }
     if(person2 == "-"){
  digitalWrite(D5, LOW);     
  digitalWrite(D6, LOW);
   }



  
  if(person1 != "-"){
  digitalWrite(D1, HIGH);     
  digitalWrite(D2, HIGH);
   }
  if(person3 != "-"){
  digitalWrite(D7, HIGH);     
  digitalWrite(D8, HIGH);
   }
     if(person2 != "-"){     
  digitalWrite(D5, HIGH);     
  digitalWrite(D6, HIGH);
   } 
  
  
   person1 = Firebase.getString("person1");
   delay(1000);
   person2 = Firebase.getString("person2");
     delay(1000);
 person3 = Firebase.getString("person3");
 delay(1000);
 
}
