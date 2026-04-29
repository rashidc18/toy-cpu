#include <stdint.h>

#include "fetch.h"
#include "cpu.h"
#include "ram.h"
#include "error.h"

uint8_t fetch_instr(CPU* cpu, RAM* ram) {
  if (cpu->pc == RAM_SIZE) {
    error(MEMORY_OVERFLOW_ERROR);
  }

  return ram->data[cpu->pc++];
}
