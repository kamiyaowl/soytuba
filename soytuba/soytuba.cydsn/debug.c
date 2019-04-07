#include "debug.h"

//#define DEBUG_MEM_N (0x2f)
//volatile uint8_t debug_mem[DEBUG_MEM_N] = {};

void debug_init() {
    EZI2C_DEBUG_Start();
//    EZI2C_DEBUG_SetBuffer1(DEBUG_MEM_N, 0, debug_mem);
    EZI2C_DEBUG_SetBuffer1(sizeof(shared_mem), 0, (uint8_t*)&shared_mem);
    
    UART_DEBUG_Start();
}
void debug_update() {
//    // 更新確認用カウンタ
//    debug_mem[DEBUG_MEM_N - 1]++;
//    // 0x00 ~ 0x0f: adc
//    debug_mem[0x00] = (shared_mem.adc_slider >> 24) & 0xff;
//    debug_mem[0x01] = (shared_mem.adc_slider >> 16) & 0xff;
//    debug_mem[0x02] = (shared_mem.adc_slider >> 8)  & 0xff;
//    debug_mem[0x03] = (shared_mem.adc_slider >> 0)  & 0xff;
//    
//    debug_mem[0x04] = (shared_mem.adc_pressure[0] >> 24) & 0xff;
//    debug_mem[0x05] = (shared_mem.adc_pressure[0] >> 16) & 0xff;
//    debug_mem[0x06] = (shared_mem.adc_pressure[0] >> 8)  & 0xff;
//    debug_mem[0x07] = (shared_mem.adc_pressure[0] >> 0)  & 0xff;
//
//    debug_mem[0x08] = (shared_mem.adc_pressure[1] >> 24) & 0xff;
//    debug_mem[0x09] = (shared_mem.adc_pressure[1] >> 16) & 0xff;
//    debug_mem[0x0a] = (shared_mem.adc_pressure[1] >> 8)  & 0xff;
//    debug_mem[0x0b] = (shared_mem.adc_pressure[1] >> 0)  & 0xff;
//
//    debug_mem[0x0c] = (shared_mem.adc_pressure[2] >> 24) & 0xff;
//    debug_mem[0x0d] = (shared_mem.adc_pressure[2] >> 16) & 0xff;
//    debug_mem[0x0e] = (shared_mem.adc_pressure[2] >> 8)  & 0xff;
//    debug_mem[0x0f] = (shared_mem.adc_pressure[2] >> 0)  & 0xff;
//    // 0x10 ~ 0x1f: acc
//    debug_mem[0x10] = (shared_mem.acc[0] >> 24) & 0xff;
//    debug_mem[0x11] = (shared_mem.acc[0] >> 16) & 0xff;
//    debug_mem[0x12] = (shared_mem.acc[0] >> 8)  & 0xff;
//    debug_mem[0x13] = (shared_mem.acc[0] >> 0)  & 0xff;
//
//    debug_mem[0x14] = (shared_mem.acc[1] >> 24) & 0xff;
//    debug_mem[0x15] = (shared_mem.acc[1] >> 16) & 0xff;
//    debug_mem[0x16] = (shared_mem.acc[1] >> 8)  & 0xff;
//    debug_mem[0x17] = (shared_mem.acc[1] >> 0)  & 0xff;
//
//    debug_mem[0x18] = (shared_mem.acc[2] >> 24) & 0xff;
//    debug_mem[0x19] = (shared_mem.acc[2] >> 16) & 0xff;
//    debug_mem[0x1a] = (shared_mem.acc[2] >> 8)  & 0xff;
//    debug_mem[0x1b] = (shared_mem.acc[2] >> 0)  & 0xff;
//    // 0x20 ~ 0x2f: gyro
//    debug_mem[0x20] = (shared_mem.gyro[0] >> 24) & 0xff;
//    debug_mem[0x21] = (shared_mem.gyro[0] >> 16) & 0xff;
//    debug_mem[0x22] = (shared_mem.gyro[0] >> 8)  & 0xff;
//    debug_mem[0x23] = (shared_mem.gyro[0] >> 0)  & 0xff;
//
//    debug_mem[0x24] = (shared_mem.gyro[1] >> 24) & 0xff;
//    debug_mem[0x25] = (shared_mem.gyro[1] >> 16) & 0xff;
//    debug_mem[0x26] = (shared_mem.gyro[1] >> 8)  & 0xff;
//    debug_mem[0x27] = (shared_mem.gyro[1] >> 0)  & 0xff;
//
//    debug_mem[0x28] = (shared_mem.gyro[2] >> 24) & 0xff;
//    debug_mem[0x29] = (shared_mem.gyro[2] >> 16) & 0xff;
//    debug_mem[0x2a] = (shared_mem.gyro[2] >> 8)  & 0xff;
//    debug_mem[0x2b] = (shared_mem.gyro[2] >> 0)  & 0xff;
}