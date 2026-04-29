#include <stdint.h>

#include "run.h"
#include "error.h"
#include "opcodes.h"
#include "ram.h"
#include "stack.h"
#include "syscall.h"
#include "fetch.h"
#include "debug.h"

void run(CPU* cpu, RAM* ram) {
  while (cpu->on) {
    run_instr(cpu, ram);
  }
}

void run_instr(CPU* cpu, RAM* ram) {
  uint8_t instr = fetch_instr(cpu, ram);

  if (DEBUG)
    debug_instr(cpu, ram, instr);

  switch (instr) {
    case OP_SYSCALL:  syscall(cpu, ram);  break;

    case OP_HALT:   halt(cpu);         break;
    case OP_PUSH:   push(cpu, ram);    break;
    case OP_ADD:    add(cpu, ram);     break;
    case OP_SUB:    sub(cpu, ram);     break;
    case OP_MUL:    mul(cpu, ram);     break;
    case OP_DIV:    op_div(cpu, ram);  break;
    case OP_JUMP:   jump(cpu, ram);    break;
    case OP_DUP:    dup(cpu, ram);     break;
    case OP_EQ:     eq(cpu, ram);      break;
    case OP_NOP:                       break;
    case OP_JUMPZ:  jumpz(cpu, ram);   break;
    case OP_CALL:   call(cpu, ram);    break;
    case OP_RET:    ret(cpu, ram);     break;

    default:
      error(UNKNOWN_INSTRUCTION_ERROR, instr);
    break;
  }
}
