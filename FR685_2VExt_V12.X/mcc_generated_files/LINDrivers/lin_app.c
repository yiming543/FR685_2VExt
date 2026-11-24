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
#include "lin_slave.h"
#include "../../board.h"
#include <stdint.h>

typedef enum {
    ID_00 = 0x0,
    ID_01 = 0x01,            
    ID_10 = 0x10,
    ID_18 = 0x18
} lin_cmd_t;

uint8_t ID_00_Data[8];
uint8_t ID_01_Data[8];
uint8_t ID_10_Data[8] = {0x10, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

lin_rx_cmd_t scheduleTable[] = {
    // Command, Type, TX/RX Length, Data Address
    {ID_00, RECEIVE, 8, ID_00_Data},
    {ID_01, RECEIVE, 8, ID_01_Data},
    {ID_10, TRANSMIT, 8, ID_10_Data},
};
#define TABLE_SIZE (sizeof(scheduleTable) / sizeof(lin_rx_cmd_t))


void change_ID(void){
    scheduleTable[2].cmd = 0x18U;
}

void LIN_Slave_Initialize(void){
    LIN_init(TABLE_SIZE, scheduleTable, processLIN);   
}

void processLIN(void){
    uint8_t tempRxData[8];
    uint8_t cmd;

    cmd = LIN_getPacket(tempRxData);
    switch(cmd){
        case ID_00:
            feedbacksignal(tempRxData);
            break;
        case ID_01:
            dataSetLed(tempRxData);
            break;
        case ID_10:
            break;
        case ID_18:
            break;
        default:
            break;
    }
}