#include <stdint.h>

#include "run.h"
#include "error.h"
#include "opcodes.h"
#include "ram.h"
#include "stack.h"
#include "syscall.h"
#include "fetch.h"
#include "debug.h"

void run(CPU* cpu, RAM* ram) {
  while (cpu->on) {
    run_instr(cpu, ram);
  }
}

void run_instr(CPU* cpu, RAM* ram) {
  uint8_t instr = fetch_instr(cpu, ram);

  if (DEBUG)
    debug_instr(cpu, ram, instr);

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

    case OP_SUB:
      sub(cpu, ram);
    break;

    case OP_MUL:
      mul(cpu, ram);
    break;

    case OP_DIV:
      op_div(cpu, ram);
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
  int a, b;
  get_two_int_from_stack(cpu, ram, &a, &b);
  stack_write_int(cpu, ram, a + b);
}

void sub(CPU* cpu, RAM* ram) {
  int a, b;
  get_two_int_from_stack(cpu, ram, &a, &b);
  stack_write_int(cpu, ram, a - b);
}

void mul(CPU* cpu, RAM* ram) {
  int a, b;
  get_two_int_from_stack(cpu, ram, &a, &b);
  stack_write_int(cpu, ram, a * b);
}

void op_div(CPU* cpu, RAM* ram) {
  int a, b;
  get_two_int_from_stack(cpu, ram, &a, &b);

  if (b == 0)
    error(ZERO_DIVISION_ERROR);
  
  stack_write_int(cpu, ram, a / b);
}

void get_two_int_from_stack(CPU* cpu, RAM* ram, int* a, int* b) {
  *b = stack_pop_int(cpu, ram);
  *a = stack_pop_int(cpu, ram);
}
