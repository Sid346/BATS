#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include "parse.h"
#include <ESP8266WiFi.h>
#include <Hash.h>
#include "ArduinoJson.h"
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

int getFingerprintIDez();

// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
SoftwareSerial mySerial(D2,D3);


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
Event_TypeDef jsonparse[5];
String hash;

char event1[20] = "Maths_Test";
char event2[20] = "Physics_Test";
char event3[20] = "Chemistry_Test";
char event4[20] = "Electronics_Test";
char event5[20] = "Mechanics_Test";
bool attendance[120]={0};

uint8_t checkID(int *attendance);
const char* ssid  = "utkarsh";//";   //replace with your own SSID
const char* password = "utkarsh123";    //replace with your own
const char* host = "bats.rf.gd";  
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
tft.setCursor(25, 35);
tft.setTextSize(2);
tft.setRotation(3);
tft.print("Welcome to ");
tft.setCursor(60,65);
tft.print("BATS");
delay(2000);
tft.setTextSize(2);
tft.fillScreen(ST7735_BLACK);
testdrawcircles(10,ST7735_YELLOW);
tft.fillScreen(ST7735_BLACK);
tft.drawRect(0,0,159,127, ST7735_GREEN);//col*rows
tft.setCursor(55,35);
tft.print("Press");
tft.drawRect(0,0,159,127, ST7735_GREEN);//col*rows
tft.setCursor(65,55);
tft.print("the");
tft.drawRect(0,0,159,127, ST7735_GREEN);//col*rows
tft.setCursor(52,75);
tft.print("Button");


}
void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=0; x < tft.width()+radius; x+=radius*2) {
    for (int16_t y=0; y < tft.height()+radius; y+=radius*2) {
      tft.drawCircle(x, y, radius, color);
      delay(30);
    }
  }
}
void loop() {
  // put your main code here, to run repeatedly:
if(digitalRead(D5)==LOW)
{
  tft.fillScreen(ST7735_BLACK);
tft.drawRect(0,0,159,127, ST7735_GREEN);//col*rows
tft.setCursor(20,35);
tft.print("Connecting");
//col*rows
tft.setCursor(65,55);
tft.print("to");
//col*rows
tft.setCursor(53,75);
tft.print("BATS");
  while( !ServerConnect());
  tft.setTextSize(1);
   tft.fillScreen(ST7735_BLACK);
  tft.drawRect(0,0 ,159,25, ST7735_GREEN);
    tft.setCursor(20,0);
  tft.print(jsonparse[0].Event);
  tft.fillCircle(10,10,5,ST7735_GREEN);
 tft.drawRect(0,25 ,159,25, ST7735_GREEN);
   tft.setCursor(20,37);
  tft.print(event2);
 tft.drawRect(0,50 ,159,25, ST7735_GREEN);
   tft.setCursor(20,62);
  tft.print(event3);
  tft.drawRect(0,75,159,25, ST7735_GREEN);
   tft.setCursor(20,87);
  tft.print(event4);
tft.drawRect(0,100,159,25, ST7735_GREEN);
   tft.setCursor(20,113);
  tft.print(event5);
  int a=0,i=0;
  while(digitalRead(D5)==HIGH){yield();}
 while(a!=1){
  if(a==2)
  {
   tft.fillCircle(10,10+25*i,5,ST7735_BLACK);
   i++;
   if(i>4)i=0;
   tft.fillCircle(10,10+25*i,5,ST7735_GREEN); 
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
  tft.setTextSize(2);
tft.drawRect(0,0,159,127, ST7735_GREEN);//col*rows
tft.setCursor(10,35);
tft.print("Press Button");
//col*rows
tft.setCursor(65,55);
tft.print("to");
//col*rows
tft.setCursor(53,75);
tft.print("Start");
  tft.setTextSize(1);
 i=0;
 while(digitalRead(D5)==HIGH){yield();}
 checkID(attendance);
 while(i< 121){
 tft.fillScreen(ST7735_BLACK);
tft.drawRect(0,0,159,127, ST7735_GREEN);//col*rows
tft.setCursor(10,35);
  tft.setTextSize(2);
tft.print("Press Button");
//col*rows
tft.setCursor(65,55);
tft.print("to");
//col*rows
tft.setCursor(48,75);
tft.print("Proceed");
  tft.setTextSize(1);
 while(digitalRead(D5)==HIGH){yield();}
  checkID(attendance);
  }
  

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
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return 4;
  }

identify = "1615";
hash = sha1(identify+"BioMetriC"); 

JsonObject& root = jsonBuffer.createObject();

root["id"] = identify;
root["hash"] = hash;
char JSONmessageBuffer[77];
root.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
//parseString(JSONmessageBuffer,jsonparse);
Serial.println(JSONmessageBuffer);

String url="/Bhatt/service1.php";//https://lastiot.000webhostapp.com/api.php

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
     line = client.readStringUntil('\0');
    Serial.println(line);}
    //Serial.print("Data Sent!");
    //
    line = client.readStringUntil('\n');
    char *line2 = (char*)line.c_str();
    Serial.println("The json response is");
    parseString(line2,jsonparse);
    Serial.println(jsonparse[0].Event);
    Serial.println(jsonparse[0].eventId);
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
tft.drawRect(0,0,159,127, ST7735_GREEN);//col*rows
tft.setCursor(35,35);
  tft.setTextSize(2);
tft.print("Put your");
//col*rows
tft.setCursor(48,55);
tft.print("Finger");
  tft.setTextSize(1);
  while(val != FINGERPRINT_OK){
  val = finger.getImage();
  if(millis() - timeout > 10000){
  tft.fillScreen(ST7735_BLACK);
tft.drawRect(0,0,159,127, ST7735_GREEN);//col*rows
tft.setCursor(20,35);
  tft.setTextSize(2);
tft.print("No Finger");
//col*rows
tft.setCursor(20,55);
tft.print("Presented!");
  tft.setTextSize(1);
   delay(1500);
  return 0;
    }
    yield();
  }
  val = finger.image2Tz();
  if(val != FINGERPRINT_OK)
  {
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(30, 55);
    tft.print("Finger too messy");
     delay(1500);
    checkID(attendance);
  }
    
  val = finger.fingerFastSearch();
  if(val == FINGERPRINT_OK)
  {
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(30,50);
    tft.print("Attendance Stored");
    tft.setCursor(10, 100);
    tft.print("Scan Admin's Finger to STOP!");
    delay(1500);
    setID(attendance);
    i++;
    return 1;
  }else {
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(10, 50);
    tft.print("No Fingerprint Found!");
    tft.setCursor(10, 80);
    tft.print("Attendance Not Marked!");
    delay(1500);
    return 0;
  }
}


