#include "mcc_generated_files/system.h"
#include "mcc_generated_files/clock.h"
#include "mcc_generated_files/interrupt_manager.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/mssp1_i2c.h"
#include "ms_timer.h"
#include "hardware_PWM.h"
#include "at_control.h"
#include "uart_manager.h"
#include "imu.h"
#include <xc.h>


////////////////////////////////////////////////////
// I2C TEST
////////////////////////////////////////////////////
/*
#define ASCII_OFFSET 48

int main(void) {
    PIN_MANAGER_Initialize();
    INTERRUPT_Initialize();
    CLOCK_Initialize();
    UART_Initialise();
    MS_TIMER_Initialize();
    MSSP1_I2C_Initialize();
    init_debug();
    
    IO_RB5_SetDirection(PIN_DIRECTION_INPUT); // SDA1
    IO_RB6_SetDirection(PIN_DIRECTION_INPUT); // SCL1
    
    imu_initialise();
    
    set_mode(OPERATION_MODE_NDOF);
    
    uint8_t id[2];
    uint8_t dummy1;
    uint8_t dummy2;
    char orientationSt[40];// = "x:      , y:      , z:      ";
    char linAccelSt[40];// = "x:      , y:      , z:      ";
    bool neg;
    int16_t val;
    uint8_t i;
    //VECTOR_OBJ orientation = get_vector(VECTOR_EULER);
    while (1) {
        VECTOR_OBJ orientation = get_vector(VECTOR_EULER);
        VECTOR_OBJ linAccel = get_vector(VECTOR_LINACCEL);
        
        
        print_debug("Orientation:", 12, true);
        
        
        
        orientationSt[27] = ' ';
        orientationSt[26] = ' ';
        orientationSt[25] = ' ';
        orientationSt[24] = ' ';
        orientationSt[23] = ' ';
        orientationSt[22] = ' ';
        
        orientationSt[17] = ' ';
        orientationSt[16] = ' ';
        orientationSt[15] = ' ';
        orientationSt[14] = ' ';
        orientationSt[13] = ' ';
        orientationSt[12] = ' ';
        
        orientationSt[7] = ' ';
        orientationSt[6] = ' ';
        orientationSt[5] = ' ';
        orientationSt[4] = ' ';
        orientationSt[3] = ' ';
        orientationSt[2] = ' ';
        
        val = orientation.x;
        neg = val < 0;
        if (neg) {
            val *= -1;
        }
        i = 0;
        if (val) {
            while (val) {
                orientationSt[7 - (i++)] = val % 10 + ASCII_OFFSET;
                val /= 10;
            }
            if (neg) {
                orientationSt[7 - i] = '-';
            }
        } else {
            orientationSt[7] = '0';
        }
        
        val = orientation.y;
        neg = val < 0;
        if (neg) {
            val *= -1;
        }
        i = 0;
        if (val) {
            while (val) {
                orientationSt[17 - (i++)] = val % 10 + ASCII_OFFSET;
                val /= 10;
            }
            if (neg) {
                orientationSt[17 - i] = '-';
            }
        } else {
            orientationSt[17] = '0';
        }
        
        val = orientation.z;
        neg = val < 0;
        if (neg) {
            val *= -1;
        }
        i = 0;
        if (val) {
            while (val) {
                orientationSt[27 - (i++)] = val % 10 + ASCII_OFFSET;
                val /= 10;
            }
            if (neg) {
                orientationSt[27 - i] = '-';
            }
        } else {
            orientationSt[27] = '0';
        }
        
        print_debug(orientationSt, 28, true);
        
        
        print_debug("LinAccel:", 9, true);
        linAccelSt[27] = ' ';
        linAccelSt[26] = ' ';
        linAccelSt[25] = ' ';
        linAccelSt[24] = ' ';
        linAccelSt[23] = ' ';
        linAccelSt[22] = ' ';
        
        linAccelSt[17] = ' ';
        linAccelSt[16] = ' ';
        linAccelSt[15] = ' ';
        linAccelSt[14] = ' ';
        linAccelSt[13] = ' ';
        linAccelSt[12] = ' ';
        
        linAccelSt[7] = ' ';
        linAccelSt[6] = ' ';
        linAccelSt[5] = ' ';
        linAccelSt[4] = ' ';
        linAccelSt[3] = ' ';
        linAccelSt[2] = ' ';
        
        val = linAccel.x;
        neg = val < 0;
        if (neg) {
            val *= -1;
        }
        i = 0;
        if (val) {
            while (val) {
                linAccelSt[7 - (i++)] = val % 10 + ASCII_OFFSET;
                val /= 10;
            }
            if (neg) {
                linAccelSt[7 - i] = '-';
            }
        } else {
            linAccelSt[7] = '0';
        }
        
        val = linAccel.y;
        neg = val < 0;
        if (neg) {
            val *= -1;
        }
        i = 0;
        if (val) {
            while (val) {
                linAccelSt[17 - (i++)] = val % 10 + ASCII_OFFSET;
                val /= 10;
            }
            if (neg) {
                linAccelSt[17 - i] = '-';
            }
        } else {
            linAccelSt[17] = '0';
        }
        
        val = linAccel.z;
        neg = val < 0;
        if (neg) {
            val *= -1;
        }
        i = 0;
        if (val) {
            while (val) {
                linAccelSt[27 - (i++)] = val % 10 + ASCII_OFFSET;
                val /= 10;
            }
            if (neg) {
                linAccelSt[27 - i] = '-';
            }
        } else {
            linAccelSt[27] = '0';
        }
        
        print_debug(linAccelSt, 28, true);
        MS_TIMER_Delay_ms(500);
        
    }
}

*/



