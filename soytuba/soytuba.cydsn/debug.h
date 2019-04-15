#ifndef DEBUG_H
#define DEBUG_H
    
#include "project.h"
#include "shared_mem.h"

void debug_init();
void debug_println(const char* str);
void debug_print_int16(const char* name, int16_t data);
void debug_print_hex(const char* name, uint32_t data);
// 処理時間測定
void debug_count();

#endif
