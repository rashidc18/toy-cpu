#ifndef _STACK_H
#define _STACK_H

#include <stdint.h>

#include "cpu.h"
#include "ram.h"

#define STACK_SIZE 20
#define STACK_START (RAM_SIZE - 1)
#define STACK_END (STACK_START - STACK_SIZE + 1)

void stack_write(CPU* cpu, RAM *ram, uint8_t byte);
void stack_write_int(CPU* cpu, RAM* ram, int value);
uint8_t stack_pop_byte(CPU* cpu, RAM *ram);
int stack_pop_int(CPU *cpu, RAM* ran);

#endif
