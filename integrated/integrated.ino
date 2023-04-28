#pragma once

// #include "sps30.h"
// #include "svm30.h"
// #include "ze08.h"
#include "gps.h"
//#include <SimpleTimer.h>
//
//SimpleTimer timer1;
//SimpleTimer timer2;
//SimpleTimer timer3;

const byte sel0 = 4;
const byte sel1 = 27;

float ze_value = 0;
float svm_value = 0;
float sps_value = 0;
double gps_lat_value = 0;
double gps_lng_value = 0;

int mux_trigger = 1; // 0 for ze08 , 1 for gps

void mux_change(int m)
{
    if(m==0)
    {           // 0 for ze08
        digitalWrite(sel1, 0);
    }
    else 
    {             // 1 for gps
        digitalWrite(sel1, 1);
    }
}


/*
m_sel0 = 4
m_sel1 = 27
*/
void setup() 
{
    pinMode(sel0, OUTPUT);
    pinMode(sel1, OUTPUT);
    digitalWrite(sel0, 1);
    digitalWrite(sel1, 1);      // 0 for ze08 , 1 for gps
  
    Serial.begin(115200);
    
    initBLE();
    
    // sps30_setup();
    // svm30_setup();
    ze08_setup();

    Serial.println("GPS Test");
}

// void sps_svm() 
// {
//     sps30_loop();
//     delay(100);
//     svm30_loop();
//     delay(100);
// }

void loop() 
{   
    // sps_svm();
    // mux_change(1);  // GPS
    // delay(100);
    // while(!gps_loop());
    
    // mux_change(0);  // ZE08
    // while(!ze08_loop());

    // gps 시간을 맞추기 위한 임시 코드
    gps_loop();
}
