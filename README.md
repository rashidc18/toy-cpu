# MINI CPU

A simple virtual CPU written in C.

## Why?
- Learning
- Because it's fun

## Build
To build the project, make sure you have a C compiler installed (such as gcc or clang).
```bash
$ git clone https://github.com/rashidc18/mini-cpu.git
$ cd min-cpu
$ make
```

## Run
To run, use:
```bash
$ ./minilisp file.bin
```

## Assembler
The project includes a simple assembler DSL implemented in Ruby to make writing programs for the virtual CPU easier.

### How to use
Import the assembler dsl.
```ruby
require "./assembler_dsl"
```

Create a new assembler instance.
```ruby
asm = Assembler.asm "output.bin"
```

Use instructions methods.
```ruby
asm.push 10
asm.push 20
asm.add
asm.out
asm.halt
```

Write instructions into output file.
```ruby
asm.write
```
