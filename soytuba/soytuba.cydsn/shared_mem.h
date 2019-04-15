#ifndef SHARED_MEM_H
#define SHARED_MEM_H

#include <stdint.h>
#include "queue.h"

#define SHARED_MEM_PRESSURE_N (3)

typedef struct tag_shared_mem_t {
    // identify
    uint16_t identify;
    // imu
    int16_t acc[3]; // 16bit, 2-compl, 正規化していないのでそのままフルスケール
    int16_t gyro[3]; // 16bit, 2-compl, 正規化していないのでそのままフルスケール。動かしていなければほぼ0
    // sensor value
    uint16_t adc_slider; // 12bit, abs, 触っていないと0xf00~0xfffあたりをさまよう。先端に触れると0、根本で0xf00付近
    uint16_t adc_pressure[SHARED_MEM_PRESSURE_N]; // 12bit, abs, 触れないと0xfcxあたり。軽く握って0x9xx, 強くて0x5xx、全力で0x2xxあたり
    // led
    uint8_t led[3]; // r,g,b 設定した分だけ光るが非線形な補正をしていないので0x00~0x10でほぼ飽和すると思っていい
    // for debug
    uint16_t counter;
    // calculated value
    
    //status
} shared_mem_t;
volatile shared_mem_t shared_mem;

void shared_mem_dma_init();
void shared_mem_init();

#endif
