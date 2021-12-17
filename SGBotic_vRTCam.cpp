

#include "SGBotic_vRTCam.h"

#if defined(__AVR__) || defined(ESP8266)
SGBotic_vRTCam::SGBotic_vRTCam(SoftwareSerial *ss)
{

    hwSerial = NULL;
    swSerial = ss;
    mySerial = swSerial;
}
#endif

SGBotic_vRTCam::SGBotic_vRTCam(HardwareSerial *hs)
{

#if defined(__AVR__) || defined(ESP8266)
    swSerial = NULL;
#endif
    hwSerial = hs;
    mySerial = hwSerial;
}

SGBotic_vRTCam::SGBotic_vRTCam(Stream *serial)
{

    hwSerial = NULL;
#if defined(__AVR__) || defined(ESP8266)
    swSerial = NULL;
#endif
    mySerial = serial;
}

void SGBotic_vRTCam::begin()
{
    delay(1000); // one second delay to let the sensor 'boot up'

    if (hwSerial)
        hwSerial->begin(VRTCAM_BAUDRATE);
#if defined(__AVR__) || defined(ESP8266)
    if (swSerial)
        swSerial->begin(VRTCAM_BAUDRATE);
#endif
}

uint8_t SGBotic_vRTCam::readData(uint16_t buffer_u16[VRTCAM_DATA_SIZE])
{
    if (!mySerial->available())
    {
        return 0;
    }

    // Read a byte at a time until we get to the special '0xAA' start-byte
    if (mySerial->peek() != VRTCAM_STARTBYTE)
    {
        mySerial->read();
        return 0;
    }

    // Now read all 14 bytes
    if (mySerial->available() < 14)
    {
        return 0;
    }
    uint8_t buffer[VRTCAM_PKT_DATA_SIZE];

    mySerial->readBytes(buffer, VRTCAM_PKT_DATA_SIZE);

#ifdef vRTCam_DEBUG
    for (int i = 0; i < VRTCAM_PKT_DATA_SIZE; i++)
    {
        Serial.print(i);
        Serial.print(":0x");
        Serial.print(buffer[i], HEX);
        Serial.print(" ");
    }
    Serial.println("");
#endif

    if (buffer[VRTCAM_PKT_DATA_SIZE - 1] != getCRC(buffer, VRTCAM_PKT_DATA_SIZE - 1))
    {
#ifdef vRTCam_DEBUG
        Serial.println("Checksum failure");
#endif
        return 0;
    }
    uint8_t retCode = 0;

    switch (buffer[1])
    {
    case VRTCAM_DATA_JOYSTICK:
        buffer_u16[VRTCAM_RIGHT_MOTOR] = ((uint16_t)buffer[2] << 8) | (uint16_t)buffer[3];
        buffer_u16[VRTCAM_LEFT_MOTOR] = ((uint16_t)buffer[4] << 8) | (uint16_t)buffer[5];
        buffer_u16[VRTCAM_X_AXIS] = ((uint16_t)buffer[6] << 8) | (uint16_t)buffer[7];
        buffer_u16[VRTCAM_Y_AXIS] = ((uint16_t)buffer[8] << 8) | (uint16_t)buffer[9];
        buffer_u16[VRTCAM_ANGLE] = ((uint16_t)buffer[10] << 8) | (uint16_t)buffer[11];
        buffer_u16[VRTCAM_SPEED] = (uint16_t)buffer[12];
        retCode = VRTCAM_DATA_JOYSTICK;
        break;

    case VRTCAM_DATA_BUTTON:
        buffer_u16[VRTCAM_BUTTON_B1] = (uint16_t)buffer[2];
        buffer_u16[VRTCAM_BUTTON_B2] = (uint16_t)buffer[3];
        buffer_u16[VRTCAM_BUTTON_B3] = (uint16_t)buffer[4];
        retCode = VRTCAM_DATA_BUTTON;
        break;

    case VRTCAM_DATA_HEARTBEAT:
        buffer_u16[VRTCAM_HEARTBEAT] = (uint16_t)buffer[2];
        retCode = VRTCAM_DATA_HEARTBEAT;
        break;

    case VRTCAM_DATA_SSID:
        
        VRTCAM_SSID = "vRTCam-";

        for (int i = 2; i < 6; i++)
        {
            ssidStr = String(buffer[i], HEX);
            ssidStr.toUpperCase();
            VRTCAM_SSID = VRTCAM_SSID + ssidStr;
        }
        retCode = VRTCAM_DATA_SSID;
        ssidStr = "";
        break;
/*
    case VRTCAM_DATA_RSSI:
        buffer_u16[VRTCAM_RSSI] = (uint16_t)buffer[2];
        retCode = VRTCAM_DATA_RSSI;
        break;
*/
    default:
        break;
    }
    return retCode;
}

uint8_t SGBotic_vRTCam::getCRC(uint8_t message[], uint8_t length)
{
    uint8_t i, j, crc = 0;

    for (i = 0; i < length; i++)
    {
        crc ^= message[i];
        for (j = 0; j < 8; j++)
        {
            if (crc & 1)
                crc ^= CRC7_POLY;
            crc >>= 1;
        }
    }
    return crc;
}
