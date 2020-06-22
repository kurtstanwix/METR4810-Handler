#ifndef _HARDWARE_PWM_H
#define	_HARDWARE_PWM_H

#include <xc.h>
#include "util.h"
#include "mcc_generated_files/pin_manager.h"

// MOTOR DEFINITIONS
// MCCP module numbers for pins 1 and 2 of motors
#define JOINT_1_3_PWM_1 1
#define JOINT_1_3_PWM_2 2

// MCCP Pin names for motors
#define JOINT_1_PIN_1 C
#define JOINT_1_PIN_2 B
#define JOINT_3_PIN_1 B
#define JOINT_3_PIN_2 A

// GPIO control of motor pins for when they aren't in use
#define JOINT_1_PIN_1_SetPin(STATE) IO_RB10_SetPin(STATE)
#define JOINT_1_PIN_2_SetPin(STATE) IO_RB12_SetPin(STATE)
#define JOINT_3_PIN_1_SetPin(STATE) IO_RB8_SetPin(STATE)
#define JOINT_3_PIN_2_SetPin(STATE) IO_RB11_SetPin(STATE)

// SERVO DEFINITIONS
// MCCP/SCCP module numbers for servo joints
#define JOINT_2_PWM 3
#define JOINT_4_PWM 4
#define JOINT_5_PWM 5

// MCCP/SCCP Pin names for servo joints
#define JOINT_2_PIN B
#define JOINT_4_PIN A
#define JOINT_5_PIN A

// GPIO control of servo pins for when not in use
#define JOINT_2_PIN_SetPin(STATE) IO_RB13_SetPin(STATE)
#define JOINT_4_PIN_SetPin(STATE) IO_RB9_SetPin(STATE)
#define JOINT_5_PIN_SetPin(STATE) IO_RA7_SetPin(STATE)

// Allows the setting of a MCCP/SCCP modules' CCP register
#define HARDWARE_PWM_CCP_REGISTER(PWM_NUM, REGISTER) PREPROCESSOR_STITCH(CCP, \
                                                     PREPROCESSOR_STITCH(PWM_NUM, REGISTER))
// Allows the setting of a MCCP/SCCP modules' pin output
#define HARDWARE_PWM_PIN_OUPUT(PWM_NUM, PIN) PREPROCESSOR_STITCH(HARDWARE_PWM_CCP_REGISTER(PWM_NUM, CON2Hbit), \
                                             PREPROCESSOR_STITCH(s.OC, \
                                             PREPROCESSOR_STITCH(PIN, EN)))

// Individual Motor PWM's Start/Stops
#define HARDWARE_PWM_JOINT_1_STOP() {HARDWARE_PWM_PIN_OUPUT(JOINT_1_3_PWM_1, JOINT_1_PIN_1) = 0; \
                                     HARDWARE_PWM_PIN_OUPUT(JOINT_1_3_PWM_2, JOINT_1_PIN_2) = 0; \
                                     JOINT_1_PIN_1_SetPin(PIN_STATE_ON); \
                                     JOINT_1_PIN_2_SetPin(PIN_STATE_ON);}

#define HARDWARE_PWM_JOINT_3_STOP() {HARDWARE_PWM_PIN_OUPUT(JOINT_1_3_PWM_1, JOINT_3_PIN_1) = 0; \
                                     HARDWARE_PWM_PIN_OUPUT(JOINT_1_3_PWM_2, JOINT_3_PIN_2) = 0; \
                                     JOINT_3_PIN_1_SetPin(PIN_STATE_ON); \
                                     JOINT_3_PIN_2_SetPin(PIN_STATE_ON);}

#define HARDWARE_PWM_JOINT_1_START() {HARDWARE_PWM_PIN_OUPUT(JOINT_1_3_PWM_1, JOINT_1_PIN_1) = 1; \
                                      HARDWARE_PWM_PIN_OUPUT(JOINT_1_3_PWM_2, JOINT_1_PIN_2) = 1;}

#define HARDWARE_PWM_JOINT_3_START() {HARDWARE_PWM_PIN_OUPUT(JOINT_1_3_PWM_1, JOINT_3_PIN_1) = 1; \
                                      HARDWARE_PWM_PIN_OUPUT(JOINT_1_3_PWM_2, JOINT_3_PIN_2) = 1;}

// Individual Servo PWM's Start/Stops
#define HARDWARE_PWM_JOINT_2_STOP() {HARDWARE_PWM_PIN_OUPUT(JOINT_2_PWM, JOINT_2_PIN) = 0; \
                                     JOINT_2_PIN_SetPin(PIN_STATE_OFF);}
#define HARDWARE_PWM_JOINT_4_STOP() {HARDWARE_PWM_PIN_OUPUT(JOINT_4_PWM, JOINT_4_PIN) = 0; \
                                     JOINT_4_PIN_SetPin(PIN_STATE_OFF);}