////////////////////////////////////////////////////
// BLUETOOTH TEST
////////////////////////////////////////////////////


#define PACKET_LENGTH 34
BUFFER_OBJ rcvBuffer;
BUFFER_OBJ sndBuffer;
BUFFER_OBJ ackBuffer;
BUFFER_OBJ packetBuffer;
bool sent = false;


#define STATE_RCV_CONNECTING 0
#define STATE_RCV_SEQ_U 1
#define STATE_RCV_SEQ_V 2
#define RCV_SEQNUM_U 0
#define RCV_SEQNUM_V 1

#define STATE_SND_CONNECTING 0
#define STATE_SND_SEQ_X 1
#define STATE_SND_SEQ_X_ACK 2
#define STATE_SND_SEQ_Y 3
#define STATE_SND_SEQ_Y_ACK 4
#define SND_SEQNUM_X 2
#define SND_SEQNUM_Y 3

#define COMMS_TIMEOUT 2000

#define ASCII_OFFSET 48

uint8_t rcvState = STATE_RCV_CONNECTING;
uint8_t sndState = STATE_SND_CONNECTING;
bool rcvACKX = false;
bool rcvACKY = false;
ms_time_t sentTime;
uint8_t rcvStatus;
uint8_t receivedSeqNum;

bool packetReady = false;

void init_comms(void) {
    init_buffer(&rcvBuffer, PACKET_LENGTH);
    init_buffer(&sndBuffer, PACKET_LENGTH);
    init_buffer(&packetBuffer, PACKET_LENGTH - 1);
    init_buffer(&ackBuffer, 7);
    
    print_debug("Waiting for connection...", 25, true);
    wait_for_connection();
    print_debug("Connected", 9, true);
    
    rcvState = STATE_RCV_SEQ_U;
    sndState = STATE_SND_SEQ_X;
    
    sent = true;
}

bool comms_get_packet(BUFFER_OBJ *dest) {
    if (packetReady) {
        copy_to_buffer(dest, packetBuffer.buffer, packetBuffer.tail - packetBuffer.buffer, true);
        packetReady = false;
        return true;
    }
    return false;
}

bool comms_send(BUFFER_OBJ *toSend) {
    if (!sent) {
        return false;
    }
    sndBuffer.tail = sndBuffer.buffer + 1;
    copy_to_buffer(&sndBuffer, toSend->buffer, toSend->tail - toSend->buffer, false);
    sent = false;
}

void send_ACK(uint8_t seqNum) {
    seqNum += ASCII_OFFSET;
    copy_to_buffer(&ackBuffer, "0ACK", 4, true);
    copy_to_buffer(&ackBuffer, &seqNum, 1, false);
    copy_to_buffer(&ackBuffer, "\r\n", 2, false);
    send_buffer(&ackBuffer, BLUETOOTH_UART_NUM, true);
}

