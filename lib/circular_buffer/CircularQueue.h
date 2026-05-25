// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <inttypes.h>

typedef struct{
    uint8_t *buffer;     // stores bytes
    uint8_t queue_size; // the actual max size is 128 due to the modulo hack (todo: search possible solutions if bottleneck)
    volatile uint8_t write_idx;
    volatile uint8_t read_idx;
} CircularQueue_t;

void CircularQueue_init(CircularQueue_t *cb, uint8_t *buffer, uint8_t queue_size);
uint8_t CircularQueue_push(CircularQueue_t *cb, uint8_t packet);
uint8_t CircularQueue_pop(CircularQueue_t *cb, uint8_t *packet);

static inline uint8_t CircularQueue_next_idx(uint8_t current_idx, uint8_t queue_size){
    // a little hack to avoid modulo operation (queue_size must be 2^n)
    return (uint8_t)((current_idx + 1) & (queue_size - 1));
}

static inline uint8_t CircularQueue_is_empty(CircularQueue_t *cb){
  return cb->read_idx==cb->write_idx;
}

static inline uint8_t CircularQueue_is_full(CircularQueue_t *cb){
  return cb->read_idx == CircularQueue_next_idx(cb->write_idx, cb->queue_size);
}