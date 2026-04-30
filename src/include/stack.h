#ifndef _STACK_H
#define _STACK_H

#include <stdint.h>

#include "cpu.h"
#include "ram.h"

void stack_push_byte(CPU* cpu, RAM *ram, uint8_t byte);
void stack_push_int(CPU* cpu, RAM* ram, int value);
uint8_t stack_pop_byte(CPU* cpu, RAM *ram);
int stack_pop_int(CPU *cpu, RAM* ran);

#endif
