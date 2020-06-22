#include <xc.h>
#include <stdio.h>
#include "pin_manager.h"
#include "../util.h"

void PIN_MANAGER_Initialize(void) {
    /****************************************************************************
     * Setting the Output Latch SFR(s)
     ***************************************************************************/
    LATA = 0x0000;
    LATB = 0x0000;

    IO_RB7_SetPin(PIN_STATE_ON); // Initial UART Condition
    /****************************************************************************
     * Setting the GPIO Direction SFR(s)
     ***************************************************************************/
    TRISA = 0x0000;
    TRISB = 0x0000;

    IO_RB7_SetDirection(PIN_DIRECTION_OUTPUT); // U1Tx
    IO_RB2_SetDirection(PIN_DIRECTION_INPUT); // U1Rx
    IO_RB3_SetDirection(PIN_DIRECTION_INPUT); // BT State
    IO_RA1_SetDirection(PIN_DIRECTION_OUTPUT); // BT Enable
    STATUS_LED_SetDirection(PIN_DIRECTION_OUTPUT);
    
    // Joint settings
    IO_RB13_SetDirection(PIN_DIRECTION_OUTPUT);
    IO_RB9_SetDirection(PIN_DIRECTION_OUTPUT);
    IO_RA7_SetDirection(PIN_DIRECTION_OUTPUT);
    IO_RB12_SetDirection(PIN_DIRECTION_OUTPUT);
    IO_RB11_SetDirection(PIN_DIRECTION_OUTPUT);
    IO_RB8_SetDirection(PIN_DIRECTION_OUTPUT);
    IO_RB10_SetDirection(PIN_DIRECTION_OUTPUT);
    /****************************************************************************
     * Setting the Weak Pull Up and Weak Pull Down SFR(s)
     ***************************************************************************/
    CNPD1 = 0x0000;
    CNPD2 = 0x0000;
    CNPU1 = 0x0000;
    CNPU2 = 0x0000;

    /****************************************************************************
     * Setting the Open Drain SFR(s)
     ***************************************************************************/
    ODCA = 0x0000;
    ODCB = 0x0000;

    /****************************************************************************
     * Setting the Analog/Digital Configuration SFR(s)
     ***************************************************************************/
    ANSA = 0x0000;
    ANSB = 0xC000;
}

