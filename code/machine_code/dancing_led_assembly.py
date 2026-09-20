"""Build the hand-assembled ROM image for the first machine-code stage.

Part 2 of the build, before the assembler is introduced: the LED program is
written out as raw opcodes rather than assembled from source. The image is
padded to 32K with NOP ($EA) and mapped at $8000-$FFFF, so the reset vector
the CPU reads from $FFFC/$FFFD lands at file offset $7FFC.

Writes led_test_rom.bin next to this file. Run: python3 dancing_led_assembly.py
"""

from pathlib import Path


ROM_SIZE = 32768
RESET_VECTOR_OFFSET = 0x7FFC
START_ADDRESS = 0x8000
OUT_FILE = Path(__file__).with_name("led_test_rom.bin")


# Minimal machine-code ROM used before the assembly toolchain is introduced.
code = bytearray([
  0xA9, 0xFF,        # lda #$ff
  0x8D, 0x02, 0x60,  # sta $6002 - configure VIA PORTB as output

  0xA9, 0x55,        # lda #$55
  0x8D, 0x00, 0x60,  # sta $6000 - show first LED pattern

  0xA9, 0xAA,        # lda #$aa
  0x8D, 0x00, 0x60,  # sta $6000 - show second LED pattern

  0x4C, 0x05, 0x80,  # jmp $8005 - repeat the visible writes
])

rom = code + bytearray([0xEA] * (ROM_SIZE - len(code)))

# The CPU reads $FFFC/$FFFD after reset. In this 32K ROM image those bytes
# are at offsets $7FFC/$7FFD, and they point execution to $8000.
rom[RESET_VECTOR_OFFSET] = START_ADDRESS & 0xFF
rom[RESET_VECTOR_OFFSET + 1] = START_ADDRESS >> 8

with OUT_FILE.open("wb") as out_file:
  out_file.write(rom)

print(f"Wrote {OUT_FILE.name} ({len(rom)} bytes)")
