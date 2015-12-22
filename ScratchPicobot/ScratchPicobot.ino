/*
  Code written by @cymplecy 
  Code based on TweetBot by @fortoffee
  Built on MotorTest by 4Tronix 

  This example code is licensed under CC-BY-SA https://creativecommons.org/licenses/by-sa/3.0/
 */
#define VERSION 0.1
#include <FastLED.h>
#include <SoftwareSerial.h>

#define L1 6  // Left motor pin1
#define L2 10  // Left motor pin2
#define R1 5  // Right motor pin1
#define R2 9  // Right motor pin2

#define IR 5  // Right motor pin1
#define IL 9  // Right motor pin2
#define LED 13  // Blue LED pin
#define DEBUG true

// WS2812B definitions
#define NUM_LEDS 2
#define DATA_PIN 4
CRGB leds[NUM_LEDS];
SoftwareSerial esp8266(2,3);

unsigned long previousMillis = 0;
const long interval = 1000;

// the setup routine runs once when you press reset:
void setup()
{                
  esp8266.begin(9600); // your esp's baud rate might be different
  delay(100);
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  allOff();
  // initialize the digital pins we will use as
  pinMode(L1, OUTPUT);     
  pinMode(L2, OUTPUT);     
  pinMode(R1, OUTPUT);     
  pinMode(R2, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(115200);

  sendData("AT+RST\r\n", "\r\nready",2000,DEBUG); // reset module
  sendData("AT+CWMODE=1\r\n",1000,DEBUG); // configure as station (client)
  /*edit and uncomment following line to attach to known AP. Config is 
    stored between resets/power cycles*/
  sendData("AT+CWJAP=\"YourSSID\",\"PASSPHRASE\"\r\n",30000,DEBUG); // connect to AP
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=0\r\n",1000,DEBUG); // ensure single connection ONLY
  sendData("AT+CIPSTART=\"TCP\",\"win8\",42001\r\n",1000,DEBUG);

  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
}


void loop()
{

  String dataraw = "";
  while(esp8266.available()) {
    char c = esp8266.read();
     dataraw += String(c);
  }
  if (dataraw.length() > 0) {
    dataraw.toLowerCase();
    //Serial.println("RAW:" + dataraw);
    //Serial.println(dataraw.indexOf("colour"));
    if (dataraw.indexOf("colour red") >=0)
      setAll(255,0,0);
    if (dataraw.indexOf("colour green") >=0)
      setAll(0,255,0);    
    if (dataraw.indexOf("colour blue") >=0)
      setAll(0,0,255);    
    if (dataraw.indexOf("colour white") >=0)
      setAll(255,255,255);    
    if (dataraw.indexOf("colour yellow") >=0)
      setAll(255,255,0); 
    if (dataraw.indexOf("colour cyan") >=0)
      setAll(0,255,255);    
    if (dataraw.indexOf("colour magenta") >=0)
      setAll(255,0,255); 
    if (dataraw.indexOf("colour orange") >=0)
      setAll(255,128,0);    
    if (dataraw.indexOf("colour purple") >=0)
      setAll(128,0,128);       
    if (dataraw.indexOf("colour pink") >=0)
      setAll(255,0,255); 
    if (dataraw.indexOf("colour warmwhite") >=0)
      setAll(255,255,255);     
    if (dataraw.indexOf("colour off") >=0)
      setAll(0,0,0);       
    int motorA = dataraw.indexOf("motora");
    if (motorA >=0) {
      String power = dataraw.substring(motorA+8,motorA+12);
      int powerInt = power.toInt();
      Serial.println("PWR:" + power + "***");
      if (powerInt > 0) {
        analogWrite(L2, (255 - power.toInt()));
        digitalWrite(L1, HIGH);
      }
      else if (powerInt < 0) {
        analogWrite(L2, (255 - power.toInt()));
        digitalWrite(L1, LOW);
      }
      else {
      digitalWrite(L2, LOW);
      digitalWrite(L1, LOW);
      }
    }

    int motorB = dataraw.indexOf("motorb");
    if (motorB >=0) {
      String power = dataraw.substring(motorB+8,motorB+12);
      int powerInt = power.toInt();
      Serial.println("PWR:" + power + "***");
      if (powerInt > 0) {
        analogWrite(R1, (255 - power.toInt()));
        digitalWrite(R2, HIGH);
      }
      else if (powerInt < 0){
        analogWrite(R1, (255 - power.toInt()));
        digitalWrite(R2, LOW);
      }
      else {
        digitalWrite(R1, LOW);
        digitalWrite(R2, LOW);
      }
    }    

  }
  else {
    String cmd;
    int cmdLen = 0;
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      cmd = ("sensor-update \"leftldr\" " + String(analogRead(0)) + " \"rightldr\" " + String(analogRead(1)) + " \"leftline\" " + String(analogRead(6)) + " \"rightline\" " + String(analogRead(7)));
      cmdLen = cmd.length();
      esp8266.print("AT+CIPSEND=");
      esp8266.println((cmd.length() + 4) );
      if (esp8266.find(">")){
        //Serial.print(">");
        //erial.print(cmd);
        esp8266.write(byte(0));
        esp8266.write(byte(0));
        esp8266.write(byte(0));
        esp8266.write(byte(cmd.length()));
        esp8266.print(cmd);
  
        if(esp8266.find("OK")){
          //Serial.println("OK");
        }else{
          Serial.println("Error");
        }
      }
    }
  }
}
String sendData(String command, const int timeout, boolean debug)
  {
    return sendData(command, "OK", timeout, debug);
  }    

String sendData(String command, String waitFor, const int timeout, boolean debug)
{
    String response = "";
    
    esp8266.print(command); // send the read character to the esp8266
    
    long int time = millis();
    bool exit = false;
    while( ((time+timeout) > millis()) && (!exit))
    {
      while((esp8266.available()) && (!exit))
      {
        
        // The esp has data so display its output to the serial window 
        char c = esp8266.read(); // read the next character.
        response+=c;
        if (response.indexOf(waitFor) > -1)
          exit = true;  //found data terminator
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}
void allOff()
{
  for (int i=0; i<NUM_LEDS; i++)
    leds[i] = 0;
  FastLED.show();
}

void setAll(int red, int green, int blue)
{
  for (int i=0; i<NUM_LEDS; i++)
  {
    leds[i].g = red;
    leds[i].r = green;
    leds[i].b = blue;
  }
  FastLED.show();
}
