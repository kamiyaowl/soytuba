#include "project.h"

#include "shared_mem.h"
#include "ymf825.h"
#include "debug.h"
#include "analog_in.h"
#include "led.h"
#include "bmi160.h"
#include "sound.h"

void init() {
    shared_mem_init();
    debug_init();
    analog_in_init();
    led_init();
    bmi160_init();
    sound_init();
    ymf825_init();
 }
int main(void) {
    init();
    CyGlobalIntEnable; 

    for(;;) {
        debug_count();
        analog_in_update();
        bmi160_update();
        sound_update();
        ymf825_update(0x1); // sound_updateで来たメッセージを音にして処理
        led_update();
        
        // test
        debug_print_hex("slider", shared_mem.adc_slider);
        debug_print_hex("pressure[0]", shared_mem.adc_pressure[0]);
        debug_print_hex("pressure[1]", shared_mem.adc_pressure[1]);
        debug_print_hex("pressure[2]", shared_mem.adc_pressure[2]);
        debug_print_int16("acc[0]", (int16_t)shared_mem.acc[0]);
        debug_print_int16("acc[1]", (int16_t)shared_mem.acc[1]);
        debug_print_int16("acc[2]", (int16_t)shared_mem.acc[2]);
        debug_print_int16("gyro[0]",(int16_t)shared_mem.gyro[0]);
        debug_print_int16("gyro[1]",(int16_t)shared_mem.gyro[1]);
        debug_print_int16("gyro[2]",(int16_t)shared_mem.gyro[2]);
        shared_mem.led[0]+=2;
        shared_mem.led[1]+=4;
        shared_mem.led[2]+=8;
        // test
    }
}

