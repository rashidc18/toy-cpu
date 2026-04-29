#include <stdio.h>
#include <stdint.h>

#include "run.h"
#include "error.h"
#include "opcodes.h"
#include "ram.h"
#include "stack.h"
#include "syscall.h"
#include "fetch.h"

void run(CPU* cpu, RAM* ram) {
  while (cpu->on) {
    run_instr(cpu, ram);
  }
}

void run_instr(CPU* cpu, RAM* ram) {
  uint8_t instr = fetch_instr(cpu, ram);

  switch (instr) {
    case OP_HALT:
      halt(cpu);
    break;

    case OP_PUSH:
      push(cpu, ram);    
    break;

    case OP_ADD:
      add(cpu, ram);
    break;

    case OP_SYSCALL:
      syscall(cpu, ram);
    break;

    default:
      error(UNKNOWN_INSTRUCTION_ERROR, instr);
    break;
  }
}

void halt(CPU* cpu) {
  cpu->on = 0;
}

void push(CPU* cpu, RAM* ram) {
  stack_write(cpu, ram, fetch_instr(cpu, ram));
  stack_write(cpu, ram, fetch_instr(cpu, ram));
  stack_write(cpu, ram, fetch_instr(cpu, ram));
  stack_write(cpu, ram, fetch_instr(cpu, ram));
}

void add(CPU* cpu, RAM* ram) {
  int b = stack_pop_int(cpu, ram);
  int a = stack_pop_int(cpu, ram);
  stack_write_int(cpu, ram, a + b);
}
