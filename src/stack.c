#include <stdint.h>

#include "stack.h"
#include "cpu.h"
#include "ram.h"
#include "error.h"

void stack_write(CPU* cpu, RAM* ram, uint8_t byte) {
  if (cpu->sp < STACK_END)
    error(STACK_OVERFLOW_ERROR);

  ram->data[cpu->sp--] = byte;
}

void stack_write_int(CPU* cpu, RAM* ram, int value) {
  stack_write(cpu, ram, (value >> 0) & 0xFF);
  stack_write(cpu, ram, (value >> 8) & 0xFF);
  stack_write(cpu, ram, (value >> 16) & 0xFF);
  stack_write(cpu, ram, (value >> 24) & 0xFF);
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
  
  return
    (byte1)       |
    (byte2 << 8)  |
    (byte3 << 16) |
    (byte4 << 24)
  ;
}
