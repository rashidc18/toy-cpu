#include <stdio.h>
#include <stdint.h>

#include "debug.h"
#include "cpu.h"
#include "ram.h"
#include "opcodes.h"
#include "bytes.h"
#include "stack.h"
#include "call_stack.h"

void debug_stack(CPU* cpu, RAM* ram) {
  printf(STRING_STACK);
  printf("[ ");
  for (int i = cpu->sp + 1; i <= STACK_START; i += 4) {
    printf("%.3d ", b2i(
      ram->data[i+3],
      ram->data[i+2],
      ram->data[i+1],
      ram->data[i]
    ));
  }
  printf("]\n");
}

void debug_call_stack(CPU* cpu, RAM* ram) {
  printf(STRING_CALL_STACK);
  printf("[ ");
  for (int i = cpu->csp + 1; i <= CALL_STACK_START; i += 4) {
    printf("%.3d ", b2i(
      ram->data[i+3],
      ram->data[i+2],
      ram->data[i+1],
      ram->data[i]
    ));
  }
  printf("]\n");
}

void debug_instr(CPU* cpu, RAM* ram, uint8_t instr) {
  debug_stack(cpu, ram);
  debug_call_stack(cpu, ram);
  printf(STRING_PC, cpu->pc - 1); /* pc was incremented when fetch_instr */
  printf(STRING_SP, cpu->sp);
  printf(STRING_CSP, cpu->csp);
  printf(STRING_INSTR, opcodes_as_string[instr], instr);

  getchar();
}
