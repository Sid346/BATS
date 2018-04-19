#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <parse.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include "ArduinoJson.h"
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(D2,D3);


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
Event_TypeDef jsonparse[5];
String hash;

char attendance[120]={'0'};

uint8_t checkID(int *attendance);
const char* ssid  = "NITS";//";   //replace with your own SSID
const char* password = "abcde";    //replace with your own
const char* host = "lastiot.000webhostapp.com";  
uint8_t checkID(bool *attendance);
uint8_t setID(bool *attendance);
#define TFT_CS     D7
#define TFT_RST    D6  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to -1!
#define TFT_DC     D8

#define TFT_SCLK D0   // set these to be whatever pins you like!
#define TFT_MOSI D1   // set these to be whatever pins you like!
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
StaticJsonBuffer<200> jsonBuffer;
bool ServerConnect(void);
  IPAddress ip;
  int i;
  String identify;
void setup() 
{
Serial.begin(115200);
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  ip = WiFi.localIP();
Serial.println("");
Serial.println("WiFi connected");  
Serial.println("IP address: ");
Serial.println(ip);
finger.begin(57600);
tft.initR(INITR_BLACKTAB); 
tft.fillScreen(ST7735_BLACK);
pinMode(D5,INPUT_PULLUP);
tft.drawRect(0,64 ,128, 40, ST7735_GREEN);
tft.setCursor(0, 80);
tft.print("   Press the Button ");


}

void loop() {
  // put your main code here, to run repeatedly:
if(digitalRead(D5)==LOW)
{
  tft.fillScreen(ST7735_BLACK);
  tft.drawRect(0,64 ,128, 40, ST7735_GREEN);
  tft.setCursor(0, 80);
  tft.print("  Waiting For Server!");
  while( !ServerConnect());
   tft.fillScreen(ST7735_BLACK);
  tft.drawRect(0,0 ,128,32, ST7735_GREEN);
    tft.setCursor(25, 15);
  tft.print(event1);
  tft.fillCircle(10,15,5,ST7735_GREEN);
    tft.drawRect(0,32 ,128,64, ST7735_GREEN);
   tft.setCursor(25, 45);
  tft.print(event2);
     tft.drawRect(0,64 ,128,96, ST7735_GREEN);
   tft.setCursor(25, 75);
  tft.print(event3);
     tft.drawRect(0,96 ,128, 128, ST7735_GREEN);
   tft.setCursor(25, 105);
  tft.print(event4);
     tft.drawRect(0,128 ,128,160, ST7735_GREEN);
   tft.setCursor(25, 135);
  tft.print(event5);
  int a=0,i=0;
  while(digitalRead(D5)==HIGH){yield();}
 while(a!=1){
  if(a==2)
  {
   tft.fillCircle(10,15+30*i,5,ST7735_BLACK);
   i++;
   if(i>4)i=0;
   tft.fillCircle(10,15+30*i,5,ST7735_GREEN); 
   Serial.println("Yo");
  }
  a=Select();
  yield();
 }
  tft.fillScreen(ST7735_BLACK);
 tft.setCursor(55, 75);
  tft.print(i);
/*  client.print(i);
  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
           "Host: " + host + "\r\n" +
           "Connection: close\r\n\r\n");
  client.print("Content-Type: application/json\r\n");
 */
 delay(2000);
 tft.fillScreen(ST7735_BLACK);
 tft.setCursor(1, 75);
 tft.print("Press Button to Start");
 i=0;
 while(i< 121){
 while(digitalRead(D5)==HIGH){yield();}
  checkID(attendance);}
  

}
}

int Select(void)
{
  int counter = 0;
  if(digitalRead(D5)==LOW)
  {
   while(digitalRead(D5)==LOW)
  {
    counter++;
    Serial.println(counter);
    delay(100);
  }
  if(counter > 5)
  {
    Serial.println("The return is 1");
    return 1;
  }
  else
  {
   Serial.println("The return is 2");
   return 2;
   }
}
return 0;
}
bool ServerConnect(void)
{

   Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 8080;
  if (!client.connect("172.16.30.20", httpPort)) {
    Serial.println("connection failed");
    return 4;
  }

identify = "1614";
hash = sha1(identify+"BioMetriC"); 

JsonObject& root = jsonBuffer.createObject();

root["id"] = identify;
root["hash"] = hash;
char JSONmessageBuffer[77];
root.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
//parseString(JSONmessageBuffer,jsonparse);
Serial.println(JSONmessageBuffer);

String url="https://lastiot.000webhostapp.com/api.php";//https://lastiot.000webhostapp.com/api.php

client.print("POST " + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n");
client.print("Content-Type: application/json\r\n");
client.print("Content-Length: 77");
client.print("\r\n");
client.print("x-verify: lol\r\n");
client.println();
client.println(JSONmessageBuffer);
client.print("\n");
//client.print(str + "\n");


/*  client.print("Content-Type: application/json\r\n"); 
  client.print("Content-Length: 42 \r\n");
  client.println(); 
  client.print(JSONmessageBuffer); */
   
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 15000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return 0;
    }
  }
String line;
    delay(100);
    for(i=0;i<12;i++){
     line = client.readStringUntil('\n');
    Serial.println(line);}
    //Serial.print("Data Sent!");
    //
    line = client.readStringUntil('\n');
    Serial.println("The json response is");
    Serial.println(line);
    //parse the char array here
  
  return 1;
  }

//typedef unsigned short uint8_t;
uint8_t setID(bool *attendance){
  attendance[finger.fingerID] = 1;
}

uint8_t checkID(bool *attendance){
  uint8_t val = finger.getImage();
   unsigned long timeout = millis();
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(10, 75);
  tft.print("Put your Finger!");
  while(val != FINGERPRINT_OK){
  val = finger.getImage();
  if(millis() - timeout > 10000){
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(10, 75);
  tft.print("No Finger Presented");
  return 0;
    }
    yield();
  }
  val = finger.image2Tz();
  if(val != FINGERPRINT_OK)
  {
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(20, 75);
    tft.print("Finger too messy");
    
    checkID(attendance);
  }
    
  val = finger.fingerFastSearch();
  if(val == FINGERPRINT_OK)
  {
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(20, 75);
    tft.print("Attendance Stored");
    tft.setCursor(0, 130);
    tft.print("  Scan Admin's Finger");
    tft.setCursor(40, 150);
    tft.print("to STOP!");
    setID(attendance);
    i++;
    return 1;
  }else {
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(20, 75);
    tft.print("Fingerprint not found!");
    return 0;
  }
}


