#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

#define SERVICE_UUID              "fb1e4001-54ae-4a28-9f74-dfccb248601d"
#define CHARACTERISTIC_UUID_RX    "fb1e4002-54ae-4a28-9f74-dfccb248601d"
#define CHARACTERISTIC_UUID_TX    "fb1e4003-54ae-4a28-9f74-dfccb248601d"

static BLECharacteristic* pCharacteristicTX;
static BLECharacteristic* pCharacteristicRX;

static bool deviceConnected = false;

void BLE_Send_Msg(char* msg)
{
    pCharacteristicTX->setValue(msg);
    pCharacteristicTX->notify();
}

void initBLE();
class MyServerCallbacks: public BLEServerCallbacks 
{
    void onConnect(BLEServer* pServer) 
    {
        deviceConnected = true;
        // Serial.print(curTilt);
        // Serial.print(", ");
        // Serial.print(curRoll);
        // Serial.print(", ");
        // Serial.println("Connected");
    }
    void onDisconnect(BLEServer* pServer) 
    {
        deviceConnected = false;
        // Serial.print(curTilt);
        // Serial.print(", ");
        // Serial.print(curRoll);
        // Serial.print(", ");
        // Serial.println("Disconnected");
        BLEDevice::startAdvertising();
    }
};



#define DELIMITER ","
//#define CMD_BUF_SIZE      256
//#define PARAM_BUF_SIZE    256
//#define PARAM_CMD

class MyCallbacks: public BLECharacteristicCallbacks 
{
    void onNotify(BLECharacteristic *pCharacteristic) 
    {
        uint8_t* pData;
        std::string value = pCharacteristic->getValue();
        int len = value.length();
        pData = pCharacteristic->getData();
        if (pData != NULL) 
        {
            Serial.print("TX : ");
            Serial.println((char*)pData);            
        }
    }

