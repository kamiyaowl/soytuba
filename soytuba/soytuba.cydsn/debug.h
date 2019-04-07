
#ifndef DEBUG_H
#define DEBUG_H
    
#include "project.h"
#include "shared_mem.h"

void debug_init();
void debug_println(const char* str);
void debug_print_data(const char* name, uint32_t data);

#endif
