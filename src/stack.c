#include <stdint.h>

#include "stack.h"
#include "cpu.h"
#include "ram.h"
#include "error.h"
#include "bytes.h"

void stack_push_byte(CPU* cpu, RAM* ram, uint8_t byte) {
  if (cpu->sp < STACK_END)
    error(STACK_OVERFLOW_ERROR);

  ram->data[cpu->sp--] = byte;
}

void stack_push_int(CPU* cpu, RAM* ram, int value) {
  uint8_t byte1, byte2, byte3, byte4;
  i2b(value, &byte1, &byte2, &byte3, &byte4);
  stack_push_byte(cpu, ram, byte1);
  stack_push_byte(cpu, ram, byte2);
  stack_push_byte(cpu, ram, byte3);
  stack_push_byte(cpu, ram, byte4);
}

uint8_t stack_pop_byte(CPU* cpu, RAM* ram) {
  if (cpu->sp >= STACK_START)
    error(STACK_UNDERFLOW_ERROR);

  return ram->data[++cpu->sp];
}

int stack_pop_int(CPU *cpu, RAM* ram) {
  uint8_t byte1, byte2, byte3, byte4;
  byte4 = stack_pop_byte(cpu, ram);
  byte3 = stack_pop_byte(cpu, ram);
  byte2 = stack_pop_byte(cpu, ram);
  byte1 = stack_pop_byte(cpu, ram);
  
  return b2i(
    byte1,
    byte2,
    byte3,
    byte4
  );
}
