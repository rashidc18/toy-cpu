#ifndef _RUN_H
#define _RUN_H

#include <stdint.h>

#include "cpu.h"
#include "ram.h"

void run(CPU* cpu, RAM* ram);
void run_instr(CPU* cpu, RAM* ram);

void halt(CPU* cpu);
void push(CPU* cpu, RAM* ram);
void add(CPU* cpu, RAM* ram);

#endif
