# The RCSA Emulator

A minimal emulator for the RCSA written in C.  For the RCSA specification, see
[**The Specification**](#the-specification).

## Compiling & Installing

This project can be easily compiled, tested, installed and uninstalled using
the makefile that stands next to the C source files. E.g., one can run the
following command to compile, test and install the RCSAE:

```
 $ make build test install clean
...
```

In the makefile exists a macro named `PREFIX` and for now its default value is
`local`, therefore the command will make a new directory in the same directory
as the makefile and installs the output files into it.  In future production
releases, the default value will be `/usr/local`.  Of course, one can specify
the directory to install the output files into by specifying `PREFIX` as an
environment variable, e.g.:

```
 $ PREFIX=$HOME/.local make build test install clean
...
```

This command will install the output files to the directory `~/.local`.

The program can be uninstalled with the following command:

```
 $ make uninstall
...
```

And of course setting `PREFIX` might be needed.

Obviously, GNU Make is required to be installed in the system.  Also, compiling
or even running might not work correctly on operating systems other than the
GNU operating system's distributions.

## The Specification

> The specification is not complete yet, it can be changed at any time
> suddenly.

The RCSA itself is designed to be a simple architecture.  The memory must be
1 KiB atleast and the processor totally has 65 registers, one being the
processor clock.

| Register Size | Registers' names |
| :------------ | :--------------- |
| **8 bits**    | B0, B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, B11, B12, B13, B14, B15 |
| **16 bits**   | SR0, SR1, SR2, SR3, SR4, SR5, SR6, SR7, SR8, SR9, SR10, SR11, SR12, SR13, SR14, SR15 |
| **32 bits**   | R0, R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11, R12, R13, R14, R15 |
| **64 bits**   | PC, LR0, LR1, LR2, LR3, LR4, LR5, LR6, LR7, LR8, LR9, LR10, LR11, LR12, LR13, LR14, LR15 |

The register *B0* is reserved for the processor state.  *PC* is the processor
clock.
