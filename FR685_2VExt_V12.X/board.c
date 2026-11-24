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

#include "LED.h"
#include "Warning_ignored.h"
#include "mcc_generated_files/pin_manager.h"
#include "uart_rx_guard.h"
#include <stdint.h>
extern void LIN_stopTimer(void);
extern bool LIN_signalTimeoutOccurred(void);

// 回饋信號
extern uint8_t ID_10_Data[8];
extern void change_ID(void);
#define R_SIDE (0U)
#define L_SIDE (1U)
#define HI_BEAM_MASK (0xC0U)
uint8_t fLamp_RL_Side = 0U; // 0:R side 1:L side

// 左方向燈 data[1]=0x10
// 右方向燈 data[1]=0x20
// 警示燈   data[1]=0x38
// 01 08 人離開一段距離 鑰匙靠近送出11 0D，但還沒解鎖,這時要有鑰匙+手放把手上會解鎖,但不會送出11 09
// 01 08 人沒離開,這時鑰匙+手放把手上會解鎖,送出11 09
// 玩太多次01 0D就不會出現了,要啟動引擎再熄火才會再出現01 0D.
// 11 08 測試方式,上鎖01 08 解鎖 11 09 鑰匙靠近11 0D 解鎖 11 09 等待一段時間11 08 LED OFF

// D2
typedef enum {
  OFF_NIGHT_P = 0x31,    // 0b0011 0001 47
  OFF_NIGHT_N = 0x71,    // 0b0111 0001 113
  OFF_DAY_P = 0x29,      // 0b0010 1001 41
  OFF_DAY_N = 0x69,      // 0b0110 1001 105
  DRIVER_NIGHT_P = 0x32, // 0b0011 0010 50
  DRIVER_NIGHT_N = 0x72, // 0b0111 0010 114
  DRIVER_DAY_P = 0x2A,   // 0b0010 1010 42
  DRIVER_DAY_N = 0x6A,   // 0b0110 1010 106
  AUTO_NIGHT_P = 0xB4,   // 0b1011 0100 180 74? 34? 切換白天/晚上的光源再切換P/N 會出現
  AUTO_NIGHT_N = 0xB4,   // 0b1011 0100 180
  AUTO_DAY_P = 0x2C,     // 0b0010 1100 44
  AUTO_DAY_N = 0x6C,     // 0b0110 1100 108
  LOBEAM_NIGHT_P = 0x33, // 0b0011 0011 51
  LOBEAM_NIGHT_N = 0x33, // 0b0011 0011 51
  LOBEAM_DAY_P = 0x2B,   // 0b0010 1011 43
  LOBEAM_DAY_N = 0x2B,   // 0b0010 1011 43
} ControlCode;

void feedbacksignal(uint8_t *data) {
  ID_10_Data[1] = data[1] & 0x07U;
}

