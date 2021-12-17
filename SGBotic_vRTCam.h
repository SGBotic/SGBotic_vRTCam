#ifndef SGBOTIC_VRTCAM_H
#define SGBOTIC_VRTCAM_H

#include "Arduino.h"
#if defined(__AVR__) || defined(ESP8266)
#include <SoftwareSerial.h>
#endif

#include <stdio.h>
#include <string.h>

//#define vRTCam_DEBUG

#define VRTCAM_STARTBYTE 0xAA
#define VRTCAM_PKT_DATA_SIZE 14
#define VRTCAM_BAUDRATE 19200

//packet type from camera
#define VRTCAM_PKT_JOYSTICK 0x1
#define VRTCAM_PKT_BUTTON 0x2
#define VRTCAM_PKT_HEARTBEAT 0x3
#define VRTCAM_PKT_SSID 0x4
#define VRTCAM_PKT_RSSI 0x5

//packet receive ID to be return to user program
#define VRTCAM_DATA_SIZE 6
#define VRTCAM_DATA_JOYSTICK 0x01
#define VRTCAM_DATA_BUTTON 0x02
#define VRTCAM_DATA_HEARTBEAT 0x03
#define VRTCAM_DATA_SSID 0x04
#define VRTCAM_DATA_RSSI 0x05

#define VRTCAM_LEFT_MOTOR 0
#define VRTCAM_RIGHT_MOTOR 1
#define VRTCAM_X_AXIS 2
#define VRTCAM_Y_AXIS 3
#define VRTCAM_ANGLE 4
#define VRTCAM_SPEED 5

#define VRTCAM_HEARTBEAT 0

#define VRTCAM_BUTTON_B1 0
#define VRTCAM_BUTTON_B2 1
#define VRTCAM_BUTTON_B3 2

//#define VRTCAM_SSID 0

#define VRTCAM_RSSI 0

#define VRTCAM_

class SGBotic_vRTCam
{
public:
    String VRTCAM_SSID; // = "vRTCam-";

#if defined(__AVR__) || defined(ESP8266)
    SGBotic_vRTCam(SoftwareSerial *ss);
#endif
    SGBotic_vRTCam(HardwareSerial *hs);
    SGBotic_vRTCam(Stream *serial);

    void begin(void);

    uint8_t readData(uint16_t buffer_u16[VRTCAM_PKT_DATA_SIZE]);

private:
    const uint8_t CRC7_POLY = 0x91;
    uint32_t ssidBuf;
    String ssidStr;

    uint8_t getCRC(uint8_t message[], uint8_t length);

    Stream *mySerial;
#if defined(__AVR__) || defined(ESP8266)
    SoftwareSerial *swSerial;
#endif
    HardwareSerial *hwSerial;
};
#endif