# 💾 TOY CPU

A simple virtual CPU written in C.

## ❓ Why?
- Learning
- Because it's fun

## 📦 Install
To install the project, make sure you have a C compiler installed (such as gcc or clang) and Ruby interpreter.
```bash
$ git clone https://github.com/rashidc18/toy-cpu.git
$ cd toy-cpu
$ sudo ./install.sh
```

Or manual build
```bash
$ git clone https://github.com/rashidc18/toy-cpu.git
$ cd toy-cpu
$ make
```

## 🚀 Usage
```bash
$ ./toycpu your-file
```

## </> Assembler
The project includes a simple assembler DSL implemented in Ruby to make writing programs for the virtual CPU easier.

### How to use
Import the assembler dsl.
```ruby
require "asmdsl"
```

Create a new assembler instance.
```ruby
asm = Assembler.new
```

Use instructions methods.
```ruby
asm.push(10)
asm.syscall(SysCall::OUT_INT)

asm.push(0)
asm.syscall(SysCall::EXIT)
```

Save program into output file.
```ruby
asm.save_program("file")
```
