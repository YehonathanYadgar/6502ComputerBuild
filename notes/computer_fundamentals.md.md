# Basics of how computers work

## Address Bus:

The CPU uses the address bus to specify which memory cell he wants to read or write to. it does that by outputting the cell location it wants to read or write to. in binary through its I/O pins.

## Read / write signal:

A pin in the CPU that indicates if it wants to read or write data through the data bus.

## Data Bus:

After the CPU the address bus and read or write signals did their thing the data bus is used to write or read the data through its I/O pins.

## The CPU Loops repeatedly in a 3 step cycle:

1. Places the address it wants to access on the address bus.
2. Uses the read/write signal to indicate whether it wants to read or write.
3. Reads data from, or writes data to, the data bus.

## Clock

Sets the speed of the cpu, and  separates the computer’s work into small steps. On one clock cycle, the CPU may put an address on the address bus. Then the memory or I/O chip has a little time to respond. On another cycle, the CPU reads or writes the data.

### Instruction Cycle vs Bus Cycle

One assembly instruction usually takes several bus cycles. For example, the CPU first reads the instruction byte from memory, then may read extra bytes such as an address, and only then does the actual read or write. So "fetch, decode, execute" is the instruction-level view, while address/data/read-write activity is the bus-level view.

## Program Counter

The **program counter** stores the address of the next instruction byte the CPU should read. It normally increases as the CPU reads the program.

## Registers

Registers are tiny storage locations inside the CPU. The CPU uses them to hold values it is currently working with, addresses, counters, and status information.

## The CPU stack

The stack is a memory area of the RAM used to store temporary data, in my build specifically return addresses for subroutines.

The stack pointer (SP) is a CPU register that decrements by one whenever a byte is pushed to the stack.

## Sub routine

A subroutine is a reusable block of code that performs a specific task. its often used for replacing a series of commands that are redundant in a code base. Whenever a subroutine is called after it finished  running the program continues from its return address.

### JSR

Before Jumping To a subroutine In order to save the return address, the CPU saves the first byte of the return address in the stack in the Current value of the SP Register. and then the next part in SP index - 1 (Because SP automatically decrements once a new byte is pushed to the stack).

### RTS

When RTS is called the CPU increments SP by one and reads the little endian byte of the return address.  and then increments by one again and reads the big endian byte. combines them and adds one ( Because`JSR` saves an address **one byte before where execution should continue**, so `RTS` adds 1 to get the correct return address. )

## Chip Selection

Different chips are assigned different addresses or address ranges.

Address decoding logic checks the CPU's address bus and activates only the chip that matches the current address.

This prevents multiple chips from responding at the same time and ensures that only the intended chip reads or writes data.

For example, if a display interface were always active, it might treat unrelated CPU writes on the data bus as display data and show incorrect output.

## EEPROM Chip (ROM):

* Gets an Input from the cpu's address bus.
* Looks up the stores data at that address.
* Outputs that data through the data bus.

## Interface chip

Can consistently output or listen for an input to or from an external device.
allows the CPU to read inputs from external devices and control outputs such as LEDs or an LCD. Its ports can be configured as inputs or outputs through internal registers.(To add an explanation under this img)

![[Pasted image 20260803193755.png]]

## Latch

A **latch** stores the value written by the CPU and keeps outputting it until the CPU writes a new value.
