/*
 * File:   Warning_ignored.c
 * Author: T00904
 *
 * Created on November 13, 2026, 10:30 AM
 */

#include <stdint.h>

//for Clear_No_Call_Warning
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/tmr0.h"
#include "mcc_generated_files/eusart.h"
#include "mcc_generated_files/tmr2.h"


#include "LED.h"
extern void LIN_stopPeriod(void);

// 消除未呼叫警告 假裝有使用這些函數

void Clear_No_Call_Warning(void) {
    uint8_t i = 0U;
    if (i == 1U) {
        PIN_MANAGER_IOC();
    } else if (i == 2U) {
        uint8_t tmp_tmr0 = TMR0_ReadTimer();
        TMR0_Reload();
    } else if (i == 3U) {
        LIN_stopPeriod();
    } else if (i == 4U) {
        bool tmp_bit0 = EUSART_is_tx_ready();
        bool tmp_bit1 = EUSART_is_tx_done();
        eusart_status_t tmp_status = EUSART_get_last_status();
    } else if (i == 5U) {
//        led.pos.is_on();
//        led.drl.is_on();
//        led.loBeam.is_on();
//        led.hiBeam.is_on();
//        led.turnLeft.is_on();
//        led.turnRight.is_on();
    } else if (i == 6U) {
        TMR2_StartTimer();
        TMR2_StopTimer();
        uint8_t tmp_tmr2 = TMR2_ReadTimer();
        TMR2_WriteTimer(0U);
        TMR2_LoadPeriodRegister(0U);

    } else {

    }
}