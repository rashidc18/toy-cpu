#include <stdio.h>
#include <stdint.h>

#include "loader.h"
#include "error.h"

void load_ram_from_file(RAM* ram, char* file) {
  FILE* fp = fopen(file, "rb");

  if (!fp) {
    error("file `%s` not found", file);
  }

  int position = 0;
  int byte;

  while ((byte = fgetc(fp)) != EOF) {
    if (position == RAM_SIZE) {
      fclose(fp);
      error("memory overflow");
    }

    ram->data[position++] = (uint8_t)byte;
  }

  fclose(fp);
}
