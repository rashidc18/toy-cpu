#include <memory.h>
#include <stdlib.h>

#include "ram.h"
#include "error.h"

RAM* new_ram() {
  RAM* ram = malloc(sizeof(RAM));
  memset(ram->data, 0, sizeof(ram->data));
  return ram;
}

void ram_write(RAM* ram, int position, uint8_t byte) {
  if (position < 0)
    error(MEMORY_UNDERFLOW_ERROR);
  if (position >= RAM_SIZE)
    error(MEMORY_OVERFLOW_ERROR);

  ram->data[position] = byte;
}
