
/*
   This sketch read the joystick data from the vRTCam and use the "left motor"
   and "right motor" data to drive two-wheeled robot

   Wiring of vRTCam:
   Connect 5V supply to vRTCam  (IMPORTANT: The 5V pin on your Arduino board will not be able to power vRTCam)
   Connect OUT pin to pin 8.
   Connect GND

   Download the sketch to Arduino board and turn on serial monitor. Set the
   baudrate to 19200

   Connect your mobile phone to SSID vRTCam-xxxxxxxx, where xxxxxxxx is the SSID of your vRTCam.
   Run web brower and set the URL address to 192.168.4.1

   You can use the joystick to individually control the left and right motor of your
   robot

*/
#include "SGBotic_vRTCam.h"

#define rcvPin 8
#define txPin 9

SoftwareSerial mySerial(rcvPin, txPin);  // RX, TX
SGBotic_vRTCam vRTCam = SGBotic_vRTCam(&mySerial);

// Hardware serial-> using Serial1
//SGBotic_vRTCam vRTCam = SGBotic_vRTCam(&Serial1);

//joystick output value
#define jsFwdMaxVal 510
#define jsCenterVal 255
#define jsRevMaxVal 0


uint16_t vRTCamData[VRTCAM_DATA_SIZE];

uint16_t leftMotorDrive;
uint16_t rightMotorDrive;

uint8_t dataType;

void setup() {
  Serial.begin(19200);

  vRTCam.begin();
}

void loop() {
  dataType = vRTCam.readData(vRTCamData);

  if (dataType == VRTCAM_DATA_JOYSTICK) {

    uint16_t leftMotorValue = vRTCamData[VRTCAM_LEFT_MOTOR];
    uint16_t rightMotorValue = vRTCamData[VRTCAM_RIGHT_MOTOR];

    Serial.print("left motor: ");
    Serial.print(leftMotorValue);
    Serial.print("   right motor: ");
    Serial.println(rightMotorValue);

    if (leftMotorValue == jsCenterVal) {
      // left wheel stop
      leftMotorStop();
      
    } else if (leftMotorValue > jsCenterVal) {
      // left wheel move forward
      leftMotorFwd(leftMotorValue - jsCenterVal);
      
    } else if (leftMotorValue < jsCenterVal) {
      // left wheel move backward
      leftMotorRev(leftMotorValue - jsCenterVal);
      
    }

    if (rightMotorValue == jsCenterVal) {
      // right wheel stop
      rightMotorStop();
      
    } else if (rightMotorValue > jsCenterVal) {
      // right wheel move forward
      rightMotorFwd(rightMotorValue - jsCenterVal);
      
    } else if (rightMotorValue < jsCenterVal) {
      // right wheel move backward
      rightMotorRev(rightMotorValue - jsCenterVal);
      
    }
  }
}

// stop left motor
void leftMotorStop() {
  
//implement your motor control code here

}

// move left motor forward
void leftMotorFwd(int val) {
  
//implement your motor control code here
  
}

// move left motor backward
void leftMotorRev(int val) {
  
//implement your motor control code here
  
}

// right motor stop
void rightMotorStop() {
  
//implement your motor control code here
  
}

// move right motor forward
void rightMotorFwd(int val) {
  
//implement your motor control code here
  
}

// move right motor backward
void rightMotorRev(int val) {
  
}
