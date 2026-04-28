#ifndef _RUN_H
#define _RUN_H

#include <stdint.h>

#include "cpu.h"
#include "ram.h"

uint8_t fetch_instr(CPU* cpu, RAM* ram);
void ram_write(RAM* ram, int position, uint8_t byte);
void run(CPU* cpu, RAM* ram);

#endif
