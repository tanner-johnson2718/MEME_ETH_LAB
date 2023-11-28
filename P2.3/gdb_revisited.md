# GDB OC Revisited

The goal here to revisit using GDB over UART as writing kdb modules to dump linux structs is silly when gdb can do it. Before reading this, make sure to check out the following for context:

* [GDB Cheat Sheet 1.0](https://github.com/tanner-johnson2718/MEME_OS_3/tree/main/Appendix/GDB)
* [Init RPI and Script Set up](../P1.2/README.md)
* [KDB](../P2.2/README.md#setting-up-the-debug-environment)
* [KGDBOC Doc](https://docs.kernel.org/dev-tools/kgdb.html)

# Cheat Sheet 2.0

[reference](https://darkdust.net/files/GDB%20Cheat%20Sheet.pdf)

| Command | Description | Comment |
| --- | --- | --- |
| `starti` | Start executing at very first instruction | Usually Dynamic Linker _start function |
| `b <addr/symbol>` | Add break point at address or symbol | - |
| `maint info breakpoints` | See all break points | - |
| `delete <i>` | Delete Breakpoint of given index | - |
| `ni` | Next instruction, stepping over function calls | - |
| `si` | Next instruction, stepping INTO function calls | - |
| `x/<N><f><u>` | N = Num units, f format i.e. x for hex, s for string, etc, u = unit. u almost always is b for bytes. | - |
| `info inferiors` | Get PID | - | 
| `info proc mappings` | See Process Memory Mappings | - |
| `lay next` | Cycle default Layouts | - |
| `tui disable` | Go back to just the gdb console | - |
| `info files` | Section Address Mappings | Good for finding GOT, PLT, etc in process memory map |
| `info reg` | Print registers | - |
| `p $<reg>` | Print a specific register | Pretty output with symbol resoltion. Good for seeing stack pointers in particular |
| `info address <symbol>` | Print the address of a symbol | - |
| `disas <none/symbol/addr>` | Print disassembly of passed symbol or address | - |
| `info variables` | Prints all local and global vars | DONT DO, huge list |
| `info local` | See local variables | - |
| `info args` | See function input args | - |

# Quirks of GDBOC and init setup

* Using the image as is, add `kgdboc=ttyAMA0 kgdbwait` to the cmdline.txt in the boot partition
* use `connect_gdb.sh` to connect the gdb console to the remote target
* Add initial breakpoints
    * You will loose the ability to halt the kernel unless you set a breakpoint that triggers
* DO NOT step
* 