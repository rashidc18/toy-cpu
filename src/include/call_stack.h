#ifndef _CALL_STACK_H
#define _CALL_STACK_H

#include "stack.h"
#include "cpu.h"
#include "ram.h"

#define CALL_STACK_SIZE 256
#define CALL_STACK_START (STACK_END - 1)
#define CALL_STACK_END (CALL_STACK_START - CALL_STACK_SIZE + 1)

void call_stack_push(CPU* cpu, RAM* ram, int address);
int call_stack_pop(CPU* cpu, RAM* ram);

#endif
