#ifndef _RUN_H
#define _RUN_H

#include <stdint.h>

#include "cpu.h"
#include "ram.h"

#define DEBUG 0

void run(CPU* cpu, RAM* ram);
void run_instr(CPU* cpu, RAM* ram);

void halt(CPU* cpu);

void push(CPU* cpu, RAM* ram);

void add(CPU* cpu, RAM* ram);
void sub(CPU* cpu, RAM* ram);
void mul(CPU* cpu, RAM* ram);
void div(CPU* cpu, RAM* ram);

void get_two_int_from_stack(CPU* cpu, RAM* ram, int* a, int* b);

#endif
