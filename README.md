# 6502 Computer Build

![Finished 6502 breadboard computer](Imgs/finished-computer.jpeg)

This repository documents my personal Ben Eater-style 6502 breadboard computer build. The build is finished through Part 7 of the 6502 video series, with code, datasheets, notes, and progress media documenting the journey.

## Current Status

- Status: **Finished**.
- Completed: Ben Eater 6502 computer through **Part 7**.
- EEPROM, RAM, W65C22 VIA, and HD44780 LCD output are ready.

## Hardware

- W65C02S CPU
- AT28C256 EEPROM
- HM62256 SRAM
- W65C22 VIA
- HD44780-compatible LCD
- 74HC00 NAND gates for address decoding

## Repository Layout

- `code/` - build code in three groups: `machine_code/` (hand-written opcodes and ROM images), `assembly/` (6502 assembly source), and `debug/` (Arduino monitor sketches).
- `docs/` - datasheets for the CPU, VIA, EEPROM, RAM, LCD, and support chips.
- `notes/` - project goals, architecture notes, computer fundamentals, and remaining work.
- `Imgs/` - build photos and progress videos.

## Build Photos

Earlier stages of the build, leading up to the finished computer shown above.

![Early breadboard setup](Imgs/img1.jpeg)

![Initial CPU wiring](Imgs/img2.jpeg)

![Expanded breadboard wiring](Imgs/img3.jpeg)

![LED output stage](Imgs/img4.jpeg)

![LCD wiring stage](Imgs/img5.jpeg)

The unedited photos are preserved in [`Imgs/originals/`](Imgs/originals/).

## Useful Commands

Regenerate the early ROM image:

```bash
python3 code/machine_code/dancing_led_assembly.py
```

Assemble a 6502 program with the Ben Eater toolchain:

```bash
vasm6502_oldstyle -Fbin -dotdir code/assembly/via_led_rotate.s -o code/assembly/via_led_rotate.bin
```

Open `code/debug/address_bus_monitor.ino` in the Arduino IDE, or upload it with `arduino-cli`, to monitor the address and data buses. Use `code/debug/ram_debug_monitor.ino` when checking RAM and EEPROM control signals.

## Documentation

- [Code stages](code/README.md)
- [Project goals](notes/project_goals.md)
- [Low-level architecture](notes/low-level-architecture.md)
- [Computer fundamentals](notes/computer_fundamentals.md.md)
- [Remaining work](notes/To_finish.md)

## Validation

There is no automated test suite. Changes are checked by rebuilding ROM binaries, verifying reset vectors and memory addresses, and testing behavior on the breadboard with the Arduino monitor or direct hardware observation.