void dataSetLed(uint8_t *tempRxData) {
  if (tempRxData[0] == 0x24U) {
    switch (tempRxData[2]) {
    case OFF_NIGHT_P:
      loBeamOff_drlOff_PosOff();
      break;

    case OFF_NIGHT_N:
      loBeamOff_drlOn_PosOff();
      break;

    case OFF_DAY_P:
      loBeamOff_drlOff_PosOff();
      break;

    case OFF_DAY_N:
      loBeamOff_drlOn_PosOff();
      break;

    case DRIVER_NIGHT_P:
      loBeamOff_drlOff_PosOn();
      break;

    case DRIVER_NIGHT_N:
      loBeamOff_drlOn_PosOff();
      break;

    case DRIVER_DAY_P:
      loBeamOff_drlOff_PosOn();
      break;

    case DRIVER_DAY_N:
      loBeamOff_drlOn_PosOff();
      break;

    case AUTO_NIGHT_P:
      // case AUTO_NIGHT_N:
      loBeamOn_drlOff_PosOn();
      break;

    case AUTO_DAY_P:
      loBeamOff_drlOff_PosOff();
      break;

    case AUTO_DAY_N:
      loBeamOff_drlOn_PosOff();
      break;

    case LOBEAM_NIGHT_P:
    case LOBEAM_DAY_P:
      // case LOBEAM_NIGHT_N:
      // case LOBEAM_DAY_N:
      loBeamOn_drlOff_PosOn();
      break;

    default:
      // 無法識別的資料，維持原本的狀態
      break;
    }

    // 只有tempRxData[0]=024才打開hiBeam
    if ((tempRxData[1] & HI_BEAM_MASK) != 0U) {
      // hiBeam or overTake
      led.hiBeam.on();
    }

  } else if ((tempRxData[0] == 0x01U) && (tempRxData[1] == 0x08U)) // lock
  {
    drlOff_PosOff();
  } else if ((tempRxData[0] == 0x11U) && (tempRxData[1] == 0x08U)) // unlock LED off
  {                                                                // unlock feedback
    drlOff_PosOff();
  } else if ((tempRxData[0] == 0x11U) && (tempRxData[1] == 0x09U)) // unlock
  {                                                                // unlock feedback
    drlOff_PosOn();
  } else if ((tempRxData[0] == 0x11U) && (tempRxData[1] == 0x0AU)) // unlock
  {                                                                // unlock feedback engine off
    drlOff_PosOn();
  } else if ((tempRxData[0] == 0x11U) && (tempRxData[1] == 0x0DU)) // unlock 鑰匙靠近
  {                                                                // unlock feedback unknow
    drlOff_PosOn();
  } else if ((tempRxData[0] == 0x11U) && (tempRxData[1] == 0x0BU)) // unlock
  {                                                                // unlock feedback door open
    drlOff_PosOn();
  } else if ((tempRxData[0] == 0x11U) && (tempRxData[1] == 0x0CU)) // unlock
  {                                                                // unlock feedback door close
    drlOff_PosOn();
  } else if ((tempRxData[0] == 0x28U) && (tempRxData[1] == 0x08U)) // unlock
  {                                                                // unlock feedback engine start
    drlOff_PosOff();
  } else if ((tempRxData[0] == 0x31U) && (tempRxData[1] == 0x0AU)) // 熄火1
  {
    drlOff_PosOn();
  } else if ((tempRxData[0] == 0x31U) && (tempRxData[1] == 0x0BU)) // 熄火2 開門
  {                                                                // unlock feedback door open
  } else if ((tempRxData[0] == 0x31U) && (tempRxData[1] == 0x0CU)) // 熄火3 關門
  {                                                                // unlock feedback door close
  } else if ((tempRxData[0] == 0x31U) && (tempRxData[1] == 0x08U)) // 熄火4
  {                                                                // LED OFF
    drlOff_PosOff();
  } else {
    // 無法識別的資料，維持原本的狀態
  }

  // 不管tempRxData[1]的狀態
  if ((tempRxData[1] & HI_BEAM_MASK) == 0U) {
    led.hiBeam.off();
  }
}

void board_init(void) {
  LED_Init();
  Clear_No_Call_Warning();
  UART_RX_GuardInitialize();
  // 左邊燈具選擇 RC5
  // 0:R side 1:L side
  fLamp_RL_Side = (!!Lamp_R_EN_PORT);
  if (fLamp_RL_Side == R_SIDE) {
    change_ID();
  }
}

void board_updata(void) {
  if (UART_RX_GuardRecoverOverflow()) {
    /*
     * 讓下一次 LIN_handler() 立即進入 LIN_RX_ERROR，
     * 放棄目前不完整的 LIN frame。
     */
    LIN_stopTimer();
  }

  if (LIN_signalTimeoutOccurred()) {
      loBeamOff_drlOff_PosOn();
    // HIBEAM_LAT = 0; // hibeam or overtake
    // P2亮,但P2是電源直接給電.
  }
}