    void onWrite(BLECharacteristic *pCharacteristic) 
    {
        char* token;
        char* cmd;
        char* param;
        String svalue;
        
        uint8_t* pData;
        std::string value = pCharacteristic->getValue();
        int len = value.length();
        pData = pCharacteristic->getData();

        if (pData != NULL) 
        {
//            BLE_Send_Msg((char*)pData);            
            
            // if(strcmp((char *)pData, CMD_FIND_MODE) == 0)
            // {
            //     if(deviceConnected)
            //     {
            //         if(find_auto)
            //         {
            //             blind_state = 0;
            //             find_auto = false;
            //             Serial.print(curTilt);
            //             Serial.print(", ");
            //             Serial.print(curRoll);
            //             Serial.print(", ");
            //             Serial.println("Solar Find Mode End");
            //             BLE_Send_Msg("Solar Find Mode End");
            //         }
            //         else
            //         {
            //             blind_state = 10;
            //             find_auto = true;
            //             Serial.print(curTilt);
            //             Serial.print(", ");
            //             Serial.print(curRoll);
            //             Serial.print(", ");
            //             Serial.println("Solar Find Mode Start");
            //             BLE_Send_Msg("Solar Find Mode Start");
            //         }
            //     }
            // }
            
            // // Line Led
            // else if(strcmp((char *)pData, CMD_LINE_LED_OFF) == 0)
            // {
            //     Serial.println("Line Led Off");

            //     if(deviceConnected)
            //     {
            //         led_state = LED_STATE_OFF;
            //         led_on = true;
            //         BLE_Send_Msg("LINE LED OFF");
            //     }
            // }
            // else if(strcmp((char *)pData, CMD_LINE_LED_RAINBOW) == 0)
            // {
            //     Serial.println("Line Led Rainbow");

            //     if(deviceConnected)
            //     {
            //         led_state = LED_STATE_RAINBOW;
            //         BLE_Send_Msg("LINE LED RAINBOW");
            //     }
            // }
            // else if(strcmp((char *)pData, CMD_LINE_LED_BLUE) == 0)
            // {
            //     Serial.println("Line Led Blue");

            //     if(deviceConnected)
            //     {
            //         led_state = LED_STATE_BLUE;
            //         led_on = true;
            //         BLE_Send_Msg("LINE LED BLUE");
            //     }
            // }
            // else if(strcmp((char *)pData, CMD_LINE_LED_GREEN) == 0)
            // {
            //     Serial.println("Line Led Green");

            //     if(deviceConnected)
            //     {
            //         led_state = LED_STATE_GREEN;
            //         led_on = true;
            //         BLE_Send_Msg("LINE LED GREEN");
            //     }
            // }
            // else if(strcmp((char *)pData, CMD_LINE_LED_RED) == 0)
            // {
            //     Serial.println("Line Led Red");

            //     if(deviceConnected)
            //     {
            //         led_state = LED_STATE_RED;
            //         led_on = true;
            //         BLE_Send_Msg("LINE LED RED");
            //     }
            // }
            // else if(strcmp((char *)pData, CMD_LINE_LED_BLUE_TOGGLE) == 0)
            // {
            //     Serial.println("Line Led Blue Toggle");

            //     if(deviceConnected)
            //     {
            //         led_state = LED_STATE_TOGGLE_B;
            //         led_on = true;
            //         BLE_Send_Msg("LINE LED TOGGLE BLUE");
            //     }
            // }
            // else if(strcmp((char *)pData, CMD_LINE_LED_GREEN_TOGGLE) == 0)
            // {
            //     Serial.println("Line Led Green Toggle");

            //     if(deviceConnected)
            //     {
            //         led_state = LED_STATE_TOGGLE_G;
            //         led_on = true;
            //         BLE_Send_Msg("LINE LED TOGGLE GREEN");
            //     }
            // }
            // else if(strcmp((char *)pData, CMD_LINE_LED_RED_TOGGLE) == 0)
            // {
            //     Serial.println("Line Led Red Toggle");

            //     if(deviceConnected)
            //     {
            //         led_state = LED_STATE_TOGGLE_R;
            //         led_on = true;
            //         BLE_Send_Msg("LINE LED TOGGLE RED");
            //     }
            // }
            // else if(strcmp((char *)pData, CMD_SERVO_OPEN) == 0)
            // {
            //     Serial.print(curTilt);
            //     Serial.print(", ");
            //     Serial.print(curRoll);
            //     Serial.print(", ");
            //     Serial.println("Servo Motor Open");

            //     if(deviceConnected)
            //     {
            //         servo_act = true;
            //         target_angle = start_angle;
            //         BLE_Send_Msg("Servo Start");
            //     }
            // }
            // else if(strcmp((char *)pData, CMD_SERVO_CLOSE) == 0)
            // {
            //     Serial.print(curTilt);
            //     Serial.print(", ");
            //     Serial.print(curRoll);
            //     Serial.print(", ");
            //     Serial.println("Servo Motor Close");

            //     if(deviceConnected)
            //     {
            //         servo_act = true;
            //         target_angle = end_angle;
            //         BLE_Send_Msg("Servo End");
            //     }
            // }

            // Step Debug
//            else if(strcmp((char *)pData, CMD_DRAW_POS_INIT) == 0)
//            {
//                Serial.println("Draw Step Position Init");
//
//                if(deviceConnected)
//                {
//                    Step_Pos_Init(0);
//                }
//            }
//            else if(strcmp((char *)pData, CMD_ROLL_POS_INIT) == 0)
//            {
//                Serial.println("Roll Step Position Init");
//
//                if(deviceConnected)
//                {
//                    Step_Pos_Init(2);
//                }
//            }
//            else if(strcmp((char *)pData, CMD_TILT_POS_INIT) == 0)
//            {
//                Serial.println("Tilt Step Position Init");
//
//                if(deviceConnected)
//                {
//                    Step_Pos_Init(1);
//                }
//            }

//             else if(strcmp((char *)pData, CMD_DRAW_FOLD) == 0)
//             {
//                 Serial.print(curTilt);
//                 Serial.print(", ");
//                 Serial.print(curRoll);
//                 Serial.print(", ");
//                 Serial.println("Draw Step Folding");

//                 if(deviceConnected)
//                 {
//                     target_angle = start_angle;
//                     servo_act = true;
//                     blind_state = 3;
//                 }
//             }
//             else if(strcmp((char *)pData, CMD_DRAW_UNFOLD) == 0)
//             {
//                 Serial.print(curTilt);
//                 Serial.print(", ");
//                 Serial.print(curRoll);
//                 Serial.print(", ");
//                 Serial.println("Draw Step UnFolding");

//                 if(deviceConnected)
//                 {
//                     blind_state = 2;
//                 }
//             }
//             else if(strcmp((char *)pData, CMD_TILT_OUT) == 0)
//             {
//                 Serial.print(curTilt);
//                 Serial.print(", ");
//                 Serial.print(curRoll);
//                 Serial.print(", ");
//                 Serial.println("Tilt Step Out");

//                 if(deviceConnected)
//                 {
//                     blind_state = 6;
//                 }
//             }
//             else if(strcmp((char *)pData, CMD_TILT_IN) == 0)
//             {
//                 Serial.print(curTilt);
//                 Serial.print(", ");
//                 Serial.print(curRoll);
//                 Serial.print(", ");
//                 Serial.println("Tilt Step In");

//                 if(deviceConnected)
//                 {
//                     blind_state = 5;
//                 }
//             }
//             else if(strcmp((char *)pData, CMD_TILT_CENTER) == 0)
//             {
//                 Serial.print(curTilt);
//                 Serial.print(", ");
//                 Serial.print(curRoll);
//                 Serial.print(", ");
//                 Serial.println("Tilt Step Center");

//                 if(deviceConnected)
//                 {
//                     blind_state = 7;
//                 }
//             }
//             else if(strcmp((char *)pData, CMD_TILT_AUTO) == 0)
//             {
//                 Serial.print(curTilt);
//                 Serial.print(", ");
//                 Serial.print(curRoll);
//                 Serial.print(", ");
//                 Serial.println("Tilt Step Find Center");

//                 if(deviceConnected)
//                 {
//                     blind_state = 5;
//                     tilt_auto = true;
//                 }
//             }
            
//             else if(strcmp((char *)pData, CMD_ROLL_RIGHT) == 0)
//             {
//                 Serial.print(curTilt);
//                 Serial.print(", ");
//                 Serial.print(curRoll);
//                 Serial.print(", ");
//                 Serial.println("Roll Step Right");

//                 if(deviceConnected)
//                 {
//                     blind_state = 9;
//                     roll_auto = false;
//                 }
//             }
//             else if(strcmp((char *)pData, CMD_ROLL_LEFT) == 0)
//             {
//                 Serial.print(curTilt);
//                 Serial.print(", ");
//                 Serial.print(curRoll);
//                 Serial.print(", ");
//                 Serial.println("Roll Step Left");

//                 if(deviceConnected)
//                 {
//                     blind_state = 8;
//                     roll_auto = false;
//                 }
//             }
//             else if(strcmp((char *)pData, CMD_ROLL_AUTO) == 0)
//             {
//                 Serial.print(curTilt);
//                 Serial.print(", ");
//                 Serial.print(curRoll);
//                 Serial.print(", ");
//                 Serial.println("Roll Step Auto");

//                 if(deviceConnected)
//                 {
// //                    step_Roll_state = 1;
//                     roll_auto = true;
//                 }
//             }
//             else if(strcmp((char *)pData, CMD_ROLL_RIGHT90) == 0)
//             {
//                 Serial.print(curTilt);
//                 Serial.print(", ");
//                 Serial.print(curRoll);
//                 Serial.print(", ");
//                 Serial.println("Roll Step RIght90");

//                 if(deviceConnected)
//                 {
//                     blind_state = 30;
// //                    start_Roll_Pos = Current_Position(TILT);
//                 }
//             }
//             else if(strcmp((char *)pData, CMD_ROLL_LEFT90) == 0)
//             {
//                 Serial.print(curTilt);
//                 Serial.print(", ");
//                 Serial.print(curRoll);
//                 Serial.print(", ");
//                 Serial.println("Roll Step Left90");

//                 if(deviceConnected)
//                 {
// //                    step_Roll_state = 20;
// //                    start_Roll_Pos = Current_Position(TILT);
//                 }
//             }
            
//             else if(strcmp((char *)pData, CMD_STEP_STOP) == 0)
//             {
//                 if(deviceConnected)
//                 {
//                     blind_state = 0;
//                     pos_save = true;
//                 }
//             }

//            else if(strcmp((char *)pData, CMD_STEP_POS) == 0)
//            {
//                Serial.println("Step Position");
//
//                if(deviceConnected)
//                {
//                    Serial.print("Draw : ");
//                    Serial.print(stepDraw.currentPosition());
//                    Serial.print(", ");
//                    Serial.print("Tilt : ");
//                    Serial.print(stepTilt.currentPosition());
//                    Serial.print(", ");
//                    Serial.print("Roll : ");
//                    Serial.println(stepRoll.currentPosition());
//                }
//            }
            
            // else
            // {
            //     token = strtok((char *)pData, DELIMITER);
            //     if(token != NULL) 
            //     {
            //         if(strcmp((char *)pData, CMD_LINE_LED_BRIGHT) == 0)
            //         {
            //             token = strtok(NULL, "");
            //             if(token != NULL) 
            //             {    
            //                 svalue = String(token);
            //                 led_bright = svalue.toInt();
            //                 led_state = LED_BRIGHT_CHANGE;
            //                 BLE_Send_Msg("LINE LED BRIGHT CHANGE");
            //             }
            //         }                    
            //     }
            //     Serial.print(curTilt);
            //     Serial.print(", ");
            //     Serial.print(curRoll);
            //     Serial.print(", ");
            //     Serial.print("RX : ");
            //     Serial.println((char*)pData);
            // }
        }
    }
};

