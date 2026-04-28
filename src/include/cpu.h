#ifndef _CPU_H
#define _CPU_H

typedef struct {
  int pc;
  uint8_t on;
} CPU;

CPU* new_cpu();

#endif
