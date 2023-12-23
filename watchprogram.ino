//sa  board choose esp8266 boards>>generic esp8266 module
// ng com is com3 pero nagbabago ito bs sa port na pisaksakan ha

float calibrationvalue=1.5;//edit calibration 

#include "MAX30105.h"
#include "heartRate.h"
#include <ESP8266WiFi.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include <Wire.h> 
  #define TFT_RST      2 
  #define TFT_DC       0
 #define TFT_CS       -1 
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
long irValue;
String t1="0.0"; 
String v1="0";
String v2="0";
String v3="0";
float t11=0.0; 
int v11=0;
int v21=0;
int v31=0;
int temp=0.0;
float t1h=0.0; 
String v1h="0";
String v2h="0";
String v3h="0";
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


int data1=0;
int data2=0;
int  send1=0;
   int count=0;
const char* host = "cmmlmarketing.com";
String line;
int fromzero=0;
MAX30105 particleSensor;

const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;
int delayread=0;


void setup()
{
delayread=7;
 Serial.begin(9600);
Serial.println("Initializing...");


connectToWiFi(); //function to connect to wifi

/*connectToFirebase();  if ever connected na sa firebase eto yung function tapos change yung need na credetials sa connection.h*/

// Initialize sensor
if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
{
Serial.println("MAX30105 was not found. Please check wiring/power. ");
while (1);
}
Serial.println("Place your index finger on the sensor with steady pressure.");

  tft.init(240, 240, SPI_MODE2);           // Init ST7789 240x240

particleSensor.setup(); //Configure sensor with default settings
particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
  // large block of text
 



  
}


void loop()
{ beatAvg = 0;
  delayread++;
  
  
  
  
  for (int thisPin = 0; thisPin < 70; thisPin++) {

irValue = particleSensor.getIR();

if (checkForBeat(irValue) == true)
{
//We sensed a beat!
long delta = millis() - lastBeat;
lastBeat = millis();

beatsPerMinute = 60 / (delta / 1000.0);

if (beatsPerMinute < 255 && beatsPerMinute > 20)
{
rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
rateSpot %= RATE_SIZE; //Wrap variable

//Take average of readings




for (byte x = 0 ; x < RATE_SIZE ; x++)
beatAvg += rates[x];
beatAvg /= RATE_SIZE;
}
}

//Serial.print("IR=");
//Serial.print(irValue);
//Serial.print(", BPM=");
//Serial.print(beatsPerMinute);
//Serial.print(", Avg BPM=");
//Serial.println(beatAvg);
//irValue1=irValue/1000;
//if (irValue1>99){irValue1=99;}


///// ito yung reading for defualt sensor values

 // debug.print(" R[");
 // debug.print(particleSensor.getRed());
 // debug.print("] IR[");
//  debug.print(particleSensor.getIR());
//  debug.print("] G[");
//  debug.print(particleSensor.getGreen());
//  debug.print("]");
}
Serial.println(irValue);
if (irValue>10000)
{//dito yung nir reading
irValue=(irValue/302)/calibrationvalue;// multiplier yung 1.5 so ito yung babaguhin para macalibrate
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(40, 30);
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(4);
  tft.println("GLUCOSE");
  tft.setTextColor(ST77XX_GREEN);
  tft.setCursor(40, 80);
  tft.setTextSize(6);
  tft.println(irValue);

} 
else

{

t11=0.0; 
v11=0;
v21=0;
v31=0;
t1="0"; 
v1="0";
v2="0";
v3="0";
    tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(40, 30);
  
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(4);
  tft.println("GLUCOSE");
  
  tft.setTextColor(ST77XX_GREEN);
  tft.setCursor(40, 80);
  tft.setTextSize(6);

  tft.println("NONE");

}


////////////////////////

}
