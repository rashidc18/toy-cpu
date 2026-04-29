#include <stdlib.h>

#include "cpu.h"
#include "ram.h"
#include "stack.h"

CPU* new_cpu() {
  CPU* cpu = malloc(sizeof(CPU));
  cpu->pc = 0;
  cpu->on = 0;
  cpu->sp = STACK_START;
  return cpu;
}
