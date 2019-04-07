#include "debug.h"

void debug_init() {
    EZI2C_DEBUG_Start();
    EZI2C_DEBUG_SetBuffer1(sizeof(shared_mem), 0, (uint8_t*)&shared_mem);
    
    UART_DEBUG_Start();
}
