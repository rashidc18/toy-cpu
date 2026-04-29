#include <stdio.h>
#include <stdint.h>

#include "debug.h"
#include "cpu.h"
#include "ram.h"
#include "opcodes.h"

void debug_instr(CPU* cpu, RAM* ram, uint8_t instr) {
  printf("---------- DEBUG ----------\n");
  printf("pc: %.3d, sp: %d\n", cpu->pc, cpu->sp);
  printf("instr: %d(%s)\n", instr, opcodes_as_string[instr]);
  printf("---------------------------\n");
  getchar();
}
