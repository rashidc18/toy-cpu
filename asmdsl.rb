#!/usr/bin/env ruby

module ASMDSL
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

  SYSCALL_EXIT = 0
  SYSCALL_OUT_INT = 1

  class Assembler
    def initialize(file)
      @file = file
      @bytecode = []
      @labels = {}
    end

    def write_instr(instr)
      @bytecode.push(instr)
    end

    def write_int(n)
      write_instr((n >> 0) & 0xFF)
      write_instr((n >> 8) & 0xFF)
      write_instr((n >> 16) & 0xFF)
      write_instr((n >> 24) & 0xFF)

    end

    def label(name)
      @labels[name] = @bytecode.size
    end

    def push(n)
      write_instr(PUSH)
      write_int(n)
    end

    def halt
      write_instr HALT
    end

    def add
      write_instr ADD
    end

    def sub
      write_instr SUB
    end

    def mul
      write_instr MUL
    end

    def div
      write_instr DIV
    end

    def jump(n)
      write_instr JUMP
      write_int n
    end
    
    def call(n)
      write_instr CALL
      write_int n
    end

    def jump_label(name)
      jump(@labels[name])
    end

    def dup
      write_instr DUP
    end

    def syscall(syscode)
      write_instr SYSCALL
      write_instr syscode
    end

    def nop
      write_instr NOP
    end

    def write_file
      halt
      File.open(@file, "wb") do |f|
        f.write(@bytecode.pack("C*"))
      end
    end
  end
end
