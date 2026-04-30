#ifndef _DEBUG_H
#define _DEBUG_H

#include <stdint.h>

#include "cpu.h"
#include "ram.h"

#define STRING_CALL_STACK "CALL STACK  "
#define STRING_STACK      "STACK       "
#define STRING_PC         "   PC       %.3d\n"
#define STRING_SP         "   SP       %.3d\n"
#define STRING_CSP        "  CSP       %.3d\n"
#define STRING_INSTR      "INSTR       %s   [%.3d]\n"

void debug_stack(CPU* cpu, RAM* ram);
void debug_instr(CPU* cpu, RAM* ram, uint8_t instr);

#endif
