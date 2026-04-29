#ifndef _OPCODES_H
#define _OPCODES_H

#include "ram.h"
#include "cpu.h" 
 
#define HLT       0  /*  HLT                ; halt                         */
#define NOP       1  /*  NOP                ; no operation                 */
#define PSI       2  /*  PSI <int>          ; push int                     */
#define PSF       3  /*  PSF <float>        ; push float                   */
#define DUP       4  /*  DUP                ; duplicate                    */
#define POP       5  /*  POP                ; pop                          */
#define IAD       6  /*  IAD                ; int add                      */
#define ISB       7  /*  ISB                ; int sub                      */
#define IML       8  /*  IML                ; int mul                      */
#define IDV       9  /*  IDV                ; int div                      */
#define IMD      10  /*  ISB                ; int mod                      */
#define ING      11  /*  ING                ; int negate                   */
#define FAD      12  /*  FAD                ; float add                    */
#define FSB      13  /*  FSB                ; float sub                    */
#define FML      14  /*  FML                ; float mul                    */
#define FDV      15  /*  FDV                ; float div                    */
#define FMD      16  /*  FSB                ; float mod                    */
#define FNG      17  /*  FNG                ; float negate                 */
#define IEQ      18  /*  IEQ                ; int equal                    */
#define INE      19  /*  INE                ; int not equal                */
#define ILT      20  /*  ILT                ; int less than                */
#define ILE      21  /*  ILE                ; int less or equal than       */
#define IGT      22  /*  IGT                ; int greater than             */
#define IGE      23  /*  IGE                ; int greater or equal than    */
#define INT      24  /*  INT                ; int not                      */
#define IAN      25  /*  IAN                ; int and                      */
#define IOR      26  /*  IOR                ; int or                       */
#define FEQ      27  /*  FEQ                ; float equal                  */
#define FNE      28  /*  FNE                ; float not equal              */
#define FLT      29  /*  FLT                ; float less than              */
#define FLE      30  /*  FLE                ; float less or equal than     */
#define FGT      31  /*  FGT                ; float greater than           */
#define FGE      32  /*  FGE                ; float greater or equal than  */
#define FNT      33  /*  FNT                ; float not                    */
#define FAN      34  /*  FAN                ; float and                    */
#define FOR      35  /*  FOR                ; float or                     */
#define ILD      36  /*  ILD <address>      ; int load                     */
#define IST      37  /*  IST <address>      ; int store                    */
#define FLD      38  /*  FLD <address>      ; float load                   */
#define FST      39  /*  FST <address>      ; float store                  */
#define ITF      40  /*  ITF                ; int to float                 */
#define FTI      41  /*  FTI                ; float to int                 */
#define JMP      42  /*  JMP <address>      ; jump                         */
#define JPZ      43  /*  JPZ <address>      ; jump if zero                 */
#define JNZ      44  /*  JNZ <address>      ; jump if not zero             */
#define CAL      45  /*  CAL <address>      ; call                         */
#define RET      46  /*  RET                ; return                       */
#define SYSCALL  47  /*  SYSCALL <syscode>  ; system call                  */

extern const char* opcodes_as_string[];

void hlt(CPU* cpu);
void nop();
void psi(CPU* cpu, RAM* ram);
void psf(CPU* cpu, RAM* ram);
void dup(CPU* cpu, RAM* ram);
void pop(CPU* cpu, RAM* ram);
void iad(CPU* cpu, RAM* ram);
void isb(CPU* cpu, RAM* ram);
void iml(CPU* cpu, RAM* ram);
void idv(CPU* cpu, RAM* ram);
void imd(CPU* cpu, RAM* ram);
void ing(CPU* cpu, RAM* ram);
void fad(CPU* cpu, RAM* ram);
void fsb(CPU* cpu, RAM* ram);
void fml(CPU* cpu, RAM* ram);
void fdv(CPU* cpu, RAM* ram);
void fmd(CPU* cpu, RAM* ram);
void fng(CPU* cpu, RAM* ram);
void ieq(CPU* cpu, RAM* ram);
void ine(CPU* cpu, RAM* ram);
void ilt(CPU* cpu, RAM* ram);
void ile(CPU* cpu, RAM* ram);
void igt(CPU* cpu, RAM* ram);
void ige(CPU* cpu, RAM* ram);
void int_(CPU* cpu, RAM* ram);
void ian(CPU* cpu, RAM* ram);
void ior(CPU* cpu, RAM* ram);
void feq(CPU* cpu, RAM* ram);
void fne(CPU* cpu, RAM* ram);
void flt(CPU* cpu, RAM* ram);
void fle(CPU* cpu, RAM* ram);
void fgt(CPU* cpu, RAM* ram);
void fge(CPU* cpu, RAM* ram);
void fnt(CPU* cpu, RAM* ram);
void fan(CPU* cpu, RAM* ram);
void for_(CPU* cpu, RAM* ram);
void ild(CPU* cpu, RAM* ram);
void ist(CPU* cpu, RAM* ram);
void fld(CPU* cpu, RAM* ram);
void fst(CPU* cpu, RAM* ram);
void itf(CPU* cpu, RAM* ram);
void fti(CPU* cpu, RAM* ram);
void jmp(CPU* cpu, RAM* ram);
void jpz(CPU* cpu, RAM* ram);
void jnz(CPU* cpu, RAM* ram);
void cal(CPU* cpu, RAM* ram);
void ret(CPU* cpu, RAM* ram);

void get_two_int_from_stack(CPU* cpu, RAM* ram, int* a, int* b);

#endif
