#include "xc.h"
#include "imu.h"
#include "ms_timer.h"
#include "mcc_generated_files/mssp1_i2c.h"

#define DEVICE_ID 0xA0
#define DEVICE_ADDRESS 0x29

#define CHIP_ID_REGISTER 0x00
#define OP_MODE_REGISTER 0x3D
#define PWR_MODE_REGISTER 0x3E
#define SYS_TRIGGER_REGISTER 0x3F

uint8_t opMode = OPERATION_MODE_CONFIG;

void imu_initialise(void) {
    set_mode(OPERATION_MODE_CONFIG);
    
    // Reset
    write(SYS_TRIGGER_REGISTER, 0b00100000);
    MS_TIMER_Delay_ms(30);
    uint8_t id;
    do {
        read(CHIP_ID_REGISTER, &id, 1);
        MS_TIMER_Delay_ms(10);
    } while (id != DEVICE_ID);
    MS_TIMER_Delay_ms(50);
    
    write(PWR_MODE_REGISTER, PWR_MODE_NORMAL);
    MS_TIMER_Delay_ms(10);
    
    write(SYS_TRIGGER_REGISTER, 0x00);
    MS_TIMER_Delay_ms(10);
}

bool read(uint8_t reg, uint8_t *buffer, uint8_t len) {
    MSSP1_I2C_MESSAGE_STATUS status = MSSP1_I2C_MESSAGE_PENDING;
    MSSP1_I2C_TRANSACTION_REQUEST_BLOCK readTRB[2];

    uint16_t timeOut = 0;
    uint16_t slaveTimeOut = 0;

    MSSP1_I2C_MasterWriteTRBBuild(readTRB, &reg, 1, DEVICE_ADDRESS);

    MSSP1_I2C_MasterReadTRBBuild(readTRB + 1, buffer, len, DEVICE_ADDRESS);

    while (status != MSSP1_I2C_MESSAGE_FAIL) {
        MSSP1_I2C_MasterTRBInsert(2, readTRB, &status);
        while (status == MSSP1_I2C_MESSAGE_PENDING) {
            MS_TIMER_Delay_ms(50);
            // timeout checking
            // check for max retry and skip this byte
            if (slaveTimeOut == 10) {
                return false;
            } else {
                slaveTimeOut++;
            }
        }
        if (status == MSSP1_I2C_MESSAGE_COMPLETE) {
            break;
        }

        if (timeOut == 3) {
            return false;
        } else {
            timeOut++;
        }
    }
    return true;
}

bool write(uint8_t reg, uint8_t value) {
    MSSP1_I2C_MESSAGE_STATUS status = MSSP1_I2C_MESSAGE_PENDING;
    MSSP1_I2C_TRANSACTION_REQUEST_BLOCK writeTRB;

    uint16_t timeOut = 0;
    uint16_t slaveTimeOut = 0;
    
    uint8_t writeBuffer[2] = {reg, value};
    
    while (status != MSSP1_I2C_MESSAGE_FAIL) {
        MSSP1_I2C_MasterWrite(writeBuffer, 2, DEVICE_ADDRESS, &status);
        while (status == MSSP1_I2C_MESSAGE_PENDING) {
            MS_TIMER_Delay_ms(50);
            // timeout checking
            // check for max retry and skip this byte
            if (slaveTimeOut == 10) {
                return false;
            } else {
                slaveTimeOut++;
            }
        }
        if (status == MSSP1_I2C_MESSAGE_COMPLETE) {
            break;
        }

        if (timeOut == 3) {
            return false;
        } else {
            timeOut++;
        }
    }
    return true;
}

void set_mode(uint8_t mode) {
    opMode = mode;
    write(OP_MODE_REGISTER, opMode);
    MS_TIMER_Delay_ms(30);
}

VECTOR_OBJ get_vector(vector_type_t vector) {
    uint8_t buffer[6];

    read((uint8_t) vector, buffer, 6);

    VECTOR_OBJ result;
    result.x = ((int16_t) buffer[0]) | (((int16_t) buffer[1]) << 8);
    result.y = ((int16_t) buffer[2]) | (((int16_t) buffer[3]) << 8);
    result.z = ((int16_t) buffer[4]) | (((int16_t) buffer[5]) << 8);
/*    
    switch(vector) {
        case VECTOR_EULER:
            result.x /= 16;
            result.y /= 16;
            result.z /= 16;
            break;
        case VECTOR_LINACCEL:
            result.x /= 100;
            result.y /= 100;
            result.z /= 100;
            break;
    }
*/
    return result;
}
