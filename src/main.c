#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "ram.h"
#include "loader.h"
#include "run.h"

#define TOY_CPU_VERSION "Toy CPU 0.1.0 (Developed by: Rashid)."

void usage() {
  printf("Usage: toycpu File [options]...\n");
  printf("Options:\n");
  printf("  --help             Display this information.\n");
  printf("  --version          Display compiler version information.\n");
}

int main(int argc, char* argv[]) {
  if (argc == 1) {
    usage();
    exit(1);
  }

  char* file = argv[1];

  if (argc > 2) {
    char* option = argv[2];

    if (strcmp(option, "--help") == 0) {
      usage();
      exit(0);
    }
    else if (strcmp(option, "--version") == 0) {
      puts(TOY_CPU_VERSION);
      exit(0);
    }
    else {
      printf("unknown option: `%s`.\n", option);
      usage();
      exit(1);
    }
  }

  RAM* ram = new_ram();
  CPU* cpu = new_cpu();
  load_ram_from_file(ram, file);

  cpu->on = 1;

  run(cpu, ram);

  return 0;
}
