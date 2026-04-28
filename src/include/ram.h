#ifndef _RAM_H
#define _RAM_H

#include <stdint.h>

#define RAM_SIZE 256

#define STACK_SIZE 20
#define STACK_START (RAM_SIZE - 1)
#define STACK_END (STACK_START - STACK_SIZE + 1)

typedef struct {
  uint8_t data[RAM_SIZE];
} RAM;

RAM* new_ram();

#endif
