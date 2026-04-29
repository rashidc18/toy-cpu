require "./asmdsl"

asm = Assembler.new

asm.push(0)

asm.new_label("loop")
asm.push(1)
asm.add

asm.dup
asm.syscall(SysCall::OUT_INT)
asm.push(1000)

asm.dup
asm.push(10)
asm.eq
asm.jumpz_label("loop")


asm.halt

asm.save_program("test.bin")

