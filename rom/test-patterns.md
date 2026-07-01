# ROM Test Patterns

## NOP image

`make_rom.py` generates a 32 KiB image filled with the 6502 `NOP` opcode
(`$EA`). This is useful for checking sequential address-bus activity while the
processor runs.

The generated image is only a wiring diagnostic. It does not initialize the
reset vector or implement application firmware.
