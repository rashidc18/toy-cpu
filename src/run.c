#include <stdio.h>
#include <stdint.h>

#include "run.h"
#include "error.h"
#include "opcodes.h"
#include "ram.h"

uint8_t fetch_instr(CPU* cpu, RAM* ram) {
  if (cpu->pc == RAM_SIZE) {
    error(MEMORY_OVERFLOW_ERROR);
  }

  return ram->data[cpu->pc++];
}

void ram_write(RAM* ram, int position, uint8_t byte) {
  if (position < 0)
    error(MEMORY_UNDERFLOW_ERROR);
  if (position >= RAM_SIZE)
    error(MEMORY_OVERFLOW_ERROR);

  ram->data[position] = byte;
}

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

void run(CPU* cpu, RAM* ram) {

  while (cpu->on) {
    uint8_t instr = fetch_instr(cpu, ram);

    switch (instr) {
      case OP_HALT:
        cpu->on = 0;
        break;

      case OP_PUSH:
        stack_write(cpu, ram, fetch_instr(cpu, ram));
        stack_write(cpu, ram, fetch_instr(cpu, ram));
        stack_write(cpu, ram, fetch_instr(cpu, ram));
        stack_write(cpu, ram, fetch_instr(cpu, ram));
        break;
      
      case OP_OUT:
        printf("%d\n", stack_pop_int(cpu, ram));
        break;

      case OP_ADD:
        int b = stack_pop_int(cpu, ram);
        int a = stack_pop_int(cpu, ram);
        stack_write_int(cpu, ram, a + b);
        break;

      default:
        error(UNKNOWN_INSTRUCTION_ERROR, instr);
    }
  }
}
