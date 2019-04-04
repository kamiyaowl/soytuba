#include "project.h"

int main(void) {
    CyGlobalIntEnable; 

    for(;;) {
        OnBoard_LED_Write(0x1);
        CyDelay(1000);
        OnBoard_LED_Write(0x0);
        CyDelay(1000);
    }
}

