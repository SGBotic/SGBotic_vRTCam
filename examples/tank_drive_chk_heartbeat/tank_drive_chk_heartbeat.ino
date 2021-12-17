
/*
   This sketch read the joystick data from the vRTCam and use the "left motor"
   and "right motor" data to drive two-wheeled robot while continuously 
   monitoring the wifi connection

   The sketch will stop the motors if wifi connection is broken.

   Wiring of vRTCam:
   Connect 5V supply to vRTCam (IMPORTANT: The 5V pin on your Arduino board will not be able to power vRTCam)
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
#define jsFwdMaxPos 510
#define jsCenterPos 255
#define jsRevMaxPos 0

#define heartBeatCountMax 10


uint16_t vRTCamData[VRTCAM_DATA_SIZE];

uint16_t leftMotorDrive;
uint16_t rightMotorDrive;

uint8_t heartBeatCount = 0;
#define heartBeatCountMax 10

unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 200;  //the value is a number of milliseconds (i.e. 0.2s)

uint8_t dataType;

void setup() {
  Serial.begin(19200);

  vRTCam.begin();
  startMillis = millis();  //initial start time
}

void loop() {
  currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)

  // run this loop every 0.2 second to increase the counter by 1
  // the counter will reset to 0 if heartbeat data is received from vRTCam (codes is located at the
  // end of this sketch)
  // if counter exceeds 10 counts (2 seconds), probably signal lost, stop motors
  if (currentMillis - startMillis >= period) { //test whether the period has elapsed (0.1second)
    heartBeatCount++; //increase heartbeat counter by 1;
    if (heartBeatCount > heartBeatCountMax) { //probably signal lost, stop robot
      
      //both wheels stop
      leftMotorStop();
      rightMotorStop();
    }
    startMillis = millis();  //reset the start time to current time
  }
  dataType = vRTCam.readData(vRTCamData);

  if (dataType == VRTCAM_DATA_JOYSTICK) {

    uint16_t leftMotorValue = vRTCamData[VRTCAM_LEFT_MOTOR];
    uint16_t rightMotorValue = vRTCamData[VRTCAM_RIGHT_MOTOR];

    Serial.print("left motor: ");
    Serial.print(leftMotorValue);
    Serial.print("   right motor: ");
    Serial.println(rightMotorValue);

    if (leftMotorValue == jsCenterPos) {
      // left wheel stop
      leftMotorStop();
      
    } else if (leftMotorValue > jsCenterPos) {
      // left wheel move forward
      leftMotorFwd(leftMotorValue - jsCenterPos);
      
    } else if (leftMotorValue < jsCenterPos) {
      // left wheel move backward
       leftMotorRev(leftMotorValue - jsCenterPos);
       
    }

    if (rightMotorValue == jsCenterPos) {
      // right wheel stop
      rightMotorStop();
      
    } else if (rightMotorValue > jsCenterPos) {
      // right wheel move forward
       rightMotorFwd(rightMotorValue - jsCenterPos);
       
    } else if (rightMotorValue < jsCenterPos) {
      // right wheel move backward
      rightMotorRev(rightMotorValue - jsCenterPos);
      
    }
  } else if (dataType == VRTCAM_DATA_HEARTBEAT) {
    Serial.print("HeartBeat: ");
    Serial.println(vRTCamData[VRTCAM_HEARTBEAT]);
    heartBeatCount = 0; //reset heartBeat counter
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
