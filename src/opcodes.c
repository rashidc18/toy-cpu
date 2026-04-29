#include "opcodes.h"
#include "error.h"
#include "stack.h"
#include "ram.h"
#include "cpu.h"
#include "fetch.h"

const char* opcodes_as_string[] = {
  [HLT] = "HLT",
  [NOP] = "NOP",
  [PSI] = "PSI",
  [PSF] = "PSF",
  [DUP] = "DUP",
  [POP] = "POP",
  [IAD] = "IAD",
  [ISB] = "ISB",
  [IML] = "IML",
  [IDV] = "IDV",
  [IMD] = "IMD",
  [ING] = "ING",
  [FAD] = "FAD",
  [FSB] = "FSB",
  [FML] = "FML",
  [FDV] = "FDV",
  [FMD] = "FMD",
  [FNG] = "FNG",
  [IEQ] = "IEQ",
  [INE] = "INE",
  [ILT] = "ILT",
  [ILE] = "ILE",
  [IGT] = "IGT",
  [IGE] = "IGE",
  [INT] = "INT",
  [IAN] = "IAN",
  [IOR] = "IOR",
  [FEQ] = "FEQ",
  [FNE] = "FNE",
  [FLT] = "FLT",
  [FLE] = "FLE",
  [FGT] = "FGT",
  [FGE] = "FGE",
  [FNT] = "FNT",
  [FAN] = "FAN",
  [FOR] = "FOR",
  [ILD] = "ILD",
  [IST] = "IST",
  [FLD] = "FLD",
  [FST] = "FST",
  [ITF] = "ITF",
  [FTI] = "FTI",
  [JMP] = "JMP",
  [JPZ] = "JPZ",
  [JNZ] = "JNZ",
  [CAL] = "CAL",
  [RET] = "RET",
  [SYSCALL] = "SYSCALL"
};

void hlt(CPU* cpu) {
  cpu->on = 0;
}

void nop() {
  /* do nothing */
}

void psi(CPU* cpu, RAM* ram) {
  stack_write_byte(cpu, ram, fetch_instr(cpu, ram));
  stack_write_byte(cpu, ram, fetch_instr(cpu, ram));
  stack_write_byte(cpu, ram, fetch_instr(cpu, ram));
  stack_write_byte(cpu, ram, fetch_instr(cpu, ram));
}

void psf(CPU* cpu, RAM* ram) {
}

void dup(CPU* cpu, RAM* ram) {
  if (cpu->sp >= STACK_START)
    error(MEMORY_UNDERFLOW_ERROR);

  uint8_t byte1, byte2, byte3, byte4;
  byte1 = ram->data[cpu->sp + 4];
  byte2 = ram->data[cpu->sp + 3];
  byte3 = ram->data[cpu->sp + 2];
  byte4 = ram->data[cpu->sp + 1];

  stack_write_byte(cpu, ram, byte1);
  stack_write_byte(cpu, ram, byte2);
  stack_write_byte(cpu, ram, byte3);
  stack_write_byte(cpu, ram, byte4);
}

void pop(CPU* cpu, RAM* ram) {
  stack_pop_int(cpu, ram);
}

void iad(CPU* cpu, RAM* ram) {
  int a, b;
  get_two_int_from_stack(cpu, ram, &a, &b);
  stack_write_int(cpu, ram, a + b);
}

void isb(CPU* cpu, RAM* ram) {
  int a, b;
  get_two_int_from_stack(cpu, ram, &a, &b);
  stack_write_int(cpu, ram, a - b);
}
void iml(CPU* cpu, RAM* ram) {
  int a, b;
  get_two_int_from_stack(cpu, ram, &a, &b);
  stack_write_int(cpu, ram, a * b);
}
void idv(CPU* cpu, RAM* ram) {
  int a, b;
  get_two_int_from_stack(cpu, ram, &a, &b);

  if (b == 0)
    error(ZERO_DIVISION_ERROR);
  
  stack_write_int(cpu, ram, a / b);
}

void imd(CPU* cpu, RAM* ram) {
  int a, b;
  get_two_int_from_stack(cpu, ram, &a, &b);

  if (b == 0)
    error(ZERO_DIVISION_ERROR);
  
  stack_write_int(cpu, ram, a % b);
}

