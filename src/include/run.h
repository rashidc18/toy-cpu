#ifndef _RUN_H
#define _RUN_H

#include <stdint.h>

#include "cpu.h"
#include "ram.h"

void run(CPU* cpu, RAM* ram, int debug_option);
void run_instr(CPU* cpu, RAM* ram, int debug_option);

#endif
