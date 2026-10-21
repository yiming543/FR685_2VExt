#include "uart_rx_guard.h"

#include "mcc_generated_files/eusart.h"

#include <stdbool.h>
#include <stdint.h>
#include <xc.h>

/*
 * 必須與 MCC 產生的 EUSART1_RX_BUFFER_SIZE 相同。
 * 目前 eusart1.c 設定為 8。
 */
#define UART_RX_BUFFER_CAPACITY 8U

static volatile bool uartRxOverflow = false;

static void UART_RX_GuardISR(void);

/*
 * 必須在 EUSART1_Initialize() 之後、開啟全域中斷之前呼叫。
 */
void UART_RX_GuardInitialize(void)
{
    uartRxOverflow = false;

    /*
     * 使用 MCC 提供的 callback API，
     * 將原本的 RX ISR 換成自訂 wrapper。
     */
    EUSART_SetRxInterruptHandler(UART_RX_GuardISR);
}

static void UART_RX_GuardISR(void)
{
    /*
     * overflow 發生後，在主程式完成復原前，
     * 後續收到的資料全部丟棄。
     */
    if (uartRxOverflow ||
        (eusartRxCount >= UART_RX_BUFFER_CAPACITY))
    {
        uint8_t discardedData = RCREG;
        (void)discardedData;

        uartRxOverflow = true;

        if (RCSTAbits.OERR != 0U)
        {
            RCSTAbits.CREN = 0U;
            RCSTAbits.CREN = 1U;
        }

        return;
    }

    /*
     * Buffer 尚未滿，交回 MCC 原本的 ISR 處理：
     * - FERR/OERR
     * - 寫入 RX buffer
     * - 更新 head 與 count
     */
    EUSART_Receive_ISR();
}

bool UART_RX_GuardRecoverOverflow(void)
{
    bool rxInterruptWasEnabled;

    if (!uartRxOverflow)
    {
        return false;
    }

    /*
     * uartRxOverflow 為 true 時，自訂 ISR 會丟棄所有新資料，
     * 因此可以安全清空 MCC ring buffer。
     */
    while (EUSART_is_rx_ready())
    {
        (void)EUSART_Read();
    }

    rxInterruptWasEnabled = (PIE1bits.RCIE != 0U);
    PIE1bits.RCIE = 0U;

    if (RCSTAbits.OERR != 0U)
    {
        RCSTAbits.CREN = 0U;
        RCSTAbits.CREN = 1U;
    }

    /*
     * 清除 UART hardware FIFO 中可能殘留的資料。
     */
    while (PIR1bits.RCIF != 0U)
    {
        uint8_t discardedData = RCREG;
        (void)discardedData;
    }

    uartRxOverflow = false;

    PIE1bits.RCIE = rxInterruptWasEnabled ? 1U : 0U;

    return true;
}