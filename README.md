# utf8_enc

UTF-8 encoder program

## Introduction

This command-line program encodes Unicode code points into UTF-8 encoded 
bytes, displays the resulting characters and prints their byte/bit 
patterns. 

## Building

The program and its files can be compiled with a C compiler (e.g. GCC) 
with the following command:

`gcc --ansi --pedantic -o utf8_enc utf8.c main.c`

## Usage

After successful build, start the program with

`./utf8_enc`

Enter Unicode code points as positive integer numbers. Entering a 0 (or
a non-numeric character) exits the program. Several code points may be 
entered. In this case the code points must be separated by space 
characters.

## Sample run

```
$ ./utf8_enc 
UTF-8 encoder
-------------
This program encodes Unicode code points using UTF-8 variable-width 
encoding.
Enter Unicode code points as positive numbers. Several code points can 
be entered at once, separated by spaces. Enter 0 to exit.
> 66
code: 66	char: "B"	bytes: 01000010 
> 7556 243 3217 1556
code: 7556	char: "ᶄ"	bytes: 11100001 10110110 10000100 
> code: 243	char: "ó"	bytes: 11000011 10110011 
> code: 3217	char: "಑"	bytes: 11100000 10110010 10010001 
> code: 1556	char: "ؔ"	bytes: 11011000 10010100 
> 0
$ 
```

## License

MIT

