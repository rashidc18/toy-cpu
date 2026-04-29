#ifndef _SYSCALL_H
#define _SYSCALL_H

#include "cpu.h"
#include "ram.h"

#define SYSCALL_EXIT 0
#define SYSCALL_OUT_INT 1

void syscall(CPU* cpu, RAM* ram);

void syscall_exit(CPU* cpu, RAM* ram);
void syscall_out_int(CPU* cpu, RAM* ram) ;

#endif
