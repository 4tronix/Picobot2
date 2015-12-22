/* 
  This requires the ESP8266 module to be fitted to the Picobot2
  You will need to uncomment the line in setup( ) starting: sendData("AT+CWJAP... and insert your access point SSID and Passphrase
  Built on MotorTest by 4Tronix

  This example code is licensed under CC-BY-SA https://creativecommons.org/licenses/by-sa/3.0/
  By Carl Monk with tweeks to work with Picobot2 library by Gareth Davies
  
 */

// See https://github.com/ForToffee/Picobot2/tree/master/TweetBot for more details

/*
Command set is currently

    Fx = forward x seconds
    Bx = backward x seconds
    Lx = turn left x 10th seconds
    Rx = turn right x 10th seconds
    [rrggbb] = light both pixels hex RGB value

tweets must contain #thingspeak #bot so

#thingspeak #bot F1L2B2R1[FFFFFF]

would result in

    Forward 1 sec,
    turn left for 0.2 sec,
    backwards 2 secs,
    turn right 0.1 sec,
    set pixels white

WARNING! There's no sanity checking on the input data so if you get a bum response then the bot will attempt to process it!
 */



#define DEBUG false

#include "Picobot2.h"
#include <SoftwareSerial.h>

Picobot2 pb2;
SoftwareSerial esp8266(2,3);
#define _speed 150 // speed of movement commands

// the setup routine runs once when you press reset:
void setup()
{                
  esp8266.begin(9600); // your esp's baud rate might be different
  delay(100);
  pb2.begin();
  Serial.begin(115200);

  sendData("AT+RST\r\n", "\r\nready",2000,DEBUG); // reset module
  sendData("AT+CWMODE=1\r\n",1000,DEBUG); // configure as station (client)
  /*uncomment following line to attach to known AP. Config is 
    stored between resets/power cycles*/
  sendData("AT+CWJAP=\"SKYA289F\",\"PAYPATUY\"\r\n",30000,DEBUG); // connect to AP
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=0\r\n",1000,DEBUG); // ensure single connection ONLY

}

// the loop routine runs over and over again forever:
String oldData;
void loop()
{
  String data = getCommand();
  if (oldData != data) {
    Serial.println("Data: " + data);
    String action = "";
    String duration;
    String colour;
    bool parseHashtag = false;  //have we found a hashtag, if so we want to skip it
    bool parseColour = false;
    for (unsigned int i = 0; i < data.length(); i++)
    {
      switch (data.charAt(i)) {
        case '#':{
            doAction(action, duration);
            action = "";
            parseHashtag = true;
            break;
          }
        case '[':{
          if (!parseHashtag){
            doAction(action, duration);
            action = "";
            parseColour = true;
          }
          break;
        }
        case ']':{
          parseColour = false;

          //http://stackoverflow.com/questions/23576827/arduino-convert-a-sting-hex-ffffff-into-3-int
          // convert colour to integer
          const char* hexColour = colour.c_str();
          long number = strtol(hexColour, NULL, 16);

          // Split them up into r, g, b values
          long r = number >> 16;
          long g = number >> 8 & 0xFF;
          long b = number & 0xFF;

          setAll(r,g,b);
        }
        case 'b':     // backward or hex value
        case 'f':{    //forward or hex value
          if (parseColour){
            colour += 'f';
          }
        }
        
        case 'l':
        case 'r':{
          if (!parseHashtag && !parseColour){
            doAction(action, duration);
            action =  data.charAt(i);
          }
          break;
        }
        case ' ':{
          parseHashtag = false;
          break;
        }
        case 'w':{
          //wander
          break;
        }
        default:{
          if (parseColour) {
            colour += data.charAt(i);
          }
          else if (isDigit(data.charAt(i))){
            duration += data.charAt(i);
          }
        }
      }
    }
    doAction(action, duration);
    oldData = data;
  }
  delay(9000);
}


void doAction(String action, String &durationVal){
  int duration = atoi(durationVal.c_str());
  Serial.println("Action: " + action);
  Serial.println("Duration: " + durationVal);

  if (durationVal != "" && action != ""){
    switch (action.charAt(0)) {
      case 'f':{
        tbForward(duration * 1000);
        halt(1);
        break;
      }
      case 'b':{
        tbReverse(duration * 1000);
        halt(1);
        break;
      }
      case 'l':{
        tbLeftSpin(duration * 100);
        halt(1);
        break;
      }
      case 'r':{
        tbRightSpin(duration * 100);
        halt(1);
        break;
      }
    }
  
    durationVal = "";
  }
}


String getCommand()
{
  //connect to server
  sendData("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n", 10000,DEBUG);

  //build request & command, don't forget \r\n terminator
  String request = "GET /channels/65715/field/2/last.txt\r\n";
  String cmd = "AT+CIPSEND=";
  cmd+= request.length();
  cmd += "\r\n";
  
  //send command
  sendData(cmd,1000,DEBUG);
  //send data
  sendData(request, "bytes",2000,DEBUG);
  
  delay(1000);
  
  //check for response  "+IPD,[size],[data]"
  if(esp8266.find("+IPD,"))
  {
    char c;
    
    //get payload size
    String dataLen = "";
    while(esp8266.available())
      {
        c = esp8266.read();
        if (String(c) == ":")
          break;
        dataLen += String(c);
      }
    Serial.println("dataLen: " + dataLen);
    
    //read payload
    String response = "";
    for (int p=0; p < dataLen.toInt(); p++)
    {
       c = esp8266.read();
       response += String(c);
    }
    response.toLowerCase();
    return response;
  }
}



void ledOn()
{
  pb2.setBlueLED(ON);
}

void ledOff()
{
  pb2.setBlueLED(OFF);
}

void tbReverse(int wait)
{
  Serial.println("Moving backward");
  pb2.reverse(_speed);
  delay(wait);
}

void tbForward(int wait)
{
  Serial.println("Moving forward");
  pb2.forward(_speed);
  delay(wait);
}

void tbRightSpin(int wait)
{
  Serial.println("Spinning right");
  pb2.spinRight(_speed);
  delay(wait);
}

void tbLeftSpin(int wait)
{
  Serial.println("Spinning left");
  pb2.spinLeft(_speed);
  delay(wait);
}

void halt(int wait)
{
  Serial.println("Stopping");
  pb2.stop(true); // Brake
//  pb2.stop(false); // Coast
  delay(wait);
}

void allOff()
{
  pb2.pixelAllOff();
}

void setAll(int red, int green, int blue)
{
  pb2.pixelAllSet(CRGB(red, green, blue));
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


