#ifndef _OPCODES_H
#define _OPCODES_H

#include "ram.h"
#include "cpu.h"

#define OP_HALT 0
#define OP_SYSCALL 1
#define OP_PUSH 2
#define OP_ADD 3
#define OP_SUB 4
#define OP_MUL 5
#define OP_DIV 6
#define OP_JUMP 7
#define OP_CALL 8
#define OP_DUP 9
#define OP_NOP 10
#define OP_EQ 11
#define OP_JUMPZ 12
#define OP_RET 13

extern const char* opcodes_as_string[];

void halt(CPU* cpu);

void push(CPU* cpu, RAM* ram);

void add(CPU* cpu, RAM* ram);
void sub(CPU* cpu, RAM* ram);
void mul(CPU* cpu, RAM* ram);
void op_div(CPU* cpu, RAM* ram);

void jump(CPU* cpu, RAM* ram);
void jumpz(CPU* cpu, RAM* ram);
void call(CPU* cpu, RAM* ram);
void ret(CPU* cpu, RAM* ram);

void dup(CPU* cpu, RAM* ram);

void eq(CPU* cpu, RAM* ram);

void get_two_int_from_stack(CPU* cpu, RAM* ram, int* a, int* b);

#endif
