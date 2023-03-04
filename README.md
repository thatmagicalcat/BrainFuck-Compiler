# BrainFuck Compiler

An actual brainfuck compiler written in C++

## Getting started

### Installation
```shell
$ git clone https://github.com/Pranjal-Patel/brainfuck-compiler
$ cd brainfuck-compiler
$ mkdir build
$ cd build
$ cmake ..
$ make
$ make install
```

<hr>

### How to use
Here's an example of how to print `Hello World` in brainfuck

```bf
>+++++++[<++++++++++>-]<++.
>>++++++++++[<++++++++++>-]<+.
>>++++++++++[<++++++++++>-]<++++++++.
>>++++++++++[<++++++++++>-]<++++++++.
>>+++++++++++[<++++++++++>-]<+.
>>+++[<++++++++++>-]<++.
>>++++++++[<++++++++++>-]<+++++++.
>>+++++++++++[<++++++++++>-]<+.
>>+++++++++++[<++++++++++>-]<++++.
>>++++++++++[<++++++++++>-]<++++++++.
>>++++++++++[<++++++++++>-]<.
>>++++++++++.
```

To run without compiling:
```shell
$ bfc sim hello.bf    # or whatever you named your file
Hello World
```
Here `sim` means simulation

<br>
<br>

To compile:
```shell
$ bfc com hello.bf
$ ./output
Hello World
```
Here `com` means compile
