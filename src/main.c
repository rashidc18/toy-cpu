#include <stdio.h>
#include "cpu.h"
#include "ram.h"
#include "error.h"
#include "loader.h"

int main(int argc, char* argv[]) {
  RAM* ram = new_ram();
  load_ram_from_file(ram, "test.bin");

  return 0;
}
