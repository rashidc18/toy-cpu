#ifndef _RAM_H
#define _RAM_H

#include <stdint.h>

#define RAM_SIZE 4096

typedef struct {
  uint8_t data[RAM_SIZE];
} RAM;

RAM* new_ram();
void ram_write(RAM* ram, int position, uint8_t byte);

#endif
