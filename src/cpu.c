#include <stdlib.h>

#include "cpu.h"

CPU* new_cpu() {
  CPU* cpu = malloc(sizeof(CPU));
  cpu->pc = 0;
  cpu->on = 0;
  return cpu;
}
