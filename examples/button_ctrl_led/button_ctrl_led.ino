
/*
 * This sketch read the serial data from the vRTCam and print to serial monitor
 * 
 * vRTCam Wiring:
 * Connect 5V supply to vRTCam (IMPORTANT: The 5V pin on your Arduino board will not be able to power vRTCam)
 * Connect OUT pin to pin 8.
 * Connect GND
 * 
 * LEDs Wiring:
 * Connect three LEDs to pin 2, 3 and 4
 * 
 * Download the sketch to Arduino board and turn on serial monitor. Set the
 * baudrate to 19200
 * 
 * Connect your mobile phone to SSID vRTCam-xxxxxxxx, where xxxxxxxx is the SSID of your vRTCam.
 * Run web brower and set the URL address to 192.168.4.1
 * 
 * Touch the buttons on your mobile's browser and observe the LEDs. The buttons' information also print 
 * to the serial monitor.
 * 
 */
#include "SGBotic_vRTCam.h"

#define rcvPin 8
#define txPin 9

#define led1Pin 2
#define led2Pin 3
#define led3Pin 4


SoftwareSerial mySerial(rcvPin, txPin);  // RX, TX
SGBotic_vRTCam vRTCam = SGBotic_vRTCam(&mySerial);

// Hardware serial-> using Serial1
//SGBotic_vRTCam vRTCam = SGBotic_vRTCam(&Serial1);

uint16_t vRTCamData[VRTCAM_DATA_SIZE];
uint8_t dataType;

uint8_t led1Stat;
uint8_t led2Stat;
uint8_t led3Stat;

void setup() {

  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  
  Serial.begin(19200);

  vRTCam.begin();
}

void loop() {
  dataType = vRTCam.readData(vRTCamData);

  if(dataType == VRTCAM_DATA_BUTTON){
    led1Stat = vRTCamData[VRTCAM_BUTTON_B1];
    led2Stat = vRTCamData[VRTCAM_BUTTON_B2];
    led3Stat = vRTCamData[VRTCAM_BUTTON_B3];
    
    Serial.print("Button 1: ");
    Serial.print(led1Stat);
    Serial.print("   Button 2: ");
    Serial.print(led2Stat);
    Serial.print("   Button 3: ");
    Serial.println(led3Stat);

    digitalWrite(led1Pin, led1Stat);
    digitalWrite(led2Pin, led2Stat);
    digitalWrite(led3Pin, led3Stat);
  }
}
