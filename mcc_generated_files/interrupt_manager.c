#include <xc.h>
#include "interrupt_manager.h"
#include "../ms_timer.h"

void INTERRUPT_Initialize(void) {
    //    UERI: U2E - UART2 Error
    //    Priority: 1
    IPC16bits.U2ERIP = 1;
    //    UTXI: U2TX - UART2 Transmitter
    //    Priority: 1
    IPC7bits.U2TXIP = 4;
    //    URXI: U2RX - UART2 Receiver
    //    Priority: 1
    IPC7bits.U2RXIP = 4;
    //    SSPI: MSSP1 - I2C/SPI Interrupt
    //    Priority: 1
    IPC4bits.SSP1IP = 5;
    //    UERI: U1E - UART1 Error
    //    Priority: 1
    IPC16bits.U1ERIP = 1;
    //    UTXI: U1TX - UART1 Transmitter
    //    Priority: 1
    IPC3bits.U1TXIP = 5;
    //    URXI: U1RX - UART1 Receiver
    //    Priority: 1
    IPC2bits.U1RXIP = 5;
    //    MS_TIMER: Tx - Timerx
    //    Priority: 7
    MS_TIMER_TxIP = 7;
    //    IOC: Change Notification
    //    Priority: 6
    IPC4bits.CNIP = 6;
    INTERRUPT_GlobalEnable();
}
