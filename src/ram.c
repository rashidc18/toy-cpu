#include <memory.h>
#include <stdlib.h>

#include "ram.h"

RAM* new_ram() {
  RAM* ram = malloc(sizeof(RAM));
  memset(ram->data, 0, sizeof(ram->data));
  return ram;
}
