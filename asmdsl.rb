#!/usr/bin/env ruby

module ASMDSL
  HALT = 0
  PUSH = 1
  ADD = 2
  SYSCALL = 3

  SYSCALL_EXIT = 0
  SYSCALL_OUT_INT = 1

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