void initBLE()
{
    BLEDevice::init("GPS_Test");
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    BLEService *pService = pServer->createService(SERVICE_UUID);
    pCharacteristicTX = pService->createCharacteristic(CHARACTERISTIC_UUID_TX, BLECharacteristic::PROPERTY_NOTIFY );
    pCharacteristicRX = pService->createCharacteristic(CHARACTERISTIC_UUID_RX, BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_WRITE_NR);
    pCharacteristicRX->setCallbacks(new MyCallbacks());
    pCharacteristicTX->setCallbacks(new MyCallbacks());
    pCharacteristicTX->addDescriptor(new BLE2902());
    pCharacteristicTX->setNotifyProperty(true);
    pService->start();

    // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
  
    Serial.println("Characteristic defined! Now you can read it in your phone!");
}

/******************************************************************/
/****************             Serial         ****************/
/******************************************************************/

#define STX   '?'
#define ETX1  0x0D
#define ETX2  0x0A

int com_state = 0;
int com_size = 0;
char com_read[256];
char com_cmd[256];
char com_para[256];

extern int led_state;

#define PCMD_FWV        "FWV"
#define PCMD_LED        "LED"

#define FWV   "FWV,Solar Louver Blind V0.1"

int para_num = 0;
void ExcuteCommand(char* cmd, char* para)
{
    if(strcmp((const char*)cmd, PCMD_FWV) == 0)
    {
        Serial.println(FWV);
    }
    else if(strcmp((const char*)cmd, PCMD_LED) == 0)
    {
        if(para == "")
        {
            Serial.println("Input Para");
            return;
        }
        para_num = atoi(para);
        led_state = para_num;
        Serial.print(PCMD_LED);
        Serial.print(",");
        Serial.println(led_state);
    }
//    else if(strcmp((const char*)cmd, PCMD_FAN) == 0)
//    {
//        if(strcmp((const char*)para, PARA_ON) == 0)
//        {
//            fan_state = true;
//            Serial.println("FAN ON");
//        }
//        else if(strcmp((const char*)para, PARA_OFF) == 0)
//        {
//            fan_state = false;
//            Serial.println("FAN OFF");
//        }
//    }    
}

bool PacketAnalysis(char* read)
{
    char* token;

    for(int i = 0; i < 256; i++)
    {
        com_para[i] = 0;
    }
    
    token = strtok((char*)read, DELIMITER);

    if(token != NULL)
    {
        if(strlen(token) < 256)
        {
            sprintf((char*)com_cmd, "%s", token);
        }
        else
        {
            
        }

        token = strtok(NULL, "");
        if(token != NULL)
        {
            sprintf((char*)com_para, "%s", token);
        }
        return true;
    }
    return false;
}
