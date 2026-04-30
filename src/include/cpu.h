#ifndef _CPU_H
#define _CPU_H

#include <stdint.h>

typedef struct {
  int pc;  /* program counter */
  int sp;  /* stack pointer */
  int csp; /* call stack pointer*/
  uint8_t on;
} CPU;

CPU* new_cpu();

#endif
