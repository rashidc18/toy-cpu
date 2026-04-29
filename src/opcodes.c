#include "opcodes.h"

const char* opcodes_as_string[] = {
  [OP_HALT] = "HALT",
  [OP_SYSCALL] = "SYSCALL",
  [OP_PUSH] = "PUSH",
  [OP_ADD] = "ADD"
};