void process_comms(void) {
    if (!BT_IS_CONNECTED()) {
        print_debug("Lost Connection\n\rReconnecting...", 32, true);
        wait_for_connection();
        print_debug("Reconnected", 11, true);
        rcvState = STATE_RCV_SEQ_U;
        sndState = STATE_SND_SEQ_X;
        sent = true;
    }
    
    rcvStatus = read_line_to_buffer(&rcvBuffer, BLUETOOTH_UART_NUM, 1);
    if (rcvStatus == UART_READ_LINE_RECEIVED) {
        // Process ACK's seperately from rcv FSM
        if (compare_strings(rcvBuffer.buffer + 1, "ACK", 3)) {
            if (rcvBuffer.buffer[4] - ASCII_OFFSET == SND_SEQNUM_X) {
                rcvACKX = true;
            } else if (rcvBuffer.buffer[4] - ASCII_OFFSET == SND_SEQNUM_Y) {
                rcvACKY = true;
            }
        } else {
            receivedSeqNum = rcvBuffer.buffer[0] - ASCII_OFFSET;
            switch (rcvState) {
                case STATE_RCV_SEQ_U:
                    if (receivedSeqNum == RCV_SEQNUM_U) {
                        // Correct sequence number received, extract packet,
                        // set ready flag and send ACK
                        print_debug("Received: ", 10, false);
                        print_debug(rcvBuffer.buffer, rcvBuffer.tail - rcvBuffer.buffer, false);
                        copy_to_buffer(&packetBuffer, rcvBuffer.buffer + 1, rcvBuffer.tail - rcvBuffer.buffer - 1, true);
                        packetReady = true;
                        send_ACK(RCV_SEQNUM_U);
                        rcvState = STATE_RCV_SEQ_V;
                    }
                    // Otherwise incorrect sequence number, discard packet
                    else {
                        print_debug("Incorrect Seq Num. Expected: ", 29, false);
                        char temp = RCV_SEQNUM_U + ASCII_OFFSET;
                        print_debug(&temp, 1, false);
                        print_debug(", Got: ", 7, false);
                        print_debug(rcvBuffer.buffer, 1, true);
                    }
                    break;
                case STATE_RCV_SEQ_V:
                    if (receivedSeqNum == RCV_SEQNUM_V) {
                        // Correct sequence number received, extract packet,
                        // set ready flag and send ACK
                        print_debug("Received: ", 10, false);
                        print_debug(rcvBuffer.buffer, rcvBuffer.tail - rcvBuffer.buffer, false);
                        copy_to_buffer(&packetBuffer, rcvBuffer.buffer + 1, rcvBuffer.tail - rcvBuffer.buffer - 1, true);
                        packetReady = true;
                        send_ACK(RCV_SEQNUM_V);
                        rcvState = STATE_RCV_SEQ_U;
                    }
                    // Otherwise incorrect sequence number, discard packet
                    else {
                        // Incorrect sequence number, discard packet
                        print_debug("Incorrect Seq Num. Expected: ", 29, false);
                        char temp = RCV_SEQNUM_V + ASCII_OFFSET;
                        print_debug(&temp, 1, false);
                        print_debug(", Got: ", 7, false);
                        print_debug(rcvBuffer.buffer, 1, true);
                    }
                    break;
            }
        }
        rcvBuffer.tail = rcvBuffer.buffer;
    }
    
    switch (sndState) {
        case STATE_SND_SEQ_X:
            if (!sent) {
                // Prepend the sequence number and send, starting the timeout timer
                sndBuffer.buffer[0] = SND_SEQNUM_X + ASCII_OFFSET;
                send_buffer(&sndBuffer, BLUETOOTH_UART_NUM, false);
                sentTime = MS_TIMER_get_time_ms();
                sndState = STATE_SND_SEQ_X_ACK;
            }
            break;
        case STATE_SND_SEQ_X_ACK:
            if (rcvACKX) {
                // Have received the correct ACK, clear send buffer and move to next seq num
                sent = true;
                sndState = STATE_SND_SEQ_Y;
                sndBuffer.tail = sndBuffer.buffer;
            } else if (MS_TIMER_get_time_ms() - sentTime > COMMS_TIMEOUT) {
                // No ACK received in time, resend message
                sndState = STATE_SND_SEQ_X;
            }
            break;
        case STATE_SND_SEQ_Y:
            if (!sent) {
                // Prepend the sequence number and send, starting the timeout timer
                sndBuffer.buffer[0] = SND_SEQNUM_Y + ASCII_OFFSET;
                send_buffer(&sndBuffer, BLUETOOTH_UART_NUM, false);
                sentTime = MS_TIMER_get_time_ms();
                sndState = STATE_SND_SEQ_Y_ACK;
            }
            break;
        case STATE_SND_SEQ_Y_ACK:
            if (rcvACKY) {
                // Have received the correct ACK, clear send buffer and move to next seq num
                sent = true;
                sndState = STATE_SND_SEQ_X;
                sndBuffer.tail = sndBuffer.buffer;
            } else if (MS_TIMER_get_time_ms() - sentTime > COMMS_TIMEOUT) {
                // No ACK received in time, resend message
                sndState = STATE_SND_SEQ_Y;
            }
            break;
    }
    rcvACKX = false;
    rcvACKY = false;
    /*
    uint8_t seqNum = packetBuffer.buffer[0] - ASCII_OFFSET;
            if (seqNum != receiveSeq) {
                print_debug("Incorrect Seq Num. Expected: ", 29, false);
                receiveSeq += ASCII_OFFSET;
                print_debug(&receiveSeq, 1, false);
                receiveSeq -= ASCII_OFFSET;
                print_debug(", Got: ", 7, false);
                print_debug(packetBuffer.buffer, 1, true);
            } else if (compare_strings((packetBuffer.buffer + 1), "MOV", 3)) {
                print_debug("Move Command Received:", 22, true);
                print_debug("Distance = ", 11, false);
                print_debug((packetBuffer.buffer + 4), 4, false);
                print_debug("mm", 2, true);
                
                sendSeq += ASCII_OFFSET;
                copy_to_buffer(&commandBuffer, &sendSeq, 1, true);
                sendSeq -= ASCII_OFFSET;
                copy_to_buffer(&commandBuffer, "ACK", 3, false);
                
                seqNum += ASCII_OFFSET;
                copy_to_buffer(&commandBuffer, &seqNum, 1, false);
                seqNum -= ASCII_OFFSET;
                copy_to_buffer(&commandBuffer, "\r\n", 2, false);
                
                if (receiveSeq == 1) {
                    receiveSeq = 0;
                } else {
                    receiveSeq = 1;
                }
                if (sendSeq == 3) {
                    sendSeq = 2;
                } else {
                    sendSeq = 3;
                }
                
                    send_buffer(&commandBuffer, BLUETOOTH_UART_NUM, true);
            } else if (compare_strings((packetBuffer.buffer + 1), "SPD", 3)) {
                print_debug("Speed Command Received:", 23, true);
                print_debug("Speed = ", 8, false);
                print_debug((packetBuffer.buffer + 4), 3, false);
                print_debug("mm/s", 4, true);
                
                sendSeq += ASCII_OFFSET;
                copy_to_buffer(&commandBuffer, &sendSeq, 1, true);
                sendSeq -= ASCII_OFFSET;
                copy_to_buffer(&commandBuffer, "ACK", 3, false);
                
                seqNum += ASCII_OFFSET;
                copy_to_buffer(&commandBuffer, &seqNum, 1, false);
                seqNum -= ASCII_OFFSET;
                copy_to_buffer(&commandBuffer, "\r\n", 2, false);
                
                if (receiveSeq == 1) {
                    receiveSeq = 0;
                } else {
                    receiveSeq = 1;
                }
                if (sendSeq == 3) {
                    sendSeq = 2;
                } else {
                    sendSeq = 3;
                }
                
                    send_buffer(&commandBuffer, BLUETOOTH_UART_NUM, true);
            } else {
                print_debug("Invalid Command: ", 17, false);
                print_debug(packetBuffer.buffer + 1, packetBuffer.tail - packetBuffer.buffer -1, false);
            }
            packetBuffer.tail = packetBuffer.buffer;
     * */
}

