## How to 6502 works

## Address Bus

The CPU uses the address bus to specify which memory cell it wants to read or write to. It does that by outputting the cell location it wants to access, in binary, through its address pins (A0–A15). These pins are outputs only, unlike the data bus pins.

## Read / write signal

A pin in the CPU that indicates if it wants to read or write data through the data bus.

## Data Bus

The data bus is used to write or read the data through its I/O pins. 

## The CPU loops repeatedly in a cycle

1. The CPU puts the address on the address bus and sets the read/write signal.
2. The data is transferred on the data bus.
## Reset vector

When the CPU It reads the two bytes at `$FFFC` and `$FFFD` and loads the program counter from them. 
## Clock

The CPU loop mentioned above happens x times per second, where x is the clock speed. 

### Instruction Cycle vs Bus Cycle

One assembly instruction usually takes several bus cycles. For example, the CPU first reads the instruction byte from memory, then may read extra bytes such as an address, and only then does the actual read or write. So "fetch, decode, execute" is the instruction level view, while address/data/read-write activity is the bus-level view.

## Program Counter

The program counter stores the address of the next memory cell the CPU should read. It normally increases as the CPU reads the program. It is loaded from the reset vector at startup, and jumps, branches, `JSR`, `RTS`.

## Registers

Registers are tiny storage locations inside the CPU. The CPU uses them to hold values it is currently working with, addresses, counters, and status information.

The 6502 has:

- **A** – the accumulator
- **X** and **Y** – the index registers
- **SP** – the stack pointer
- **PC** – the program counter
- **P** – the status register

## The CPU stack

The stack is a memory area of the RAM used to store temporary data: return addresses for subroutines, and also the status register and PC when an interrupt or `BRK` happens. `PHA` and `PHP` let you push values manually.

The stack pointer (SP) is a CPU register that decrements by one whenever a byte is pushed to the stack.

Two important details:

- SP is only 8 bits. The actual address it points to is `$0100 + SP`. The stack is hardwired to page 1, `$0100`–`$01FF`, so it is 256 bytes and it wraps around instead of overflowing into page 0.
- SP points at the next free slot. The CPU writes the byte to `$0100 + SP` first, and only then decrements.

The reset does not initialize SP to anything useful, which is why programs normally start with `LDX #$FF` and `TXS`.

## Sub routine

A subroutine is a reusable block of code that performs a specific task. It's often used to replace a series of commands that are redundant in a code base. After a subroutine is executed, the program continues from the subroutine's return address which is saved on the stack.

### JSR

Before jumping to a subroutine, the CPU saves the return address on the stack. It pushes the **high byte first**, to `$0100 + SP`, then decrements SP, then pushes the **low byte**, then decrements again.

Because SP counts downwards, the low byte ends up at the lower address. That is exactly the little-endian layout, and it's what makes `RTS` able to pull the bytes back in the right order.

The address that gets pushed is the address of the last byte of the `JSR` instruction, which is one byte before where execution should actually continue.

### RTS

When `RTS` is called, the CPU increments SP by one and reads the **low byte** of the return address. Then it increments by one again and reads the **high byte**. It combines them into a 16-bit address and adds one, because `JSR` saved an address one byte before where execution should continue.

Note: "little endian" and "big endian" are not names for bytes. They describe the convention of which byte is stored at the lower address. The bytes themselves are just the low byte and the high byte.

## Chip Selection

Different chips are assigned different addresses or address ranges.

Address decoding logic checks the CPU's address bus and activates only the chip that matches the current address.

This prevents multiple chips from responding at the same time and ensures that only the intended chip reads or writes data.

For example, if a display interface were always active, it might treat unrelated CPU writes on the data bus as display data and show incorrect output.

### What my build actually does

The decoding in this build is deliberately simple: one quad-NAND gate looking at the top address lines (A15, A14, A13). The ROM is selected when A15 is high, so it takes the whole top half of the map. The RAM and the VIA share the bottom half.

This is **incomplete decoding**, which means addresses get mirrored. The results are real and you can see them:

- The RAM chip is 32K, but only 16K of it is reachable, because not all of its address lines are decoded.
- The VIA only has 16 registers, but they repeat over and over across its whole address window.

You can test the mirroring by writing to two different addresses and watching them hit the same register.

(Check the exact address lines against my own wiring before writing the final version of this section.)

## EEPROM Chip (ROM)

The EEPROM is an Electrically Erasable Programmable Read Only Memory. It works by:

- Getting an input from the CPU's address bus.
- Looking up the stored data at that address.
- Outputting that data through the data bus.

It also has a chip-enable and an output-enable pin, so it only drives the data bus when it is actually selected.

An important correction to what I wrote before: an EEPROM like the 28C256 **can** be written in circuit, byte by byte, by pulling its write-enable (WE) pin low. That is the whole point of "electrically erasable", and it's what separates EEPROM from EPROM (erased with UV light) and mask ROM. In my build WE is tied high and the chip is mapped so the CPU only ever reads from it, so I program it with a separate EEPROM programmer. That is a choice in the design, not a limitation of the chip.

The EEPROM's access time is also what limits how fast the whole computer can be clocked.

## Interface chip

The 65C22 VIA lets the CPU read inputs from external devices and control outputs such as LEDs or an LCD.

It does more than just input and output:

- Two ports, A and B. Direction is set **per pin** through the DDRA and DDRB registers, not per whole port. So PB0–PB3 can be outputs while PB4–PB7 are inputs.
- Two 16-bit timers.
- A shift register.
- Handshake lines (CA1, CA2, CB1, CB2).
- It can assert IRQ to interrupt the CPU.

(To add an explanation under this img)

## Latch

A **latch** stores the value written by the CPU and keeps outputting it until the CPU writes a new value.