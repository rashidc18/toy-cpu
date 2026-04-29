#ifndef _OPCODES_H
#define _OPCODES_H

#define OP_HALT 0
#define OP_SYSCALL 1
#define OP_PUSH 2
#define OP_ADD 3
#define OP_SUB 4
#define OP_MUL 5
#define OP_DIV 6

extern const char* opcodes_as_string[];

#endif
