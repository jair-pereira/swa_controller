/*
Implementation of a CircularQueue to store bytes
  - full when read==write 
    - to decide: keep this check or simply overwrite?
  - avoid modulo operation but requires size to be 2^n
    - for 1 byte, it makes the max size only 128 
    - to decide: other ways to handle this 

Copyright (C) 2026  Jair Pereira Junior
SPDX-License-Identifier: GPL-3.0-or-later

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "CircularQueue.h"
#include <inttypes.h>
#include <util/atomic.h> 

void CircularQueue_init(CircularQueue_t *cb, uint8_t *buffer, uint8_t queue_size){
  cb->buffer = buffer;
  cb->queue_size  = queue_size;
  cb->read_idx  = 0;
  cb->write_idx = 0;
}

uint8_t CircularQueue_push(CircularQueue_t *cb, uint8_t packet){
  uint8_t success = 0;

  ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
    uint8_t next = CircularQueue_next_idx(cb->write_idx, cb->queue_size);
    if(next != cb->read_idx){ // full when next_write==read
      cb->buffer[cb->write_idx] = packet;
      cb->write_idx = next;
      success = 1;
    }
  }

  return success;
}

uint8_t CircularQueue_pop(CircularQueue_t *cb, uint8_t *packet){
	uint8_t success = 0;

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		if(!CircularQueue_is_empty(cb)){
			*packet = cb->buffer[cb->read_idx];
			cb->read_idx = CircularQueue_next_idx(cb->read_idx, cb->queue_size);
			success = 1;
		}
	}

	return success;
}