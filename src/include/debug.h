#ifndef _DEBUG_H
#define _DEBUG_H

#include <stdint.h>

#include "cpu.h"
#include "ram.h"

void debug_instr(CPU* cpu, RAM* ram, uint8_t instr);

#endif
