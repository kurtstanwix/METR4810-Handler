#ifndef IMU_H
#define	IMU_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#define PWR_MODE_NORMAL 0x00

#define OPERATION_MODE_CONFIG 0x00
#define OPERATION_MODE_NDOF 0x0C

typedef struct vector {
    int16_t x;
    int16_t y;
    int16_t z;
} VECTOR_OBJ;

typedef enum vector_type {
    VECTOR_EULER = 0x1A,
    VECTOR_LINACCEL = 0x28
} vector_type_t;

void imu_initialise(void);

bool read(uint8_t reg, uint8_t *buffer, uint8_t len);

bool write(uint8_t reg, uint8_t value);

void set_mode(uint8_t mode);

VECTOR_OBJ get_vector(vector_type_t vector);

#endif	// IMU_H

