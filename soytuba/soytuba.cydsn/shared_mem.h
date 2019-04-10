#ifndef SHARED_MEM_H
#define SHARED_MEM_H

#include "project.h"
    
#define SHARED_MEM_PRESSURE_N (3)

struct shared_mem_t {
    uint8_t id;// imu chipid(debug)
    
    uint16_t acc[3];
    uint16_t gyro[3];
    // identify
    uint16_t identify;
    // for debug
    uint16_t counter;
    // sensor value
    uint16_t adc_slider;
    uint16_t adc_pressure[SHARED_MEM_PRESSURE_N];
    // led
    uint8_t led[3]; // r,g,b
    // calculated value
    
    //status
};
volatile struct shared_mem_t shared_mem;

void shared_mem_dma_init();
void shared_mem_init();

#endif
