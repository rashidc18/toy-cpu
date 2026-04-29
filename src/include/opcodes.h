#ifndef _OPCODES_H
#define _OPCODES_H

#include "ram.h"
#include "cpu.h" 
 
#define HLT       0  /*  HLT                ; halt                         */
#define NOP       1  /*  NOP                ; no operation                 */
#define PSI       2  /*  PSI <int>          ; push int                     */
#define PSF       3  /*  PSF <float>        ; push float                   */
#define DUP       4  /*  DUP                ; duplicate                    */
#define ISP       5  /*  ISP                ; int swap                     */
#define FSP       6  /*  FSP                ; float swap                   */
#define IFS       7  /*  IFS                ; int float swap               */
#define FIS       8  /*  FIS                ; float int swap               */
#define POP       9  /*  POP                ; pop                          */
#define IAD      10  /*  IAD                ; int add                      */
#define ISB      11  /*  ISB                ; int sub                      */
#define IML      12  /*  IML                ; int mul                      */
#define IDV      13  /*  IDV                ; int div                      */
#define IMD      14  /*  ISB                ; int mod                      */
#define ING      15  /*  ING                ; int negate                   */
#define FAD      16  /*  FAD                ; float add                    */
#define FSB      17  /*  FSB                ; float sub                    */
#define FML      18  /*  FML                ; float mul                    */
#define FDV      19  /*  FDV                ; float div                    */
#define FMD      20  /*  FSB                ; float mod                    */
#define FNG      21  /*  FNG                ; float negate                 */
#define IEQ      22  /*  IEQ                ; int equal                    */
#define INE      23  /*  INE                ; int not equal                */
#define ILT      24  /*  ILT                ; int less than                */
#define ILE      25  /*  ILE                ; int less or equal than       */
#define IGT      26  /*  IGT                ; int greater than             */
#define IGE      27  /*  IGE                ; int greater or equal than    */
#define INT      28  /*  INT                ; int not                      */
#define IAN      29  /*  IAN                ; int and                      */
#define IOR      30  /*  IOR                ; int or                       */
#define FEQ      31  /*  FEQ                ; float equal                  */
#define FNE      32  /*  FNE                ; float not equal              */
#define FLT      33  /*  FLT                ; float less than              */
#define FLE      34  /*  FLE                ; float less or equal than     */
#define FGT      35  /*  FGT                ; float greater than           */
#define FGE      36  /*  FGE                ; float greater or equal than  */
#define FNT      37  /*  FNT                ; float not                    */
#define FAN      38  /*  FAN                ; float and                    */
#define FOR      39  /*  FOR                ; float or                     */
#define ILD      40  /*  ILD <address>      ; int load                     */
#define IST      41  /*  IST <address>      ; int store                    */
#define FLD      42  /*  FLD <address>      ; float load                   */
#define FST      43  /*  FST <address>      ; float store                  */
#define ITF      44  /*  ITF                ; int to float                 */
#define FTI      45  /*  FTI                ; float to int                 */
#define JMP      46  /*  JMP <address>      ; jump                         */
#define JPZ      47  /*  JPZ <address>      ; jump if zero                 */
#define JNZ      48  /*  JNZ <address>      ; jump if not zero             */
#define CAL      49  /*  CAL <address>      ; call                         */
#define RET      50  /*  RET                ; return                       */
#define SYSCALL  51  /*  SYSCALL <syscode>  ; system call                  */

extern const char* opcodes_as_string[];

void hlt(CPU* cpu);
void nop();
void psi(CPU* cpu, RAM* ram);
void psf(CPU* cpu, RAM* ram);
void dup(CPU* cpu, RAM* ram);
void isp(CPU *cpu, RAM* ram);
void fsp(CPU *cpu, RAM* ram);
void ifs(CPU *cpu, RAM* ram);
void fis(CPU *cpu, RAM* ram);
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
