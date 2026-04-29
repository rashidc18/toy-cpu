#ifndef _RUN_H
#define _RUN_H

#include <stdint.h>

#include "cpu.h"
#include "ram.h"

#define DEBUG 1

void run(CPU* cpu, RAM* ram);
void run_instr(CPU* cpu, RAM* ram);

#endif
