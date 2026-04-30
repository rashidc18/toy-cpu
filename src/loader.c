#include <stdio.h>
#include <stdint.h>

#include "loader.h"
#include "cpu.h"
#include "ram.h"
#include "error.h"

void load_ram_from_file(RAM* ram, char* file) {
  FILE* fp = fopen(file, "rb");

  if (!fp) {
    error(FILE_NOT_FOUND_ERROR, file);
  }

  int position = 0;
  int byte;

  while ((byte = fgetc(fp)) != EOF) {
    if (position > CODE_END) {
      fclose(fp);
      error(MEMORY_OVERFLOW_ERROR);
    }

    ram->data[position++] = (uint8_t)byte;
  }

  fclose(fp);
}
