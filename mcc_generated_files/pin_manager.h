#ifndef _PIN_MANAGER_H
#define _PIN_MANAGER_H

#include <xc.h>

#define PIN_STATE_OFF 0
#define PIN_STATE_ON 1

#define PIN_DIRECTION_OUTPUT 0
#define PIN_DIRECTION_INPUT 1

// RA0 is the ICSP PGC
#define IO_RA0_SetPin(STATE)          (_LATA0 = STATE)
#define IO_RA0_Toggle()           (_LATA0 ^= 1)
#define IO_RA0_GetValue()         _RA0
#define IO_RA0_SetDirection(DIR)  (_TRISA0 = DIR)

// RA1 is the ICSP PGD
#define IO_RA1_SetPin(STATE)          (_LATA1 = STATE)
#define IO_RA1_Toggle()           (_LATA1 ^= 1)
#define IO_RA1_GetValue()         _RA1
#define IO_RA1_SetDirection(DIR)  (_TRISA1 = DIR)

#define IO_RA2_SetPin(STATE)          (_LATA2 = STATE)
#define IO_RA2_Toggle()           (_LATA2 ^= 1)
#define IO_RA2_GetValue()         _RA2
#define IO_RA2_SetDirection(DIR)  (_TRISA2 = DIR)

#define IO_RA3_SetPin(STATE)          (_LATA3 = STATE)
#define IO_RA3_Toggle()           (_LATA3 ^= 1)
#define IO_RA3_GetValue()         _RA3
#define IO_RA3_SetDirection(DIR)  (_TRISA3 = DIR)

#define IO_RA4_SetPin(STATE)          (_LATA4 = STATE)
#define IO_RA4_Toggle()           (_LATA4 ^= 1)
#define IO_RA4_GetValue()         _RA4
#define IO_RA4_SetDirection(DIR)  (_TRISA4 = DIR)

#define IO_RA5_SetPin(STATE)          (_LATA5 = STATE)
#define IO_RA5_Toggle()           (_LATA5 ^= 1)
#define IO_RA5_GetValue()         _RA5
#define IO_RA5_SetDirection(DIR)  (_TRISA5 = DIR)

#define IO_RA7_SetPin(STATE)          (_LATA7 = STATE)
#define IO_RA7_Toggle()           (_LATA7 ^= 1)
#define IO_RA7_GetValue()         _RA7
#define IO_RA7_SetDirection(DIR)  (_TRISA7 = DIR)


#define IO_RB0_SetPin(STATE)          (_LATB0 = STATE)
#define IO_RB0_Toggle()           (_LATB0 ^= 1)
#define IO_RB0_GetValue()         _RB0
#define IO_RB0_SetDirection(DIR)  (_TRISB0 = DIR)

#define IO_RB1_SetPin(STATE)          (_LATB1 = STATE)
#define IO_RB1_Toggle()           (_LATB1 ^= 1)
#define IO_RB1_GetValue()         _RB1
#define IO_RB1_SetDirection(DIR)  (_TRISB1 = DIR)

#define IO_RB2_SetPin(STATE)          (_LATB2 = STATE)
#define IO_RB2_Toggle()           (_LATB2 ^= 1)
#define IO_RB2_GetValue()         _RB2
#define IO_RB2_SetDirection(DIR)  (_TRISB2 = DIR)

#define IO_RB3_SetPin(STATE)          (_LATB3 = STATE)
#define IO_RB3_Toggle()           (_LATB3 ^= 1)
#define IO_RB3_GetValue()         _RB3
#define IO_RB3_SetDirection(DIR)  (_TRISB3 = DIR)

#define IO_RB4_SetPin(STATE)          (_LATB4 = STATE)
#define IO_RB4_Toggle()           (_LATB4 ^= 1)
#define IO_RB4_GetValue()         _RB4
#define IO_RB4_SetDirection(DIR)  (_TRISB4 = DIR)

#define IO_RB5_SetPin(STATE)          (_LATB5 = STATE)
#define IO_RB5_Toggle()           (_LATB5 ^= 1)
#define IO_RB5_GetValue()         _RB5
#define IO_RB5_SetDirection(DIR)  (_TRISB5 = DIR)

#define IO_RB6_SetPin(STATE)          (_LATB6 = STATE)
#define IO_RB6_Toggle()           (_LATB6 ^= 1)
#define IO_RB6_GetValue()         _RB6
#define IO_RB6_SetDirection(DIR)  (_TRISB6 = DIR)

// Do not use as IO, RB7 is UART1 Tx
#define IO_RB7_SetPin(STATE)          (_LATB7 = STATE)
#define IO_RB7_Toggle()           (_LATB7 ^= 1)
#define IO_RB7_GetValue()         _RB7
#define IO_RB7_SetDirection(DIR)  (_TRISB7 = DIR)

#define IO_RB8_SetPin(STATE)          (_LATB8 = STATE)
#define IO_RB8_Toggle()           (_LATB8 ^= 1)
#define IO_RB8_GetValue()         _RB8
#define IO_RB8_SetDirection(DIR)  (_TRISB8 = DIR)

#define IO_RB9_SetPin(STATE)          (_LATB9 = STATE)
#define IO_RB9_Toggle()           (_LATB9 ^= 1)
#define IO_RB9_GetValue()         _RB9
#define IO_RB9_SetDirection(DIR)  (_TRISB9 = DIR)

#define IO_RB10_SetPin(STATE)          (_LATB10 = STATE)
#define IO_RB10_Toggle()           (_LATB10 ^= 1)
#define IO_RB10_GetValue()         _RB10
#define IO_RB10_SetDirection(DIR)  (_TRISB10 = DIR)

#define IO_RB11_SetPin(STATE)          (_LATB11 = STATE)
#define IO_RB11_Toggle()           (_LATB11 ^= 1)
#define IO_RB11_GetValue()         _RB11
#define IO_RB11_SetDirection(DIR)  (_TRISB11 = DIR)

#define IO_RB12_SetPin(STATE)          (_LATB12 = STATE)
#define IO_RB12_Toggle()           (_LATB12 ^= 1)
#define IO_RB12_GetValue()         _RB12
#define IO_RB12_SetDirection(DIR)  (_TRISB12 = DIR)

#define IO_RB13_SetPin(STATE)          (_LATB13 = STATE)
#define IO_RB13_Toggle()           (_LATB13 ^= 1)
#define IO_RB13_GetValue()         _RB13
#define IO_RB13_SetDirection(DIR)  (_TRISB13 = DIR)

#define IO_RB14_SetPin(STATE)          (_LATB14 = STATE)
#define IO_RB14_Toggle()           (_LATB14 ^= 1)
#define IO_RB14_GetValue()         _RB14
#define IO_RB14_SetDirection(DIR)  (_TRISB14 = DIR)

#define IO_RB15_SetPin(STATE)          (_LATB15 = STATE)
#define IO_RB15_Toggle()           (_LATB15 ^= 1)
#define IO_RB15_GetValue()         _RB15
#define IO_RB15_SetDirection(DIR)  (_TRISB15 = DIR)

void PIN_MANAGER_Initialize (void);

#endif
