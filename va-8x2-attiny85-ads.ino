/*
this sketch is adapted by niq_ro from
http://www.tehnic.go.ro
http://www.niqro.3x.ro
http://nicuflorica.blogspot.ro/
http://arduinotehniq.blogspot.com/
for made a dual thermometer & battery status for car with ATtiny85 as Arduino..
 * 3-pin Arduino interface for HD44780 LCDs via 74HC595 Shift Register
 *     by Rowan Simms   code@rowansimms.com
 *     License: Creative Commons - Attribution.
 *     Full Documentation and Description:  http://rowansimms.com/article.php/lcd-hookup-in-seconds
 *
 * This sketch allows Arduinos to use a shift register to control an LCD, allowing 
 * a reduction in pins it requires from 6 to 3 while still retaining full control
 * including backlight on/off.
 * This requires the use of the LiquidCrystal595 library
 * available at:https://bitbucket.org/rowansimms/arduino-lcd-3pin/downloads/
 * http://nicuflorica.blogspot.ro/2015/01/termometru-dublu-si-indicator-tensiune.html
 * http://nicuflorica.blogspot.ro/2017/07/programator-pentru-attiny254585-cu.html
 */
#include <TinyWireM.h> //https://github.com/adafruit/TinyWireM
#include <LiquidCrystal595.h>    // include the library
LiquidCrystal595 lcd(3,1,4);     // datapin, latchpin, clockpin pb0, pb1, pb2
#include <Adafruit_ADS1015.h>  //https://github.com/adafruit/Adafruit_ADS1X15

Adafruit_ADS1115 ads(0x48);
float Voltage = 0.0;
float Voltage1 = 0.0;
float Voltage2 = 0.0;
float Voltage3 = 0.0;


float current = 0.;   // valoare curent
float tensiune = 0.; // valoare tensiune


void setup() {
 //  analogReference(INTERNAL); 
  
    lcd.begin(8,2);             // 8characters, 2 rows
 
 ads.begin();

 lcd.clear(); // clear the screen
 lcd.setCursor(0, 0); 
 lcd.print("ATtiny85"); // print a text
 lcd.setCursor(3, 1); 
 lcd.print("V-A"); // print a text
 delay (1500);
 lcd.clear(); // clear the screen


 lcd.setCursor(0, 1); 
 lcd.print("@ VladGh"); 
 delay (1000);
 lcd.clear(); 
 uint16_t time = millis();
}


void loop() {
   int16_t adc0;  // we read from the ADC, we have a sixteen bit integer as a result
int16_t adc1; 
int16_t adc2; 
int16_t adc3; 
adc0 = ads.readADC_SingleEnded(0);
  Voltage = (adc0 * 0.1875)/1000;
  adc1 = ads.readADC_SingleEnded(1);
  Voltage1 = (adc1 * 0.1875)/1000;
  adc2 = ads.readADC_SingleEnded(2);
  Voltage2 = (adc2 * 0.1875)/1000;
  adc3 = ads.readADC_SingleEnded(3);
  Voltage3 = (adc3 * 0.1875)/1000;
delay(100);
  //  tensiune=((.467/(.467+99.66))*Voltage);
    tensiune=(0.0043*Voltage);
  current=Voltage1/0.01;
  lcd.setCursor(0, 0);
    lcd.print("U=");
    if (tensiune*50000 < 10.0) lcd.print(" ");  // daca tensiunea e mai mica de 10V 
    lcd.print(tensiune*50000,2);
    lcd.print("V");
     lcd.setCursor(0, 1);
    lcd.print("I=");
    if (current/10 < 10.0) lcd.print(" ");  // daca curentul e mai mic de 10A 
    lcd.print(current/10,2);
    lcd.print("A");
    lcd.setCursor(0, 1);
   
}
