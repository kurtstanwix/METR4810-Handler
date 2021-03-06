#include "hardware_PWM.h"

// Current MCCP mode
static const uint16_t OCMode = 0b110; // Edge-Aligned PWM;

// Duty cycles of each joint
uint16_t dutyCycle1 = 0;
uint16_t dutyCycle2 = 0;
uint16_t dutyCycle3 = 0;
uint16_t dutyCycle4 = 0;
uint16_t dutyCycle5 = 0;

/**
 * Intialises the Hardware PWM's to be ready for use
 */
void Hardware_PWM_Initialise(void) {
    HARDWARE_PWM_CCP_REGISTER(JOINT_1_3_PWM_1, CON1L) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_1_3_PWM_2, CON1L) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_2_PWM, CON1L) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_4_PWM, CON1L) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_5_PWM, CON1L) = 0x0000;
    // Prescaler = 16
    HARDWARE_PWM_CCP_REGISTER(JOINT_1_3_PWM_1, CON1Lbits).TMRPS = 0b10;
    HARDWARE_PWM_CCP_REGISTER(JOINT_1_3_PWM_2, CON1Lbits).TMRPS = 0b10;
    HARDWARE_PWM_CCP_REGISTER(JOINT_2_PWM, CON1Lbits).TMRPS = 0b10;
    HARDWARE_PWM_CCP_REGISTER(JOINT_4_PWM, CON1Lbits).TMRPS = 0b10;
    HARDWARE_PWM_CCP_REGISTER(JOINT_5_PWM, CON1Lbits).TMRPS = 0b10;
    // Mode = Dual Edge Compare mode, buffered
    HARDWARE_PWM_CCP_REGISTER(JOINT_1_3_PWM_1, CON1Lbits).MOD = 0b0101;
    HARDWARE_PWM_CCP_REGISTER(JOINT_1_3_PWM_2, CON1Lbits).MOD = 0b0101;
    HARDWARE_PWM_CCP_REGISTER(JOINT_2_PWM, CON1Lbits).MOD = 0b0101;
    HARDWARE_PWM_CCP_REGISTER(JOINT_4_PWM, CON1Lbits).MOD = 0b0101;
    HARDWARE_PWM_CCP_REGISTER(JOINT_5_PWM, CON1Lbits).MOD = 0b0101;
    
    HARDWARE_PWM_CCP_REGISTER(JOINT_1_3_PWM_1, CON1H) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_1_3_PWM_2, CON1H) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_2_PWM, CON1H) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_4_PWM, CON1H) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_5_PWM, CON1H) = 0x0000;
    
    HARDWARE_PWM_CCP_REGISTER(JOINT_1_3_PWM_1, CON2L) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_1_3_PWM_2, CON2L) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_2_PWM, CON2L) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_4_PWM, CON2L) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_5_PWM, CON2L) = 0x0000;
    
    HARDWARE_PWM_CCP_REGISTER(JOINT_1_3_PWM_1, CON2H) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_1_3_PWM_2, CON2H) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_2_PWM, CON2H) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_4_PWM, CON2H) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_5_PWM, CON2H) = 0x0000;
    
    HARDWARE_PWM_CCP_REGISTER(JOINT_1_3_PWM_1, CON3L) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_1_3_PWM_2, CON3L) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_2_PWM, CON3L) = 0x0000;
    
    HARDWARE_PWM_CCP_REGISTER(JOINT_1_3_PWM_1, CON3H) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_1_3_PWM_2, CON3H) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_2_PWM, CON3H) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_4_PWM, CON3H) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_5_PWM, CON3H) = 0x0000;
    // Only lower word of timer register is used in double buffered PWM mode
    HARDWARE_PWM_CCP_REGISTER(JOINT_1_3_PWM_1, TMRL) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_1_3_PWM_2, TMRL) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_2_PWM, TMRL) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_4_PWM, TMRL) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_5_PWM, TMRL) = 0x0000;
    // Only lower word of period register is used in double buffered PWM mode
    HARDWARE_PWM_CCP_REGISTER(JOINT_1_3_PWM_1, PRL) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_1_3_PWM_2, PRL) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_2_PWM, PRL) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_4_PWM, PRL) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_5_PWM, PRL) = 0x0000;
    // Low-high transition match, should be 0 for standard PWM
    HARDWARE_PWM_CCP_REGISTER(JOINT_1_3_PWM_1, RA) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_1_3_PWM_2, RA) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_2_PWM, RA) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_4_PWM, RA) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_5_PWM, RA) = 0x0000;
    // High-low transition match, controls duty cycle in standard PWM
    HARDWARE_PWM_CCP_REGISTER(JOINT_1_3_PWM_1, RB) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_1_3_PWM_2, RB) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_2_PWM, RB) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_4_PWM, RB) = 0x0000;
    HARDWARE_PWM_CCP_REGISTER(JOINT_5_PWM, RB) = 0x0000;
    HARDWARE_PWM_ENABLE();
}