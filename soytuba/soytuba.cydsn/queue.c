#include "queue.h"

static queue_type_t arr[QUEUE_SIZE_N];

// RTOS化を見込んで双参照にしたがあまり意味はない
static uint32_t wr_start_ptr;
static uint32_t wr_end_ptr;
static uint32_t rd_start_ptr;
static uint32_t rd_end_ptr;

void queue_init() {
    wr_start_ptr = 0;
    wr_end_ptr = 0;
    rd_start_ptr = 0;
    rd_end_ptr = 0;
}

uint8_t queue_enqueue(queue_type_t data) {
    if(queue_count() > QUEUE_SIZE_N - 2) {
        return 0;
    }
    arr[wr_start_ptr] = data;
    wr_start_ptr = (wr_start_ptr < QUEUE_SIZE_N - 2) ? wr_start_ptr + 1 : 0;
    rd_end_ptr = (rd_end_ptr < QUEUE_SIZE_N - 2) ? rd_end_ptr + 1 : 0;
    return 1;
}
uint8_t queue_dequeue(queue_type_t* data) {
    if(queue_count() < 1) {
        return 0;
    }
    *data = arr[rd_start_ptr];
    rd_start_ptr = (rd_start_ptr < QUEUE_SIZE_N - 2) ? rd_start_ptr + 1 : 0;
    wr_end_ptr = (wr_end_ptr < QUEUE_SIZE_N - 2) ? wr_end_ptr + 1 : 0;
    return 1;
}

queue_type_t* queue_get_enqueue_ptr() {
 if(queue_count() > QUEUE_SIZE_N - 2) {
        return NULL;
    }
    return &arr[wr_start_ptr];
}
void queue_enqueue_ptr() {
    wr_start_ptr = (wr_start_ptr < QUEUE_SIZE_N - 2) ? wr_start_ptr + 1 : 0;
    rd_end_ptr = (rd_end_ptr < QUEUE_SIZE_N - 2) ? rd_end_ptr + 1 : 0;
}


uint8_t queue_head(queue_type_t* data) {
    if(queue_count() < 1) {
        return 0;
    }
    *data = arr[rd_start_ptr];
    return 1;
}
uint8_t queue_tail(queue_type_t* data) {
    if(queue_count() < 1) {
        return 0;
    }
    *data = arr[rd_end_ptr - 1];
    return 1;
}

uint32_t queue_count() {
    uint32_t len = rd_start_ptr < rd_end_ptr ? rd_end_ptr - rd_start_ptr : rd_start_ptr - rd_end_ptr;
    return len;
}
