#include <stdint.h>

#include "run.h"
#include "error.h"
#include "opcodes.h"
#include "ram.h"
#include "stack.h"
#include "syscall.h"
#include "fetch.h"
#include "debug.h"

void run(CPU* cpu, RAM* ram, int debug_option) {
  while (cpu->on) {
    run_instr(cpu, ram, debug_option);
  }
}

void run_instr(CPU* cpu, RAM* ram, int debug_option) {
  uint8_t instr = fetch_instr(cpu, ram);

  if (debug_option)
    debug_instr(cpu, ram, instr);

  switch (instr) {
    case HLT:     hlt(cpu);           break;
    case NOP:     nop();              break;
    case PSI:     psi(cpu, ram);      break;
    case PSF:     psf(cpu, ram);      break;
    case DUP:     dup(cpu, ram);      break;
    case ISP:     isp(cpu, ram);      break;
    case FSP:     fsp(cpu, ram);      break;
    case IFS:     ifs(cpu, ram);      break;
    case FIS:     fis(cpu, ram);      break;
    case POP:     pop(cpu, ram);      break;
    case IAD:     iad(cpu, ram);      break;
    case ISB:     isb(cpu, ram);      break;
    case IML:     iml(cpu, ram);      break;
    case IDV:     idv(cpu, ram);      break;
    case IMD:     imd(cpu, ram);      break;
    case ING:     ing(cpu, ram);      break;
    case FAD:     fad(cpu, ram);      break;
    case FSB:     fsb(cpu, ram);      break;
    case FML:     fml(cpu, ram);      break;
    case FDV:     fdv(cpu, ram);      break;
    case FMD:     fmd(cpu, ram);      break;
    case FNG:     fng(cpu, ram);      break;
    case IEQ:     ieq(cpu, ram);      break;
    case INE:     ine(cpu, ram);      break;
    case ILT:     ilt(cpu, ram);      break;
    case ILE:     ile(cpu, ram);      break;
    case IGT:     igt(cpu, ram);      break;
    case IGE:     ige(cpu, ram);      break;
    case INT:     int_(cpu, ram);     break;
    case IAN:     ian(cpu, ram);      break;
    case IOR:     ior(cpu, ram);      break;
    case FEQ:     feq(cpu, ram);      break;
    case FNE:     fne(cpu, ram);      break;
    case FLT:     flt(cpu, ram);      break;
    case FLE:     fle(cpu, ram);      break;
    case FGT:     fgt(cpu, ram);      break;
    case FGE:     fge(cpu, ram);      break;
    case FNT:     fnt(cpu, ram);      break;
    case FAN:     fan(cpu, ram);      break;
    case FOR:     for_(cpu, ram);     break;
    case ILD:     ild(cpu, ram);      break;
    case IST:     ist(cpu, ram);      break;
    case FLD:     fld(cpu, ram);      break;
    case FST:     fst(cpu, ram);      break;
    case ITF:     itf(cpu, ram);      break;
    case FTI:     fti(cpu, ram);      break;
    case JMP:     jmp(cpu, ram);      break;
    case JPZ:     jpz(cpu, ram);      break;
    case JNZ:     jnz(cpu, ram);      break;
    case CAL:     cal(cpu, ram);      break;
    case RET:     ret(cpu, ram);      break;
    case SYSCALL: syscall(cpu, ram);  break;

    default:
      error(UNKNOWN_INSTRUCTION_ERROR, instr);
    break;
  }
}
