class OpCodes
  HALT = 0
  SYSCALL = 1
  PUSH = 2
  ADD = 3
  SUB = 4
  MUL = 5
  DIV = 6
  JUMP = 7
  CALL = 8
  DUP = 9
  NOP = 10
  EQ = 11
  JUMPZ = 12
  RET = 13
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

  def push(value)
    add_instruction(OpCodes::PUSH)
    add_int(value)
  end

  def jump(address)
    add_instruction(OpCodes::JUMP)
    add_int(address)
  end

  def call(address)
    add_instruction(OpCodes::CALL)
    add_int(address)
  end

  def call_label(label)
    call(@labels[label])
  end

  def jumpz(address)
    add_instruction(OpCodes::JUMPZ)
    add_int(address)
  end

  def jump_label(label)
    jump(@labels[label])
  end

  def jumpz_label(label)
    jumpz(@labels[label])
  end

  {
    halt: OpCodes::HALT,
    add: OpCodes::ADD,
    sub: OpCodes::SUB,
    mul: OpCodes::MUL,
    div: OpCodes::DIV,
    dup: OpCodes::DUP,
    nop: OpCodes::NOP,
    eq: OpCodes::EQ,
    ret: OpCodes::RET
  }.each do |name, opcode|
    define_method(name) do
      add_instruction(opcode)
    end
  end

end 

def char(c)
  c.ord
end
