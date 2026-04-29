#!/usr/bin/env ruby

module ASMDSL
  HALT = 0
  SYSCALL = 1
  PUSH = 2
  ADD = 3
  SUB = 4
  MUL = 5
  DIV = 6

  SYSCALL_EXIT = 0
  SYSCALL_OUT_INT = 1

  #define OP_HALT 0
  #define OP_SYSCALL 1
  #define OP_PUSH 2
  #define OP_ADD 3
  #define OP_SUB 4
  #define OP_MUL 5
  #define OP_DIV 6

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

    def syscall(syscode)
      write_instr SYSCALL
      write_instr syscode
    end

    def write_file
      halt
      File.open(@file, "wb") do |f|
        f.write(@bytecode.pack("C*"))
      end
    end
  end
end
