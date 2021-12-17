
/*
 * This sketch read the data from the vRTCam and print to serial monitor
 * 
 * Wiring:
 * Connect 5V supply to vRTCam (IMPORTANT: The 5V pin on your Arduino board will not be able to power vRTCam)
 * Connect OUT pin to pin 8. 
 * Connect GND
 * 
 * Download the sketch to Arduino board and turn on serial monitor. Set the
 * baudrate to 19200
 * 
 * Connect your mobile phone to SSID vRTCam-xxxxxxxx, where xxxxxxxx is the SSID of your vRTCam.
 * Run web brower and set the URL address to 192.168.4.1
 * 
 * When you move the joystick or touch the buttons on your mobile's browser, the sketch will print the 
 * information to serial monitor.
 * 
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

  if(dataType == VRTCAM_DATA_JOYSTICK){
    
    Serial.print("left motor: ");
    Serial.print(vRTCamData[VRTCAM_LEFT_MOTOR]);
    Serial.print("   right motor: ");
    Serial.print(vRTCamData[VRTCAM_RIGHT_MOTOR]);
    Serial.print("   X-Axis: ");
    Serial.print(vRTCamData[VRTCAM_X_AXIS]);
    Serial.print("   Y-Axis: ");
    Serial.print(vRTCamData[VRTCAM_Y_AXIS]);
    Serial.print("   Angle: ");
    Serial.print(vRTCamData[VRTCAM_ANGLE]);
    Serial.print("   Speed: ");
    Serial.println(vRTCamData[VRTCAM_SPEED]);
      
  }else if(dataType == VRTCAM_DATA_BUTTON){
    Serial.print("Button 1: ");
    Serial.print(vRTCamData[VRTCAM_BUTTON_B1]);
    Serial.print("   Button 2: ");
    Serial.print(vRTCamData[VRTCAM_BUTTON_B2]);
    Serial.print("   Button 3: ");
    Serial.println(vRTCamData[VRTCAM_BUTTON_B3]);
    
  }else if(dataType == VRTCAM_DATA_HEARTBEAT){
    Serial.print("HeartBeat: ");
    Serial.println(vRTCamData[VRTCAM_HEARTBEAT]);
    
  }else if(dataType == VRTCAM_DATA_SSID){
    Serial.print("SSID of connected vRTCam module is: ");
    Serial.println(vRTCam.VRTCAM_SSID);
  
  }
}
