# Low-Level Architecture

This file describes this specific 6502 computer, not computer concepts in general. Use it when debugging wiring, address decoding, ROM code, RAM behavior, or LCD output.

## Current Build Target

The target system is the Ben Eater 6502 computer through part 7: W65C02S CPU, AT28C256 EEPROM, HM62256 RAM, W65C22 VIA, HD44780 LCD, and 74HC00 NAND gates for address decoding.

Current status: EEPROM, VIA, and LCD have worked before. RAM is being connected/debugged. Update this section whenever the verified hardware state changes.

## Main Buses And Shared Signals

The CPU controls the address bus, data bus, and read/write signal.

- Address bus: `A0`-`A15`, output from CPU.
- Data bus: `D0`-`D7`, bidirectional.
- `RWB`: high means read, low means write.
- Clock: CPU advances on clock cycles.
- Reset: CPU starts by reading the reset vector from `$FFFC` and `$FFFD`.

Only one memory or I/O chip should drive the data bus during a read. If two chips output at the same time, the bus can show wrong values.

## Address Map

Target address map:


| Address range   | Device     | Notes                                       |
| --------------- | ---------- | ------------------------------------------- |
| `$0000`-`$3FFF` | RAM        | Includes zero page and stack page.          |
| `$6000`-`$6003` | W65C22 VIA | Registers used by current LCD/LED programs. |
| `$8000`-`$FFFF` | EEPROM     | Program code and reset vector.              |


TODO: verify whether unused addresses mirror devices because of incomplete address decoding.

## Boot Sequence

After reset, the CPU reads two bytes:

- `$FFFC`: low byte of reset address.
- `$FFFD`: high byte of reset address.

In the current programs, the reset vector points to `$8000`, so execution starts in EEPROM at the label `reset`.

Example from `code/program3.s`:

```asm
.org $8000
reset:
  ldx #$ff
  txs

.org $fffc
.word reset
.word $0000
```



## EEPROM

The AT28C256 stores the program. The CPU sees it in the upper half of the address space, including `$8000` and `$FFFC`.

Expected behavior:

- When the CPU reads from EEPROM range, EEPROM outputs one byte on `D0`-`D7`.
- When the CPU reads `$FFFC/$FFFD`, EEPROM provides the reset vector.
- EEPROM should not drive the data bus when RAM or VIA is selected.

TODO: write the exact chip select equation from the breadboard wiring.

## RAM

The HM62256 is used for writable memory. It must cover at least:

- Zero page: `$0000`-`$00FF`.
- Stack: `$0100`-`$01FF`.

Part 5/stack code needs RAM because `jsr`, `rts`, `pha`, `pla`, and `txs` use the stack.

Expected behavior:

- On CPU write, RAM stores the byte on the data bus.
- On CPU read, RAM outputs the stored byte.
- RAM must not output when EEPROM or VIA is selected.

TODO: verify RAM address lines, data lines, `WE`, `OE`, and `CS` wiring.

## VIA And LCD

The W65C22 VIA is memory-mapped at `$6000`-`$6003` in the current code:


| Address | Name    | Purpose                        |
| ------- | ------- | ------------------------------ |
| `$6000` | `PORTB` | LCD data lines or LEDs.        |
| `$6001` | `PORTA` | LCD control lines.             |
| `$6002` | `DDRB`  | Direction register for port B. |
| `$6003` | `DDRA`  | Direction register for port A. |


LCD control bits in `PORTA`:


| Bit mask    | Name | Meaning                      |
| ----------- | ---- | ---------------------------- |
| `%10000000` | `E`  | LCD enable pulse.            |
| `%01000000` | `RW` | LCD read/write select.       |
| `%00100000` | `RS` | LCD instruction/data select. |


`PORTB` carries the 8-bit LCD instruction or character byte. `PORTA` controls whether that byte is treated as an instruction or text data.

## Debug Checklist

When the system fails:

1. Check reset wiring and confirm the CPU reads `$FFFC/$FFFD`.
2. Check clock behavior and button debounce.
3. Check that only the selected chip drives the data bus.
4. Check address decoding for EEPROM, RAM, and VIA.
5. Check VIA direction registers before expecting output.
6. Check LCD `RS`, `RW`, and `E` timing.



## Open Questions

- What is the exact current RAM chip select logic?
- Which address ranges mirror RAM, VIA, or EEPROM?
- Is the current RAM bug caused by address wiring, data wiring, or chip select logic?
- Which photos or diagrams should be linked here to document the final wiring?

