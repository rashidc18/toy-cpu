class OpCodes
  HLT      =  0
  NOP      =  1
  PSI      =  2
  PSF      =  3
  DUP      =  4
  ISP      =  5
  FSP      =  6
  IFS      =  7
  FIS      =  8
  POP      =  9
  IAD      = 10
  ISB      = 11
  IML      = 12
  IDV      = 13
  IMD      = 14
  ING      = 15
  FAD      = 16
  FSB      = 17
  FML      = 18
  FDV      = 19
  FMD      = 20
  FNG      = 21
  IEQ      = 22
  INE      = 23
  ILT      = 24
  ILE      = 25
  IGT      = 26
  IGE      = 27
  INT      = 28
  IAN      = 29
  IOR      = 30
  FEQ      = 31
  FNE      = 32
  FLT      = 33
  FLE      = 34
  FGT      = 35
  FGE      = 36
  FNT      = 37
  FAN      = 38
  FOR      = 39
  ILD      = 40
  IST      = 41
  FLD      = 42
  FST      = 43
  ITF      = 44
  FTI      = 45
  JMP      = 46
  JPZ      = 47
  JNZ      = 48
  CAL      = 49
  RET      = 50
  SYSCALL  = 51
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
    @labels_to_link = {} # "label" => program position that need to be linked
  end

  def save_program(file)
    link_labels()
    File.open(file, "wb") do |f|
      f.write(@program.pack("C*"))
    end
  end

  def new_label(label)
    @labels[label] = @program.size
  end

  def get_label(label)
    if @labels.has_key?(label)
      return @labels[label]
    else
      @labels_to_link[label] = @program.size+1
      return 0
    end
  end

  def entry_point(label)
    jmp_label(label)
  end

  def add_instruction(instr)
    @program.push(instr)
  end

  def int_to_bytes(value)
    return [
      (value >> 0) & 0xFF,
      (value >> 8) & 0xFF,
      (value >> 16) & 0xFF,
      (value >> 24) & 0xFF,
    ]
  end

  def add_int(value)
    int_to_bytes(value).each do |byte|
      add_instruction(byte)
    end
  end

  def cal_label(label)
    cal(get_label(label))
  end

  def jpz(address)
    add_instruction(OpCodes::JPZ)
    add_int(address)
  end

  def jmp_label(label)
    jmp(get_label(label))
  end

  def jpz_label(label)
    jpz(get_label(label))
  end

  def link_labels
    @labels_to_link.each do |label, position|
      if !@labels.has_key?(label)
        puts "error: label `#{label}` was not defined."
        exit 1
      end
      address = @labels[label]
      bytes = int_to_bytes(address)
      
      i = 0
      bytes.each do |byte|
        @program[position + i] = byte
        i += 1
      end
    end
  end

  def show_program
    @labels.each do |k,v|
      puts format("%s: %.3d", k, v)
    end

    column = 1
    column_max = 5
    program = ""

    i = 0
    @program.each do |byte|
      if column == 1
        program += format("%.3d: ", i)
      end
      
      program += format("%.3d ", byte)

      if column == column_max
        column = 1
        program += "\n"
      else
        column += 1
      end

      i += 1
    end

    puts program
  end

  {
    syscall: OpCodes::SYSCALL
  }.each do |name, opcode|
    define_method(name) do |bytev|
      add_instruction(opcode)
      add_instruction(bytev)
    end
  end

  {
    psi: OpCodes::PSI,
    jmp:  OpCodes::JMP,
    cal: OpCodes::CAL
  }.each do |name, opcode|
    define_method(name) do |intv|
      add_instruction(opcode)
      add_int(intv)
    end
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
    isp: OpCodes::ISP,
  }.each do |name, opcode|
    define_method(name) do
      add_instruction(opcode)
    end
  end
end 

def char(c)
  c.ord
end
