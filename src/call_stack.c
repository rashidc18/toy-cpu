#include <stdint.h>

#include "stack.h"
#include "cpu.h"
#include "ram.h"
#include "bytes.h"
#include "error.h"
#include "call_stack.h"

void call_stack_push(CPU* cpu, RAM* ram, int address) {
  if (cpu->csp < CALL_STACK_END)
    error(CALL_STACK_OVERFLOW_ERROR);

  uint8_t byte1, byte2, byte3, byte4;
  i2b(address, &byte1, &byte2, &byte3, &byte4);

  ram->data[cpu->csp--] = byte1;
  ram->data[cpu->csp--] = byte2;
  ram->data[cpu->csp--] = byte3;
  ram->data[cpu->csp--] = byte4;
}

int call_stack_pop(CPU* cpu, RAM* ram) {
  if (cpu->csp >= CALL_STACK_START)
    error(CALL_STACK_UNDERFLOW_ERROR);
  
  uint8_t byte1, byte2, byte3, byte4;

  byte4 = ram->data[++cpu->csp];
  byte3 = ram->data[++cpu->csp];
  byte2 = ram->data[++cpu->csp];
  byte1 = ram->data[++cpu->csp];

  return b2i(byte1, byte2, byte3, byte4);
}
