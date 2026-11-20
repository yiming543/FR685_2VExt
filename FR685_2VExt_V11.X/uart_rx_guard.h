#ifndef UART_RX_GUARD_H
#define UART_RX_GUARD_H

#include <stdbool.h>

void UART_RX_GuardInitialize(void);
bool UART_RX_GuardRecoverOverflow(void);

#endif