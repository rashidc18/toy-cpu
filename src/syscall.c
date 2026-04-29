#include <stdio.h>
#include <stdlib.h>

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
