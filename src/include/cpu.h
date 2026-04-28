#ifndef _CPU_H
#define _CPU_H

#include <stdint.h>

typedef struct {
  int pc;
  int sp;
  uint8_t on;
} CPU;

CPU* new_cpu();

#endif
