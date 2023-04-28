///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////// ZE 08 ////////////////////////////////////////////////////////////////////
#pragma once

#include <HardwareSerial.h>

// ZE 08 Init Declaration //
#define MAXLENGTH 9
#define VREF 5.0 // voltage on AREF pin

extern float ze_value;

// long tenMinutes = 10 * 60 * 1000L; // on time of heater
HardwareSerial mySerial(2);

byte receivedCommandStack[MAXLENGTH];
byte checkSum(byte array[], byte length);
boolean receivedFlag;

byte checkSum(byte array[], byte length) {
  byte sum = 0;
  for (int i = 1; i < length - 1; i ++) {
    sum += array[i];
  }
  sum = (~sum) + 1;
  return sum;
}

boolean available1() 
{ //new data was recevied
    while (mySerial.available()) 
    {
        for (byte index = 0; index < MAXLENGTH - 1; index++) 
        {
            receivedCommandStack[index] = receivedCommandStack[index + 1];
        }
        receivedCommandStack[MAXLENGTH - 1] = mySerial.read();

        byte sumNum = checkSum(receivedCommandStack, MAXLENGTH);
        if ( (receivedCommandStack[0] == 0xFF) && (receivedCommandStack[1] == 0x17) && (receivedCommandStack[2] == 0x04) && (receivedCommandStack[MAXLENGTH - 1] == sumNum) ) 
        { //head bit and sum are all right
            receivedFlag = 1; //new data received
            return receivedFlag;
        }
        else 
        {
            receivedFlag = 0; //data loss or error
            return receivedFlag;
        }
    }

    return receivedFlag;
}

float ze08_PPM() 
{
    if (available1() == 1) 
    {
        receivedFlag = 0;

        float ppb = (unsigned int) (receivedCommandStack[4] * 256) + receivedCommandStack[5]; // bit 4: ppm high 8-bit; bit 5: ppm low 8-bit
        float ppm = ppb / 1000; // 1ppb = 1000ppm
        ze_value = ppm;
        return ppm;
    }
    else return 0;
}

float analogReadPPM() 
{
    float analogVoltage = analogRead(A0) / 1024.0 * VREF;
    float ppm = 3.125 * analogVoltage - 1.25; //linear relationship (0.4V for 0 ppm and 2V for 5ppm)

    if ( ppm < 0 ) 
    {
        ppm = 0;
    }
    else if ( ppm > 5 ) 
    {
        ppm = 5;
    }
    return ppm;
}


void ze08_setup() 
{
    mySerial.begin(9600, SERIAL_8N1, 16, 17);
}

bool ze08_loop() 
{
    float data = 0;
    data = ze08_PPM();
    if(data != 0)
    {
        Serial.print("ze08 value : ");
        Serial.println(ze_value);

        return true;
    }
    return false;
}
