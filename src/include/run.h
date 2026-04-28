#ifndef _RUN_H
#define _RUN_H

#include <stdint.h>

#include "cpu.h"
#include "ram.h"

uint8_t fetch_instr(CPU* cpu, RAM* ram);
void ram_write(RAM* ram, int position, uint8_t byte);
void stack_write(CPU* cpu, RAM *ram, uint8_t byte);
uint8_t stack_pop_byte(CPU* cpu, RAM *ram);
int stack_pop_int(CPU *cpu, RAM* ran);
void run(CPU* cpu, RAM* ram);

#endif