void ing(CPU* cpu, RAM* ram) {
  stack_write_int(cpu, ram, -stack_pop_int(cpu, ram));
}

void fad(CPU* cpu, RAM* ram) {
}

void fsb(CPU* cpu, RAM* ram) {
}

void fml(CPU* cpu, RAM* ram) {
}

void fdv(CPU* cpu, RAM* ram) {
}

void fmd(CPU* cpu, RAM* ram) {
}

void fng(CPU* cpu, RAM* ram) {
}

void ieq(CPU* cpu, RAM* ram) {
  int a, b;
  get_two_int_from_stack(cpu, ram, &a, &b); 
  stack_write_int(cpu, ram, a == b);
}

void ine(CPU* cpu, RAM* ram) {
  int a, b;
  get_two_int_from_stack(cpu, ram, &a, &b); 
  stack_write_int(cpu, ram, a != b);
}

void ilt(CPU* cpu, RAM* ram) {
  int a, b;
  get_two_int_from_stack(cpu, ram, &a, &b); 
  stack_write_int(cpu, ram, a < b);
}

void ile(CPU* cpu, RAM* ram) {
  int a, b;
  get_two_int_from_stack(cpu, ram, &a, &b); 
  stack_write_int(cpu, ram, a <= b);
}

void igt(CPU* cpu, RAM* ram) {
  int a, b;
  get_two_int_from_stack(cpu, ram, &a, &b); 
  stack_write_int(cpu, ram, a > b);
}

void ige(CPU* cpu, RAM* ram) {
  int a, b;
  get_two_int_from_stack(cpu, ram, &a, &b); 
  stack_write_int(cpu, ram, a >= b);
}

void int_(CPU* cpu, RAM* ram) {
  stack_write_int(cpu, ram, !stack_pop_int(cpu, ram));
}

void ian(CPU* cpu, RAM* ram) {
  int a, b;
  get_two_int_from_stack(cpu, ram, &a, &b); 
  stack_write_int(cpu, ram, a && b);
}

void ior(CPU* cpu, RAM* ram) {
  int a, b;
  get_two_int_from_stack(cpu, ram, &a, &b); 
  stack_write_int(cpu, ram, a || b);
}

void feq(CPU* cpu, RAM* ram) {
}

void fne(CPU* cpu, RAM* ram) {
}

void flt(CPU* cpu, RAM* ram) {
}

void fle(CPU* cpu, RAM* ram) {
}

void fgt(CPU* cpu, RAM* ram) {
}

void fge(CPU* cpu, RAM* ram) {
}

void fnt(CPU* cpu, RAM* ram) {
}

void fan(CPU* cpu, RAM* ram) {
}

void for_(CPU* cpu, RAM* ram) {
}

void ild(CPU* cpu, RAM* ram) {
}

void ist(CPU* cpu, RAM* ram) {
}

void fld(CPU* cpu, RAM* ram) {
}

void fst(CPU* cpu, RAM* ram) {
}

void itf(CPU* cpu, RAM* ram) {
}

void fti(CPU* cpu, RAM* ram) {
}

void jmp(CPU* cpu, RAM* ram) {
  int address = fetch_int(cpu, ram);
  cpu->pc = address;
}

void jpz(CPU* cpu, RAM* ram) {
  int address = fetch_int(cpu, ram);

  if (stack_pop_int(cpu, ram) == 0)
    cpu->pc = address;
}

void jnz(CPU* cpu, RAM* ram) {
}

void cal(CPU* cpu, RAM* ram) {
  int addr = fetch_int(cpu, ram);
  stack_write_int(cpu, ram, cpu->fp);
  stack_write_int(cpu, ram, cpu->pc);
  cpu->fp = cpu->sp;
  cpu->pc = addr;
}

void ret(CPU* cpu, RAM* ram) {
  cpu->sp = cpu->fp;
  cpu->pc = stack_pop_int(cpu, ram);
  cpu->fp = stack_pop_int(cpu, ram);
}

void get_two_int_from_stack(CPU* cpu, RAM* ram, int* a, int* b) {
  *b = stack_pop_int(cpu, ram);
  *a = stack_pop_int(cpu, ram);
}