int main(void) {
    // initialize the device
    //SYSTEM_Initialize();
    PIN_MANAGER_Initialize();
    INTERRUPT_Initialize();
    CLOCK_Initialize();
    UART_Initialise();
    MS_TIMER_Initialize();
    init_debug();
    
    IO_RB0_SetDirection(PIN_DIRECTION_OUTPUT); // U2Tx
    IO_RB0_SetPin(PIN_STATE_ON); // Initial UART Condition
    IO_RB1_SetDirection(PIN_DIRECTION_INPUT); // U2Rx
    
    IO_RB7_SetDirection(PIN_DIRECTION_OUTPUT); // U1Tx
    IO_RB7_SetPin(PIN_STATE_ON); // Initial UART Condition
    IO_RB2_SetDirection(PIN_DIRECTION_INPUT); // U1Rx
    
    IO_RB5_SetDirection(PIN_DIRECTION_INPUT); // SDA1
    IO_RB6_SetDirection(PIN_DIRECTION_INPUT); // SCL1
    
    IO_RB3_SetDirection(PIN_DIRECTION_INPUT); // BT State
    IO_RA1_SetDirection(PIN_DIRECTION_OUTPUT); // BT Enable
    
    AT_PIN_Clear();

    PC_CLEAR_RX_BUFFER();
    PC_CLEAR_TX_BUFFER();
    
    init_bluetooth();
    init_comms();
    
    BUFFER_OBJ testRcvBuffer;
    init_buffer(&testRcvBuffer, 32 + 2 - 1);
    BUFFER_OBJ testingBuffer;
    init_buffer(&testingBuffer, 32 + 2 - 1);
    
    uint8_t pcrxStatus;
    bool takingInput = true;

    while (1) {
        process_comms();
        if (comms_get_packet(&testRcvBuffer)) {
            print_debug("Got: ", 5, false);
            print_debug(testRcvBuffer.buffer, testRcvBuffer.tail - testRcvBuffer.buffer, false);
        }
        if (takingInput) {
            pcrxStatus = read_line_to_buffer(&testingBuffer, PC_UART_NUM, 1);
            if (pcrxStatus == UART_READ_LINE_RECEIVED) {
                if (takingInput = comms_send(&testingBuffer)) {
                    testingBuffer.tail = testingBuffer.buffer;
                }
            }
        } else {
            if (takingInput = comms_send(&testingBuffer)) {
                testingBuffer.tail = testingBuffer.buffer;
            }
        }
    }
}

