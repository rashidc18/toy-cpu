#!/usr/bin/env ruby

HALT = 0
PUSH = 1
OUT = 2

class Assembler
  def initialize(file)
    @file = file
    @bytecode = []
  end

  def write_instr(instr)
    @bytecode.push(instr)
  end

  def push(n)
    write_instr(PUSH)
    write_instr((n >> 0) & 0xFF)
    write_instr((n >> 8) & 0xFF)
    write_instr((n >> 16) & 0xFF)
    write_instr((n >> 24) & 0xFF)
  end

  def out
    write_instr OUT
  end

  def halt
    write_instr HALT
  end

  def write_file
    halt
    File.open(@file, "wb") do |f|
      f.write(@bytecode.pack("C*"))
    end
  end
end

asm = Assembler.new "test.bin"

asm.push 123
asm.push 1234
asm.out
asm.out

asm.write_file
