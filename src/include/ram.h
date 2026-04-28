#ifndef _RAM_H
#define _RAM_H

#include <stdint.h>

#define RAM_SIZE 256

typedef struct {
  uint8_t data[RAM_SIZE];
} RAM;

RAM* new_ram();

#endif
