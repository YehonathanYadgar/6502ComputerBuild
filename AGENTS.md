# Repository Guidelines

## Project Structure & Module Organization

This repository documents a personal 6502 breadboard computer build. Target final state: part 7 of Ben Eater's 6502 video series. Preserve the learning trail by explaining low-level behavior, wiring decisions, and debugging notes, not just final results.

- `code/` contains staged 6502 assembly examples, Arduino monitor sketches, ROM-generation scripts, and ROM binaries.
- `docs/` contains datasheets for the CPU, VIA, EEPROM, RAM, LCD, and support chips.
- `notes/` contains architecture notes, `project_goals`, learning notes, and progress logs. Update these when hardware behavior or understanding changes.
- `Imgs/` contains build photos and videos. Add progress evidence when it clarifies wiring, bugs, or milestones.

## Build, Test, and Development Commands

There is no project-wide build system. Use the relevant tool for the file being changed.

- `cd code && python3 rom1.py` regenerates the ROM image. Check the output filename before committing binaries.
- `vasm6502_oldstyle -Fbin -dotdir code/program1.s -o code/program1.bin` assembles a 6502 program when the Ben Eater toolchain is installed.
- Open `code/monitor1.ino` in the Arduino IDE, or upload with `arduino-cli`, to monitor the address and data buses.

## Coding Style & Naming Conventions

Match the existing examples. Use two-space indentation in Python, Arduino, and assembly. Keep 6502 labels lowercase and descriptive. Use uppercase names for registers and bit masks, such as `PORTB`, `DDRA`, `RS`, and `E`. For tutorial-derived files, continue the numbered pattern (`program4.s`, `monitor2.ino`) and document the source/video stage in `code/README.md`.

## Testing Guidelines

No automated test framework is configured. Validate assembly by rebuilding the binary and checking reset vectors, memory addresses, and expected I/O writes. Validate Arduino sketches on the target board and record serial output or observations in `notes/progress_logs.md`. For hardware changes, compare behavior against the relevant Ben Eater stage and add useful photos or videos in `Imgs/`.

## Commit & Pull Request Guidelines

Recent commits use short imperative subjects, for example `Add build images` and `Organize notes and add 6502 datasheets`. Keep the first line concise. Pull requests should explain the change, list commands or manual checks, link related notes or issues, and include screenshots, serial logs, photos, or videos when behavior changed.

## Agent-Specific Instructions

Before editing, check for uncommitted work and avoid unrelated notes, code, or media. Do not overwrite binaries or photos unless required. Keep wiring and documentation useful, but do not over-polish at the expense of progress toward part 7 or understanding the system.
