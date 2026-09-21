# How the 6502 works

These are my learning notes for the breadboard computer. The build uses a W65C02S, a CMOS version of the 6502.

## Address Bus

The CPU uses the address bus to specify which memory cell it wants to read or write to. It does that by outputting the cell location it wants to access, in binary, through its address pins (A0–A15). These pins are outputs only, unlike the data bus pins.

With 16 address bits, the CPU can address 65,536 byte locations (64 KB), from `$0000` to `$FFFF`. Some addresses select memory, while others select registers in an interface chip.

## Read / write signal

A pin in the CPU that indicates if it wants to read or write data through the data bus. High means read; low means write.

## Data Bus

The data bus has eight pins, D0–D7, so it transfers one byte (8 bits) at a time. On a read, the selected chip supplies the byte and the CPU receives it. On a write, the CPU supplies the byte and the selected chip receives it.

## The CPU loops repeatedly in a cycle

1. The CPU puts the address on the address bus and sets the read/write signal.
2. The data is transferred on the data bus.

## Reset vector

During the reset sequence, the CPU reads the two bytes at `$FFFC` and `$FFFD` and loads the program counter from them. `$FFFC` holds the low byte and `$FFFD` holds the high byte. For example, `$00` followed by `$80` tells the CPU to begin executing at `$8000`.

## Clock

The clock coordinates the CPU's steps. During normal running, one bus cycle takes one clock period. A 1 MHz clock provides one million clock cycles per second, not one million completed instructions.

### Instruction Cycle vs Bus Cycle

One assembly instruction usually takes several bus cycles. For example, the CPU first reads the instruction byte from memory, then may read extra bytes such as an address, and only then does the actual read or write. So "fetch, decode, execute" is the instruction level view, while address/data/read-write activity is the bus-level view.

## Program Counter

The program counter (PC) is a 16-bit register that tracks the CPU's position in the program. It advances as instruction bytes (opcodes and operands) are fetched. Reading a variable from RAM does not move PC to that variable's address.

PC is loaded from the reset vector during reset. Jumps, taken branches, `JSR`, and `RTS` change where execution continues.

## Registers

Registers are tiny storage locations inside the CPU. The CPU uses them to hold values it is currently working with, addresses, counters, and status information.

The 6502 has:

- **A** – the accumulator
- **X** and **Y** – the index registers
- **SP** – the stack pointer
- **PC** – the program counter
- **P** – the status register

### ALU and status flags

The arithmetic and logic unit (ALU) performs operations such as addition, subtraction, AND, and OR. Instructions tell the CPU which operation to perform and where to put the result.

