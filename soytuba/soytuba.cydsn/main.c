#include "project.h"

#include "shared_mem.h"
#include "ymf825.h"
#include "debug.h"

void init() {
    shared_mem_init();
    
    ymf825_init();
    ymf825_set_tone();
    ymf825_set_ch();

    debug_init();
    
    
    // TODO: Isolate other file
    ADC_SLIDER_AMux_Start();
    ADC_SLIDER_StartConvert();
    ADC_SAR_PRESSURE_Start();
    ADC_SAR_PRESSURE_StartConvert();
 }
int main(void) {
    init();
    CyGlobalIntEnable; 

    volatile uint16_t hoge;
    volatile uint32_t fuga;
    for(;;) {
        hoge = ADC_SAR_PRESSURE_GetResult16(0);
        fuga = ADC_SLIDER_GetResult32();
        ymf825_test();
    }
}

