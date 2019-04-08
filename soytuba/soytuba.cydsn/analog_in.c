#include "analog_in.h"

void analog_in_init() {
    ADC_SAR_Start();
    ADC_SAR_StartConvert();
}
void analog_in_update() {
    shared_mem.adc_slider = ADC_SAR_GetResult16(0);
    shared_mem.adc_pressure[0] = ADC_SAR_GetResult16(1);
    shared_mem.adc_pressure[1] = ADC_SAR_GetResult16(2);
    shared_mem.adc_pressure[2] = ADC_SAR_GetResult16(3);
}
