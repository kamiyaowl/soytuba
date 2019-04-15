#ifndef SOUND_H
#define SOUND_H

#include "shared_mem.h"
#include <stdint.h>

typedef enum enum_sound_status {
    KeyOff, KeyOn, Mute,
} sound_status;

typedef struct tag_sound_control_t {
    sound_status keyon; // 音を鳴らすかどうか
    uint16_t vovol; // 音声設定
    uint8_t  block; // オクターブ選択
    uint16_t fnum;  // 周波数
    uint8_t vol; // 音量 4bit
    uint8_t vibrato; // ビブラード(DVB) 3bit
    uint8_t interpolation; // 途中を補完するか 0=enable(default)
} sound_control_t;

void sound_init();
void sound_update();

#endif
    