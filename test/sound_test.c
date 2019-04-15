#include <stdio.h>

#include "shared_mem.h"
#include "sound.h"
#include "queue.h"

void initialize() {
    shared_mem_init();
    sound_init();
}
int main(void) {
    initialize();

    printf("test\n");
    return 0;
}