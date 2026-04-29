#include "opcodes.h"
#include "error.h"
#include "stack.h"
#include "ram.h"
#include "cpu.h"
#include "fetch.h"

const char* opcodes_as_string[] = {
  [OP_HALT] = "HALT",
  [OP_SYSCALL] = "SYSCALL",
  [OP_PUSH] = "PUSH",
  [OP_ADD] = "ADD",
  [OP_SUB] = "SUB",
  [OP_MUL] = "MUL",
  [OP_DIV] = "DIV",
  [OP_JUMP] = "JUMP",
  [OP_CALL] = "CALL",
  [OP_DUP] = "DUP",
  [OP_NOP] = "NOP",
  [OP_EQ] = "EQ",
  [OP_JUMPZ] = "JUMPZ",
  [OP_RET] = "RET"
};

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

