#ifndef _RAM_H
#define _RAM_H

#include <stdint.h>

#define RAM_SIZE          65536
#define CODE_START            0
#define CODE_END           8191
#define DATA_START         8192
#define DATA_END          12287
#define HEAP_START        12288
#define HEAP_END          49151
#define CALL_STACK_END    49152
#define CALL_STACK_START  57343
#define STACK_END         57344
#define STACK_START       65535

typedef struct {
  uint8_t data[RAM_SIZE];
} RAM;

RAM* new_ram();
void ram_write(RAM* ram, int position, uint8_t byte);

#endif
