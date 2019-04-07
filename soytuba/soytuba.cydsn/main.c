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
    ADC_SAR_Start();
    ADC_SAR_StartConvert();
 }
int main(void) {
    init();
    CyGlobalIntEnable; 

    volatile uint16_t hoge;
    volatile uint16_t fuga;
    for(;;) {
        hoge = ADC_SAR_GetResult16(0);
        fuga = ADC_SAR_GetResult16(3);
        ymf825_test();
    }
}

