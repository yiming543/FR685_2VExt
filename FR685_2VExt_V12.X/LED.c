#include "LED.h"
#include "mcc_generated_files/pin_manager.h"

#define LED_ON (1U)
#define LED_OFF (0U)

// 2. 【真正的 Private 狀態變數】僅佔用 6 Bytes RAM，外部完全無法直接修改
static uint8_t led_states[LED_COUNT] = {
    LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_OFF};

// 3. 內部硬體操作函式（加上 static 隱藏於此檔案內部）

static void POS_ON(void) {
  if (led_states[POS] == LED_OFF) {
    // LED1_SetHigh();
    POS_SetHigh();
    led_states[POS] = LED_ON;
  }
}

static void POS_OFF(void) {
  if (led_states[POS] != LED_OFF) {
    // LED1_SetLow();
    POS_SetLow();
    led_states[POS] = LED_OFF;
  }
}

static uint8_t LED_POS_IS_ON(void) {
  return led_states[POS];
}

static void DRL_ON(void) {
  if (led_states[DRL] == LED_OFF) {
    // LED2_SetHigh();
    DRL_SetHigh();
    led_states[DRL] = LED_ON;
  }
}

static void DRL_OFF(void) {
  if (led_states[DRL] != LED_OFF) {
    // LED2_SetLow();
    DRL_SetLow();
    led_states[DRL] = LED_OFF;
  }
}

static uint8_t LED_DRL_IS_ON(void) {
  return led_states[DRL];
}

static void LO_BEAM_ON(void) {
  if (led_states[LO_BEAM] == LED_OFF) {
    // LED3_SetHigh();
    LOBEAM_SetHigh();
    led_states[LO_BEAM] = LED_ON;
  }
}

static void LO_BEAM_OFF(void) {
  if (led_states[LO_BEAM] != LED_OFF) {
    // LED3_SetLow();
    LOBEAM_SetLow();
    led_states[LO_BEAM] = LED_OFF;
  }
}

static uint8_t LED_LO_BEAM_IS_ON(void) {
  return led_states[LO_BEAM];
}

static void HI_BEAM_ON(void) {
  if (led_states[HI_BEAM] == LED_OFF) {
    // LED4_SetHigh();
    HIBEAM_SetHigh();
    led_states[HI_BEAM] = LED_ON;
  }
}

static void HI_BEAM_OFF(void) {
  if (led_states[HI_BEAM] != LED_OFF) {
    // LED4_SetLow();
    HIBEAM_SetLow();
    led_states[HI_BEAM] = LED_OFF;
  }
}

static uint8_t LED_HI_BEAM_IS_ON(void) {
  return led_states[HI_BEAM];
}

static void TURN_LEFT_ON(void) {
  if (led_states[TURN_LEFT] == LED_OFF) {
    // LED5_SetHigh();
    TURN_LEFT_SetHigh();
    led_states[TURN_LEFT] = LED_ON;
  }
}

static void TURN_LEFT_OFF(void) {
  if (led_states[TURN_LEFT] != LED_OFF) {
    // LED5_SetLow();
    TURN_LEFT_SetLow();
    led_states[TURN_LEFT] = LED_OFF;
  }
}

static uint8_t LED_TURN_LEFT_IS_ON(void) {
  return led_states[TURN_LEFT];
}

static void TURN_RIGHT_ON(void) {
  if (led_states[TURN_RIGHT] == LED_OFF) {
    // LED6_SetHigh();
    TURN_RIGHT_SetHigh();
    led_states[TURN_RIGHT] = LED_ON;
  }
}

static void TURN_RIGHT_OFF(void) {
  if (led_states[TURN_RIGHT] != LED_OFF) {
    // LED6_SetLow();
    TURN_RIGHT_SetLow();
    led_states[TURN_RIGHT] = LED_OFF;
  }
}

static uint8_t LED_TURN_RIGHT_IS_ON(void) {
  return led_states[TURN_RIGHT];
}

// static void TURN_LEFT_RESPONSE_ON(void) {
//   if (led_states[TURN_LEFT_RESPONSE] == LED_OFF) {
//     // LED7_SetHigh();
//     led_states[TURN_LEFT_RESPONSE] = LED_ON;
//   }
// }

