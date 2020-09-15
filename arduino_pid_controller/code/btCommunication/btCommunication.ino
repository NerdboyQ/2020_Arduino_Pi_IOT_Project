/*
 * Author :  Princton Brennan
 * Purpose : Beginner's Example for Bluetooth Communication 
 * Requirements : 1 LED, Bluetooh Module Hc-05 or newer), an Arduino, &   
 * a Bluetooth Terminal App (or something similar).
 * 
 * Function : The arduino will turn an LED on or off depending on the 
 * commands via Blueooth.
 * 
 * NOTE :: Most LED's that come in kits are rated for 3V, so to be safe place a 150ohm
 * to 250ohm resistor in series with the LED for current limiting. 
 * 
 * HC-05 example : https://create.arduino.cc/projecthub/electropeak/getting-started-with-hc-05-bluetooth-module-arduino-e0ca81
 * 
 * This sketch uses the "SoftwareSerial" Library:
 * 
 * The Arduino hardware has built-in support for serial communication on pins 0 and 1 
 * (which also goes to the computer via the USB connection). The native serial support 
 * happens via a piece of hardware (built into the chip) called a UART. This hardware 
 * allows the Atmega chip to receive serial communication even while working on other 
 * tasks, as long as there room in the 64 byte serial buffer.
 * 
 * The SoftwareSerial library has been developed to allow serial communication on other 
 * digital pins of the Arduino, using software to replicate the functionality (hence the 
 * name "SoftwareSerial"). It is possible to have multiple software serial ports with 
 * speeds up to 115200 bps. A parameter enables inverted signaling for devices which require 
 * that protocol.
 * 
 * For more info : https://www.arduino.cc/en/Reference/softwareSerial
 */
 
#include <SoftwareSerial.h> 
#include <Servo.h>

const byte servoPin = 6;    // Servo pin assigned as pin 6 [servos require a PWM pin].
Servo servo;                // To create a servo instance, we use the Servo class from Servo.h.

// Using the SoftwareSerial Library, the Digital IO pins 2 & 3 are repurposed as Soft Serial Pins
// NOTE : For wiring the TX pin of the target device/module is connected to the assigned RX pin of the
// Microcontroller, and the RX pin of the target device/module is connected to the assigned TX pin of
// the Microcontroller.  
SoftwareSerial BT_Module(2, 3); // assigned RX , assigned TX 
byte bt_msg;    // The bluetooth messagge will be received one byte a time, which can be represented as a character (char) 
const byte led1_pin = 11;   // The led1_pin assigned to pin 11.
const byte led2_pin = 12;   // The led2_pin assigned to pin 12.

// Every Arduino sketch requires at least a setup loop for initializing I/O pins and serial ports
// and a main function called "loop" that will loop indefinitely while the board is powered.
void setup() 
{   
 Serial.begin(9600);       // The default baudrate for the HC-05 is 38400, and 9600 for the HM-10 
 BT_Module.begin(9600);       // If the baudrate is incorrect the messages will not be read/displayed correctly.
 pinMode(led1_pin, OUTPUT);      // The led pin gets setup as an output pin. 
 pinMode(led2_pin, OUTPUT);
 servo.attach(servoPin);
 
 //Serial.println("Ready to connect\nDefualt password is 1234 or 000"); 
} 
void loop() 
{ 
 // While there is no incoming data, the Serial available function will return a 0,
 // but when it is receiving data it will no longer be 0. So we wait to read the
 // incoming message before we handle any actions. 
 if (BT_Module.available() > 0)
 { 
     //readBT_Msg();
     Serial.print("new msg: ");
     bt_msg = BT_Module.read();
     Serial.println(bt_msg, HEX);
     byte upper_nibble = bt_msg & 0b11110000;  // Masking lower 4 bits to focus on the upper 4 bits
     byte lower_nibble = bt_msg & 0b00001111;
     upper_nibble = upper_nibble >> 4;
     // Serial.println(upper_nibble, HEX);
     // Serial.println(lower_nibble, HEX);
     if (upper_nibble == 9)
     {
       switch(lower_nibble)
       {
        case 12:
         Serial.println("Servo Sanity Check: 180 degrees");
         servo.write(180); 
         break;
        case 8:
         Serial.println("Servo Sanity Check: 150 degrees");
         servo.write(150); 
         break;
        case 4:
         Serial.println("Servo Sanity Check: 120 degrees");
         servo.write(120);
         break; 
        case 0:
         Serial.println("Servo Sanity Check: 90 degrees");
         servo.write(90); 
         break;
        case 1:
         Serial.println("Servo Sanity Check: 60 degrees");
         servo.write(60); 
         break;
        case 2:
         Serial.println("Servo Sanity Check: 30 degrees");
         servo.write(30); 
         break;
        case 3:
         Serial.println("Servo Sanity Check: 0 degrees");
         servo.write(0); 
         break;
        case 6:
          Serial.println("Servo Sanity Check: Sweep");       
          for(byte pos = 0; pos<=180;pos+=30)
          {
           servo.write(pos); 
           delay(1000);
          }
          for(byte pos = 150; pos>0;pos-=30)
          {
           servo.write(pos);
            delay(1000);
          }
          servo.write(0);
         break;
       }
     }
     digitalWrite(led1_pin, HIGH);
     delay(1500);
 }
 else
 {
   digitalWrite(led1_pin, LOW);
   digitalWrite(led2_pin, LOW); 
 }

}  
