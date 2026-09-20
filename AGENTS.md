# Repository Guidelines

## Project Structure & Module Organization

This repository documents a personal 6502 breadboard computer build. Target final state: part 7 of Ben Eater's 6502 video series. Preserve the learning trail by explaining low-level behavior, wiring decisions, and debugging notes, not just final results.

- `code/` contains the staged build code, split into `machine_code/` (hand-written opcodes and ROM images), `assembly/` (6502 assembly source), and `debug/` (Arduino monitor sketches).
- `docs/` contains datasheets for the CPU, VIA, EEPROM, RAM, LCD, and support chips.
- `notes/` contains architecture notes, `project_goals`, learning notes, and progress logs. Update these when hardware behavior or understanding changes.
- `Imgs/` contains build photos and videos. Add progress evidence when it clarifies wiring, bugs, or milestones.

## Build, Test, and Development Commands

There is no project-wide build system. Use the relevant tool for the file being changed.

- `python3 code/machine_code/dancing_led_assembly.py` regenerates `code/machine_code/led_test_rom.bin`. Check the output filename before committing binaries.
- `vasm6502_oldstyle -Fbin -dotdir code/assembly/via_led_rotate.s -o code/assembly/via_led_rotate.bin` assembles a 6502 program when the Ben Eater toolchain is installed.
- Open `code/debug/address_bus_monitor.ino` in the Arduino IDE, or upload with `arduino-cli`, to monitor the address and data buses.

## Coding Style & Naming Conventions

Match the existing examples. Use two-space indentation in Python, Arduino, and assembly. Keep 6502 labels lowercase and descriptive. Use uppercase names for registers and bit masks, such as `PORTB`, `DDRA`, `RS`, and `E`. Prefer descriptive code filenames, such as `hello_world_short_version.s`, place each file in the matching `code/` subfolder, and document the source/video stage in `code/README.md`.

## Testing Guidelines

No automated test framework is configured. Validate assembly by rebuilding the binary and checking reset vectors, memory addresses, and expected I/O writes. Validate Arduino sketches on the target board and record serial output or observations in `notes/progress_logs.md`. For hardware changes, compare behavior against the relevant Ben Eater stage and add useful photos or videos in `Imgs/`.

## Commit & Pull Request Guidelines

Recent commits use short imperative subjects, for example `Add build images` and `Organize notes and add 6502 datasheets`. Keep the first line concise. Pull requests should explain the change, list commands or manual checks, link related notes or issues, and include screenshots, serial logs, photos, or videos when behavior changed.

## Agent-Specific Instructions

Before editing, check for uncommitted work and avoid unrelated notes, code, or media. Do not overwrite binaries or photos unless required. Keep wiring and documentation useful, but do not over-polish at the expense of progress toward part 7 or understanding the system.
