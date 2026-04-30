#ifndef _CALL_STACK_H
#define _CALL_STACK_H

#include "stack.h"
#include "cpu.h"
#include "ram.h"

void call_stack_push(CPU* cpu, RAM* ram, int address);
int call_stack_pop(CPU* cpu, RAM* ram);

#endif
