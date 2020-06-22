#include <stdint.h>
#include "xc.h"
#include "clock.h"

void CLOCK_Initialize(void) {
    // RCDIV FRC/1; DOZE 1:8; DOZEN disabled; ROI disabled; 
    CLKDIV = 0x3000;
    // TUN Center frequency; 
    OSCTUN = 0x00;
    // ROEN disabled; ROSEL FOSC; RODIV 0; ROSSLP disabled; 
    REFOCON = 0x00;
    // ADC1MD enabled; SSP1MD enabled; T1MD enabled; U2MD enabled; U1MD enabled; 
    PMD1 = 0x00;
    // CCP2MD enabled; CCP1MD enabled; CCP4MD enabled; CCP3MD enabled; CCP5MD enabled; 
    PMD2 = 0x00;
    // SSP2MD enabled; RTCCMD enabled; CMPMD enabled; DAC1MD enabled; 
    PMD3 = 0x00;
    // CTMUMD enabled; REFOMD enabled; ULPWUMD enabled; HLVDMD enabled; 
    PMD4 = 0x00;
    // AMP2MD enabled; AMP1MD enabled; DAC2MD enabled; 
    PMD6 = 0x00;
    // CLC1MD enabled; CLC2MD enabled; 
    PMD8 = 0x00;
    // CF no clock failure; NOSC FRCPLL; SOSCEN disabled; SOSCDRV disabled; CLKLOCK unlocked; OSWEN Switch is Complete; 
    __builtin_write_OSCCONH((uint8_t) (0x01));
    __builtin_write_OSCCONL((uint8_t) (0x00));
}
