#ifndef _FETCH_H
#define _FETCH_H

#include <stdint.h>

#include "cpu.h"
#include "ram.h"

uint8_t fetch_instr(CPU* cpu, RAM* ram);

#endif