#define HARDWARE_PWM_JOINT_5_STOP() {HARDWARE_PWM_PIN_OUPUT(JOINT_5_PWM, JOINT_5_PIN) = 0; \
                                     JOINT_5_PIN_SetPin(PIN_STATE_OFF);}

#define HARDWARE_PWM_JOINT_2_START() {HARDWARE_PWM_PIN_OUPUT(JOINT_2_PWM, JOINT_2_PIN) = 1;}
#define HARDWARE_PWM_JOINT_4_START() {HARDWARE_PWM_PIN_OUPUT(JOINT_4_PWM, JOINT_4_PIN) = 1;}
#define HARDWARE_PWM_JOINT_5_START() {HARDWARE_PWM_PIN_OUPUT(JOINT_5_PWM, JOINT_5_PIN) = 1;}

/*
 * Valid values are:
 * 64, 16, 4, 1
 * Do not set otherwise
 */
#define HARDWARE_PWM_TMR_PRESCALER 16

// Set the duty cycle of the given PWM
#define HARDWARE_PWM_DUTY_CYCLE_SET(PWM_NUM, DUTY_CYCLE) \
        {HARDWARE_PWM_CCP_REGISTER(PWM_NUM, RB) = \
        (uint16_t) ((uint32_t) HARDWARE_PWM_CCP_REGISTER(PWM_NUM, PRL) * (DUTY_CYCLE) / 1000); \
         PREPROCESSOR_STITCH(dutyCycle, PWM_NUM) = (DUTY_CYCLE);}

// Period to register value calculation
#define PERIOD_CALCULATION(PERIOD_US) ((uint16_t) ((PERIOD_US) * \
                                      (CLOCK_PeripheralFrequencyGet() / \
                                      (HARDWARE_PWM_TMR_PRESCALER * 1000000UL)) - 1))

// Set the period of the PWM in microseconds
#define HARDWARE_PWM_PERIOD_SET_US(PWM_NUM, PERIOD_US) \
        {HARDWARE_PWM_CCP_REGISTER(PWM_NUM, PRL) = PERIOD_CALCULATION(PERIOD_US); \
         HARDWARE_PWM_DUTY_CYCLE_SET(PWM_NUM, PREPROCESSOR_STITCH(dutyCycle, PWM_NUM));}

// Set the pulse width of the PWM in microseconds
#define HARDWARE_PWM_PULSE_WIDTH_SET(PWM_NUM, PULSE_WIDTH_US) \
        {HARDWARE_PWM_CCP_REGISTER(PWM_NUM, RB) = PERIOD_CALCULATION(PULSE_WIDTH_US); \
         PREPROCESSOR_STITCH(dutyCycle, PWM_NUM) = HARDWARE_PWM_CCP_REGISTER(PWM_NUM, PRL) \
                                                   / HARDWARE_PWM_CCP_REGISTER(PWM_NUM, RB);}
        
// Enable the timers for all the MCCP modules
#define HARDWARE_PWM_ENABLE() {HARDWARE_PWM_CCP_REGISTER(JOINT_1_3_PWM_1, CON1Lbits.CCPON) = 1; \
                               HARDWARE_PWM_CCP_REGISTER(JOINT_1_3_PWM_2, CON1Lbits.CCPON) = 1; \
                               HARDWARE_PWM_CCP_REGISTER(JOINT_2_PWM, CON1Lbits.CCPON) = 1; \
                               HARDWARE_PWM_CCP_REGISTER(JOINT_4_PWM, CON1Lbits.CCPON) = 1; \
                               HARDWARE_PWM_CCP_REGISTER(JOINT_5_PWM, CON1Lbits.CCPON) = 1;}

#define HARDWARE_PWM_DISABLE() {HARDWARE_PWM_CCP_REGISTER(JOINT_1_3_PWM_1, CON1Lbits.CCPON) = 0; \
                                HARDWARE_PWM_CCP_REGISTER(JOINT_1_3_PWM_2, CON1Lbits.CCPON) = 0; \
                                HARDWARE_PWM_CCP_REGISTER(JOINT_2_PWM, CON1Lbits.CCPON) = 0; \
                                HARDWARE_PWM_CCP_REGISTER(JOINT_4_PWM, CON1Lbits.CCPON) = 0; \
                                HARDWARE_PWM_CCP_REGISTER(JOINT_5_PWM, CON1Lbits.CCPON) = 0;}

// Duty cycles of each joint
extern uint16_t dutyCycle1;
extern uint16_t dutyCycle2;
extern uint16_t dutyCycle3;
extern uint16_t dutyCycle4;
extern uint16_t dutyCycle5;

void Hardware_PWM_Initialise(void);

#endif	// _HARDWARE_PWM_H

