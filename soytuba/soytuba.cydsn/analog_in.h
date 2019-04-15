#ifndef ANALOG_IN_H
#define ANALOG_IN_H

#include "project.h"
#include "shared_mem.h"

void analog_in_init();
// TODO: DMAでやればこのタスク時間ゼロ
void analog_in_update();
    
#endif
    