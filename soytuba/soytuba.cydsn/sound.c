#include "sound.h"

static sound_command_t* control;

// Queueから使える領域をもらえるまでまつ
sound_command_t* alloc_sound_control() {
    sound_command_t* ptr;
    do {
        ptr = queue_get_enqueue_ptr();
    } while(ptr == 0); // == NULL
    return ptr;
}
void sound_init() {
    // default setting
    // TODO: 領域は現物で変更可能性が高い
    shared_mem.sound_setting.slider_low_limit = 0;
    shared_mem.sound_setting.slider_high_limit = 0x0fff;

    // control allocate
    control = alloc_sound_control();
}
void sound_update() {
}
