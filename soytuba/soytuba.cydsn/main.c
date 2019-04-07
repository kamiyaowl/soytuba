#include "project.h"

#include "shared_mem.h"
#include "ymf825.h"

uint16_t slider_value = 0;

void init() {
    shared_mem_init();
    
    ymf825_init();
    ymf825_set_tone();
    ymf825_set_ch();
    
    ADC_SLIDER_AMux_Start();
 }
int main(void) {
    init();
    
    CyGlobalIntEnable; 

    for(;;) {
        ymf825_test();
    }
}

