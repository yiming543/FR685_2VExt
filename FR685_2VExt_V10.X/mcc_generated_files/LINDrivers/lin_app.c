/**
  LIN Slave Application
	
  Company:
    Microchip Technology Inc.

  File Name:
    lin_app.c

  Summary:
    LIN Slave Application

  Description:
    This source file provides the interface between the user and 
    the LIN drivers.

 */

#include "lin_app.h"
#include "../../lamp.h"
#include <stdint.h>
void LIN_Slave_Initialize(void){
    LIN_init(TABLE_SIZE, scheduleTable, processLIN);   
}

void processLIN(void){
    uint8_t tempRxData[8];
    uint8_t cmd;

    cmd = LIN_getPacket(tempRxData);
    if(cmd == ID_00){
        NOP();
        NOP();
        NOP();
    }
    switch(cmd){
        case ID_00:
            feedbacksignal(tempRxData);
            break;
        case ID_01:
            lamp(tempRxData);
            break;
        case ID_10:
            break;
            case ID_18:
            break;
        default:
            break;
    }
}