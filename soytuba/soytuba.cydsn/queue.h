#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>
#define QUEUE_SIZE_N (16)

// なんかもうCだるいしめんどいのでQueueに直接書いちゃう
typedef struct tag_sound_command_t {
    uint8_t keyon; // 音を鳴らすかどうか
    uint8_t  block; // オクターブ選択 3bit
    uint16_t fnum;  // 周波数: 10bit
    uint8_t vol; // 音量 4bit
    uint8_t interpolation; // 途中を補完するか YMFのレジスタ上では負論理なので注意(DIR_MT): 1bit
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