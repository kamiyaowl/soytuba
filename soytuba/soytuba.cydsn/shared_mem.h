#ifndef SHARED_MEM_H
#define SHARED_MEM_H

#include "project.h"
    
#define SHARED_MEM_PRESSURE_N (3)

struct shared_mem_t {
    // identify
    uint32_t identify;
    // for debug
    uint32_t counter;
    // sensor value
    uint32_t adc_slider;
    uint32_t adc_pressure[SHARED_MEM_PRESSURE_N];
    uint32_t acc[3];
    uint32_t gyro[3];
    // calculated value
    
    //status
};
volatile struct shared_mem_t shared_mem;

void shared_mem_dma_init();
void shared_mem_init();

#endif
