#include "led.h"

void led_init(){
    PWM_R_Start();
    PWM_G_Start();
    PWM_B_Start();
}
void led_update(){
    shared_mem.led[0] = shared_mem.tapping ? 0xff : 0x0;
    shared_mem.led[1] = shared_mem.has_keyon ? 0xff : 0x0;
    shared_mem.led[2] = 0xff;

    // TODO:これもDMA化できる
    PWM_R_WriteCompare(shared_mem.led[0]);
    PWM_G_WriteCompare(shared_mem.led[1]);
    PWM_B_WriteCompare(shared_mem.led[2]);
}
