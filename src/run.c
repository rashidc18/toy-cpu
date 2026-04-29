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
    case OP_SYSCALL:  syscall(cpu, ram);  break;

    case OP_HALT:   halt(cpu);         break;
    case OP_PUSH:   push(cpu, ram);    break;
    case OP_ADD:    add(cpu, ram);     break;
    case OP_SUB:    sub(cpu, ram);     break;
    case OP_MUL:    mul(cpu, ram);     break;
    case OP_DIV:    op_div(cpu, ram);  break;
    case OP_JUMP:   jump(cpu, ram);    break;
    case OP_DUP:    dup(cpu, ram);     break;
    case OP_EQ:     eq(cpu, ram);      break;
    case OP_NOP:                       break;
    case OP_JUMPZ:  jumpz(cpu, ram);   break;
    case OP_CALL:   call(cpu, ram);    break;
    case OP_RET:    ret(cpu, ram);     break;

    default:
      error(UNKNOWN_INSTRUCTION_ERROR, instr);
    break;
  }
}

void halt(CPU* cpu) {
  cpu->on = 0;
}

void push(CPU* cpu, RAM* ram) {
  stack_write_byte(cpu, ram, fetch_instr(cpu, ram));
  stack_write_byte(cpu, ram, fetch_instr(cpu, ram));
  stack_write_byte(cpu, ram, fetch_instr(cpu, ram));
  stack_write_byte(cpu, ram, fetch_instr(cpu, ram));
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

void eq(CPU* cpu, RAM* ram) {
  int a, b;
  get_two_int_from_stack(cpu, ram, &a, &b); 
  stack_write_int(cpu, ram, a == b);
}

void jump(CPU* cpu, RAM* ram) {
  int address = fetch_int(cpu, ram);
  cpu->pc = address;
}

void jumpz(CPU* cpu, RAM* ram) {
  int address = fetch_int(cpu, ram);

  if (stack_pop_int(cpu, ram) == 0)
    cpu->pc = address;
}

void call(CPU* cpu, RAM* ram) {
  int addr = fetch_int(cpu, ram);
  stack_write_int(cpu, ram, cpu->fp);
  stack_write_int(cpu, ram, cpu->pc);
  cpu->fp = cpu->sp;
  cpu->pc = addr;
}

void ret(CPU* cpu, RAM* ram) {
  cpu->sp = cpu->fp;
  cpu->pc = stack_pop_int(cpu, ram);
  cpu->fp = stack_pop_int(cpu, ram);
}

void get_two_int_from_stack(CPU* cpu, RAM* ram, int* a, int* b) {
  *b = stack_pop_int(cpu, ram);
  *a = stack_pop_int(cpu, ram);
}

void dup(CPU* cpu, RAM* ram) {
  if (cpu->sp >= STACK_START)
    error(MEMORY_UNDERFLOW_ERROR);

  uint8_t byte1, byte2, byte3, byte4;
  byte1 = ram->data[cpu->sp + 4];
  byte2 = ram->data[cpu->sp + 3];
  byte3 = ram->data[cpu->sp + 2];
  byte4 = ram->data[cpu->sp + 1];

  stack_write_byte(cpu, ram, byte1);
  stack_write_byte(cpu, ram, byte2);
  stack_write_byte(cpu, ram, byte3);
  stack_write_byte(cpu, ram, byte4);
}
