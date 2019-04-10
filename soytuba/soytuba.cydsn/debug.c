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
// 遅い
void debug_print_int16(const char* name, int16_t src){
    UART_DEBUG_PutString(name);
    uint16_t data;
    if (src > -1) {
        data = src;
        UART_DEBUG_PutString(": +");
    } else {
        data = (uint16_t)(-src);
        UART_DEBUG_PutString(": -");
    }
    // 全部で10桁、下の桁から処理する
    uint8_t nums[10] = {};
    for(uint8_t i = 0 ; i < 10 ; ++i) {
        nums[9 - i] = data % 10;
        data /= 10;
    }
    // 上から表示
    uint8_t visible = 0x0;// 0 paddingしない
    for(uint8_t i = 0 ; i < 10 ; ++i) {
        if (!nums[i] && !visible) {
            continue;
        } else {
            visible = 0x1;
            UART_DEBUG_PutChar(nums[i] + '0');
        }
    }
    if (!visible){
        UART_DEBUG_PutChar('0');
    }
    UART_DEBUG_PutString("\r\n");
}

void debug_print_hex(const char* name, uint32_t data){
    UART_DEBUG_PutString(name);
    UART_DEBUG_PutString(": 0x");
    
    for(uint8_t i = 0 ; i < 8 ; ++i) {
        uint8_t d = (data >> ((7 - i) * 4)) & 0xf;
        uint8_t c = (d < 10) ? ('0' + d) : ('a' + d - 10);
        UART_DEBUG_PutChar(c);
    }
    UART_DEBUG_PutString("\r\n");
}
void debug_count(){
    shared_mem.counter++;
}
