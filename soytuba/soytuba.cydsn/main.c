#include "project.h"

#include "shared_mem.h"
#include "ymf825.h"
#include "debug.h"
#include "analog_in.h"
#include "led.h"
#include "bmi160.h"

void init() {
    shared_mem_init();
    debug_init();
    analog_in_init();
    led_init();
    bmi160_init();
    
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
        led_update();
        bmi160_update();
        ymf825_test();
        
        // test
        debug_print_hex("slider", shared_mem.adc_slider);
        debug_print_hex("pressure[0]", shared_mem.adc_pressure[0]);
        debug_print_hex("pressure[1]", shared_mem.adc_pressure[1]);
        debug_print_hex("pressure[2]", shared_mem.adc_pressure[2]);
        debug_print_hex("id", shared_mem.id);
        debug_print_int16("acc[0]", (int16_t)shared_mem.acc[0]);
        debug_print_int16("acc[1]", (int16_t)shared_mem.acc[1]);
        debug_print_int16("acc[2]", (int16_t)shared_mem.acc[2]);
        debug_print_int16("gyro[0]",(int16_t)shared_mem.gyro[0]);
        debug_print_int16("gyro[1]",(int16_t)shared_mem.gyro[1]);
        debug_print_int16("gyro[2]",(int16_t)shared_mem.gyro[2]);
        debug_print_hex("acc[0]", shared_mem.acc[0]);
        debug_print_hex("acc[1]", shared_mem.acc[1]);
        debug_print_hex("acc[2]", shared_mem.acc[2]);
        debug_print_hex("gyro[0]", shared_mem.gyro[0]);
        debug_print_hex("gyro[1]", shared_mem.gyro[1]);
        debug_print_hex("gyro[2]", shared_mem.gyro[2]);
        shared_mem.led[0]+=2;
        shared_mem.led[1]+=4;
        shared_mem.led[2]+=8;
        // test
    }
}