//////////////////////////////////////////
/*
int main(void) {
    // initialize the device
    //SYSTEM_Initialize();
    
    PIN_MANAGER_Initialize();
    INTERRUPT_Initialize();
    CLOCK_Initialize();
    MS_TIMER_Initialize();
    //UART_Initialise();
    //Hardware_PWM_Initialise();
    
    
    IO_RB3_SetDirection(PIN_DIRECTION_OUTPUT); // BT State
    IO_RA1_SetDirection(PIN_DIRECTION_OUTPUT); // BT Enable
    
    //IO_RB13_SetDirection(PIN_DIRECTION_OUTPUT);
    uint16_t dc = 0;
    /*
    HARDWARE_PWM_PERIOD_SET_US(JOINT_2_PWM, 1000);
    HARDWARE_PWM_DUTY_CYCLE_SET(JOINT_2_PWM, dc);
    HARDWARE_PWM_ENABLE();
    HARDWARE_PWM_JOINT_2_START();
    *
    
    uint8_t counts = 0;
    
    while (1) {
        // Add your application code
        
        
        
        
        /*
        HARDWARE_PWM_DUTY_CYCLE_SET(JOINT_2_PWM, dc);
        MS_TIMER_Delay_ms(100);
        dc += 10;
        if (dc > 1000) {
            dc = 0;
            counts++;
            if (counts > 2) {
                HARDWARE_PWM_JOINT_2_STOP();
            }
        }*
    }

    return 1;
}
*/
/**
 End of File
 */