// static void TURN_LEFT_RESPONSE_OFF(void) {
//   if (led_states[TURN_LEFT_RESPONSE] != LED_OFF) {
//     // LED7_SetLow();
//     led_states[TURN_LEFT_RESPONSE] = LED_OFF;
//   }
// }

// static uint8_t LED_TURN_LEFT_RESPONSE_IS_ON(void) {
//   return led_states[TURN_LEFT_RESPONSE];
// }

// static void TURN_RIGHT_RESPONSE_ON(void) {
//   if (led_states[TURN_RIGHT_RESPONSE] == LED_OFF) {
//     // LED8_SetHigh();
//     led_states[TURN_RIGHT_RESPONSE] = LED_ON;
//   }
// }

// static void TURN_RIGHT_RESPONSE_OFF(void) {
//   if (led_states[TURN_RIGHT_RESPONSE] != LED_OFF) {
//     // LED8_SetLow();
//     led_states[TURN_RIGHT_RESPONSE] = LED_OFF;
//   }
// }

// static uint8_t LED_TURN_RIGHT_RESPONSE_IS_ON(void) {
//   return led_states[TURN_RIGHT_RESPONSE];
// }

// 4. 編譯期靜態初始化物件（存放於 Flash 唯讀區）
const LEDs_t led = {
    .pos = {.on = POS_ON, .off = POS_OFF, .is_on = LED_POS_IS_ON},
    .drl = {.on = DRL_ON, .off = DRL_OFF, .is_on = LED_DRL_IS_ON},
    .loBeam = {.on = LO_BEAM_ON, .off = LO_BEAM_OFF, .is_on = LED_LO_BEAM_IS_ON},
    .hiBeam = {.on = HI_BEAM_ON, .off = HI_BEAM_OFF, .is_on = LED_HI_BEAM_IS_ON},
    .turnLeft = {.on = TURN_LEFT_ON, .off = TURN_LEFT_OFF, .is_on = LED_TURN_LEFT_IS_ON},
    .turnRight = {.on = TURN_RIGHT_ON, .off = TURN_RIGHT_OFF, .is_on = LED_TURN_RIGHT_IS_ON}};
// .turnLeftResponse = {.on = TURN_LEFT_RESPONSE_ON, .off = TURN_LEFT_RESPONSE_OFF, .is_on = LED_TURN_LEFT_RESPONSE_IS_ON},
// .turnRightResponse = {.on = TURN_RIGHT_RESPONSE_ON, .off = TURN_RIGHT_RESPONSE_OFF, .is_on = LED_TURN_RIGHT_RESPONSE_IS_ON}};

// 5. 開機硬體狀態同步函式

void LED_Init(void) {
  led.pos.off();
  led.drl.off();
  led.loBeam.off();
  led.hiBeam.off();
  led.turnLeft.off();
  led.turnRight.off();
  // led.turnLeftResponse.off();
  // led.turnRightResponse.off();
  // 消除never call警告
  uint8_t tmp_pos = LED_POS_IS_ON();
  uint8_t tmp_drl = LED_DRL_IS_ON();
  uint8_t tmp_loBeam = LED_LO_BEAM_IS_ON();
  uint8_t tmp_hiBeam = LED_HI_BEAM_IS_ON();
  uint8_t tmp_turnLeft = LED_TURN_LEFT_IS_ON();
  uint8_t tmp_turnRight = LED_TURN_RIGHT_IS_ON();
  // uint8_t tmp_turnLeftRespone = LED_TURN_LEFT_RESPONSE_IS_ON();
  // uint8_t tmp_turnRightRespone = LED_TURN_RIGHT_RESPONSE_IS_ON();
}

void loBeamOn_drlOff_PosOn(void) {
  led.loBeam.on();
  led.drl.off();
  led.pos.on();
}

void loBeamOff_drlOff_PosOff(void) {
  led.loBeam.off();
  led.drl.off();
  led.pos.off();
}

void loBeamOff_drlOn_PosOff(void) {
  led.loBeam.off();
  led.drl.on();
  led.pos.off();
}

void loBeamOff_drlOff_PosOn(void) {
  led.loBeam.off();
  led.drl.off();
  led.pos.on();
}

void drlOff_PosOff(void) {
  led.drl.off();
  led.pos.off();
}

// void drlOn_PosOff(void) {
//   led.drl.on();
//   led.pos.off();
// }

void drlOff_PosOn(void) {
  led.drl.off();
  led.pos.on();
}