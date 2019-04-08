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
        debug_count();
        
        debug_print_hex("adc0", ADC_SAR_GetResult16(0));
        debug_print_hex("adc1", ADC_SAR_GetResult16(1));
        debug_print_hex("adc2", ADC_SAR_GetResult16(2));
        debug_print_hex("adc3", ADC_SAR_GetResult16(3));
        // ymf825_test();
    }
}

