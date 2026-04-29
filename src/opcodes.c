#include "opcodes.h"

const char* opcodes_as_string[] = {
  [OP_HALT] = "HALT",
  [OP_SYSCALL] = "SYSCALL",
  [OP_PUSH] = "PUSH",
  [OP_ADD] = "ADD",
  [OP_SUB] = "SUB",
  [OP_MUL] = "MUL",
  [OP_DIV] = "DIV",
  [OP_JUMP] = "JUMP",
  [OP_CALL] = "CALL",
  [OP_DUP] = "DUP",
  [OP_NOP] = "NOP"
};
