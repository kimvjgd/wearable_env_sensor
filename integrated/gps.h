#include <TinyGPSPlus.h>
#include "ze08.h"
#include "Time.h"
#include "myBLE.h"

/*
   This sample sketch demonstrates the normal use of a TinyGPSPlus (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int RXPin = 16, TXPin = 17;
static const uint32_t GPSBaud = 9600;

char lat_list[30];
char lng_list[30];
char hour_list[10];

// The TinyGPSPlus object
TinyGPSPlus gps;

extern double gps_lat_value;
extern double gps_lng_value;

const int UTC_offset = 9;     // For Repulic of Korea

// int new_hour;asdasdasdsadsadsada
bool displayInfo()
{ 
    // Serial.println("###############################");
    // Serial.print(gps.time);
    // Serial.print(gps.time());
    // Serial.println("###############################");
    int n_year;
    byte n_month;
    byte n_day;
    byte n_hour;
    byte n_minute;
    String str;
    char data[256];
    
    if (gps.location.isValid())
    {
      gps_lat_value = gps.location.lat();
      gps_lng_value = gps.location.lng();
      
      Serial.print("gps lat : ");
      Serial.print(gps_lat_value);
            
      str = "gps_lat:" + String(gps_lat_value);
      str.toCharArray(data, str.length() + 1);
      
      BLE_Send_Msg(data);
      Serial.print("gps lng : ");
      Serial.println(lat_list);

      str = "gps_lng:" + String(gps_lng_value);
      str.toCharArray(data, str.length() + 1);
      BLE_Send_Msg(data);
      // time loading
        n_year = gps.date.year();
        n_month = byte(gps.date.month());
        n_day = byte(gps.date.day());
      
        n_hour = byte(gps.time.hour());
        n_minute = byte(gps.time.minute());
        setTime(n_hour, n_minute, 0, n_day, n_month, n_year);
        adjustTime(UTC_offset * SECS_PER_HOUR);
        
        // if (gps.time.hour() < 10) Serial.print(F("0"));
        // Serial.print(gps.time.hour());
        if (hour() < 10) Serial.print(F("0"));
        Serial.print(hour());
        Serial.print(F(":"));
        if (gps.time.minute() < 10) Serial.print(F("0"));
        Serial.println(gps.time.minute());

      return true;
    }
    else
    {
      

          n_year = gps.date.year();
          n_month = byte(gps.date.month());
          n_day = byte(gps.date.day());

          n_hour = byte(gps.time.hour());
          n_minute = byte(gps.time.minute());
          setTime(n_hour, n_minute, 0, n_day, n_month, n_year);
          adjustTime(UTC_offset * SECS_PER_HOUR);
        
          // if (gps.time.hour() < 10) Serial.print(F("0"));
          // Serial.print(gps.time.hour());
          if (hour() < 10) Serial.print(F("0"));
          Serial.print(hour());
          Serial.print(F(":"));
          if (gps.time.minute() < 10) Serial.print(F("0"));
          Serial.println(gps.time.minute());
          
          str = "Hour : " + String(hour());
          str.toCharArray(data, str.length() + 1);
          BLE_Send_Msg(data);
      

        return false;
    }
}

extern int mux_trigger;
bool gps_loop() 
{   
  if(mySerial.available())
  {
    if (gps.encode(mySerial.read()))
    {
        Serial.print("GPS info : ");
        displayInfo();

        return true;
    }
  }

    return false;
}
