#include "shared_mem.h"
/////////////////////////////////////////////////////////////
// init DMA

void shared_mem_dma_init() {
}

/////////////////////////////////////////////////////////////
// init

void shared_mem_init() {
    shared_mem.adc_slider = 0;
    for(uint8_t i = 0 ; i < SHARED_MEM_PRESSURE_N ; ++i) {
        shared_mem.adc_pressure[i] = 0;
    }
    shared_mem_dma_init();
}