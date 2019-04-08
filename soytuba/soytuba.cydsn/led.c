#include "led.h"

void led_init(){
    PWM_R_Start();
    PWM_G_Start();
    PWM_B_Start();
}
void led_update(){
    // TODO:これもDMA化できる
    PWM_R_WriteCompare(shared_mem.led[0]);
    PWM_G_WriteCompare(shared_mem.led[1]);
    PWM_B_WriteCompare(shared_mem.led[2]);
}
