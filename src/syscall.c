#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <stdint.h>

#include "syscall.h"
#include "stack.h"
#include "error.h"
#include "cpu.h"
#include "ram.h"
#include "fetch.h"

void syscall(CPU* cpu, RAM* ram) {
  uint8_t syscode = fetch_instr(cpu, ram);

  switch (syscode) {
    case SYSCALL_EXIT:
      syscall_exit(cpu, ram);
    break;

    case SYSCALL_OUT_INT:
      syscall_out_int(cpu, ram);
    break;

    case SYSCALL_SLEEP:
      syscall_sleep(cpu, ram);
    break;

    default:
      error(UNKNOWN_SYSCALL_CODE_ERROR, syscode);
    break;
  }
}

void syscall_exit(CPU* cpu, RAM* ram) {
  exit(stack_pop_int(cpu, ram));
}

void syscall_out_int(CPU* cpu, RAM* ram) {
  printf("%d\n", stack_pop_int(cpu, ram));
}

void syscall_sleep(CPU* cpu, RAM* ram) {
  int time_sleep = stack_pop_int(cpu, ram);
  struct timespec ts;
  ts.tv_sec = time_sleep / 1000;
  ts.tv_nsec = (time_sleep % 1000) * 1000000;

  nanosleep(&ts, NULL);
}
