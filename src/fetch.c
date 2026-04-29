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

int fetch_int(CPU* cpu, RAM* ram) {
  uint8_t byte1, byte2, byte3, byte4;
  byte1 = fetch_instr(cpu, ram);
  byte2 = fetch_instr(cpu, ram);
  byte3 = fetch_instr(cpu, ram);
  byte4 = fetch_instr(cpu, ram);

  return
    (byte1)       |
    (byte2 << 8)  |
    (byte3 << 16) |
    (byte4 << 24)
  ;
}
