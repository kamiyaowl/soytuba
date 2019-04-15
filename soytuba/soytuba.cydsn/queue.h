#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>
#include "sound.h"

#define QUEUE_SIZE_N (16)

typedef uint8_t queue_type_t; // c言語残念すぎでは

void queue_init();
uint8_t queue_enqueue(queue_type_t data);
uint8_t queue_dequeue(queue_type_t* data);

uint8_t queue_head(queue_type_t* data);
uint8_t queue_tail(queue_type_t* data);

uint32_t queue_count();

#endif