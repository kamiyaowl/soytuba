#include "project.h"

#include "shared_mem.h"
#include "ymf825.h"
#include "debug.h"
#include "analog_in.h"

void init() {
    shared_mem_init();
    debug_init();
    analog_in_init();

    // TODO: YMF825の音色調整、切り替え
    ymf825_init();
    ymf825_set_tone();
    ymf825_set_ch();

    
 }
int main(void) {
    init();
    CyGlobalIntEnable; 

    for(;;) {
        debug_count();
        analog_in_update();
        
        debug_print_hex("slider", shared_mem.adc_slider);
        debug_print_hex("pressure[0]", shared_mem.adc_pressure[0]);
        debug_print_hex("pressure[1]", shared_mem.adc_pressure[1]);
        debug_print_hex("pressure[2]", shared_mem.adc_pressure[2]);
        ymf825_test();
    }
}

