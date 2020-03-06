
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "ba52360f6a86424b941e7ac5169f6658";
char ssid[] = "redmi";
char pass[] = "smriti123";
#define REED_SWITCH 5 //D1
int doorClosed = 1;
int G=A0;
void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  Serial.println("ready");
  pinMode(REED_SWITCH,INPUT_PULLUP);
  pinMode(G,INPUT);
}
void loop()
{
  Blynk.run();
  convert();
  if ((digitalRead(REED_SWITCH) == HIGH) && (doorClosed == 1))
    {
      Serial.println("DOOR OPEN!!");
      while (get_http(String("DOOR_OPEN_")) != 0);
      Blynk.notify("DOOR IS OPEN");      
      doorClosed = 0;
    } 
    else if ((digitalRead(REED_SWITCH) == LOW) && (doorClosed == 0))
    {
      Serial.println("DOOR CLOSED!!");
      while (get_http(String("DOOR_CLOSED_")) != 0);      
      doorClosed = 1;
    }
    //G=analogRead(A0);
 }
int get_http(String state)
{
   HTTPClient http;
   int ret = 0;
   Serial.print("[HTTP] begin...\n");
   http.begin("http://maker.ifttt.com/trigger/door/with/key/fjHZ-ceUP_SGcB4gbeGo04pn9cLi6bsnJ5QMcWiLaCk"); //HTTP
   Serial.print("[HTTP] GET...\n");
    int httpCode = http.GET();
    if(httpCode > 0) {
    Serial.printf("[HTTP] GET code: %d\n", httpCode);
       if(httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);
      }
    } else {
        ret = -1;
        Serial.printf("[HTTP] GET failed, error: %s\n", http.errorToString(httpCode).c_str());
        delay(500); // wait for half sec before retry again
    }
    http.end();
    return ret;
}
void convert()
{
  int s=analogRead(G);
      Blynk.virtualWrite(V6, s);
      Serial.println(V6);
      if(s>700)
      { 
        Blynk.notify("GAS GAS GAS!!!");}
      }
}