Flags in P record information about results. For example, Z indicates a zero result, N reflects bit 7 of a result, C holds carry information, and V indicates signed arithmetic overflow. Each instruction defines which flags it changes; some leave them alone. Conditional branches test flags to decide whether to jump. See the [W65C02S datasheet](https://www.westerndesigncenter.com/wdc/documentation/w65c02s.pdf) for the instruction details.

## The CPU stack

The stack is a memory area of the RAM used to store temporary data: return addresses for subroutines, and also the status register and PC when an interrupt or `BRK` happens. `PHA` and `PHP` let you push values manually.

The stack pointer (SP) is a CPU register that decrements by one whenever a byte is pushed to the stack.

Two important details:

- SP is only 8 bits. The actual address it points to is `$0100 + SP`. The stack is hardwired to page 1, `$0100`–`$01FF`, so it is 256 bytes and it wraps around instead of overflowing into page 0.
- SP points at the next free slot. The CPU writes the byte to `$0100 + SP` first, and only then decrements.

The reset does not initialize SP to anything useful, which is why programs normally start with `LDX #$FF` and `TXS`.

## Subroutine

A subroutine is a reusable block of code that performs a specific task. It's often used to replace a series of commands that are redundant in a code base. After a subroutine is executed, the program continues from the subroutine's return address which is saved on the stack.

### JSR

Before jumping to a subroutine, the CPU saves the return address on the stack. It pushes the **high byte first**, to `$0100 + SP`, then decrements SP, then pushes the **low byte**, then decrements again.

Because SP counts downwards, the low byte normally ends up at the lower address (except when SP wraps around). `RTS` retrieves the bytes correctly because it reverses the push order: low byte first, then high byte.

The address that gets pushed is the address of the last byte of the `JSR` instruction, which is one byte before where execution should actually continue.

### RTS

When `RTS` is called, the CPU increments SP by one and reads the **low byte** of the return address. Then it increments by one again and reads the **high byte**. It combines them into a 16-bit address and adds one, because `JSR` saved an address one byte before where execution should continue.

Note: "little endian" and "big endian" are not names for bytes. They describe the convention of which byte is stored at the lower address. The bytes themselves are just the low byte and the high byte.

## Chip Selection

Different chips are assigned different addresses or address ranges.

Address decoding logic checks the CPU's address bus and activates only the chip that matches the current address.

This prevents multiple chips from responding at the same time and ensures that only the intended chip reads or writes data.

The VIA uses **memory-mapped I/O**: ordinary CPU read/write instructions access its registers at assigned addresses. In my programs, `$6000` is `PORTB` and `$6002` is `DDRB`. Writing to these addresses controls the VIA instead of storing an ordinary variable in RAM.

For example, if a display interface were always active, it might treat unrelated CPU writes on the data bus as display data and show incorrect output.

### Intended decoding in my build — wiring still to verify

The intended decoding follows the simple Ben Eater design, using a quad-NAND chip (four NAND gates in one package) and the top address lines (A15, A14, A13). The ROM occupies the top half of the map, where A15 is high. RAM and the VIA occupy regions in the bottom half.

Two different ideas matter here:

- **Mapped capacity:** giving a 32 KB RAM chip a 16 KB address region makes only 16 KB available through that region. That alone is not mirroring.
- **Mirroring:** multiple CPU addresses select the same physical byte or register because some address bits are ignored. The VIA has 16 registers selected by A0–A3. If its selected window is larger than 16 bytes and the remaining bits do not distinguish registers, those registers repeat across the window.

For example, if both `$6000` and `$6010` select the VIA and A4 is ignored, both access `PORTB`. This is a prediction to check against my wiring, not a recorded hardware test.

(Check the exact address lines against my own wiring before writing the final version of this section.)

## EEPROM Chip (ROM)

The EEPROM is an Electrically Erasable Programmable Read Only Memory. It works by:

- Getting an input from the CPU's address bus.
- Looking up the stored data at that address.
- Outputting that data through the data bus.

It also has a chip-enable and an output-enable pin, so it only drives the data bus when it is actually selected.

An important correction to what I wrote before: an EEPROM like the 28C256 **can** be written in circuit, byte by byte, by pulling its write-enable (WE) pin low. That is the whole point of "electrically erasable", and it's what separates EEPROM from EPROM (erased with UV light) and mask ROM. In my build WE is tied high and the chip is mapped so the CPU only ever reads from it, so I program it with a separate EEPROM programmer. That is a choice in the design, not a limitation of the chip.

The EEPROM's access time is one limit on how fast the computer can be clocked. CPU timing requirements, address-decoding delays, other chips, and the quality of the wiring also matter. The data must reach the CPU in time for it to read it reliably.

## Interface chip

The 65C22 VIA lets the CPU read inputs from external devices and control outputs such as LEDs or an LCD.

It does more than just input and output:

- Two ports, A and B. Direction is set **per pin** through the DDRA and DDRB registers, not per whole port. So PB0–PB3 can be outputs while PB4–PB7 are inputs.
- Two 16-bit timers.
- A shift register.
- Handshake lines (CA1, CA2, CB1, CB2).
- It can assert IRQ to interrupt the CPU.

## Latch

A **latch** stores a value. In the VIA's normal output mode, the output register holds the byte written by the CPU, so the output pins can keep their values while the CPU uses the bus for something else.

## Worked example: from ROM bytes to a VIA output

Assume `DDRB` at `$6002` has already been set to `$FF`, making all eight Port B pins outputs, and the VIA is in normal output mode. This matches the setup used in my LED programs. The [W65C22 datasheet](https://www.westerndesigncenter.com/wdc/documentation/w65c22.pdf) describes the port and direction registers.

Suppose these instructions start at `$8000` in ROM:

```asm
  lda #$01
  sta $6000
```

The assembler encodes them as five bytes:

| CPU address | Byte | Meaning |
| --- | --- | --- |
| `$8000` | `$A9` | Opcode for `LDA` with an immediate value |
| `$8001` | `$01` | Value to load into A |
| `$8002` | `$8D` | Opcode for `STA` with an absolute address |
| `$8003` | `$00` | Low byte of the destination address |
| `$8004` | `$60` | High byte of the destination address |

The CPU reads `$A9`, decodes it, and reads the following `$01` into A. It then reads `$8D` and the two address bytes, which identify `$6000` as the destination.

For the write, the CPU puts `$6000` on the address bus, sets read/write low, and puts `$01` on the data bus. The decoding selects the VIA, which stores the byte in its Port B output register. With the setup above, PB0 goes high and PB1–PB7 go low. Whether an LED lights depends on how it is connected.

PC now points to `$8005`, the next instruction byte. It never jumped to `$6000`; that was the destination of a data write. The VIA keeps the output value while the CPU continues fetching instructions.
