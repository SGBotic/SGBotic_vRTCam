
/*
   This sketch read the SSID from the vRTCam and print to serial monitor

   Wiring:
   Connect 5V supply to vRTCam (IMPORTANT: The 5V pin on your Arduino board will not be able to power vRTCam)
   Connect OUT pin to pin 8. 
   Connect GND

   Download the sketch to Arduino board and turn on serial monitor. Set the
   baudrate to 19200

   Press the reset button on vRTCam. The SSID will print to serial monitor.

*/
#include "SGBotic_vRTCam.h"

#define rcvPin 8
#define txPin 9

SoftwareSerial mySerial(rcvPin, txPin);  // RX, TX
SGBotic_vRTCam vRTCam = SGBotic_vRTCam(&mySerial);

// Hardware serial-> using Serial1
//SGBotic_vRTCam vRTCam = SGBotic_vRTCam(&Serial1);

uint16_t vRTCamData[VRTCAM_DATA_SIZE];
uint8_t dataType;

void setup() {
  Serial.begin(19200);

  vRTCam.begin();
}

void loop() {
  dataType = vRTCam.readData(vRTCamData);

  if (dataType == VRTCAM_DATA_SSID) {
    Serial.print("SSID of connected vRTCam module is: ");
    Serial.println(vRTCam.VRTCAM_SSID);
  }
}
