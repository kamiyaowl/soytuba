#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>
#define QUEUE_SIZE_N (16)

// なんかもうCだるいしめんどいのでQueueに直接書いちゃう
typedef enum enum_sound_status {
    KeyOff, KeyOn, Mute,
} sound_status;

typedef struct tag_sound_command_t {
    sound_status keyon; // 音を鳴らすかどうか
    uint16_t vovol; // 音声設定
    uint8_t  block; // オクターブ選択
    uint16_t fnum;  // 周波数
    uint8_t vol; // 音量 4bit
    uint8_t vibrato; // ビブラード(DVB) 3bit
    uint8_t interpolation; // 途中を補完するか 0=enable(default)
} sound_command_t;

typedef sound_command_t queue_type_t; // c言語残念すぎでは

void queue_init();
uint8_t queue_enqueue(queue_type_t data);
uint8_t queue_dequeue(queue_type_t* data);

// enqueueで全コピーが入るとめっちゃ遅いので
queue_type_t* queue_get_enqueue_ptr();
void queue_enqueue_ptr();

uint8_t queue_head(queue_type_t* data);
uint8_t queue_tail(queue_type_t* data);

uint32_t queue_count();

#endif