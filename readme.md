Picobot2
=======
Picobot2 is an enhanced and upgraded version of the popular original Picobot. It keeps the same form factor, but adds the following exciting features:

 - Acrylic case
 - Built-in Rechargeable battery
 - Built-in smart battery charge circuit with Charge (Red) and Done
   (Green) indicator LEDs. Automatically stops charging when the battery
   is full
 - USB connection for programming and charging. No need for additional
   USB programming converters
 - Smart H-Bridge motor driver that supports both "coast to stop" and
   "brake now" modes
 - Optional Bluetooth BLE module using nRF51822 BLE chip
 - Optional WiFi module using ESP8266 (ESP-12E/F)

Picobot2 Released Files
======================
All files are Licensed under Creative Commons BY-SA
See creativecommons.org/licenses/by-sa/3.0/ for details

The Picobot2 requires drivers for the CH340 USB chip. These *will* install automatically on both Windows 7 (or later), and Ubuntu 15.xx or later

When using the Arduino IDE, select board type UNO. The Picobot2 is fully compatible with the UNO


Picobot2 Software
================
Install the Picobot2 library using the Arduino IDE library manager.
This will also install the following example files within the examples folder of the IDE
You will also need to install the FastLED library: In the Arduino IDE, go to the Menu item Sketch/Include Library/Manage Libraries then search for FastLED and select Install.

 - **DemoAll** - Uses the Mode button to switch between 5 different demos.
   After pressing the button it flashes the LEDs the number of times for
   the following demos:
   	1. Flash all the LEDs
   	2. Line Follower
   	3. Light Seeker
   	4. Obstacle avoider
   	5. Constant distance
 - **LEDTest** - Flashes all the LEDs
 - **AnalogTest** - outputs analog values from light and line following
   sensors to Serial Monitor (also to Bluetooth if present)
 - **MotorTest** - Turns the motors Forwards, Reverse, Spin Left, Spin
   Right, Halt in turn
 - **UltraTest** - Outputs the distance reading from the Ultrasonic sensor
   to the Serial Monitor


----------


There are a couple of other examples programs as well:

 - **Tweetbot** This was written by Carl Monk and allows you to tweet settings to the Picobot2 (assuming you have it fitted with a WiFi module. Visit [Carl's Github](https://github.com/ForToffee/Picobot2/tree/master/TweetBot) for latest information
 - **ScratchPicobot**. This is an experimental program by Simon Walters and allows the WIFi connected Picobot2 to be controlled directly by a Scratch 1.4 program running on the same network as the Picobot2. 

