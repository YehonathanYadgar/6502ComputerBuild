# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this repository is

A personal Ben Eater-style 6502 breadboard computer build, documented as it progresses toward the machine shown through **part 7** of the video series. The real artifact is hardware on a breadboard; this repo holds the code that runs on it, the datasheets it was wired from, and the notes that record what is understood so far.

Two consequences that shape almost every task here:

- **Nothing in this repo can be verified by running it.** Assembly targets a CPU that is not this machine; the `.ino` sketches only mean something attached to the breadboard. Verification is reading the code against the datasheets in `docs/` and against `notes/low-level-architecture.md`, then testing on hardware.
- **The notes are a deliverable, not scaffolding.** Per `notes/project_goals.md`, the point is low-level understanding, not working code. Explain *why* a register write or wiring choice works, and update the notes when hardware behavior or understanding changes — don't just fix the code and move on.

`AGENTS.md` holds the repo's own contributor guidelines (style, commit/PR conventions); it and this file should agree.

## Commands

There is no project-wide build system, no test framework, and no linter. Use the tool that matches the file.

```bash
# Regenerate the hand-assembled ROM image (writes led_test_rom.bin alongside it, 32768 bytes)
python3 code/machine_code/dancing_led_assembly.py

# Assemble a 6502 source file (Ben Eater's vasm build; NOT currently installed on this machine)
vasm6502_oldstyle -Fbin -dotdir code/assembly/via_led_rotate.s -o code/assembly/via_led_rotate.bin
```

Arduino sketches are opened in the Arduino IDE and flashed to an Arduino Mega (`address_bus_monitor.ino` uses pins 22–53, so it requires a Mega). `arduino-cli` is not installed either — do not assume you can build or upload from the shell.

## The ROM image layout

Every program in this build is a **32 KB image mapped at `$8000`–`$FFFF`**, so `file offset = address - $8000`. Two invariants follow, and breaking either produces a machine that does nothing at all:

1. Code starts with `.org $8000` under a `reset:` label.
2. The image ends with `.org $fffc` / `.word reset`, so the CPU's reset vector at `$FFFC`/`$FFFD` lands at file offset `$7FFC`.

`dancing_led_assembly.py` does this by hand — it pads with `$EA` (`NOP`) and pokes `START_ADDRESS` into `RESET_VECTOR_OFFSET = 0x7FFC` — which is worth reading once, because it makes the vector mechanics concrete before `vasm` hides them behind `.org`.

## Hardware architecture

W65C02S CPU · AT28C256 EEPROM · HM62256 SRAM · W65C22 VIA · HD44780 LCD · 74HC00 for address decoding. Datasheets for all of these are in `docs/`.

| Range | Device | Notes |
| --- | --- | --- |
| `$0000`–`$3FFF` | RAM | Zero page `$0000`–`$00FF`, stack `$0100`–`$01FF` |
| `$6000`–`$6003` | VIA | `PORTB`, `PORTA`, `DDRB`, `DDRA` |
| `$8000`–`$FFFF` | EEPROM | Program code and reset vector |

**Address decoding is deliberately incomplete** — one 74HC00 looking at the top address lines, ROM selected whenever A15 is high. Mirroring is expected, not a bug: only 16K of the 32K RAM is reachable, and the VIA's 16 registers repeat across its whole window. When a program writes to an unexpected address and something responds, suspect mirroring before suspecting wiring. The exact chip-select equation has not been written down yet (open TODO in `notes/low-level-architecture.md`).

LCD control lines live on `PORTA`: `E = %10000000`, `RW = %01000000`, `RS = %00100000`. `PORTB` carries the data byte; `RS` decides whether it's an instruction or a character. Writing a byte means: put it on `PORTB`, set the control bits, pulse `E` high then low.

**RAM is the current focus and is not yet trusted.** Anything using `jsr`, `rts`, `pha`, `pla`, or `txs` depends on a working stack — so `hello_world_short_version.s` needs RAM while `hello_world_long_version.s` deliberately does not. That is why the long inline version still exists; don't "simplify" it into the subroutine version.

`ram_debug_monitor.ino` is the tool for this: the Arduino drives PHI2 manually (`p` = one pulse, `t` = ten, `rc` = run, `x` = stop, `s` = status) and prints the data bus alongside `/CE`, RAM `/CS` `/WE` `/OE`, `A15`, and CPU R/W. Its `RW_WE_MATCH` column is the point — it should always read `YES`.

## Code

`code/` is split by the form the code takes, which tracks the build's progression:

- `machine_code/` - `dancing_led_assembly.py` and the `led_test_rom.bin` it emits. Raw opcodes, before the assembler exists.
- `assembly/` - `.s` sources assembled with `vasm`. `program1.s` (literal addresses) then `via_led_rotate.s` (named constants) are the same program; the two `hello_world_*` files are the no-RAM and stack-based LCD versions.
- `debug/` - the Arduino sketches. Not part of the 6502 program; they observe it.

The `code/` folder contains the machine-code, assembly, and debugging files. Put new files in the subfolder matching their form.

Two stale references survive in the docs and point at files that were deleted, not renamed: `notes/To_finish.md` (linked from `README.md`) and `notes/progress_logs.md` (cited in `AGENTS.md`). Either write those notes or drop the links. Also note `notes/computer_fundamentals.md.md` really does carry a doubled extension.

## Working in this repo

- The working tree carries a large uncommitted rename-and-rewrite in progress. Check `git status` before editing and stay out of unrelated staged work.
- Don't regenerate or overwrite `led_test_rom.bin`, the datasheets in `docs/`, or the photos and videos in `Imgs/` unless the task needs it — the media is progress evidence tied to specific build stages.
- Two-space indentation across Python, Arduino, and assembly. 6502 labels lowercase and descriptive; registers and bit masks uppercase (`PORTB`, `DDRA`, `RS`, `E`).
- Comments in the `.s` files carry the teaching load — they name the stage, the address being hit, and the reason for the write. Match that density rather than trimming it.
