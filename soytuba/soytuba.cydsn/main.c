#include "project.h"
#include "ymf825.h"

int main(void) {
    ymf825_init();
    ymf825_set_tone();
    ymf825_set_ch();
    
    CyGlobalIntEnable; 

    for(;;) {
        ymf825_test();
    }
}

