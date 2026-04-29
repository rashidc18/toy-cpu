#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"
#include "ram.h"
#include "error.h"
#include "loader.h"
#include "run.h"

void usage() {
  printf("Usage: toycpu [options] File...\n");
  printf("Options:\n");
  printf("  --help\n");
  printf("  --version\n");
}

int main(int argc, char* argv[]) {
  if (argc == 1) {
    usage();
    exit(1);
  }

  char* file = argv[1];

  RAM* ram = new_ram();
  CPU* cpu = new_cpu();
  load_ram_from_file(ram, file);

  cpu->on = 1;

  run(cpu, ram);

  return 0;
}
