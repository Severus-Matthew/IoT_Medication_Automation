
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <DateTime.h>

#define TIME_MSG_LEN 11

#define TIME_HEADER 255

#define FIREBASE_HOST "experiment-1-98c23.firebaseio.com"
#define FIREBASE_AUTH "wiuzs4l5jlHavs18WfhPpIt6n8noP99WCDLrH8DJ"
#define WIFI_SSID "blackhole"
#define WIFI_PASSWORD "jhujhu1312"



FirebaseData firebaseData;

const long utcOffsetInSeconds = 19800;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);






void setup()
{

  

  Serial.begin(115200);
  timeClient.begin();
 Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();



 

  
  Firebase.reconnectWiFi(true);

  
  


  
  if(Firebase.getInt(firebaseData, "/Hour"))
  {
    //Success
    Serial.print("Get int data success, int = ");
    Serial.println(firebaseData.intData());
    
  }else{
    //Failed?, get the error reason from firebaseData

    Serial.print("Error in getInt, ");
    Serial.println(firebaseData.errorReason());
  }

  
  timeClient.update();

  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getDay());
  Serial.print(", ");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());

  pinMode(D7 , OUTPUT);
  pinMode(D5 , INPUT);
  pinMode(D6 , OUTPUT);
  
  int n;
  int m;
 

}

void loop()
{ 
  timeClient.update();
  int hrsC = timeClient.getHours();
  int mintsC = timeClient.getMinutes();

  
 if(Firebase.getInt(firebaseData, "/Hour") )
  {
    //Success
    Serial.print("Get int data success, int = ");
    Serial.println(firebaseData.intData());
    if(hrsC == firebaseData.intData()){
       if(Firebase.getInt(firebaseData, "/Min") )
  {
    //Success
    Serial.print("Get int data success, int = ");
    Serial.println(firebaseData.intData());
    if(mintsC == firebaseData.intData()){
      digitalWrite(D7 , HIGH);
      while(digitalRead(D5) != HIGH ){
        Serial.print("Low");
        digitalWrite(D6, LOW);
        delay(100);
      }
      if(digitalRead(D5)== HIGH){
        digitalWrite(D6, HIGH);
        Serial.print("high");
        delay(500);
        digitalWrite(D6, LOW);
      }
        
        
      
    }
    else{
      digitalWrite(D7 , LOW);
      Serial.println("abhi time nai hua h bsdk!!");
    }
  }else{
    //Failed?, get the error reason from firebaseData
    
    Serial.print("Error in getInt, ");
    Serial.println(firebaseData.errorReason());
  }
  
    
  
    }
    else{
    digitalWrite(D7 , LOW);
    }
  }else{
    //Failed?, get the error reason from firebaseData

    Serial.print("Error in getInt, ");
    Serial.println(firebaseData.errorReason());
  }
    
  }
 
