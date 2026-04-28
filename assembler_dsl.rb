
class Assembler
  def initialize(file)
    @file = file
    @bytecode = []
  end

  def write_instr(instr)
    @bytecode.push(instr)
  end

  def write_file
    File.open(@file, "wb") do |f|
      f.write(@bytecode.pack("C*"))
    end
  end
end

asm = Assembler.new "test.bin"
asm.write_instr 0
asm.write_instr 1
asm.write_file
