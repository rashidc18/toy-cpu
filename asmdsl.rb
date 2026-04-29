class OpCodes
  HLT      =  0
  NOP      =  1
  PSI      =  2
  PSF      =  3
  DUP      =  4
  POP      =  5
  IAD      =  6
  ISB      =  7
  IML      =  8
  IDV      =  9
  IMD      = 10
  ING      = 11
  FAD      = 12
  FSB      = 13
  FML      = 14
  FDV      = 15
  FMD      = 16
  FNG      = 17
  IEQ      = 18
  INE      = 19
  ILT      = 20
  ILE      = 21
  IGT      = 22
  IGE      = 23
  INT      = 24
  IAN      = 25
  IOR      = 26
  FEQ      = 27
  FNE      = 28
  FLT      = 29
  FLE      = 30
  FGT      = 31
  FGE      = 32
  FNT      = 33
  FAN      = 34
  FOR      = 35
  ILD      = 36
  IST      = 37
  FLD      = 38
  FST      = 39
  ITF      = 40
  FTI      = 41
  JMP      = 42
  JPZ      = 43
  JNZ      = 44
  CAL      = 45
  RET      = 46
  SYSCALL  = 47
end

class SysCall
  EXIT = 0
  OUT_INT = 1
  OUT_CHAR = 2
  SLEEP = 3
end

class Assembler
  def initialize
    @program = []
    @labels = {}
  end

  def save_program(file)
    File.open(file, "wb") do |f|
      f.write(@program.pack("C*"))
    end
  end

  def new_label(label)
    @labels[label] = @program.size
  end

  def add_instruction(instr)
    @program.push(instr)
  end

  def add_int(value)
    add_instruction((value >> 0) & 0xFF)
    add_instruction((value >> 8) & 0xFF)
    add_instruction((value >> 16) & 0xFF)
    add_instruction((value >> 24) & 0xFF)
  end

  def syscall(syscode)
    add_instruction(OpCodes::SYSCALL)
    add_instruction(syscode)
  end

  def psi(value)
    add_instruction(OpCodes::PSI)
    add_int(value)
  end

  def jump(address)
    add_instruction(OpCodes::JMP)
    add_int(address)
  end

  def call(address)
    add_instruction(OpCodes::CAL)
    add_int(address)
  end

  def call_label(label)
    call(@labels[label])
  end

  def jumpz(address)
    add_instruction(OpCodes::JPZ)
    add_int(address)
  end

  def jump_label(label)
    jump(@labels[label])
  end

  def jumpz_label(label)
    jumpz(@labels[label])
  end

  def out_int
    syscall(SysCall::OUT_INT)
  end

  def out_char
    syscall(SysCall::OUT_CHAR)
  end

  def macro_out_int(n)
    psi(n)
    out_int
  end

  def macro_out_char(c)
    psi(c.ord)
    out_char
  end

  def out_endl
    macro_out_char("\n")
  end

  {
    hlt: OpCodes::HLT,
    iad: OpCodes::IAD,
    isb: OpCodes::ISB,
    iml: OpCodes::IML,
    idv: OpCodes::IDV,
    dup: OpCodes::DUP,
    nop: OpCodes::NOP,
    ieq: OpCodes::IEQ,
    ret: OpCodes::RET,
    imd: OpCodes::IMD,
    ing: OpCodes::ING,
    pop: OpCodes::POP,
    ine: OpCodes::INE,
    ilt: OpCodes::ILT,
    ile: OpCodes::ILE,
    igt: OpCodes::IGT,
    ige: OpCodes::IGE,
    int: OpCodes::INT,
    ian: OpCodes::IAN,
    ior: OpCodes::IOR,

  }.each do |name, opcode|
    define_method(name) do
      add_instruction(opcode)
    end
  end

end 

def char(c)
  c.ord
end
