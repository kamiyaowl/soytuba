#include "shared_mem.h"
/////////////////////////////////////////////////////////////
// init DMA

void shared_mem_dma_init() {
}

/////////////////////////////////////////////////////////////
// init

void shared_mem_init() {
    shared_mem.identify = 0xa53c;
    shared_mem.counter = 0x0;
    shared_mem.adc_slider = 0;
    for(uint8_t i = 0 ; i < SHARED_MEM_PRESSURE_N ; ++i) {
        shared_mem.adc_pressure[i] = 0;
    }
    shared_mem.led[0] = 0;
    shared_mem.led[1] = 0;
    shared_mem.led[2] = 0;

    shared_mem.tapping = 0;
    shared_mem_dma_init();
}
