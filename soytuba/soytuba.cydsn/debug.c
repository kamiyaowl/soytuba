#include "debug.h"

void debug_init() {
    EZI2C_DEBUG_Start();
    EZI2C_DEBUG_SetBuffer1(sizeof(shared_mem), 0, (uint8_t*)&shared_mem);
    
    UART_DEBUG_Start();
}
void debug_print(const char* str){
    UART_DEBUG_PutString(str);
}
void debug_println(const char* str){
    UART_DEBUG_PutString(str);
    UART_DEBUG_PutString("\r\n");
}
void debug_print_data(const char* name, uint32_t data){
    UART_DEBUG_PutString(name);
    UART_DEBUG_PutString(": 0x");
    
    for(uint8_t i = 0 ; i < 8 ; ++i) {
        uint8_t d = (data >> ((7 - i) * 4)) & 0xf;
        uint8_t c = (d < 10) ? ('0' + d) : ('a' + d - 10);
        UART_DEBUG_PutChar(c);
    }
    UART_DEBUG_PutString("\r\n");
}
