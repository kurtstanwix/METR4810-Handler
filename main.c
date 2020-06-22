#include "mcc_generated_files/system.h"
#include "mcc_generated_files/clock.h"
#include "mcc_generated_files/interrupt_manager.h"
#include "mcc_generated_files/pin_manager.h"
#include "ms_timer.h"
#include "hardware_PWM.h"
#include "at_control.h"
#include "uart_manager.h"
#include "comms.h"
#include <xc.h>



int main(void) {
    // initialize the device
    SYSTEM_Initialize();

    // Motor 1kHz
    HARDWARE_PWM_PERIOD_SET_US(JOINT_1_3_PWM_1, 1000);
    HARDWARE_PWM_PERIOD_SET_US(JOINT_1_3_PWM_2, 1000);
    
    // Servos 50Hz, mid point pulse width initial
    HARDWARE_PWM_PERIOD_SET_US(JOINT_2_PWM, 20000);
    HARDWARE_PWM_PULSE_WIDTH_SET(JOINT_2_PWM, 1500);
    
    HARDWARE_PWM_PERIOD_SET_US(JOINT_4_PWM, 20000);
    HARDWARE_PWM_PULSE_WIDTH_SET(JOINT_4_PWM, 1500);
    
    HARDWARE_PWM_PERIOD_SET_US(JOINT_5_PWM, 20000);
    HARDWARE_PWM_PULSE_WIDTH_SET(JOINT_5_PWM, 1500);
    
    HARDWARE_PWM_ENABLE();
    
    // Start the servos, stop the motors
    HARDWARE_PWM_JOINT_2_START();
    HARDWARE_PWM_JOINT_4_START();
    HARDWARE_PWM_JOINT_5_START();
    
    HARDWARE_PWM_JOINT_1_STOP();
    HARDWARE_PWM_JOINT_3_STOP();
    
    init_debug();
    
    // Put in comms mode
    AT_PIN_Clear();
    
    // Delay so a quick turn on and off won't reset Bluetooth
    MS_TIMER_Delay_ms(4000);

    init_comms();

    BUFFER_OBJ rcvBuffer;
    init_buffer(&rcvBuffer, PACKET_LENGTH - 1); // Length of packet without seq number

    while (1) {
        process_comms();
        if (comms_get_packet(&rcvBuffer)) {
            process_packet(&rcvBuffer);
        }
    }
}