#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cpu.h"
#include "ram.h"
#include "error.h"
#include "loader.h"
#include "run.h"

#define DEBUG 0

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

  struct timespec load_start_time, load_end_time;

  clock_gettime(CLOCK_MONOTONIC, &load_start_time);
  load_ram_from_file(ram, file);
  clock_gettime(CLOCK_MONOTONIC, &load_end_time);

  double load_time = 
    (load_end_time.tv_sec - load_start_time.tv_sec) + 
    (load_end_time.tv_nsec - load_start_time.tv_nsec) / 1e9;

  if (DEBUG)
    printf("[%f] File %s loaded into memory successfully.\n", load_time, file);

  cpu->on = 1;

  run(cpu, ram);

  return 0;
}
