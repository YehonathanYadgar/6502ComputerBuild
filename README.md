# 6502 Breadboard Computer

Build notes, firmware, diagnostics, and reference material for a breadboard-based
6502 computer.

## Repository layout

- `images/` — project photographs and captured analyzer output
- `docs/` — build, wiring, memory-map, debugging, and bill-of-materials notes
- `rom/` — ROM builder, generated image, and test-pattern documentation
- `arduino-monitor/` — Arduino bus-monitor firmware
- `schematics/` — exported circuit schematic

## Status

This repository currently contains the initial project structure. Files marked
as placeholders should be replaced with measurements and artifacts from the
physical build.

## Build the starter ROM

```sh
python3 rom/make_rom.py
```

The command writes a 32 KiB ROM image to `rom/rom.bin`.
