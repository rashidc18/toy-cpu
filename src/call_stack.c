#include <stdint.h>

#include "stack.h"
#include "cpu.h"
#include "ram.h"
#include "bytes.h"

void call_stack_push(CPU* cpu, RAM* ram, int address) {
  uint8_t byte1, byte2, byte3, byte4;
  i2b(address, &byte1, &byte2, &byte3, &byte4);

  ram->data[cpu->csp--] = byte1;
  ram->data[cpu->csp--] = byte2;
  ram->data[cpu->csp--] = byte3;
  ram->data[cpu->csp--] = byte4;
}

int call_stack_pop(CPU* cpu, RAM* ram) {
  uint8_t byte1, byte2, byte3, byte4;

  byte4 = ram->data[++cpu->csp];
  byte3 = ram->data[++cpu->csp];
  byte2 = ram->data[++cpu->csp];
  byte1 = ram->data[++cpu->csp];

  return b2i(byte1, byte2, byte3, byte4);
}
